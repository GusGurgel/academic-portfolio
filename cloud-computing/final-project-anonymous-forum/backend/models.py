from sqlalchemy import Column, Integer, String, DateTime, Text, ForeignKey, Boolean
from sqlalchemy.orm import relationship
from sqlalchemy.sql import func
from database import Base

class User(Base):
    __tablename__ = "users"
    
    id = Column(Integer, primary_key=True, index=True)
    user_key = Column(String, unique=True, index=True)  # UUID stored in localStorage
    nickname = Column(String, index=True)
    created_at = Column(DateTime(timezone=True), server_default=func.now())
    
    threads = relationship("Thread", back_populates="author")
    posts = relationship("Post", back_populates="author")

class Thread(Base):
    __tablename__ = "threads"
    
    id = Column(Integer, primary_key=True, index=True)
    title = Column(String, index=True)
    content = Column(Text)
    content_html = Column(Text)  # Rendered markdown
    author_id = Column(Integer, ForeignKey("users.id"))
    created_at = Column(DateTime(timezone=True), server_default=func.now())
    updated_at = Column(DateTime(timezone=True), server_default=func.now(), onupdate=func.now())
    has_image = Column(Boolean, default=False)
    
    author = relationship("User", back_populates="threads")
    posts = relationship("Post", back_populates="thread", cascade="all, delete-orphan")

class Post(Base):
    __tablename__ = "posts"
    
    id = Column(Integer, primary_key=True, index=True)
    content = Column(Text)
    content_html = Column(Text)  # Rendered markdown
    thread_id = Column(Integer, ForeignKey("threads.id"))
    author_id = Column(Integer, ForeignKey("users.id"))
    created_at = Column(DateTime(timezone=True), server_default=func.now())
    
    thread = relationship("Thread", back_populates="posts")
    author = relationship("User", back_populates="posts")