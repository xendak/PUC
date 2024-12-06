document.addEventListener('DOMContentLoaded', async () => {
    // Load all sections
    await loadPopularSeries();
    await loadNewSeries();
    await loadFavorites();

});

// Modified carousel initialization function
function initializeCarousel() {
    const carousel = document.getElementById('popular-series');
    const carouselContainer = carousel.querySelector('.carousel-container');
    const items = carouselContainer.querySelectorAll('.carousel-item');
    let currentSlide = 0;

    // Create navigation buttons
    const prevButton = document.createElement('button');
    const nextButton = document.createElement('button');
    prevButton.className = 'carousel-button prev-button';
    nextButton.className = 'carousel-button next-button';
    prevButton.innerHTML = '❮';
    nextButton.innerHTML = '❯';

    // Add buttons directly to the carousel section, not the container
    carousel.insertBefore(prevButton, carouselContainer);
    carousel.insertBefore(nextButton, carouselContainer.nextSibling);

    function showSlide(index) {
        // Handle wrapping around
        const newIndex = (index + items.length) % items.length;

        // Remove active class from current slide
        items[currentSlide].classList.remove('active');

        // Update current slide and add active class
        currentSlide = newIndex;
        items[currentSlide].classList.add('active');
    }

    // Event listeners for buttons
    prevButton.addEventListener('click', (e) => {
        e.preventDefault();
        showSlide(currentSlide - 1);
    });

    nextButton.addEventListener('click', (e) => {
        e.preventDefault();
        showSlide(currentSlide + 1);
    });

    // Auto-advance carousel
    const autoAdvance = setInterval(() => showSlide(currentSlide + 1), 10000);

    // Stop auto-advance on hover
    carouselContainer.addEventListener('mouseenter', () => {
        clearInterval(autoAdvance);
    });

    carouselContainer.addEventListener('click', () => {
        let id = items[currentSlide].getAttribute('data-series-id');
        window.location.href = `/detalhes.html?id=${id}`;
    });

    // Resume auto-advance when mouse leaves
    carouselContainer.addEventListener('mouseleave', () => {
        setInterval(() => showSlide(currentSlide + 1), 10000);
    });

    // Show first slide
    showSlide(0);
}

async function loadPopularSeries() {
    const { results } = await api.getPopularSeries();
    const carousel = document.getElementById('popular-series');

    // Create carousel container
    const carouselContainer = document.createElement('div');
    carouselContainer.className = 'carousel-container';

    results.slice(0, 7).forEach((series, index) => {
        console.log(`Index: ${index}, ID: ${series.id}`); // Debugging line
        const item = document.createElement('div');
        item.className = `carousel-item ${index === 0 ? 'active' : ''}`;

        // Create and append image
        const img = document.createElement('img');
        img.src = getImageUrl(series.backdrop_path, 'w1280');
        img.alt = series.name;
        img.className = 'carousel-image';

        // Create caption
        const caption = document.createElement('div');
        caption.className = 'carousel-caption';
        caption.innerHTML = `
            <h3>${series.name}</h3>
            <p>${series.overview}</p>
            `;

        // Append elements
        item.setAttribute('data-series-id', series.id); // Set data attribute for debugging
        item.appendChild(img);
        item.appendChild(caption);

        carouselContainer.appendChild(item);
    });

    // Clear existing content and append new container
    carousel.innerHTML = '';
    carousel.appendChild(carouselContainer);

    // Initialize carousel after content is loaded
    initializeCarousel();
}

async function loadNewSeries() {
    const { results } = await api.getNewSeries();
    const container = document.getElementById('new-series');

    // Create grid container
    const gridContainer = document.createElement('div');
    gridContainer.className = 'series-grid';

    results.slice(0, 5).forEach(series => {
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
        gridContainer.appendChild(card);
    });

    container.appendChild(gridContainer);
}

async function loadFavorites() {
    const favorites = await api.getFavorites();
    const container = document.getElementById('favorite-series');

    // Create grid container
    const gridContainer = document.createElement('div');
    gridContainer.className = 'favorites-grid';

    for (const favorite of favorites) {
        const series = await api.getSeriesDetails(favorite.serieId);
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
        gridContainer.appendChild(card);
    }

    container.appendChild(gridContainer);
}
