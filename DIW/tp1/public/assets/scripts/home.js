document.addEventListener('DOMContentLoaded', async () => {
    await loadPopularSeries();
    await loadNewSeries();
    await loadFavorites();
    await loadAuthorInfo();

});

async function loadAuthorInfo() {
    const profile = await api.getProfile();
    renderAuthorInfo(profile);
}

function renderAuthorInfo(profile) {
    const authorInfoSection = document.getElementById("author-info");
    if (!authorInfoSection) return;

    authorInfoSection.innerHTML = `
        <h2 class="section-title">Informações do Aluno</h2>
        <div class="profile-card">
          <img src="${profile.avatar}" alt="Photo" class="profile-avatar">
          <div class="profile-info">
            <h3>${profile.name}</h3>
            <p id="divisor"<span class="divisor"></span></p>
            <p><strong>Curso:</strong> ${profile.course}</p>
            <p id="divisor"<span class="divisor"></span></p>
            <p><strong>Disciplina:</strong> ${profile.classroom}</p>
            <p id="divisor"<span class="divisor"></span></p>
            <p id="small-text">${profile.biography}</p>
            <p id="small-text">${profile.outro}</p>
            <p id="divisor"<span class="divisor"></span></p>
            <div class="social-links">
              <a href="${profile.github}" target="_blank" class="social-link">
                <i class="fab fa-github"></i>
                GitHub
              </a>
              <span class="divisor"></span>
              <a href="mailto:${profile.email}" class="social-link">
                <i class="fas fa-envelope"></i>
                Email
              </a>
            </div>
          </div>
        </div>
    `;
}

function initializeCarousel() {
    const carousel = document.getElementById('popular-series');
    const carouselContainer = carousel.querySelector('.carousel-container');
    const items = carouselContainer.querySelectorAll('.carousel-item');
    let currentSlide = 0;

    const prevButton = document.createElement('button');
    const nextButton = document.createElement('button');
    prevButton.className = 'carousel-button prev-button';
    nextButton.className = 'carousel-button next-button';
    prevButton.innerHTML = '❮';
    nextButton.innerHTML = '❯';

    carousel.insertBefore(prevButton, carouselContainer);
    carousel.insertBefore(nextButton, carouselContainer.nextSibling);

    function showSlide(index) {
        const newIndex = (index + items.length) % items.length;

        items[currentSlide].classList.remove('active');

        currentSlide = newIndex;
        items[currentSlide].classList.add('active');
    }

    prevButton.addEventListener('click', (e) => {
        e.preventDefault();
        showSlide(currentSlide - 1);
    });

    nextButton.addEventListener('click', (e) => {
        e.preventDefault();
        showSlide(currentSlide + 1);
    });

    const autoAdvance = setInterval(() => showSlide(currentSlide + 1), 10000);

    carouselContainer.addEventListener('mouseenter', () => {
        clearInterval(autoAdvance);
    });

    carouselContainer.addEventListener('click', () => {
        let id = items[currentSlide].getAttribute('data-series-id');
        window.location.href = `/detalhes.html?id=${id}`;
    });

    carouselContainer.addEventListener('mouseleave', () => {
        setInterval(() => showSlide(currentSlide + 1), 10000);
    });

    showSlide(0);
}

async function loadPopularSeries() {
    const { results } = await api.getPopularSeries();
    const carousel = document.getElementById('popular-series');

    const carouselContainer = document.createElement('div');
    carouselContainer.className = 'carousel-container';

    results.slice(0, 7).forEach((series, index) => {
        const item = document.createElement('div');
        item.className = `carousel-item ${index === 0 ? 'active' : ''}`;

        const img = document.createElement('img');
        img.src = getImageUrl(series.backdrop_path, 'w1280');
        img.alt = series.name;
        img.className = 'carousel-image';

        const caption = document.createElement('div');
        caption.className = 'carousel-caption';
        caption.innerHTML = `
            <h3>${series.name}</h3>
            <p>${series.overview}</p>
            `;

        item.setAttribute('data-series-id', series.id);
        item.appendChild(img);
        item.appendChild(caption);

        carouselContainer.appendChild(item);
    });

    carousel.innerHTML = '';
    carousel.appendChild(carouselContainer);

    initializeCarousel();
}

async function loadNewSeries() {
    const { results } = await api.getNewSeries();
    const container = document.getElementById('new-series');

    const gridContainer = document.createElement('div');
    gridContainer.className = 'series-grid';

    const validSeries = results.filter(series => series.poster_path && series.overview);

    validSeries.slice(0, 5).forEach(series => {
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

    const gridContainer = document.createElement('div');
    gridContainer.className = 'series-grid';

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
