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
                <p><strong>Airing Date:</strong> <span id="series-air-date">${series.first_air_date}</span></p>
                <p><strong>Rating:</strong> <span id="series-rating">${series.vote_average}/10</span></p>
                <p><strong>Genres:</strong> <span id="series-genres">${series.genres.map(g => g.name).join(', ')}</span></p>
                <button class="favorite-btn" id="favorite-btn" onclick="toggleFavorite(${series.id})">
                    <svg class="heart-icon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" width="24" height="24">
                    <path d="M12 21.35l-1.45-1.32C5.4 15.36 2 12.28 2 8.5 2 6 3.98 4 6.5 4c1.74 0 3.41.81 4.5 2.09C12.09 4.81 13.76 4 15.5 4 18.02 4 20 6 20 8.5c0 3.78-3.4 6.86-8.55 11.54L12 21.35z">
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

    container.innerHTML = '';
    cast.slice(0, 8).forEach(person => {
        // only creates if theres a photo.
        if (person.profile_path) {
            const card = document.createElement('div');
            card.className = 'cast-card';
            card.innerHTML = `
                <img src="${getImageUrl(person.profile_path, 'w185')}" 
                    alt="${person.name}" 
                    class="cast-image">
                <h3 class="cast-name">${person.name}</h3>
                <p class="cast-character">${person.character}</p>
            `;
            container.appendChild(card);
        }
    });

    if (container.innerHTML === '') {
        container.innerHTML = '<p>Sem informaçoes do elenco.</p>';
    }
}

async function toggleFavorite(sid) {
    const favoriteBtn = document.getElementById('favorite-btn');

    const favorites = await api.getFavorites();
    const existing = favorites.find(f => f.serieId === Number(sid));    

    if (existing) {
        console.log(existing);
        await api.removeFavorite(existing.id);
        favoriteBtn.classList.remove('favorited');
        alert('Removed from favorites!');
    } else {
        await api.addFavorite(sid);
        favoriteBtn.classList.add('favorited');
        alert('Added to favorites!');
    }
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
