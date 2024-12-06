document.addEventListener('DOMContentLoaded', init);

function init() {
    const state = {
        currentPage: 1,
        totalPages: 1,
        query: '',
        resultsPerPage: 35, // 5 columns x 7 rows
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
    // Skip
    if (!series.poster_path || !series.overview) {
        return null;
    }

    const card = document.createElement('div');
    card.className = 'card';
    card.innerHTML = `
        <img src="${getImageUrl(series.poster_path, 'w500')}" 
             alt="${series.name}" 
             class="card-image">
        <div class="card-content">
            <h3 class="card-title">${series.name}</h3>
            <p class="card-description">${series.overview}</p>
        </div>
    `;
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

