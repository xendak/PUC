document.addEventListener('DOMContentLoaded', async () => {
    const urlParams = new URLSearchParams(window.location.search);
    const seriesId = urlParams.get('id');

    if (!seriesId) {
        window.location.href = '/';
        return;
    }

    await loadSeriesDetails(seriesId);
    await loadSeriesCast(seriesId);
    await initializeFavoriteButton(seriesId); 
});

async function loadSeriesDetails(seriesId) {
    const series = await api.getSeriesDetails(seriesId);
    const container = document.getElementById('series-overview');

    container.innerHTML = `
        <div class="series-info-box">
            <img src="${getImageUrl(series.poster_path, 'w500')}" 
                alt="${series.name}" 
                class="series-poster">
            <div class="series-info">
                <h1 id="series-title">${series.name}</h1>
                <p id="series-description">${series.overview}</p>
                <p><strong>Data de Lançamento:</strong> <span id="series-air-date">${series.first_air_date}</span></p>
                <p><strong>Nota:</strong> <span id="series-rating">${series.vote_average}/10</span></p>
                <p><strong>Gêneros:</strong> <span id="series-genres">${series.genres.map(g => g.name).join(', ')}</span></p>
                <button class="favorite-btn" id="favorite-btn" onclick="toggleFavorite(${series.id})">
                    <svg class="heart-icon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 512 512">
                        <path d="M47.6 300.4L228.3 469.1c7.5 7 17.4 10.9 27.7 10.9s20.2-3.9 27.7-10.9L464.4 300.4c30.4-28.3 47.6-68 47.6-109.5v-5.8c0-69.9-50.5-129.5-119.4-141C347 36.5 300.6 51.4 268 84L256 96 244 84c-32.6-32.6-79-47.5-124.6-39.9C50.5 55.6 0 115.2 0 185.1v5.8c0 41.5 17.2 81.2 47.6 109.5z">
                        </path>
                    </svg>
                </button>
            </div>
        </div>
    `;
}

async function loadSeriesCast(seriesId) {
    const { cast } = await api.getSeriesCast(seriesId);
    const container = document.getElementById('cast-grid-container');
    const defaultProfileImage = './assets/img/default-profile.png';

    container.innerHTML = '';
    cast.slice(0, 8).forEach(person => {
        const card = document.createElement('div');
        card.className = 'cast-card';
        const profileImage = person.profile_path 
            ? getImageUrl(person.profile_path, 'w185') 
            : defaultProfileImage;
        card.innerHTML = `
            <img src="${profileImage}" 
                alt="${person.name}" 
                class="cast-image">
            <h3 class="cast-name">${person.name}</h3>
            <p class="cast-character">${person.character}</p>
        `;
        container.appendChild(card);
    });

    if (container.innerHTML === '') {
        container.innerHTML = '<p>Sem informaçoes do elenco.</p>';
    }
}

async function toggleFavorite(sid) {
    const favoriteBtn = document.getElementById('favorite-btn');

    const favorites = await api.getFavorites();
    const existing = favorites.find(f => f.serieId === Number(sid));    

    const message = existing ? 'Removido dos favoritos!' : 'Adicionado aos favoritos!';

    if (existing) {
        await api.removeFavorite(existing.id);
        favoriteBtn.classList.remove('favorited');
    } else {
        await api.addFavorite(sid);
        favoriteBtn.classList.add('favorited');
    }

    showNotification(message);
}

async function initializeFavoriteButton(sid) {
    const favoriteBtn = document.getElementById('favorite-btn');

    const favorites = await api.getFavorites();
    const existing = favorites.find(f => f.serieId === Number(sid));    

    if (existing) {
        favoriteBtn.classList.add('favorited');
    } else {
        favoriteBtn.classList.remove('favorited');
    }
}
