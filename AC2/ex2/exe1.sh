#!/bin/bash

# --- Configuração ---
# Arquivo de código-fonte C
SOURCE_FILE="1.c"
# Nome dos binários compilados
BIN_NO_OPT="bin1"
BIN_OPT="bin1_opt"
# Arquivo de saída CSV
OUTPUT_CSV="out1.csv"

# Parâmetros para os testes
N_VALUES=(1024 2048 4096)
REPEAT=100
STRIDE_VALUES=(1 2 4 8 16 32)
MODE_VALUES=(0 1 2)

# --- Verificação e Compilação ---

# 1. Verificar se o arquivo .c existe
if [ ! -f "$SOURCE_FILE" ]; then
    echo "Erro: O arquivo de código-fonte '$SOURCE_FILE' não foi encontrado."
    echo "Por favor, faça o download ou coloque-o no mesmo diretório do script."
    exit 1
fi

# 2. Compilar as duas versões do programa
echo "Compilando o programa..."
clang "$SOURCE_FILE" -O0 -o "$BIN_NO_OPT" -lm
if [ $? -ne 0 ]; then
    echo "Falha na compilação sem otimização. Verifique o código e as dependências (como a biblioteca matemática -lm)."
    exit 1
fi

clang "$SOURCE_FILE" -O2 -o "$BIN_OPT" -lm
if [ $? -ne 0 ]; then
    echo "Falha na compilação com otimização (-O2)."
    exit 1
fi

echo "Compilação bem-sucedida! Binários '$BIN_NO_OPT' e '$BIN_OPT' criados."
echo

# --- Execução e Coleta de Dados ---

# 3. Criar o arquivo CSV e escrever o cabeçalho
echo "N,REPEAT,STRIDE,MODE,flag,Tempo(s)" > "$OUTPUT_CSV"

echo "Iniciando a execução dos testes. Isso pode levar vários minutos..."
echo "Os resultados serão salvos em '$OUTPUT_CSV'."
echo

# 4. Loop através de todas as combinações de parâmetros
for n in "${N_VALUES[@]}"; do
    for stride in "${STRIDE_VALUES[@]}"; do
        for mode in "${MODE_VALUES[@]}"; do
            
            # --- Execução sem Otimização (-O0) ---
            echo "Executando: N=$n, REPEAT=$REPEAT, STRIDE=$stride, MODE=$mode, flag=-O0"
            # Executa o programa e filtra a saída com 'awk' para pegar o valor do tempo
            time_o0=$(./"$BIN_NO_OPT" "$n" "$REPEAT" "$stride" "$mode" | awk '/Tempo\(s\):/ {print $2}')
            # Escrever a linha no CSV
            echo "$n,$REPEAT,$stride,$mode,-O0,$time_o0" >> "$OUTPUT_CSV"


            # --- Execução com Otimização (-O2) ---
            echo "Executando: N=$n, REPEAT=$REPEAT, STRIDE=$stride, MODE=$mode, flag=-O2"
            time_o2=$(./"$BIN_OPT" "$n" "$REPEAT" "$stride" "$mode" | awk '/Tempo\(s\):/ {print $2}')
            # Escrever a linha no CSV
            echo "$n,$REPEAT,$stride,$mode,-O2,$time_o2" >> "$OUTPUT_CSV"

            echo "---"
        done
    done
done

echo
echo "Todos os testes foram concluídos com sucesso!"
echo "Os dados foram salvos no arquivo '$OUTPUT_CSV'."
