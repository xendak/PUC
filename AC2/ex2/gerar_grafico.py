import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os
import sys

# --- Configurações ---
ATIV1_CSV = "ativ1.csv"
ATIV2_CSV = "ativ2.csv"
OUTPUT_DIR = "img"

def plot_activity1_results(df: pd.DataFrame):
    """Gera todos os gráficos para a Atividade 01."""
    print("\n--- Gerando gráficos para a Atividade 01 ---")

    # --- Gráfico 1: Impacto do STRIDE no Desempenho (Cache Locality) ---
    # Este gráfico ajuda a responder: "Acessos com STRIDE=1 são melhores?"
    print("Gerando gráfico: Impacto do STRIDE...")
    plt.figure(figsize=(12, 7))
    
    # Filtra para o maior N e para o código otimizado (-O2), que é o cenário mais realista
    df_stride = df[(df['N'] == 4096) & (df['Optimization'] == '-O2')].copy()
    
    # Mapeia os modos para nomes mais descritivos para a legenda
    df_stride['Legenda'] = df_stride['MODE'].map({
        0: 'Float com IF',
        1: 'Float Branchless',
        2: 'Inteiro'
    })

    sns.lineplot(data=df_stride, x='STRIDE', y='Avg_Time_s', hue='Legenda', style='Legenda', marker='o', markersize=8)
    
    plt.title('Impacto do STRIDE no Tempo de Execução (N=4096, -O2)', fontsize=16)
    plt.xlabel('STRIDE (Passo de Acesso à Memória)', fontsize=12)
    plt.ylabel('Tempo Médio de Execução (s) - Escala Logarítmica', fontsize=12)
    plt.xscale('log', base=2) # Stride é potência de 2, escala log base 2 faz sentido
    plt.yscale('log')
    plt.xticks(df_stride['STRIDE'].unique()) # Garante que todos os pontos de stride apareçam
    plt.grid(True, which="both", ls="--")
    plt.legend(title='Modo de Execução')
    plt.tight_layout()
    plt.savefig(os.path.join(OUTPUT_DIR, "1_ativ1_impacto_stride.png"))
    plt.close()

    # --- Gráfico 2: Comparação de Modos (Branch Prediction e Tipos de Dados) ---
    # Este gráfico ajuda a responder: "A versão com IF (MODE=0) é mais lenta que a sem IF (MODE=1)?"
    print("Gerando gráfico: Comparação de Modos...")
    plt.figure(figsize=(10, 6))
    
    # Filtra para um caso com boa localidade (STRIDE=1) e otimizado
    df_modes = df[(df['N'] == 4096) & (df['Optimization'] == '-O2') & (df['STRIDE'] == 1)]
    
    ax = sns.barplot(data=df_modes, x='MODE', y='Avg_Time_s', palette='viridis')
    ax.bar_label(ax.containers[0], fmt='%.3fs') # Adiciona o valor no topo da barra
    
    plt.title('Comparação de Desempenho entre Modos (N=4096, STRIDE=1, -O2)', fontsize=16)
    plt.xlabel('Modo de Execução', fontsize=12)
    plt.ylabel('Tempo Médio de Execução (s)', fontsize=12)
    plt.xticks(ticks=[0, 1, 2], labels=['0: Float com IF\n(Ruim para Predição)', '1: Float Branchless\n(Bom para Predição)', '2: Inteiro\n(Mais Rápido)'])
    plt.tight_layout()
    plt.savefig(os.path.join(OUTPUT_DIR, "2_ativ1_comparacao_modos.png"))
    plt.close()

    # --- Gráfico 3: Impacto da Otimização do Compilador ---
    # Gráfico bônus que demonstra visualmente o efeito da flag -O2
    print("Gerando gráfico: Impacto da Otimização...")
    plt.figure(figsize=(10, 6))
    
    df_opt = df[(df['N'] == 2048) & (df['STRIDE'] == 1) & (df['MODE'] == 0)]
    
    ax = sns.barplot(data=df_opt, x='Optimization', y='Avg_Time_s', palette='magma')
    ax.bar_label(ax.containers[0], fmt='%.3fs')
    
    plt.title('Impacto da Otimização do Compilador (N=2048, STRIDE=1, Modo 0)', fontsize=16)
    plt.xlabel('Flag de Otimização', fontsize=12)
    plt.ylabel('Tempo Médio de Execução (s)', fontsize=12)
    plt.tight_layout()
    plt.savefig(os.path.join(OUTPUT_DIR, "3_ativ1_impacto_otimizacao.png"))
    plt.close()

def plot_activity2_results(df: pd.DataFrame):
    """Gera todos os gráficos para a Atividade 02."""
    print("\n--- Gerando gráficos para a Atividade 02 ---")
    
    # Filtra para um N0 base para manter os gráficos limpos
    df = df[df['N0_base'] == df['N0_base'].max()].copy()
    df_strong = df[df['scaling_mode'] == 'strong']
    df_weak = df[df['scaling_mode'] == 'weak']

    # --- Gráfico 4: Strong Scaling - Speedup ---
    # Ajuda a responder: "Execuções com mais threads são sempre melhores?"
    print("Gerando gráfico: Strong Scaling (Speedup)...")
    plt.figure(figsize=(10, 6))
    
    threads = df_strong['threads']
    plt.plot(threads, df_strong['avg_speedup'], marker='o', linestyle='-', label='Speedup Medido')
    plt.plot(threads, threads, linestyle='--', color='red', label='Speedup Ideal (Linear)')
    
    plt.title(f'Strong Scaling - Speedup (Tamanho Fixo: N={df_strong.iloc[0]["N"]})', fontsize=16)
    plt.xlabel('Número de Threads', fontsize=12)
    plt.ylabel('Speedup (Aceleração)', fontsize=12)
    plt.xticks(threads)
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(OUTPUT_DIR, "4_ativ2_strong_scaling_speedup.png"))
    plt.close()

    # --- Gráfico 5: Strong Scaling - Eficiência ---
    # Complementa a resposta sobre "mais threads é sempre melhor?" mostrando o custo
    print("Gerando gráfico: Strong Scaling (Eficiência)...")
    plt.figure(figsize=(10, 6))
    
    plt.plot(df_strong['threads'], df_strong['avg_efficiency'], marker='o', linestyle='-')
    
    plt.title(f'Strong Scaling - Eficiência (Tamanho Fixo: N={df_strong.iloc[0]["N"]})', fontsize=16)
    plt.xlabel('Número de Threads', fontsize=12)
    plt.ylabel('Eficiência', fontsize=12)
    plt.xticks(threads)
    plt.ylim(0, 1.1) # Eficiência vai de 0 a 1
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(OUTPUT_DIR, "5_ativ2_strong_scaling_eficiencia.png"))
    plt.close()

    # --- Gráfico 6: Weak Scaling - Tempo de Execução ---
    # Ajuda a justificar a utilidade do Weak Scaling para análise
    print("Gerando gráfico: Weak Scaling (Tempo de Execução)...")
    plt.figure(figsize=(10, 6))
    
    plt.plot(df_weak['threads'], df_weak['avg_t_best_s'], marker='o', linestyle='-')
    
    plt.title(f'Weak Scaling - Tempo de Execução (Carga por Thread Constante)', fontsize=16)
    plt.xlabel('Número de Threads', fontsize=12)
    plt.ylabel('Tempo Médio de Execução (s)', fontsize=12)
    plt.xticks(df_weak['threads'])
    plt.grid(True)
    # Linha de base para mostrar o quão constante o tempo se manteve
    plt.axhline(y=df_weak['avg_t_best_s'].iloc[0], color='r', linestyle='--', label=f'Tempo Base (1 thread)')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(OUTPUT_DIR, "6_ativ2_weak_scaling_tempo.png"))
    plt.close()

def main():
    """Função principal para carregar dados e chamar as funções de plotagem."""
    # Cria o diretório de saída se ele não existir
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    
    # Configura o estilo dos gráficos
    sns.set_theme(style="whitegrid", context="talk")

    # Processa Atividade 1
    try:
        df1 = pd.read_csv(ATIV1_CSV)
        plot_activity1_results(df1)
    except FileNotFoundError:
        print(f"ERRO: Arquivo '{ATIV1_CSV}' não encontrado. Execute o script 'gerar_dados.py' primeiro.", file=sys.stderr)

    # Processa Atividade 2
    try:
        df2 = pd.read_csv(ATIV2_CSV)
        plot_activity2_results(df2)
    except FileNotFoundError:
        print(f"ERRO: Arquivo '{ATIV2_CSV}' não encontrado. Execute o script 'gerar_dados.py' primeiro.", file=sys.stderr)

    print(f"\nGráficos gerados com sucesso na pasta '{OUTPUT_DIR}'!")

if __name__ == "__main__":
    main()
