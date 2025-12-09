import csv
import subprocess
import re
import os
import sys
import statistics
from typing import List, Dict

NUM_AVERAGE_RUNS = 3 

ATIV1_SOURCE = "1.c"
ATIV1_CSV_OUTPUT = "ativ1.csv"
ATIV1_PARAMS = {
    'N': [512, 1024, 2048, 4096],
    'REPEAT': [20],
    'STRIDE': [1, 2, 4, 8, 16, 32],
    'MODE': [0, 1, 2],
    'OPTIMIZATION': ['-O0', '-O2']
}

ATIV2_SOURCE = "2.c"
ATIV2_CSV_OUTPUT = "ativ2.csv"
ATIV2_PARAMS = {
    'mode': ['strong', 'weak'],
    'N0': [1048576, 2097152],
    # 1, 2, 4, 8, 16 threads
    'MAX_POW_THREADS': [4],
    'REPEAT': [2],
    'WORK': [64]
}


def compile_code(source_file: str, output_name: str, flags: List[str] = []):
    cmd = ["gcc", source_file, "-o", output_name, "-lm"] + flags
    print(f"Compilando: {' '.join(cmd)}")
    try:
        subprocess.run(cmd, check=True, capture_output=True, text=True)
    except subprocess.CalledProcessError as e:
        print(f"ERRO na compilação de {source_file} com flags {flags}:")
        print(e.stderr)
        sys.exit(1)

def run_activity1():
    print("\n--- Iniciando Atividade 01 (com cálculo de média) ---")
    
    header = ['N', 'REPEAT', 'STRIDE', 'MODE', 'Optimization', 'Avg_Time_s', 'Std_Dev_s']
    
    with open(ATIV1_CSV_OUTPUT, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(header)

        for opt_level in ATIV1_PARAMS['OPTIMIZATION']:
            executable = f"exe01_{opt_level.replace('-', '')}"
            compile_code(ATIV1_SOURCE, executable, [opt_level])

            for n in ATIV1_PARAMS['N']:
                for repeat in ATIV1_PARAMS['REPEAT']:
                    for stride in ATIV1_PARAMS['STRIDE']:
                        for mode in ATIV1_PARAMS['MODE']:
                            cmd = [f"./{executable}", str(n), str(repeat), str(stride), str(mode)]
                            print(f"Avaliando configuração: {' '.join(cmd)}")
                            
                            execution_times = []
                            for i in range(NUM_AVERAGE_RUNS):
                                try:
                                    print(f"  -> Execução {i+1}/{NUM_AVERAGE_RUNS}...")
                                    result = subprocess.run(cmd, check=True, capture_output=True, text=True, timeout=600)
                                    match = re.search(r"Tempo\(s\):\s*([0-9.]+)", result.stdout)
                                    if match:
                                        execution_times.append(float(match.group(1)))
                                except subprocess.CalledProcessError as e:
                                    print(f"  -> ERRO ao executar: {e.stderr}")
                                except subprocess.TimeoutExpired:
                                    print("  -> ERRO: O comando demorou demais e foi interrompido.")

                            if len(execution_times) > 0:
                                avg_time = statistics.mean(execution_times)
                                std_dev = statistics.stdev(execution_times) if len(execution_times) > 1 else 0.0
                                print(f"  -> MÉDIA CALCULADA: {avg_time:.6f}s (desvio padrão: {std_dev:.6f}s)")
                                writer.writerow([n, repeat, stride, mode, opt_level, avg_time, std_dev])
                            else:
                                print(f"  -> AVISO: Nenhuma execução bem-sucedida para esta configuração. Pulando.")
                                
    print(f"--- Atividade 01 concluída. Resultados salvos em {ATIV1_CSV_OUTPUT} ---")

def run_activity2():
    print("\n--- Iniciando Atividade 02 (com cálculo de média) ---")
    
    header = [
        'scaling_mode', 'N0_base', 'work_load', 'threads', 'N', 
        'avg_t_best_s', 'stdev_t_best_s', 'avg_speedup', 'stdev_speedup', 
        'avg_efficiency', 'stdev_efficiency'
    ]
    
    executable = "exe02_ativ2"
    compile_code(ATIV2_SOURCE, executable, ["-O2", "-fopenmp"])

    with open(ATIV2_CSV_OUTPUT, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(header)
        
        for mode in ATIV2_PARAMS['mode']:
            for n0 in ATIV2_PARAMS['N0']:
                for max_pow in ATIV2_PARAMS['MAX_POW_THREADS']:
                    for repeat in ATIV2_PARAMS['REPEAT']:
                        for work in ATIV2_PARAMS['WORK']:
                            cmd = [f"./{executable}", mode, str(n0), str(max_pow), str(repeat), str(work)]
                            print(f"Avaliando configuração: {' '.join(cmd)}")

                            results_aggregator: Dict[int, List[List[float]]] = {}

                            for i in range(NUM_AVERAGE_RUNS):
                                try:
                                    print(f"  -> Execução {i+1}/{NUM_AVERAGE_RUNS}...")
                                    result = subprocess.run(cmd, check=True, capture_output=True, text=True, timeout=600)
                                    
                                    for line in result.stdout.strip().split('\n'):
                                        if line.startswith('#'): continue
                                        
                                        values = line.split()
                                        if len(values) == 7:
                                            threads = int(values[0])
                                            metrics = [float(v) for v in [values[2], values[5], values[6]]] # t_best, speedup, efficiency
                                            
                                            if threads not in results_aggregator:
                                                results_aggregator[threads] = []
                                            results_aggregator[threads].append(metrics)
                                except subprocess.CalledProcessError as e:
                                    print(f"  -> ERRO ao executar: {e.stderr}")
                                except subprocess.TimeoutExpired:
                                    print("  -> ERRO: O comando demorou demais e foi interrompido.")
                            
                            print("  -> CÁLCULO DAS MÉDIAS:")
                            for threads, collected_runs in sorted(results_aggregator.items()):
                                if not collected_runs: continue

                                # Transpõe a lista de listas para calcular a média por coluna
                                # collected_runs = [[t1, s1, e1], [t2, s2, e2], ...]
                                # transposed = [(t1, t2, ...), (s1, s2, ...), (e1, e2, ...)]
                                transposed = list(zip(*collected_runs))
                                avg_metrics = [statistics.mean(col) for col in transposed]
                                stdev_metrics = [statistics.stdev(col) if len(col) > 1 else 0.0 for col in transposed]
                                
                                N_val = int(subprocess.run(cmd, check=True, capture_output=True, text=True).stdout.strip().split('\n')[-1].split()[1])
                                
                                writer.writerow([
                                    mode, n0, work, threads, N_val,
                                    avg_metrics[0], stdev_metrics[0], # avg_t_best, stdev_t_best
                                    avg_metrics[1], stdev_metrics[1], # avg_speedup, stdev_speedup
                                    avg_metrics[2], stdev_metrics[2]  # avg_efficiency, stdev_efficiency
                                ])
                                print(f"    - Threads={threads}: Média t_best={avg_metrics[0]:.6f}s")

    print(f"--- Atividade 02 concluída. Resultados salvos em {ATIV2_CSV_OUTPUT} ---")

if __name__ == "__main__":
    if not os.path.exists(ATIV1_SOURCE) or not os.path.exists(ATIV2_SOURCE):
        print("ERRO: Certifique-se que os arquivos 'exe02_ativ1.c' e 'exe02_ativ2.c' estão no mesmo diretório.")
        sys.exit(1)
        
    run_activity1()
    run_activity2()
    print("\nTodos os testes foram concluídos!")
