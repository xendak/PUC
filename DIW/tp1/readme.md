## Instruções para Acessar a Página Web

### Requisitos
1. **json-server**
2. **Chave da API IMDB**

### Nix ou NixOS
1. **Método Alternativo com Nix ou NixOS:** - Se você usa Nix ou NixOS, execute o comando: ```sh nix develop ``` - Isso garantirá que você tenha as versões corretas dos pacotes. - Em seguida, siga as instruções abaixo para iniciar o json-server ou executar o script Node.js.

### Passos para Acessar a Página

1. **Configurar o json-server:**
   - Certifique-se de ter o json-server instalado. Você pode instalá-lo globalmente usando npm:
     ```sh
     npm install -g json-server
     ```

2. **Obter a Chave da API IMDB:**
   - Registre-se no site do IMDB para obter sua chave de API.
   - Adicione essa chave ao seu arquivo de configuração ou diretamente no seu código, conforme necessário.
   - **Altere a variável `API_KEY` no arquivo `./public/assets/scripts/api.js`:**
     ```javascript
     const API_KEY = 'API_HERE';
     ```
   - ps: Eu deixei a minha chave de API aqui, pois o trabalho nao explicou nada sobre como deixar para os corretores, entretanto, por favor utilizar a sua própria chave, conforme explicado acima.

3. **Iniciar o json-server:**
   - Navegue até o diretório onde está localizado o arquivo `db.json` e inicie o json-server:
     ```sh
     json-server --watch ./db/db.json
     ```

4. **Acessar o Servidor Local:**
   - Com o json-server rodando, abra seu navegador e vá para `http://localhost:3000` para acessar a aplicação.

### Alternativa com Node.js

1. **Certifique-se de que as dependências estejam instaladas:**
   - Verifique se o `json-server` está instalado em `node_modules` executando:
     ```sh
     npm install
     ```

2. **Executar o Script Node.js:**
   - Você também pode iniciar a aplicação executando o script `index.js`:
     ```sh
     node index.js
     ```

3. **Acessar o Servidor Local:**
   - Com o script em execução, abra seu navegador e vá para `http://localhost:3000`.
