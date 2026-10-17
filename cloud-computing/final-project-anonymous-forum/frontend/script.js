// Main JavaScript file for the anonymous forum

// Get or generate user key
function getUserKey() {
    let userKey = localStorage.getItem('forum_user_key');
    if (!userKey) {
        userKey = 'user_' + Math.random().toString(36).substr(2, 16) + '_' + Date.now();
        localStorage.setItem('forum_user_key', userKey);
    }
    return userKey;
}

// API call helper
async function apiCall(endpoint, options = {}) {
    const url = `${window.API_BASE_URL}${endpoint}`;
    try {
        const response = await fetch(url, {
            headers: {
                'Content-Type': 'application/json',
                ...options.headers
            },
            ...options
        });
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        return await response.json();
    } catch (error) {
        console.error('API call failed:', error);
        throw error;
    }
}

// Load user information
async function loadUserInfo() {
    try {
        const userKey = getUserKey();
        const user = await apiCall(`/user/${userKey}`);
        document.getElementById('userNickname').textContent = user.nickname;
    } catch (error) {
        console.error('Failed to load user info:', error);
        document.getElementById('userNickname').textContent = 'Anônimo';
    }
}

// Format date
function formatDate(dateString) {
    const date = new Date(dateString);
    const now = new Date();
    const diffMs = now - date;
    const diffMinutes = Math.floor(diffMs / 60000);
    const diffHours = Math.floor(diffMinutes / 60);
    const diffDays = Math.floor(diffHours / 24);
    
    if (diffMinutes < 1) return 'agora';
    if (diffMinutes < 60) return `${diffMinutes} min atrás`;
    if (diffHours < 24) return `${diffHours}h atrás`;
    if (diffDays < 7) return `${diffDays} dias atrás`;
    
    return date.toLocaleDateString('pt-BR');
}

// Extract and resize images in HTML content
function processImages(htmlContent) {
    const tempDiv = document.createElement('div');
    tempDiv.innerHTML = htmlContent;
    
    const images = tempDiv.querySelectorAll('img');
    images.forEach(img => {
        img.classList.add('thread-image');
        // Set max dimensions to maintain aspect ratio while limiting size
        img.style.maxWidth = '200px';
        img.style.maxHeight = '150px';
        img.style.objectFit = 'cover';
    });
    
    return tempDiv.innerHTML;
}

function getFirstImage(htmlContent) {
    if (!htmlContent) return null;
    
    // Cria um elemento temporário para parsear o HTML
    const tempDiv = document.createElement('div');
    tempDiv.innerHTML = htmlContent;
    
    // Busca a primeira imagem
    const firstImg = tempDiv.querySelector('img');
    
    return firstImg ? firstImg.outerHTML : null;
}

// Load threads for main page
async function loadThreads() {
    try {
        const threads = await apiCall('/threads');
        const container = document.getElementById('threadsList');
        const loading = document.getElementById('threadsLoading');
        
        if (threads.length === 0) {
            container.innerHTML = `
                <div class="empty-state">
                    <h4>Nenhum tópico ainda</h4>
                    <p>Seja o primeiro a criar um tópico!</p>
                    <a href="create-post.html" class="btn btn-primary">Criar Primeiro Tópico</a>
                </div>
            `;
        } else {
            container.innerHTML = threads.map(thread => {
                const processedContent = processImages(thread.content_html);
                const preview = thread.content.length > 200 
                    ? thread.content.substring(0, 200) + '...' 
                    : thread.content;
                
                return `
                    <div class="thread-item" onclick="window.location.href='thread.html?id=${thread.id}'">
                        <div class="d-flex justify-content-between align-items-start">
                            <div class="flex-grow-1">
                                <h5 class="thread-title mb-2">${thread.title}</h5>
                                <div class="thread-preview">${preview}</div>
                                ${thread.has_image ? `<div class="mt-2">${getFirstImage(processedContent)}</div>` : ''}
                                <div class="thread-meta mt-2">
                                    <span class="nickname-badge">${thread.author_nickname}</span>
                                    <span class="ms-2 text-white">${formatDate(thread.created_at)}</span>
                                    ${thread.post_count > 0 ? `<span class="ms-2 text-white">• ${thread.post_count} resposta${thread.post_count > 1 ? 's' : ''}</span>` : ''}
                                    ${thread.last_post_author !== thread.author_nickname ? `<span class="ms-2">• Última: ${thread.last_post_author}</span>` : ''}
                                </div>
                            </div>
                        </div>
                    </div>
                `;
            }).join('');
        }
        
        loading.style.display = 'none';
        container.style.display = 'block';
    } catch (error) {
        console.error('Failed to load threads:', error);
        document.getElementById('threadsList').innerHTML = `
            <div class="text-center p-4 text-danger">
                <p>Erro ao carregar tópicos. Tente novamente.</p>
                <button class="btn btn-outline-primary" onclick="loadThreads()">Tentar Novamente</button>
            </div>
        `;
        document.getElementById('threadsLoading').style.display = 'none';
        document.getElementById('threadsList').style.display = 'block';
    }
}

// Create new thread
async function createThread() {
    const title = document.getElementById('threadTitle').value.trim();
    const content = document.getElementById('threadContent').value.trim();
    const submitBtn = document.getElementById('submitBtn');
    const submitText = document.getElementById('submitText');
    const submitSpinner = document.getElementById('submitSpinner');
    
    if (!title || !content) {
        alert('Por favor, preencha todos os campos.');
        return;
    }
    
    submitBtn.disabled = true;
    submitText.textContent = 'Criando...';
    submitSpinner.style.display = 'inline-block';
    
    try {
        const userKey = getUserKey();
        const formData = new FormData();
        formData.append('title', title);
        formData.append('content', content);
        formData.append('user_key', userKey);
        
        const response = await fetch(`${window.API_BASE_URL}/threads`, {
            method: 'POST',
            body: formData
        });
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        const thread = await response.json();
        window.location.href = `thread.html?id=${thread.id}`;
    } catch (error) {
        console.error('Failed to create thread:', error);
        alert('Erro ao criar tópico. Tente novamente.');
    } finally {
        submitBtn.disabled = false;
        submitText.textContent = 'Criar Tópico';
        submitSpinner.style.display = 'none';
    }
}

// Load specific thread
async function loadThread(threadId) {
    try {
        const thread = await apiCall(`/threads/${threadId}`);
        
        // Update page title and thread title
        document.title = `${thread.title} - Fórum Anônimo`;
        document.getElementById('threadTitle').textContent = thread.title;
        
        // Display original thread content
        const threadContent = document.getElementById('threadContent');
        threadContent.innerHTML = `
            <div class="d-flex justify-content-between align-items-start mb-3">
                <h4 class="mb-0">${thread.title}</h4>
                <div class="text-muted small">
                    <span class="nickname-badge">${thread.author_nickname}</span>
                    <span class="ms-2 text-white">${formatDate(thread.created_at)}</span>
                </div>
            </div>
            <div class="post-content">${processImages(thread.content_html)}</div>
        `;
        
        // Display posts
        const postsContainer = document.getElementById('postsContainer');
        if (thread.posts.length === 0) {
            postsContainer.innerHTML = `
                <div class="text-center text-muted mb-4">
                    <p>Seja o primeiro a comentar neste tópico!</p>
                </div>
            `;
        } else {
            postsContainer.innerHTML = thread.posts.map(post => `
                <div class="card mb-3">
                    <div class="card-body post-item">
                        <div class="post-meta">
                            <span class="nickname-badge">${post.author_nickname}</span>
                            <span class="ms-2 text-white">${formatDate(post.created_at)}</span>
                        </div>
                        <div class="post-content">${processImages(post.content_html)}</div>
                    </div>
                </div>
            `).join('');
        }
    } catch (error) {
        console.error('Failed to load thread:', error);
        document.getElementById('threadContent').innerHTML = `
            <div class="text-center text-danger">
                <p>Erro ao carregar tópico.</p>
                <a href="index.html" class="btn btn-primary">Voltar ao Fórum</a>
            </div>
        `;
    }
}

// Reply to thread
async function replyToThread(threadId) {
    const content = document.getElementById('replyContent').value.trim();
    const replyBtn = document.getElementById('replyBtn');
    const replyText = document.getElementById('replyText');
    const replySpinner = document.getElementById('replySpinner');
    
    if (!content) {
        alert('Por favor, escreva uma resposta.');
        return;
    }
    
    replyBtn.disabled = true;
    replyText.textContent = 'Enviando...';
    replySpinner.style.display = 'inline-block';
    
    try {
        const userKey = getUserKey();
        const formData = new FormData();
        formData.append('content', content);
        formData.append('user_key', userKey);
        
        const response = await fetch(`${window.API_BASE_URL}/threads/${threadId}/posts`, {
            method: 'POST',
            body: formData
        });
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        // Clear form and reload thread
        document.getElementById('replyContent').value = '';
        document.getElementById('replyPreview').innerHTML = 'Digite algo acima para ver o preview...';
        await loadThread(threadId);
        
        // Scroll to bottom to show new post
        window.scrollTo(0, document.body.scrollHeight);
    } catch (error) {
        console.error('Failed to reply:', error);
        alert('Erro ao enviar resposta. Tente novamente.');
    } finally {
        replyBtn.disabled = false;
        replyText.textContent = 'Responder';
        replySpinner.style.display = 'none';
    }
}