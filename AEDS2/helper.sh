#!/bin/sh

curl "http://verde.icei.pucminas.br:3333/atividade/zip/[YOUR_ACTIVITY_ID]" \
  -H 'User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:139.0) Gecko/20100101 Firefox/139.0' \
  -H 'Accept: */*' \
  -H 'Accept-Language: en-US,en;q=0.5' \
  -H 'Accept-Encoding: gzip, deflate' \
  -H "Authorization: Bearer $2" \
  -H 'Referer: http://verde.icei.pucminas.br/' \
  -H 'Origin: http://verde.icei.pucminas.br' \
  -H 'Connection: keep-alive' \
  --output "$PWD/pubs.zip"

  unzip "$PWD/pubs.zip"
  rm "$PWD/pubs.zip"
