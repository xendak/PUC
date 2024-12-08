document.addEventListener('DOMContentLoaded', init);

function init() {
    const state = {
        currentPage: 1,
        totalPages: 1,
        query: '',
        resultsPerPage: 35, // 7 x 5
    };

    const searchForm = document.getElementById('search-form');
    const prevPageButtons = document.querySelectorAll('#prev-page');
    const nextPageButtons = document.querySelectorAll('#next-page');

    prevPageButtons.forEach((button) => {
        button.addEventListener('click', () => handlePageBtn(state, "prev"));
    });

    nextPageButtons.forEach((button) => {
        button.addEventListener('click', () => handlePageBtn(state, "next"));
    });

    searchForm.addEventListener('submit', (event) => handleSearch(event, state));

    fetchDefaultResults(state);
}

async function fetchDefaultResults(state) {
    const response = await api.getPopularSeries(state.currentPage); 
    state.totalPages = response.total_pages;
    renderResults(response.results, state);
}

async function handleSearch(event, state) {
    event.preventDefault();
    const query = document.getElementById('search-input').value.trim();

    if (!query) {
        state.query = '';
        state.currentPage = 1;
        fetchDefaultResults(state);
        return;
    }

    state.query = query;
    state.currentPage = 1;

    const response = await api.searchSeries(query, state.currentPage);
    state.totalPages = response.total_pages;
    renderResults(response.results, state);
}

async function handlePageBtn(state, dir) {
    if (dir === "next") {
        if (state.currentPage < state.totalPages) {
            state.currentPage++;
        }
    } else {
        if (state.currentPage > 1) {
            state.currentPage--;
        }
    }

    if (state.query) {
        const response = await api.searchSeries(state.query, state.currentPage);
        renderResults(response.results, state);
    } else {
        fetchDefaultResults(state);
    }

    window.scrollTo({
        top: 0,
        behavior: 'smooth',
    });
}

function renderResults(results, state) {
    const container = document.getElementById('search-results');
    const paginationContainer = document.getElementById('pagination');
    const pageInfo = document.querySelectorAll('#page-info');

    container.innerHTML = '';

    if (!results || results.length === 0) {
        container.innerHTML = '<p>Nada foi encontrado.</p>';
        paginationContainer.style.display = 'none';
        return;
    }

    results.forEach(series => {
        const card = createCard(series);
        if (card) {
            container.appendChild(card);
        }
    });

    updatePaginationInfo(state, pageInfo);
}

function createCard(series) {
    const defaultPoster = './assets/img/default-series.png';

    const posterPath = series.poster_path ? getImageUrl(series.poster_path, 'w500') : defaultPoster;

    const card = document.createElement('div');
    card.className = 'card';
    card.innerHTML = `
        <img src="${posterPath}" 
             alt="${series.name}" 
             class="card-image">
        <button class="card-favorite-btn" id="card-favorite-btn-${series.id}">
            <svg class="card-heart-icon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 512 512">
                <path d="M47.6 300.4L228.3 469.1c7.5 7 17.4 10.9 27.7 10.9s20.2-3.9 27.7-10.9L464.4 300.4c30.4-28.3 47.6-68 47.6-109.5v-5.8c0-69.9-50.5-129.5-119.4-141C347 36.5 300.6 51.4 268 84L256 96 244 84c-32.6-32.6-79-47.5-124.6-39.9C50.5 55.6 0 115.2 0 185.1v5.8c0 41.5 17.2 81.2 47.6 109.5z">
                </path>
            </svg>
        </button>
        <div class="card-content">
            <h3 class="card-title">${series.name}</h3>
            <p class="card-description">${series.overview}</p>
        </div>
    `;

    const favoriteBtn = card.querySelector(`#card-favorite-btn-${series.id}`);
    favoriteBtn.addEventListener('click', (event) => {
        event.stopPropagation();
        toggleFavorite(series.id, favoriteBtn);
    });

    initializeFavoriteButton(series.id, favoriteBtn);

    card.addEventListener('click', () => {
        window.location.href = `/detalhes.html?id=${series.id}`;
    });

    return card;
}


function updatePaginationInfo(state, pageInfo) {
    const prevPageButtons = document.querySelectorAll('#prev-page');
    const nextPageButtons = document.querySelectorAll('#next-page');

    prevPageButtons.forEach((button) => {
        button.style.visibility = state.currentPage > 1 ? 'visible' : 'hidden';
    });
    nextPageButtons.forEach((button) => {
        button.style.visibility = state.currentPage < state.totalPages ? 'visible' : 'hidden';
    });    

    pageInfo.forEach((button) => {
        button.textContent = `${state.currentPage} of ${state.totalPages}`;
    });
}

async function toggleFavorite(seriesId, button) {
    const favorites = await api.getFavorites();
    const existing = favorites.find(f => f.serieId === Number(seriesId));
    const message = existing ? 'Removido dos favoritos!' : 'Adicionado aos favoritos!';

    if (existing) {
        await api.removeFavorite(existing.id);
        button.classList.remove('favorited');
    } else {
        await api.addFavorite(seriesId);
        button.classList.add('favorited');
    }

    showNotification(message);
}


async function initializeFavoriteButton(seriesId, button) {
    const favorites = await api.getFavorites();
    const isFavorited = favorites.some(f => f.serieId === Number(seriesId));

    if (isFavorited) {
        button.classList.add('favorited');
    } else {
        button.classList.remove('favorited');
    }
}

