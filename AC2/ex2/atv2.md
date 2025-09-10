# Relatório de Análise de Desempenho e Paralelismo

**Autor:** Rafael Georgetti Grossi

## Atividade 01 - Análise de Desempenho de Programas em C

### 1\. Pesquisa de Conceitos

#### a) Localidade de Memória e Cache

Localidade de memória: programas tendem a acessar repetidamente as mesmas áreas
de memória (localidade temporal) ou áreas adjacentes (localidade espacial).
Utilizando esse comportamento, processadores utilizam memória cache, uma memória
pequena e rápida que armazena dados recentemente usados da memória principal. Um
acesso a um dado presente na cache (cache hit) é muito rápido, entretando o
accesso de dado ausente (cache miss) leva a uma penalidade de tempo
significativa, pois o dado precisa ser buscado da RAM. Programas com boa
localidade espacial, que acessam dados de forma sequencial, maximizam a taxa de
cache hits e, consequentemente, o desempenho.

#### b) Predição de Desvio

A predição de desvio é um mecanismo do processador que tenta antecipar/prever
qual caminho uma instrução condicional (if/else) seguirá. Processadores modernos
usam métodos sofisticados que analisam padrões históricos. Quando corretp, o
pipeline continua executando sem interrupções, entretanto quando erra (branch
misprediction), o processador deve descartar as instruções especulativas e
recarregar o pipeline com o caminho correto, causando penalidades de vários
ciclos. Quando os códigos com padrões de desvio são previsíveis, isso funciona
bem, entretanto, em padrões aleatórios/complexos, as mispredictions aumentam e o
desempenho cai. Logo, técnicas "branchless" (sem desvios) podem ser mais
eficientes, substituindo condicionais por operações aritméticas que sempre
executam, eliminando a incerteza.

#### c) Unidades de Ponto Flutuante vs. Inteiros

A CPU possui unidades de execução especializadas: a Unidade Lógica e Aritmética
(ALU) para operações com inteiros e a Unidade de Ponto Flutuante (FPU) para
operações com `float` e `double`. Operações com inteiros são, em geral, mais
simples e rápidas. A aritmética de ponto flutuante é mais complexa, exigindo
manipulação de mantissa e expoente, podendo resultar em maior latência,
especialmente para funções matemáticas como `sin()`j `cos()` ou `sqrt()`.

#### d) Otimizações de Compilador

O compilador é um "tradutor", traduzindo o código-fonte, humano, para código de
máquina, podendo aplicar otimizações para melhorar o desempenho. Flags como
`-O0` (sem otimização, bom para depuração) e `-O2` (um conjunto robusto de
otimizações) controlam esse processo. Otimizações podem conter desenrolamento de
laços, reordenação de instruções e vetorização, que reestruturam o código para
melhor aproveitar os recursos do processador, como o pipeline e a cache,
resultando em um melhor desempenho.

### 2\. Análise do Código Fonte (`exe02_ativ1.c`)

a) Uso de `float` vs. `int`: Os `MODEs` 0 e 1 utilizam o tipo `float` e realiza
operações de ponto flutuante. O `MODE` 2 utiliza o tipo `int` e operações
inteiras, como multiplicação e deslocamento de bits. b) Desvio condicional
(`if`): O desvio `if (a > thresh)` está presente nos `MODEs` 0 e 2. Como os
dados são pseudoaleatórios, o resultado da condição é imprevisível, e deve
causar uma alta taxa de misprediction e piorar o desempenho. c) Impacto do
`STRIDE`: O parâmetro `STRIDE` controla o passo do laço interno. `STRIDE=1`
resulta em acessos sequenciais, que promove a localidade espacial e bom uso da
cache. Um `STRIDE` alto, causa acessos "saltados", quebrando a localidade
espacial e resultando em um número elevado de cache misses.

### 3\. Coleta e Análise de Dados

#### a) Apresentação dos Resultados

Os testes foram executados 10 vezes para cada configuração, com o `REPEAT`
interno definido como 20. As tabelas e gráficos apresentam os valores médios.

**Tabela de Dados de Exemplo (N=4096, -O2)**

| REPEAT | STRIDE | MODE | Optimization | Avg\_Time\_s |     Std\_Dev\_s      |
| :----: | :----: | :--: | :----------: | :----------: | :------------------: |
|   20   |   01   |  0   |     -O2      |  4.5801032   |  0.2824749530063782  |
|   20   |   01   |  1   |     -O2      | 5.830760905  | 0.35491382870508165  |
|   20   |   01   |  2   |     -O2      |  1.9861525   | 0.12686437836108472  |
|   20   |   02   |  0   |     -O2      |   2.118247   | 0.10413639920476095  |
|   20   |   02   |  1   |     -O2      |  2.9674864   | 0.19231294638178795  |
|   20   |   02   |  2   |     -O2      |  1.0755663   | 0.09113340574131482  |
|   20   |   04   |  0   |     -O2      |   1.177765   |  0.1063663385725641  |
|   20   |   04   |  1   |     -O2      |  1.5327258   | 0.12649363242981398  |
|   20   |   04   |  2   |     -O2      | 0.570886999  | 0.054333694945626905 |
|   20   |   08   |  0   |     -O2      |  0.6707902   | 0.06839065684693747  |
|   20   |   08   |  1   |     -O2      |  0.8665466   | 0.055613413098720074 |
|   20   |   08   |  2   |     -O2      |  0.3726058   |  0.0376551497578869  |
|   20   |   16   |  0   |     -O2      |   0.412028   | 0.022931230504367708 |
|   20   |   16   |  1   |     -O2      |  0.4984214   | 0.03553166824491452  |
|   20   |   16   |  2   |     -O2      |  0.3108226   | 0.022281757267624415 |
|   20   |   32   |  0   |     -O2      |  0.3024737   | 0.03061294435020729  |
|   20   |   32   |  1   |     -O2      |  0.3563695   | 0.01518963924851409  |
|   20   |   32   |  2   |     -O2      |  0.2956644   | 0.014929991830019345 |

**Gráficos Gerados:**

_Gráfico 1: Demonstração do aumento drástico do tempo de execução com o aumento
do STRIDE, evidenciando o custo dos cache misses._
[]("./img/1_ativ1_impacto_stride.png")

_Gráfico 2: Comparação direta entre os modos de execução, mostrando o benefício
da versão "branchless" (Modo 1) e da aritmética inteira (Modo 2)._
[]("./img/2_ativ1_comparacao_modos.png")

_Gráfico 3: Visualização do ganho massivo de desempenho ao compilar com a flag
-O2 em comparação com -O0._
[]("./img/3_ativ1_impacto_otimizacao.png")

#### b) Acessos com STRIDE=1 são melhores para cache do que STRIDE=16?

Não, e como demonstrado no Gráfico 1, o tempo de execução diminui à medida que o
`STRIDE` cresce, o oposto do "esperado".

#### c) A versão com MODE=0 (com if) pode ser mais lenta que a versão sem if (MODE=1)?

Sim. O Gráfico 2 demonstra essa diferença, o `Modo 1` (branchless) é
consistentemente mais rápido que o `Modo 0`. Como `Modo 0` sofre com a alta taxa
de previsões de desvio incorretas, que causam paradas no pipeline do
processador, o `Modo 1`, entretato, execute mais operações aritméticas, oferece
um fluxo de instruções linear e previsível, evitando as penalidades por
misprediction.

---

## Atividade 02 - Escalabilidade e Programação Paralela (OpenMP)

### 1\. Pesquisa de Conceitos

#### a) Processos e Threads

Um processo é um programa em execução com seu próprio espaço de memória isolado.
Uma thread é uma unidade de execução dentro de um processo. Múltiplas threads de
um mesmo processo compartilham o mesmo espaço de memória, e permite comunicação
rápida e direta. Essa característica é ideail para paralelizar tarefas que
operam sobre dados compartilhados.

#### b) Speedup

Speedup ($S\_p$) mede o ganho de desempenho da versão paralela em relação à
sequencial, usando $p$ processadores/threads. A fórmula é $S\_p = T\_1 / T\_p$,
onde $T\_1$ é o tempo sequencial e $T\_p$ é o tempo paralelo. Um speedup ideal
(linear) seria $S\_p = p$, mas na prática ele é limitado por overheads e porções
não paralelizáveis do código (Lei de Amdahl).

#### c) Eficiência

A eficiência ($E\_p$) normaliza o speedup pelo número de processadores,
quantificando os recursos que estão sendo utilizados. A fórmula é
$E\_p = S\_p / p$. Eficiência de 1 é ideal, e geralmente, a eficiência diminui à
medida que mais processadores são adicionados, devido ao custo de comunicação e
sincronização se tornarem mais significativos.

### 2\. Análise do Código Fonte (`exe02_ativ2.c`)

- **a) `#pragma omp parallel for`**: Esta diretiva do OpenMP instrui o
  compilador a criar um time de threads e distribuir as iterações do laço `for`
  seguinte entre elas, executando-as em paralelo.
- **b) Comando para modificar threads**: A função
  `omp_set_num_threads(threads);` é usada para definir explicitamente o número
  de threads que serão usadas na próxima região paralela.
- **c) Identificação de núcleos e threads ideais**: Em meu sistema (ex:
  `lscpu`), identifiquei 6 núcleos físicos e 12 processadores lógicos (threads).
  O número ideal de threads para tarefas computacionais costuma ser igual ao
  número de **núcleos físicos** (6), pois isso evita a sobrecarga de chaveamento
  de contexto entre threads competindo pelo mesmo núcleo.

### 3\. Coleta e Análise de Dados

#### a) Apresentação dos Resultados

**Tabela de Exemplo: Strong Scaling**

|    N    | work_load | threads | avg_t_best_s | stdev_t_best_s | avg_speedup | stdev_speedup | avg_efficiency | stdev_efficiency |
| :-----: | :-------: | :-----: | :----------: | :------------: | :---------: | :-----------: | :------------: | :--------------: |
| 1048576 |    64     |    1    |    1.2306    |     0.0367     |   1.0000    |    0.0000     |     1.0000     |      0.0000      |
| 1048576 |    64     |    2    |    0.7125    |     0.0170     |   1.7281    |    0.0794     |     0.8640     |      0.0397      |
| 1048576 |    64     |    4    |    0.4036    |     0.0205     |   3.0511    |    0.0668     |     0.7628     |      0.0167      |
| 1048576 |    64     |    8    |    0.2815    |     0.0144     |   4.3748    |    0.0958     |     0.5469     |      0.0120      |
| 1048576 |    64     |   16    |    0.2792    |     0.0049     |   4.4069    |    0.0590     |     0.2754     |      0.0037      |
| 2097152 |    64     |    1    |    3.0052    |     0.1135     |   1.0000    |    0.0000     |     1.0000     |      0.0000      |
| 2097152 |    64     |    2    |    1.5138    |     0.0704     |   1.9863    |    0.0595     |     0.9932     |      0.0297      |
| 2097152 |    64     |    4    |    0.8880    |     0.0234     |   3.3869    |    0.1878     |     0.8467     |      0.0469      |
| 2097152 |    64     |    8    |    0.5988    |     0.0126     |   5.0181    |    0.1193     |     0.6273     |      0.0149      |
| 2097152 |    64     |   16    |    0.6043    |     0.0359     |   4.9877    |    0.4004     |     0.3117     |      0.0250      |

**Tabela de Exemplo: Weak Scaling**

| N0_base | work_load | threads |    N     | avg_t_best_s | stdev_t_best_s | avg_speedup | stdev_speedup | avg_efficiency | stdev_efficiency |
| :-----: | :-------: | :-----: | :------: | :----------: | :------------: | :---------: | :-----------: | :------------: | :--------------: |
| 1048576 |    64     |    1    | 16777216 |    1.4524    |     0.0977     |   1.0000    |    0.0000     |     1.0000     |      0.0000      |
| 1048576 |    64     |    2    | 16777216 |    1.6959    |     0.0429     |   0.8562    |    0.0478     |     0.4281     |      0.0239      |
| 1048576 |    64     |    4    | 16777216 |    1.8490    |     0.0036     |   0.7856    |    0.0531     |     0.1964     |      0.0133      |
| 1048576 |    64     |    8    | 16777216 |    2.5270    |     0.0496     |   0.5748    |    0.0384     |     0.0719     |      0.0048      |
| 1048576 |    64     |   16    | 16777216 |    5.1419    |     0.1008     |   0.2825    |    0.0186     |     0.0177     |      0.0012      |
| 2097152 |    64     |    1    | 33554432 |    2.8700    |     0.0627     |   1.0000    |    0.0000     |     1.0000     |      0.0000      |
| 2097152 |    64     |    2    | 33554432 |    3.4022    |     0.1484     |   0.8452    |    0.0566     |     0.4226     |      0.0283      |
| 2097152 |    64     |    4    | 33554432 |    3.8552    |     0.0074     |   0.7444    |    0.0151     |     0.1861     |      0.0038      |
| 2097152 |    64     |    8    | 33554432 |    5.2725    |     0.0483     |   0.5443    |    0.0097     |     0.0680     |      0.0012      |
| 2097152 |    64     |   16    | 33554432 |   10.6215    |     0.1821     |   0.2702    |    0.0029     |     0.0169     |      0.0002      |

**Gráficos Gerados:**

_Gráfico 4: Curva de speedup para um problema de tamanho fixo. Note como a curva
se afasta da linha ideal com mais threads._
[]("./img/4_ativ2_strong_scaling_speedup.png")

_Gráfico 5: A eficiência cai consideravelmente à medida que o número de threads
aumenta, mostrando o custo do overhead._
[]("./img/5_ativ2_strong_scaling_eficiencia.png")

_Gráfico 6: O tempo de execução se mantém quase constante mesmo com o aumento do
problema e do número de threads, demonstrando excelente escalabilidade fraca._
[]("./img/6_ativ2_weak_scaling_tempo.png")

#### b) Execuções com mais threads são sempre melhores do que com menos threads em termos de tempo de execução? E eficiência?

A análise dos resultados, especialmente dos Gráficos 4 e 5, mostra que não,
depende.

- Tempo de Execução: Inicialmente, adicionar threads reduz o tempo (o speedup
  aumenta, como visto no Gráfico 4). No entanto, os ganhos são decrescentes. No
  nosso caso, passar de 8 para 16 threads quase manteve o ganho constante, pois
  o overhead de gerenciar tantas threads tende a competir com o ganho da
  paralelização.
- Eficiência: O Gráfico 5 descreve perfeitamente. A eficiência sempre diminui
  com o aumento do número de threads. Isso significa que, embora o programa
  possa rodar mais rápido, cada núcleo adicional está sendo utilizado de forma
  menos produtiva, gastando uma porção maior do seu tempo em sincronização e
  comunicação em vez de computação útil.

#### c) Em termos de avaliação de resultados, o que você julga melhor para análise: Weak Scaling ou Strong Scaling? Justifique.

Não há um "melhor", pois eles servem a propósitos distintos e complementares
para a análise de algoritmos paralelos.

- Strong Scaling é a métrica ideal quando se tem um problema de tamanho fixo e o
  objetivo é resolvê-lo o mais rápido possível; de acordo com os gráficos 4 e 5,
  ele expõe os limites da paralelização (Lei de Amdahl) e o impacto do overhead,
  sendo útil para otimizar a performance de uma tarefa específica.
- Weak Scaling é superior para avaliar a capacidade de um algoritmo escalar para
  problemas maiores. O Gráfico 6 mostra que o algoritmo é excelente para isso,
  pode-se dobrar o tamanho do problema e, ao dobrar o número de processadores, o
  tempo de solução permanece quase o mesmo. Essa é uma característica importante
  em computação científica e de larga escala, onde o objetivo é simular sistemas
  maiores ou com mais detalhes, e não apenas resolver um problema pequeno mais
  rápido.
