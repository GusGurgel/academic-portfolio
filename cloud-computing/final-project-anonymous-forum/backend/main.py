from fastapi import FastAPI, HTTPException, Depends, Form
from fastapi.middleware.cors import CORSMiddleware
from sqlalchemy.orm import Session
from typing import List, Optional
import markdown
import random
import re

from database import get_db, create_tables
from models import User, Thread, Post
from config import SUBSTANTIVOS, ADJETIVOS, PORT

app = FastAPI()

# CORS middleware
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Create tables on startup
create_tables()

def render_markdown(text: str) -> str:
    """Convert markdown to HTML"""
    return markdown.markdown(text, extensions=['nl2br'])

def check_for_image(text: str) -> bool:
    """Check if text contains image markdown syntax"""
    image_pattern = r'!\[.*?\]\(.*?\)'
    return bool(re.search(image_pattern, text))

def get_or_create_user(user_key: str, db: Session) -> User:
    """Get existing user or create new one with anonymous nickname"""
    user = db.query(User).filter(User.user_key == user_key).first()
    if not user:
        substantivo = random.choice(SUBSTANTIVOS)
        adjetivo = random.choice(ADJETIVOS)
        nickname = f"{substantivo}_{adjetivo}"
        
        # Ensure nickname is unique
        existing = db.query(User).filter(User.nickname == nickname).first()
        while existing:
            substantivo = random.choice(SUBSTANTIVOS)
            adjetivo = random.choice(ADJETIVOS)
            nickname = f"{substantivo}_{adjetivo}"
            existing = db.query(User).filter(User.nickname == nickname).first()
        
        user = User(user_key=user_key, nickname=nickname)
        db.add(user)
        db.commit()
        db.refresh(user)
    return user

@app.get("/api/threads")
def get_threads(db: Session = Depends(get_db)):
    """Get all threads ordered by last activity (bump system)"""
    threads = db.query(Thread).order_by(Thread.updated_at.desc()).all()
    
    result = []
    for thread in threads:
        post_count = db.query(Post).filter(Post.thread_id == thread.id).count()
        last_post = db.query(Post).filter(Post.thread_id == thread.id).order_by(Post.created_at.desc()).first()
        
        result.append({
            "id": thread.id,
            "title": thread.title,
            "content": thread.content,
            "content_html": thread.content_html,
            "author_nickname": thread.author.nickname,
            "created_at": thread.created_at,
            "updated_at": thread.updated_at,
            "post_count": post_count,
            "has_image": thread.has_image,
            "last_post_author": last_post.author.nickname if last_post else thread.author.nickname,
            "last_post_date": last_post.created_at if last_post else thread.created_at
        })
    
    return result

@app.get("/api/threads/{thread_id}")
def get_thread(thread_id: int, db: Session = Depends(get_db)):
    """Get specific thread with all posts"""
    thread = db.query(Thread).filter(Thread.id == thread_id).first()
    if not thread:
        raise HTTPException(status_code=404, detail="Thread not found")
    
    posts = db.query(Post).filter(Post.thread_id == thread_id).order_by(Post.created_at.asc()).all()
    
    posts_data = [{
        "id": post.id,
        "content": post.content,
        "content_html": post.content_html,
        "author_nickname": post.author.nickname,
        "created_at": post.created_at
    } for post in posts]
    
    return {
        "id": thread.id,
        "title": thread.title,
        "content": thread.content,
        "content_html": thread.content_html,
        "author_nickname": thread.author.nickname,
        "created_at": thread.created_at,
        "has_image": thread.has_image,
        "posts": posts_data
    }

@app.post("/api/threads")
def create_thread(
    title: str = Form(...),
    content: str = Form(...),
    user_key: str = Form(...),
    db: Session = Depends(get_db)
):
    """Create new thread"""
    user = get_or_create_user(user_key, db)
    
    content_html = render_markdown(content)
    has_image = check_for_image(content)
    
    thread = Thread(
        title=title,
        content=content,
        content_html=content_html,
        author_id=user.id,
        has_image=has_image
    )
    
    db.add(thread)
    db.commit()
    db.refresh(thread)
    
    return {
        "id": thread.id,
        "title": thread.title,
        "content": thread.content,
        "content_html": thread.content_html,
        "author_nickname": user.nickname,
        "created_at": thread.created_at,
        "has_image": thread.has_image
    }

@app.post("/api/threads/{thread_id}/posts")
def create_post(
    thread_id: int,
    content: str = Form(...),
    user_key: str = Form(...),
    db: Session = Depends(get_db)
):
    """Create new post in thread"""
    thread = db.query(Thread).filter(Thread.id == thread_id).first()
    if not thread:
        raise HTTPException(status_code=404, detail="Thread not found")
    
    user = get_or_create_user(user_key, db)
    content_html = render_markdown(content)
    
    post = Post(
        content=content,
        content_html=content_html,
        thread_id=thread_id,
        author_id=user.id
    )
    
    db.add(post)
    
    # Update thread's updated_at to implement bump system
    from sqlalchemy import func
    thread.updated_at = func.now()
    
    db.commit()
    db.refresh(post)
    
    return {
        "id": post.id,
        "content": post.content,
        "content_html": post.content_html,
        "author_nickname": user.nickname,
        "created_at": post.created_at
    }

@app.get("/api/user/{user_key}")
def get_user(user_key: str, db: Session = Depends(get_db)):
    """Get user info or create if doesn't exist"""
    user = get_or_create_user(user_key, db)
    return {
        "nickname": user.nickname,
        "user_key": user.user_key,
        "created_at": user.created_at
    }

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=PORT)