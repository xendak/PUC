// API Configuration
const API_KEY = '2fcf24d155701ad465c7d59c7b0e91f1';
const TMDB_BASE_URL = 'https://api.themoviedb.org/3';
const IMAGE_BASE_URL = 'https://image.tmdb.org/t/p';

// API Helper Functions
const api = {
    // TMDB API Calls
    async getPopularSeries(page = 1) {
        const response = await fetch(
            `${TMDB_BASE_URL}/tv/popular?api_key=${API_KEY}&language=en-US&page=${page}`
        );
        return response.json();
    },

    async getNewSeries(page = 1) {
        const response = await fetch(
            `${TMDB_BASE_URL}/tv/on_the_air?api_key=${API_KEY}&language=en-US&page=${page}`
        );
        return response.json();
    },

    async searchSeries(query, page = 1) {
        const response = await fetch(
            `${TMDB_BASE_URL}/search/tv?api_key=${API_KEY}&language=en-US&query=${encodeURIComponent(query)}&page=${page}`
        );
        return response.json();
    },

    async getSeriesDetails(id) {
        const response = await fetch(
            `${TMDB_BASE_URL}/tv/${id}?api_key=${API_KEY}&language=en-US`
        );
        return response.json();
    },

    async getSeriesCast(id) {
        const response = await fetch(
            `${TMDB_BASE_URL}/tv/${id}/credits?api_key=${API_KEY}&language=en-US`
        );
        return response.json();
    },

    // JSON Server API Calls
    async getProfile() {
        const response = await fetch('/profile');
        return response.json();
    },

    async getFavorites() {
        const response = await fetch('/favorites');
        return response.json();
    },

    async addFavorite(sid) {
        const response = await fetch('/favorites', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                serieId: sid,
                userId: 1
            })
        });
        return response.json();
    },

    async removeFavorite(id) {
        const response = await fetch(`/favorites/${id}`, {
            method: 'DELETE'
        });
        return response.ok;
    }
};

// Helper function to get image URL
function getImageUrl(path, size = 'original') {
    if (!path) return '/assets/img/no-image.jpg';
    return `${IMAGE_BASE_URL}/${size}${path}`;
}
