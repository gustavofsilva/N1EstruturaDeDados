#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINHA 1024

// TAD Processo
typedef struct {
    char id_processo[50];
    char numero_sigilo[50];
    char sigla_grau[10];
    char procedimento[100];
    char ramo_justica[10];
    char sigla_tribunal[10];
    char id_tribunal[10];
    char recurso[10];
    char id_ultimo_oj[50];
    char dt_recebimento[20];
    char id_ultima_classe[50];
    int flag_violencia_domestica;
    int flag_feminicidio;
    int flag_ambiental;
    int flag_quilombolas;
    int flag_indigenas;
    int flag_infancia;
    char decisao[20];
    char dt_resolvido[20];
    int cnm1;
    int primeirasentm1;
    int baixm1;
    int decm1;
    int mpum1;
    int julgadom1;
    int desm1;
    int susm1;
} Processo;

// Funções para manipulação do arquivo
Processo* ler_arquivo_csv(const char* filename, int* total_processos);
void liberar_processos(Processo* processos);

// Funções para as questões
int contar_processos(Processo* processos, int total);
char* buscar_ultimo_oj(Processo* processos, int total, const char* id_processo);
char* encontrar_processo_mais_antigo(Processo* processos, int total);
int contar_flag(Processo* processos, int total, const char* flag_nome);
int calcular_dias_entre_datas(const char* data1, const char* data2);
float calcular_meta1(Processo* processos, int total);
void gerar_csv_julgados(Processo* processos, int total);

// Funções auxiliares
int parse_int(const char* str);
void parse_flags(Processo* p, const char* flag_violencia, const char* flag_feminicidio, 
                const char* flag_ambiental, const char* flag_quilombolas, 
                const char* flag_indigenas, const char* flag_infancia);

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

Processo* ler_arquivo_csv(const char* filename, int* total_processos) {
    FILE* arquivo = fopen(filename, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo %s\n", filename);
        return NULL;
    }
    
    char linha[MAX_LINHA];
    Processo* processos = NULL;
    int capacidade = 1000; // Capacidade inicial
    int count = 0;
    
    // Alocar memória inicial
    processos = malloc(capacidade * sizeof(Processo));
    if (processos == NULL) {
        printf("Erro ao alocar memoria\n");
        fclose(arquivo);
        return NULL;
    }
    
    // Pular cabeçalho
    fgets(linha, MAX_LINHA, arquivo);
    
    while (fgets(linha, MAX_LINHA, arquivo)) {
        // Remover quebra de linha
        linha[strcspn(linha, "\n")] = 0;
        
        // Verificar se precisa realocar mais memória
        if (count >= capacidade) {
            capacidade *= 2; // Dobrar a capacidade
            Processo* temp = realloc(processos, capacidade * sizeof(Processo));
            if (temp == NULL) {
                printf("Erro ao realocar memoria\n");
                free(processos);
                fclose(arquivo);
                return NULL;
            }
            processos = temp;
        }
        
        Processo p;
        char* token;
        int campo = 0;
        
        // Inicializar a estrutura
        memset(&p, 0, sizeof(Processo));
        
        token = strtok(linha, ";");
        while (token != NULL && campo < 27) {
            switch (campo) {
                case 0: strncpy(p.id_processo, token, sizeof(p.id_processo)-1); break;
                case 1: strncpy(p.numero_sigilo, token, sizeof(p.numero_sigilo)-1); break;
                case 2: strncpy(p.sigla_grau, token, sizeof(p.sigla_grau)-1); break;
                case 3: strncpy(p.procedimento, token, sizeof(p.procedimento)-1); break;
                case 4: strncpy(p.ramo_justica, token, sizeof(p.ramo_justica)-1); break;
                case 5: strncpy(p.sigla_tribunal, token, sizeof(p.sigla_tribunal)-1); break;
                case 6: strncpy(p.id_tribunal, token, sizeof(p.id_tribunal)-1); break;
                case 7: strncpy(p.recurso, token, sizeof(p.recurso)-1); break;
                case 8: strncpy(p.id_ultimo_oj, token, sizeof(p.id_ultimo_oj)-1); break;
                case 9: strncpy(p.dt_recebimento, token, sizeof(p.dt_recebimento)-1); break;
                case 10: strncpy(p.id_ultima_classe, token, sizeof(p.id_ultima_classe)-1); break;
                case 11: p.flag_violencia_domestica = parse_int(token); break;
                case 12: p.flag_feminicidio = parse_int(token); break;
                case 13: p.flag_ambiental = parse_int(token); break;
                case 14: p.flag_quilombolas = parse_int(token); break;
                case 15: p.flag_indigenas = parse_int(token); break;
                case 16: p.flag_infancia = parse_int(token); break;
                case 17: strncpy(p.decisao, token, sizeof(p.decisao)-1); break;
                case 18: strncpy(p.dt_resolvido, token, sizeof(p.dt_resolvido)-1); break;
                case 19: p.cnm1 = parse_int(token); break;
                case 20: p.primeirasentm1 = parse_int(token); break;
                case 21: p.baixm1 = parse_int(token); break;
                case 22: p.decm1 = parse_int(token); break;
                case 23: p.mpum1 = parse_int(token); break;
                case 24: p.julgadom1 = parse_int(token); break;
                case 25: p.desm1 = parse_int(token); break;
                case 26: p.susm1 = parse_int(token); break;
            }
            campo++;
            token = strtok(NULL, ";");
        }
        
        processos[count] = p;
        count++;
    }
    
    fclose(arquivo);
    *total_processos = count;
    
    // Reduzir para o tamanho exato se necessário
    if (count < capacidade) {
        Processo* temp = realloc(processos, count * sizeof(Processo));
        if (temp != NULL) {
            processos = temp;
        }
    }
    
    return processos;
}

void liberar_processos(Processo* processos) {
    free(processos);
}

int contar_processos(Processo* processos, int total) {
    return total;
}

char* buscar_ultimo_oj(Processo* processos, int total, const char* id_processo) {
    for (int i = 0; i < total; i++) {
        if (strcmp(processos[i].id_processo, id_processo) == 0) {
            return processos[i].id_ultimo_oj;
        }
    }
    return "Nao encontrado";
}

char* encontrar_processo_mais_antigo(Processo* processos, int total) {
    if (total == 0) return "Nenhum processo";
    
    int mais_antigo_idx = 0;
    for (int i = 1; i < total; i++) {
        if (strcmp(processos[i].dt_recebimento, processos[mais_antigo_idx].dt_recebimento) < 0) {
            mais_antigo_idx = i;
        }
    }
    return processos[mais_antigo_idx].id_processo;
}

int contar_flag(Processo* processos, int total, const char* flag_nome) {
    int count = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(flag_nome, "violencia_domestica") == 0 && processos[i].flag_violencia_domestica) count++;
        else if (strcmp(flag_nome, "feminicidio") == 0 && processos[i].flag_feminicidio) count++;
        else if (strcmp(flag_nome, "ambiental") == 0 && processos[i].flag_ambiental) count++;
        else if (strcmp(flag_nome, "quilombolas") == 0 && processos[i].flag_quilombolas) count++;
        else if (strcmp(flag_nome, "indigenas") == 0 && processos[i].flag_indigenas) count++;
        else if (strcmp(flag_nome, "infancia") == 0 && processos[i].flag_infancia) count++;
    }
    return count;
}

int calcular_dias_entre_datas(const char* data1, const char* data2) {
    // Formato esperado: YYYY-MM-DD
    struct tm tm1 = {0}, tm2 = {0};
    
    if (strlen(data1) == 0 || strlen(data2) == 0) {
        return 0;
    }
    
    sscanf(data1, "%d-%d-%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
    sscanf(data2, "%d-%d-%d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday);
    
    tm1.tm_year -= 1900;
    tm1.tm_mon -= 1;
    tm2.tm_year -= 1900;
    tm2.tm_mon -= 1;
    
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    
    if (time1 == -1 || time2 == -1) {
        return 0;
    }
    
    double diferenca = difftime(time2, time1);
    return (int)(diferenca / (60 * 60 * 24));
}

float calcular_meta1(Processo* processos, int total) {
    int total_cnm1 = 0, total_desm1 = 0, total_susm1 = 0, total_julgadom1 = 0;
    
    for (int i = 0; i < total; i++) {
        total_cnm1 += processos[i].cnm1;
        total_desm1 += processos[i].desm1;
        total_susm1 += processos[i].susm1;
        total_julgadom1 += processos[i].julgadom1;
    }
    
    int denominador = total_cnm1 + total_desm1 - total_susm1;
    if (denominador == 0) {
        return 0.0;
    }
    
    return ((float)total_julgadom1 / denominador) * 100;
}

void gerar_csv_julgados(Processo* processos, int total) {
    FILE* saida = fopen("processos_julgados.csv", "w");
    if (saida == NULL) {
        printf("Erro ao criar arquivo de saida\n");
        return;
    }
    
    // Cabeçalho
    fprintf(saida, "id_processo;numero_sigilo;sigla_grau;procedimento;ramo_justica;");
    fprintf(saida, "sigla_tribunal;id_tribunal;recurso;id_ultimo_oj;dt_recebimento;");
    fprintf(saida, "id_ultima_classe;julgadom1\n");
    
    // Dados
    for (int i = 0; i < total; i++) {
        if (processos[i].julgadom1 > 0) {
            fprintf(saida, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%d\n",
                   processos[i].id_processo,
                   processos[i].numero_sigilo,
                   processos[i].sigla_grau,
                   processos[i].procedimento,
                   processos[i].ramo_justica,
                   processos[i].sigla_tribunal,
                   processos[i].id_tribunal,
                   processos[i].recurso,
                   processos[i].id_ultimo_oj,
                   processos[i].dt_recebimento,
                   processos[i].id_ultima_classe,
                   processos[i].julgadom1);
        }
    }
    
    fclose(saida);
}

int parse_int(const char* str) {
    if (str == NULL || strlen(str) == 0) return 0;
    return atoi(str);
}