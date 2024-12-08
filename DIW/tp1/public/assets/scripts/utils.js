document.addEventListener('DOMContentLoaded', async () => {
    const themeToggleButton = document.getElementById('theme-toggle');
    const themeIcon = document.getElementById('theme-icon');
    
    currentTheme = localStorage.getItem('theme') || 'day';

    document.documentElement.setAttribute('data-theme', currentTheme);
    themeIcon.className = currentTheme === 'night' ? 'fas fa-sun' : 'fas fa-moon';

    themeToggleButton.addEventListener('click', async () => {
        console.log('cliked');
        const newTheme = currentTheme === 'night' ? 'day' : 'night';
        document.documentElement.setAttribute('data-theme', newTheme);
        currentTheme = newTheme;

        themeIcon.className = newTheme === 'night' ? 'fas fa-sun' : 'fas fa-moon';

        localStorage.setItem('theme', newTheme);
    });
});


function showNotification(message) {
    const notification = document.createElement('div');
    notification.className = 'notification';
    notification.textContent = message;

    document.body.appendChild(notification);

    setTimeout(() => { notification.remove(); }, 2000);
}
