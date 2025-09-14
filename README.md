📊 Processador de Dados do DataJUD
Este é um programa em C desenvolvido para processar arquivos CSV do sistema DataJud do Poder Judiciário brasileiro. O programa realiza análises estatísticas sobre processos judiciais e calcula métricas importantes como o cumprimento da Meta 1 do CNJ.

🎯 O que o programa faz
O programa processa um arquivo CSV contendo dados de processos judiciais e responde às seguintes questões:

Contagem total de processos no arquivo

Busca do último órgão julgador por ID do processo

Identificação do processo mais antigo pela data de recebimento

Contagem de processos por tema (violência doméstica, feminicídio, ambiental, etc.)

Cálculo de dias entre recebimento e resolução do processo

Cálculo do percentual de cumprimento da Meta 1 do CNJ

Geração de arquivo CSV com processos julgados

🏗️ Estrutura do Código
📦 TAD (Tipo Abstrato de Dados) - Processo
c
typedef struct {
    char id_processo[50];
    char numero_sigilo[50];
    char sigla_grau[10];
    // ... outros campos
    int flag_violencia_domestica;
    int flag_feminicidio;
    // ... outras flags
    int cnm1;
    int julgadom1;
    // ... outros campos da Meta 1
} Processo;
O que é isso?
Uma struct é como uma "ficha" que agrupa todos os dados de um processo. Cada campo armazena uma informação específica:

char[]: campos de texto (strings)

int: campos numéricos e flags (0 ou 1)

🔧 Funções Principais
1. ler_arquivo_csv()
O que faz: Lê o arquivo CSV e transforma em um array de processos
Como funciona:

Abre o arquivo com fopen()

Pula a primeira linha (cabeçalho)

Lê cada linha com fgets()

Divide a linha em partes usando strtok() (separador ";")

Converte texto em números com atoi()

Aloca memória dinamicamente conforme necessário

2. contar_processos()
O que faz: Retorna o total de processos lidos
Simplesmente: Retorna o contador total

3. buscar_ultimo_oj()
O que faz: Encontra o último órgão julgador de um processo específico
Como: Procura pelo ID do processo no array e retorna o campo correspondente

4. encontrar_processo_mais_antigo()
O que faz: Encontra o processo com a data de recebimento mais antiga
Como: Compara as datas de todos os processos usando strcmp()

5. contar_flag()
O que faz: Conta quantos processos têm cada flag temática ativada
Como: Verifica cada processo e incrementa o contador se a flag for 1 (TRUE)

6. calcular_dias_entre_datas()
O que faz: Calcula a diferença em dias entre duas datas
Como: Converte as datas para formato tm e usa difftime()

7. calcular_meta1()
O que faz: Calcula o percentual de cumprimento da Meta 1 do CNJ
Fórmula: (julgadom1 / (cnm1 + desm1 - susm1)) * 100

8. gerar_csv_julgados()
O que faz: Cria um novo arquivo CSV apenas com processos julgados
Como: Abre um novo arquivo e escreve apenas os processos onde julgadom1 > 0

🚀 Como Executar
Pré-requisitos
Compilador GCC instalado

Arquivo TJDFT_filtrado.csv na mesma pasta do programa

Passo a Passo
Salve o código em um arquivo chamado processador_datajud.c

Compile o programa (no terminal):

bash
gcc -o processador processador_datajud.c
Execute o programa:

bash
./processador
Verifique os resultados:

Os resultados aparecerão no terminal

Um arquivo processos_julgados.csv será criado

📋 Exemplo de Saída
text
=== PROCESSADOR DE DADOS DO DATAJUD ===

Processando 15000 processos...

1. Numero de processos: 15000
2. id_ultimo_oj do processo PROC-123: OJ-456
3. id_processo mais antigo: PROC-001
4. Processos com violencia domestica: 250
5. Processos com feminicidio: 120
...
11. Percentual de cumprimento da Meta 1: 105.75%
12. Gerando arquivo CSV de processos julgados...
    Arquivo 'processos_julgados.csv' gerado!
🛠️ Conceitos de Programação Usados
Alocação Dinâmica de Memória
c
Processo* processos = malloc(capacidade * sizeof(Processo));
Processo* temp = realloc(processos, nova_capacidade * sizeof(Processo));
Por que é importante: Permite lidar com arquivos grandes sem limite fixo

Manipulação de Strings
c
strcpy(destino, origem);      // Copia strings
strcmp(str1, str2);           // Compara strings
strtok(string, ";");          // Divide strings
Usado para: Processar o formato CSV

Estruturas de Dados
c
struct tm {                   // Estrutura para datas
    int tm_year;
    int tm_mon;
    int tm_mday;
};
Usado para: Manipulação de datas

Arquivos
c
FILE* arquivo = fopen("arquivo.csv", "r");  // Abre para leitura
FILE* saida = fopen("saida.csv", "w");      // Abre para escrita
Usado para: Ler entrada e gerar saída

⚠️ Possíveis Erros e Soluções
"Arquivo não encontrado"

Verifique se TJDFT_filtrado.csv está na pasta correta

"Erro ao alocar memória"

O arquivo pode ser muito grande para a memória disponível

Datas em formato inválido

O programa espera datas no formato "YYYY-MM-DD"

📊 Formatos Esperados
Entrada (CSV)
text
id_processo;numero_sigilo;sigla_grau;...;flag_violencia_domestica;...;julgadom1
PROC-001;12345;G1;...;1;...;5
PROC-002;67890;G2;...;0;...;0
Saída (Terminal)
text
Estatísticas calculadas e exibidas no terminal
Saída (Arquivo)
text
processos_julgados.csv - Contém apenas processos com julgadom1 > 0
🎓 Para Estudantes Iniciantes
Dicas de Aprendizado:
Comece entendendo a estrutura Processo - é o coração do programa

Teste cada função separadamente para entender o que faz

Use printf() para debuggar e ver o que está acontecendo

Modifique pequenas partes e veja como afeta o resultado

Próximos Passos:
Adicione mais estatísticas

Melhore o tratamento de erros

Adicione interface gráfica

Otimize o desempenho para arquivos muito grandes

Este programa é um excelente exemplo de como processar dados reais usando conceitos fundamentais de programação em C! 🚀