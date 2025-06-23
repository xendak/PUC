// ==UserScript==
// @name         PUC Verde Token Grabber
// @namespace    http://tampermonkey.net/
// @version      2025.06.23
// @description  Automatically copies the auth token from localStorage on a specific site.
// @author       Xendak
// @match        http://verde.icei.pucminas.br/*
// @grant        GM_setClipboard
// ==/UserScript==

(function() {
  'use strict';

  window.addEventListener('load', function() {
    try {
      const tokenKey = '@token';

      const token = localStorage.getItem(tokenKey);

      if (token) {
        console.log('Token found. Copying to clipboard.');
        GM_setClipboard(token, 'text');
      } else {
        console.log('Token not found in localStorage with key:', tokenKey);
      }
    } catch (error) {
      console.error('Error grabbing token:', error);
    }
  });
})();
