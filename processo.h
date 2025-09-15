#ifndef PROCESSO_H
#define PROCESSO_H

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

#endif