#!/bin/sh
# curl -H "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VySWQiOjcxMjUsImNhbnZhIjoiMTE3NDh-WEh6N3hyRzhyVFJINm42QzZGeXo4R2FmREgybUF4NlBKR3lFV05EcjZSSDdZQkJyNFBLUGFMNE0yYWU2R1JONiIsInJvbGUiOiJhbHVubyIsInR1cm1hcyI6WzAsNjM3NywxOTkxMjIsMjUyMTMsMjE5NjY0LDIxOTY2NSwyMjA1MTIsMjE5NjYwLDIyMDUxMywyMTk2NjgsMjE5NjYxLDY4OTAyLDY4OTczLDIxOTY3MV0sImlhdCI6MTc0OTQwMzE3NywiZXhwIjoxNzQ5NDA2Nzc3fQ.tGLlGs_pSune900klMATa3X7NKZ6umNqOcTTa822tco" http://verde.icei.pucminas.br:3333/atividade/zip/"$1" -o pub.zip

mv "$HOME/Downloads/pubs.zip" "$PWD"
unzip "$PWD/pubs.zip"
rm "pubs.zip"
