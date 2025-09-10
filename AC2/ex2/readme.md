Atividade 01 - Análise de Desempenho de Programas em C
Contexto

A análise de desempenho é uma atividade fundamental em Arquitetura de Computadores. Não basta saber se um programa “roda rápido ou devagar”: é necessário compreender quais fatores influenciam esse tempo, como tipos de dados, uso de cache, predição de desvio, estruturação de laços, além de considerar otimizações do compilador.

Nesta atividade, você utilizará um programa em C sequencial que realiza operações matemáticas intensivas sobre grandes matrizes. O programa foi construído para permitir variações no comportamento de acesso à memória, no uso de ponto flutuante versus inteiros e na presença ou não de desvios condicionais.

A partir dele, você poderá observar como mudanças simples no código podem impactar o desempenho em diferentes arquiteturas.

Você deverá entregar, como de costume, um relatório em PDF contendo todas as pesquisas realizadas, informações obtidas, e resultados solicitados nesta atividade.
Conceitos explorados

Durante a execução e modificação do programa, os seguintes conceitos de Arquitetura serão revisitados:

    Localidade de memória e cache: variação do STRIDE e reordenação de laços.

    Predição de desvio: comparação entre versões com e sem if.

    Unidades de ponto flutuante vs. inteiros: impacto do tipo de dados no desempenho.

    Otimizações de compilador: diferenças entre -O0 e -O2.

ENTREGA: Como primeira parte dessa atividade, você deverá pesquisar e explicar, com um breve texto (2 ou 3 parágrafos), o que cada um dos 4 conceitos acima significa.
Programa fornecido

O programa exe02_ativ1.c

Download exe02_ativ1.c deve ser compilado em C, sem e com otimizações do compilador. Exemplos de como compilar e executar o programa estão a seguir:

    Sem otimização (baseline):

gcc exe02_ativ1.c -O0 -o exe02_ativ1 -lm

    Com otimização (para comparação):

gcc exe02_ativ1.c -O2 -o exe02_ativ1_opt -lm

    Uso/execução do programa, com os parâmetros:

./exe02_ativ1 N REPEAT STRIDE MODE

    N: tamanho da matriz NxN.

        Ex.: 2048 gera uma matriz 2048×2048.

        Controla a quantidade total de dados (maior N → mais memória e mais tempo de execução).

    REPEAT: número de repetições do cálculo.

        Permite prolongar a execução para tornar medições mais visíveis.

    STRIDE: passo de acesso à memória.

        1 → acesso sequencial (boa localidade de cache).

        16 → acesso salteado (ruim para cache, mais misses).

    MODE: versão do algoritmo.

        0: float com desvio (if no laço, impacta branch prediction).

        1: float sem desvio (branchless, usa seleção aritmética).

        2: inteiro (remove ponto flutuante, usa operações inteiras).

ENTREGA (QUESTÕES): Neste ponto, avalie o código fonte, investigando suas estruturas e comandos. Identifique:
a) Onde ocorre o uso de ponto flutuante (float) e de inteiros (int)?
b) Onde aparece o desvio condicional (if) e como ele pode, na sua opinião e com base no que foi pesquisado, afetar o desempenho?
c) Com base no que você estudou, é possível identificar como o parâmetro STRIDE altera o padrão de acesso à memória?
Execuções variadas

Criei uma planilha (MS Excel, Libre Office Calc, Google Sheets, etc.) com as seguintes colunas:

N, REPEAT, STRIDE, MODE, flag (-O0 ou -O2), Tempo (s)

Cada linha representará uma configuração de parâmetros de cada execução testada. Após executar cada uma delas, anote o tempo em segundos obtido.

Execute, pelo menos, as seguintes variações (e outras se achar viável):

    Compare MODE=0 (com if) vs MODE=1 (sem if - branchless).

    Varie STRIDE (1, 2, 4, 8, 16, 32…) e observe o tempo.

    Aumente o tamanho da entrada N (4096, 8192, etc.).
    Repita os melhores casos com a versão otimizada com -O2.

    O parâmetro REPEAT pode ser mantido em 3 (ou mais), para repetir as execuções do kernel, e trazer mais confiabilidade aos dados coletados (usar a média).

ENTREGA (COLETA DE DADOS): Agora que você executou várias versões do código, faça e responda:
a) Apresente os resultados coletados no relatório, preferencialmente lançando mão de gráficos que permitam uma análise visual.
b) Acessos com STRIDE =1 são melhores para cache do que STRIDE=16? (Retome os conceitos de localidade de memória pesquisados) 
c) Você consegue opinar se a verssão com MODE=0, que usa if, pode ser mais lenta em alguma situação do que a versão sem if (MODE=1)? (Retome os conceitos de predição de desvio pesquisados)

 
Atividade 02 - Escalabilidade e Programação Paralela (OpenMP)
Contexto

A evolução da Arquitetura de Computadores não se dá apenas pelo aumento da frequência de clock. Limites físicos, como consumo energético e dissipação térmica, levaram à adoção de arquiteturas multicore. Assim, o ganho de desempenho depende cada vez mais de explorar paralelismo em software.
Nota: Futuramente, em Arquitetura de Computadores III, você aprenderá mais detalhes sobre arquiteturas paralelas. Aqui só teremos uma breve introdução sobre o assunto, voltado para a Análise do Desempenho.

Para avaliar o impacto do uso de múltiplos núcleos, utilizamos métricas de escalabilidade:

    Strong scaling: manter o problema fixo e aumentar o número de threads (unidades de trabalho), verificando se o tempo de execução diminui proporcionalmente.

    Weak scaling: aumentar o tamanho do problema à medida que se aumenta o número de threads, verificando se o tempo de execução se mantém aproximadamente constante.

Nesta atividade, você irá experimentar essas formas de escalabilidade com um código em C + OpenMP (uma biblioteca de programação paralela), observando como o desempenho se altera ao variar número de threads e tamanho da carga de trabalho.

ENTREGA: Como primeira parte dessa atividade, você deverá pesquisar e explicar, com um breve texto (2 ou 3 parágrafos), os seguuintes conceitos:
a) Processos e threads
b) Speedup
c) Eficiência (em computação paralela)
Programa fornecido

O programa exe02_ativ2.c

Download exe02_ativ2.c  implementa um kernel computacional simples, com carga ajustável e paralelização por OpenMP. Também deve ser compilado em C, observando a inclusão da biblioteca do OpenMP. As linhas de comando para compilar e executar o programa está a seguir:

    Compilando:

gcc exe02_ativ2.c -O2 -fopenmp -o exe02_ativ2 -lm

    Uso/execução do programa, com os parâmetros:

./exe02_ativ2 <mode> <N0> <MAX_POW_THREADS> <REPEAT> <WORK>

    mode: strong ou weak (define o tipo de escalabilidade).

    N0: tamanho base do problema (em elementos).

    MAX_POW_THREADS: máximo de potências de 2 para threads (ex.: 3 → threads = 1, 2, 4, 8).

    REPEAT: número de repetições (para estabilizar medições).

    WORK: quantidade de operações por elemento (aumenta a carga de cálculo).

 

    Exemplos de execução:

        Strong scaling:
    ./exe02_ativ2 strong 1048576 3 5 64

        Weak scaling:
    ./exe02_ativ2 weak 524288 3 5 64

    O programa gera uma tabela com as seguintes colunas:
    threads | N | t_best | t_avg | checksum | speedup | efficiency

ENTREGA (QUESTÕES): Neste ponto, avalie o código fonte, investigando suas estruturas e comandos. Procure pesquisar e informe:
a) O que faz a diretiva #pragma omp parallel for ?
b) Qual o comando no código que modifica o número de threads geradas pelo programa?
c) Você consegue identificar quantos processadores/núcleos possui o computador que está usando? Com base nessa informação, qual seria o número de threads ideal do programa, e por quê?
Execuções variadas

Criei uma planilha (MS Excel, Libre Office Calc, Google Sheets, etc.) com as colunas e informações da saída do programa. O objetivo é similar ao da Atividade 01.

Cada linha representará uma configuração de parâmetros de cada execução testada.

Execute, pelo menos, as seguintes variações (e outras se achar viável):

    Varie o tamanho base do problema (comece no valor de exemplo, e em seguida vá dobrando este valor)
    O próprio programa já testa variados números de threads (utilize o parametro MAX_POW_THREADS com valor 3 ou 4)
    Compare Strong Scaling com Weak Scaling (mode weak e mode strong)

ENTREGA (COLETA DE DADOS): Agora que você executou várias versões do código, faça e responda:
a) Apresente os resultados coletados no relatório, preferencialmente lançando mão de gráficos que permitam uma análise visual.
b) Execuções com mais threads são sempre melhores do que com menos threads em termos de tempo de execução? E eficiência?
c) Em termos de avaliação de resultados, o que você julga melhor para análise: Weak Scaling ou Strong Scaling? Justifique

