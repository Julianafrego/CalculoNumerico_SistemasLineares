#include <stdio.h>   // Biblioteca para entrada e saída padrão
#include <stdlib.h>  // Biblioteca para manipulação de arquivos e memória
#include <time.h>    // Biblioteca para medição de tempo

int main() {
    int N;
    FILE *arquivo;

    // Abre o arquivo "dados.txt" no modo leitura
    arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1; // Encerra o programa em caso de erro na abertura
    }

    // Leitura da ordem da matriz (N)
    fscanf(arquivo, "%d", &N);

    // Declaração das matrizes e vetores
    double A[N][N];  // Matriz dos coeficientes
    double b[N];     // Vetor dos termos independentes
    double x[N];     // Vetor solução

    // Leitura da matriz A e vetor b do arquivo
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(arquivo, "%lf", &A[i][j]);
        }
        fscanf(arquivo, "%lf", &b[i]);
    }

    fclose(arquivo); // Fecha o arquivo após a leitura

    // Impressão do sistema lido (matriz A e vetor b)
    printf("\nMatriz dos coeficientes (A) e vetor dos termos independentes (b):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%8.3lf ", A[i][j]);
        }
        printf("| %8.3lf\n", b[i]);
    }

    // Medição do tempo de execução
    clock_t inicio = clock();

    // Etapa 1: Eliminação de Gauss
    for (int k = 0; k < N - 1; k++) {
        // Verifica se o pivô é zero (método sem pivotamento pode falhar)
        if (A[k][k] == 0) {
            printf("Erro: elemento pivô zero. O método pode falhar sem pivotamento.\n");
            return 1;
        }

        // Para cada linha abaixo do pivô
        for (int i = k + 1; i < N; i++) {
            double fator = A[i][k] / A[k][k]; // Calcula o fator multiplicador

            // Elimina a variável da coluna k
            for (int j = k; j < N; j++) {
                A[i][j] -= fator * A[k][j];
            }

            // Atualiza o vetor b
            b[i] -= fator * b[k];
        }
    }
    // Etapa 2: Substituição Regressiva

    for (int i = N - 1; i >= 0; i--) {
        double soma = 0;
        // Soma os produtos das variáveis já conhecidas
        for (int j = i + 1; j < N; j++) {
            soma += A[i][j] * x[j];
        }
        // Calcula o valor da variável atual
        x[i] = (b[i] - soma) / A[i][i];
    }

    clock_t fim = clock();
    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Impressão da solução
    printf("\nSolução do sistema:\n");
    for (int i = 0; i < N; i++) {
        printf("x[%d] = %.6lf\n", i + 1, x[i]);
    }

    // Tempo de execução
    printf("\nTempo de execução: %.6lf segundos\n", tempo_execucao);

    return 0; // Fim do programa
}

