# 📊 Processador de Dados do DataJUD - Guia Completo

Este repositório contém um programa em linguagem C projetado para ler, processar e analisar dados de processos judiciais, originados do [DataJud](https://www.cnj.jus.br/tecnologia-da-informacao-e-comunicacao/datajud/), o banco de dados do Poder Judiciário brasileiro.

Este guia foi criado para ser **extremamente detalhado e amigável para iniciantes**, explicando cada parte do projeto, desde o seu propósito até a última linha de código.

## 🎯 1. O que o Projeto Faz?

O objetivo principal deste programa é realizar uma análise estatística em um arquivo de processos judiciais no formato `.csv`. Ele responde a perguntas específicas sobre os dados, como:

1.  **Contagem Total:** Quantos processos existem no arquivo?
2.  **Busca Específica:** Qual foi o último órgão que julgou um determinado processo?
3.  **Análise Temporal:** Qual é o processo mais antigo?
4.  **Mapeamento de Temas:** Quantos processos são sobre violência doméstica, feminicídio, meio ambiente, etc.?
5.  **Cálculo de Duração:** Qual o tempo (em dias) entre o recebimento e a resolução de um processo?
6.  **Análise de Metas:** Qual o percentual de cumprimento da **Meta 1 do CNJ**?
7.  **Geração de Relatório:** Cria um novo arquivo `.csv` contendo apenas os processos que foram julgados.

### O que é a Meta 1 do CNJ?

A **Meta 1 do Conselho Nacional de Justiça (CNJ)** é um objetivo anual para os tribunais brasileiros. Ela busca garantir que os tribunais julguem uma quantidade de processos maior do que a quantidade de casos novos que chegam a cada ano. O cálculo é uma forma de medir a eficiência e a vazão do sistema judiciário.

---

## 🚀 2. Como Executar o Programa

Para compilar e executar este projeto, você precisará de um compilador C (como o GCC) e do arquivo de dados.

### Pré-requisitos

*   **Compilador GCC:** Se você usa Linux ou macOS, ele geralmente já vem instalado. No Windows, você pode instalar o [MinGW](https://www.mingw-w64.org/).
*   **Arquivo de Dados:** O programa espera um arquivo chamado `TJDFT_filtrado.csv` na mesma pasta onde o executável será criado.

### Passo a Passo para Execução

1.  **Clone ou Baixe o Repositório:**
    Salve os arquivos `main.c`, `processo.c`, `processo.h` e `TJDFT_filtrado.csv` na mesma pasta.

2.  **Abra o Terminal:**
    Navegue até a pasta onde você salvou os arquivos.

3.  **Compile o Código:**
    Execute o seguinte comando para compilar os arquivos `.c` e gerar um programa executável chamado `processador`:
    ```bash
    gcc main.c processo.c -o processador
    ```
    *   `gcc`: Invoca o compilador.
    *   `main.c processo.c`: São os arquivos de código-fonte que queremos compilar.
    *   `-o processador`: Indica que a saída (o programa compilado) deve se chamar `processador`.

4.  **Execute o Programa:**
    Após a compilação, um novo arquivo `processador` (ou `processador.exe` no Windows) aparecerá na pasta. Execute-o com:
    ```bash
    ./processador
    ```

5.  **Verifique os Resultados:**
    *   O terminal exibirá as estatísticas calculadas.
    *   Um novo arquivo, `processos_julgados.csv`, será criado na pasta.

### Exemplo de Saída no Terminal
```
=== PROCESSADOR DE DADOS DO DATAJUD ===

Processando 15000 processos...

1. Numero de processos: 15000
2. id_ultimo_oj do processo PROC-123: OJ-456
3. id_processo mais antigo: PROC-001
4. Processos com violencia domestica: 250
...
11. Percentual de cumprimento da Meta 1: 105.75%
12. Gerando arquivo CSV de processos julgados...
    Arquivo 'processos_julgados.csv' gerado!
```

---

## 🏗️ 3. Estrutura do Projeto

O código é modularizado para facilitar o entendimento e a manutenção. Ele é dividido em três arquivos principais:

### `processo.h` (Arquivo de Cabeçalho)

*   **O que faz?** Funciona como um "índice" ou "contrato". Ele declara a estrutura de dados `Processo` e os protótipos de todas as funções que manipulam esses dados.
*   **Por que usar?** Ao incluir este arquivo em `main.c` e `processo.c`, garantimos que ambos "conheçam" a estrutura `Processo` e as funções disponíveis, permitindo que o compilador verifique se tudo está sendo usado corretamente.

### `processo.c` (Arquivo de Implementação)

*   **O que faz?** Contém a "lógica pesada". É aqui que as funções declaradas em `processo.h` são de fato implementadas. A leitura do CSV, os cálculos e a geração do novo arquivo estão todos aqui.
*   **Por que usar?** Separa a implementação dos detalhes da sua utilização. O `main.c` não precisa saber *como* a Meta 1 é calculada, apenas que existe uma função `calcular_meta1()` que faz isso.

### `main.c` (Arquivo Principal)

*   **O que faz?** É o ponto de entrada do programa. Ele orquestra a execução:
    1.  Chama a função `ler_arquivo_csv()` para carregar os dados.
    2.  Chama as diversas funções de análise (`contar_processos`, `calcular_meta1`, etc.).
    3.  Imprime os resultados no terminal.
    4.  Chama `gerar_csv_julgados()` para criar o arquivo de saída.
    5.  Libera a memória alocada.
*   **Por que usar?** Mantém o fluxo principal do programa limpo e legível, delegando as tarefas complexas para as funções de `processo.c`.

---

## 🔬 4. Análise Detalhada do Código

Vamos mergulhar nos detalhes técnicos de cada parte do código.

### A Estrutura `Processo` (TAD)

O coração do programa é a `struct Processo`, definida em `processo.h`. Ela é um **Tipo Abstrato de Dados (TAD)**, o que significa que é uma estrutura de dados personalizada para representar uma entidade do mundo real — neste caso, um processo judicial.

```c
// processo.h

typedef struct {
    // Identificadores
    char id_processo[50];
    char numero_sigilo[50];
    char id_ultimo_oj[50];

    // Datas
    char dt_recebimento[20];
    char dt_resolvido[20];

    // Flags temáticas (0 para Falso, 1 para Verdadeiro)
    int flag_violencia_domestica;
    int flag_feminicidio;
    int flag_ambiental;
    // ... outras flags

    // Campos para cálculo da Meta 1
    int cnm1;         // Casos novos que entraram no ano
    int julgadom1;    // Processos julgados no ano
    int desm1;        // Processos desarquivados
    int susm1;        // Processos suspensos

    // Outros campos...
} Processo;
```

*   **`char[]`**: Usado para armazenar textos (strings), como IDs e datas.
*   **`int`**: Usado para números inteiros e "flags" (bandeiras), que marcam com `1` (verdadeiro) ou `0` (falso) se um processo pertence a um tema.

### Funções Principais (em `processo.c`)

#### `Processo* ler_arquivo_csv(const char* filename, int* total_processos)`

*   **O que faz:** Lê o arquivo `.csv` linha por linha e armazena os dados em um array dinâmico de `struct Processo`.
*   **Passo a Passo:**
    1.  Abre o arquivo com `fopen()`.
    2.  Aloca um bloco inicial de memória com `malloc()`.
    3.  Lê e ignora a primeira linha (cabeçalho) com `fgets()`.
    4.  Entra em um loop `while` para ler cada linha do arquivo.
    5.  A cada linha lida, usa `strtok()` para quebrar a string em "tokens" (pedaços), usando o ponto e vírgula (`;`) como delimitador.
    6.  Converte os tokens que são números de texto para `int` com `atoi()`.
    7.  Copia os valores para os campos da `struct Processo`.
    8.  Se o array de processos ficar cheio, ele **dobra de tamanho** usando `realloc()`, garantindo que o programa não quebre com arquivos grandes.
*   **Retorno:** Um ponteiro para o início do array de processos na memória. O número total de processos lidos é retornado através do ponteiro `total_processos`.

#### `void liberar_processos(Processo* processos)`

*   **O que faz:** Libera a memória alocada dinamicamente por `malloc`/`realloc`.
*   **Por que é crucial?** Evita vazamentos de memória (`memory leaks`). Se a memória não for liberada, o programa consumirá recursos desnecessariamente após o término.

#### `int contar_processos(...)`

*   **O que faz:** Simplesmente retorna o número total de processos lidos.

#### `char* buscar_ultimo_oj(...)`

*   **O que faz:** Percorre o array de processos até encontrar um com o `id_processo` correspondente e retorna o `id_ultimo_oj` dele.

#### `char* encontrar_processo_mais_antigo(...)`

*   **O que faz:** Compara a data de recebimento (`dt_recebimento`) de todos os processos usando `strcmp()` (que compara strings em ordem alfabética) para encontrar a mais antiga.

#### `int contar_flag(...)`

*   **O que faz:** Conta quantos processos têm uma determinada flag temática (ex: `flag_violencia_domestica`) com valor `1`.

#### `int calcular_dias_entre_datas(...)`

*   **O que faz:** Calcula a diferença em dias entre duas datas no formato "AAAA-MM-DD".
*   **Como funciona:**
    1.  Converte as strings de data para uma estrutura `struct tm`, que é padrão do C para tempo.
    2.  Usa `mktime()` para converter `struct tm` em `time_t` (um número que representa o tempo).
    3.  Usa `difftime()` para calcular a diferença em segundos entre os dois `time_t`.
    4.  Converte a diferença de segundos para dias.

#### `float calcular_meta1(...)`

*   **O que faz:** Calcula o percentual de cumprimento da Meta 1 do CNJ.
*   **Fórmula:** `(Total de Julgados / (Casos Novos + Desarquivados - Suspensos)) * 100`

#### `void gerar_csv_julgados(...)`

*   **O que faz:** Cria um novo arquivo chamado `processos_julgados.csv`.
*   **Como funciona:**
    1.  Abre o arquivo em modo de escrita (`"w"`) com `fopen()`.
    2.  Escreve o cabeçalho no novo arquivo com `fprintf()`.
    3.  Percorre o array de processos e, se um processo tiver `julgadom1 > 0`, escreve seus dados no arquivo.
    4.  Fecha o arquivo com `fclose()`.

---

## 💾 5. Formato dos Dados

### Arquivo de Entrada: `TJDFT_filtrado.csv`

O programa espera um arquivo `.csv` onde as colunas são separadas por ponto e vírgula (`;`). A ordem das colunas é fundamental.

**Exemplo de linha:**
```csv
id_processo;numero_sigilo;...;flag_violencia_domestica;...;julgadom1
PROC-001;12345;...;1;...;5
```

### Arquivo de Saída: `processos_julgados.csv`

O arquivo gerado contém um subconjunto dos processos originais, apenas aqueles que foram julgados (`julgadom1 > 0`).

**Exemplo de linha:**
```csv
id_processo;numero_sigilo;...;julgadom1
PROC-001;12345;...;5
```

---

## 🎓 6. Conceitos de Programação em C para Iniciantes

Este projeto é um excelente exemplo prático de conceitos fundamentais da linguagem C.

### `struct` (Estrutura)

Pense em uma `struct` como criar seu próprio tipo de "ficha de cadastro". Em vez de ter variáveis separadas para cada dado de um processo (um `char id[50]`, um `char data[20]`, etc.), você agrupa todas elas em um único tipo `Processo`.

### Ponteiros (`*`)

Um ponteiro é uma variável que armazena um **endereço de memória**.
*   `Processo* processos;` não armazena os processos em si, mas sim *onde* na memória o array de processos começa.
*   Eles são essenciais para a alocação dinâmica e para passar grandes volumes de dados para funções sem ter que copiar tudo.

### Alocação Dinâmica (`malloc`, `realloc`, `free`)

*   **`malloc`**: "Memory Allocate". Pede ao sistema operacional um bloco de memória de um tamanho específico. Usamos para criar o array de processos sem saber o tamanho exato do arquivo de antemão.
*   **`realloc`**: "Re-allocate". Redimensiona um bloco de memória já alocado. Usamos quando o array inicial fica pequeno demais.
*   **`free`**: Libera a memória que pedimos, devolvendo-a ao sistema operacional. É uma boa prática fundamental para evitar que seu programa consuma memória indefinidamente.

### Manipulação de Arquivos (`FILE*`, `fopen`, `fgets`, `fprintf`, `fclose`)

*   **`FILE*`**: Um ponteiro especial para manipular arquivos.
*   **`fopen("nome", "r")`**: Abre um arquivo. `"r"` para leitura (`read`), `"w"` para escrita (`write`).
*   **`fgets(...)`**: Lê uma linha inteira de um arquivo.
*   **`fprintf(...)`**: Escreve texto formatado em um arquivo (semelhante ao `printf` do terminal).
*   **`fclose(...)`**: Fecha o arquivo, salvando as alterações e liberando o recurso.

### Manipulação de Strings (`string.h`)

*   **`strtok(string, "delimitador")`**: "String Tokenizer". Usado para quebrar uma string em pedaços. É a principal ferramenta para processar o formato CSV.
*   **`strcpy(destino, origem)`**: "String Copy". Copia uma string para outra.
*   **`strcmp(str1, str2)`**: "String Compare". Compara duas strings. Retorna `0` se forem iguais.
*   **`strlen(str)`**: "String Length". Retorna o comprimento de uma string.

---

Este programa é um exemplo robusto de como a linguagem C pode ser usada para tarefas de processamento de dados do mundo real, combinando manipulação de baixo nível da memória com lógica de alto nível para análise de dados. 🚀
