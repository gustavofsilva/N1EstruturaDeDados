#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processo.h"


int main() {
    int total_processos = 0;
    Processo* processos = NULL;
    
    printf("=== PROCESSADOR DE DADOS DO DATAJUD ===\n\n");
    
    // Ler arquivo CSV
    processos = ler_arquivo_csv("TJDFT_filtrado.csv", &total_processos);
    
    if (processos == NULL || total_processos == 0) {
        printf("Erro ao ler arquivo ou arquivo vazio.\n");
        return 1;
    }
    
    printf("Processando %d processos...\n\n", total_processos);
    
    // Resolver as questões
    printf("1. Numero de processos: %d\n", contar_processos(processos, total_processos));
    
    // Para a questão 2, vamos usar o primeiro processo como exemplo
    if (total_processos > 0) {
        printf("2. id_ultimo_oj do processo %s: %s\n", 
               processos[0].id_processo, 
               buscar_ultimo_oj(processos, total_processos, processos[0].id_processo));
    }
    
    printf("3. id_processo mais antigo: %s\n", 
           encontrar_processo_mais_antigo(processos, total_processos));
    
    printf("4. Processos com violencia domestica: %d\n", 
           contar_flag(processos, total_processos, "violencia_domestica"));
    printf("5. Processos com feminicidio: %d\n", 
           contar_flag(processos, total_processos, "feminicidio"));
    printf("6. Processos ambientais: %d\n", 
           contar_flag(processos, total_processos, "ambiental"));
    printf("7. Processos quilombolas: %d\n", 
           contar_flag(processos, total_processos, "quilombolas"));
    printf("8. Processos indigenas: %d\n", 
           contar_flag(processos, total_processos, "indigenas"));
    printf("9. Processos infancia/juventude: %d\n", 
           contar_flag(processos, total_processos, "infancia"));
    
    // Para a questão 10, vamos calcular para o primeiro processo com ambas as datas
    if (total_processos > 0 && strlen(processos[0].dt_recebimento) > 0 && 
        strlen(processos[0].dt_resolvido) > 0) {
        printf("10. Dias entre recebimento e resolucao: %d\n", 
               calcular_dias_entre_datas(processos[0].dt_recebimento, processos[0].dt_resolvido));
    } else {
        printf("10. Dias entre recebimento e resolucao: Dados insuficientes\n");
    }
    
    printf("11. Percentual de cumprimento da Meta 1: %.2f%%\n", 
           calcular_meta1(processos, total_processos));
    
    printf("12. Gerando arquivo CSV de processos julgados...\n");
    gerar_csv_julgados(processos, total_processos);
    printf("    Arquivo 'processos_julgados.csv' gerado!\n");
    
    // Liberar memória
    liberar_processos(processos);
    
    return 0;
}