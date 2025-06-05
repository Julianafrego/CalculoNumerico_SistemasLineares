#include <stdio.h>   // Biblioteca padrão de entrada e saída
#include <math.h>    // Biblioteca para funções matemáticas, como fabs (valor absoluto)
#include <stdlib.h>  // Biblioteca padrão, usada para manipulação de arquivos, memória, etc.
#include <time.h>    // Biblioteca usada para medir o tempo de execução

#define TOL 0.0001   // Definindo a tolerância para critério de parada (critério de erro)
#define MAX_IT 1000  // Definindo o número máximo de iterações permitidas

int main() {
    int N; // Ordem da matriz (será lida do arquivo)

    FILE *arquivo; // Ponteiro para arquivo
    arquivo = fopen("dados.txt", "r"); // Abre o arquivo "dados.txt" no modo leitura
    // Complexidade: O(1) (abertura de arquivo)

    if (arquivo == NULL) { // Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo.\n");
        return 1; // Encerra o programa caso haja erro
    }

    fscanf(arquivo, "%d", &N); // Lê a ordem da matriz do arquivo
    // Complexidade: O(1)

    // Declaração das matrizes e vetores dinamicamente baseados em N
    double A[N][N];   // Matriz dos coeficientes
    double b[N];      // Vetor dos termos independentes
    double x[N];      // Vetor da aproximação atual
    double x_new[N];  // Vetor da próxima aproximação

    // Leitura da matriz A e do vetor b
    for (int i = 0; i < N; i++) {       // Loop externo - percorre linhas
        for (int j = 0; j < N; j++) {   // Loop interno - percorre colunas
            fscanf(arquivo, "%lf", &A[i][j]); // Lê cada elemento da matriz
        }
        fscanf(arquivo, "%lf", &b[i]);  // Lê cada elemento do vetor b
        x[i] = 0;                       // Inicializa o vetor de aproximação com zero
    }
    // Complexidade desse bloco: O(N²) (leitura da matriz) + O(N) (vetor b e inicialização)

    fclose(arquivo); // Fecha o arquivo
    // Complexidade: O(1)

    // Exibe a matriz A e vetor b para conferência
    printf("\nMatriz dos coeficientes (A) e vetor dos termos independentes (b):\n");
    for (int i = 0; i < N; i++) {       // Loop linhas
        for (int j = 0; j < N; j++) {   // Loop colunas
            printf("%8.3lf ", A[i][j]); // Exibe elemento da matriz
        }
        printf("| %8.3lf\n", b[i]);     // Exibe o termo independente
    }
    // Complexidade: O(N²) para impressão da matriz

    // Declarações auxiliares para o método
    int iter;           // Contador de iterações
    double erro, soma;  // Variáveis para controle de erro e soma das equações

    // Variáveis para medir tempo
    clock_t inicio, fim;
    double tempo_execucao;

    inicio = clock(); // Marca o início da medição do tempo
    // Complexidade: O(1)

    printf("\nIniciando iteracoes...\n");

    // Loop principal do método de Gauss-Jacobi
    for (iter = 1; iter <= MAX_IT; iter++) { // Máximo de MAX_IT iterações
        erro = 0.0;                          // Reinicia o erro em cada iteração

        for (int i = 0; i < N; i++) {         // Loop sobre cada variável
            soma = b[i];                      // Inicializa a soma com o termo independente

            for (int j = 0; j < N; j++) {     // Loop sobre os coeficientes da linha
                if (j != i) {                 // Evita usar o coeficiente da diagonal
                    soma -= A[i][j] * x[j];   // Subtrai os termos conhecidos
                }
            }
            // Complexidade do loop interno: O(N)

            x_new[i] = soma / A[i][i];        // Calcula a nova aproximação para x[i]
            erro += fabs(x_new[i] - x[i]);    // Soma o erro absoluto dessa variável
        }
        // Complexidade do loop externo de variáveis: O(N²) por iteração

        // Atualiza as aproximações atuais
        for (int i = 0; i < N; i++) {
            x[i] = x_new[i]; // Atualiza o vetor de aproximação
        }
        // Complexidade: O(N)

        // Exibe os valores da iteração atual
        printf("Iteracao %d: ", iter);
        for (int i = 0; i < N; i++) {
            printf("%.6lf ", x[i]);
        }
        printf("\n");
        // Complexidade: O(N) para impressão

        // Verifica critério de parada baseado na tolerância
        if (erro < TOL) {
            printf("\nConvergencia atingida apos %d iteracoes.\n", iter);
            break; // Sai do loop se convergiu
        }
    }
    // Complexidade total do laço de iterações: O(MAX_IT * N²)

    fim = clock(); // Marca o fim do tempo
    // Complexidade: O(1)

    // Calcula o tempo de execução em segundos
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    // Complexidade: O(1)

    // Caso não tenha convergido dentro do limite de iterações
    if (iter > MAX_IT) {
        printf("\nNumero maximo de iteracoes atingido sem convergencia.\n");
    }

    // Exibe a solução final aproximada
    printf("\nSolucao aproximada:\n");
    for (int i = 0; i < N; i++) {
        printf("x[%d] = %.6lf\n", i + 1, x[i]);
    }
    // Complexidade: O(N)

    // Exibe o tempo de execução do processo
    printf("\nTempo de execucao durante a convergencia: %.6lf segundos\n", tempo_execucao);

    return 0; // Fim do programa
}