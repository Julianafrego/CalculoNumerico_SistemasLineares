#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_ITER 1000 // Número máximo de iterações
#define EPSILON 0.05 // Tolerância de 


// Calcula a norma relativa ||x(k) - x(k-1)|| / ||x(k-1)||
// para verificar se o método de Gauss-Seidel está convergindo
double calcula_convergencia(int n, double *x, double *v) {
    double numerador = 0.0;
    double denominador = 0.0;
    for (int i = 0; i < n; i++) { //percorre vetor
        double diff = fabs(v[i] - x[i]); // diferença entre os valores de x e v, x consiste no valor atual e v no valor anterior
        if (diff > numerador)  // guarda a maior diferença  entre x e v, se for maior que o numerador atual, o numerador recebe a diferença
            numerador = diff; 
        if (fabs(v[i]) > denominador) //
            denominador = fabs(v[i]); // se o valor de v for maior que o denominador, o denominador recebe o valor de v
        v[i] = x[i];  // Atualiza vetor v com os valores atuais de x
    }
    // retorna a norma relativa, se donominador for zero, retornar apenas o numerador
    return numerador / (denominador == 0 ? 1 : denominador); // evita divisão por zero
}


// Método de Gauss-Seidel 
int gauss_seidel(int n, double **A, double *b, double *x, int *iteracoes) {
    double *v = (double *)malloc(n * sizeof(double)); // vetor auxiliar v, para guardar o valor anterior
    int convergiu = 0; // variável para verificar se o método de Gauss-Seidel está convergindo

    // Inicializa x e v com zeros
    for (int i = 0; i < n; i++) { // para cada linha da matriz
        x[i] = 0.0; // vetor x, para guardar o valor atual
        v[i] = 0.0; // vetor v, para guardar o valor anterior
    }



    // tenta resolver o sistema de equações, até atingir o número máximo de iterações ou convergir
    for (*iteracoes = 0; *iteracoes < MAX_ITER; (*iteracoes)++) { // para cada iteração
        for (int i = 0; i < n; i++) { // para cada linha da matriz
            double soma = 0.0; // inicializa a soma da linha com zero

            for (int j = 0; j < n; j++) {  // percorre colunas
                if (j != i) // se a coluna não for a diagonal, ignora a diagonal
                    soma += A[i][j] * x[j]; // soma o valor da linha i e coluna j com o valor de x
            }

            v[i] = x[i]; // guarda valor atual de x
            x[i] = (b[i] - soma) / A[i][i]; // atualiza o valor de x
            // calculo da formula gauss-seidel
        }



        double norma = calcula_convergencia(n, x, v); // calcula erro entre essa iteração e a anterior
        
        printf("Iteracao %d: ", *iteracoes + 1); // imprime o número da iteração atual
        for (int i = 0; i < n; i++) {
            printf("x[%d]=%.6f ", i + 1, x[i]); // imprime o valor de x atual
        }
        printf("| Norma = %.6f\n", norma);// imprime o erro entre essa iteração e a anterior

        if (norma <= EPSILON) { // se o erro for menor que a tolerância, o método de Gauss-Seidel está convergindo
            convergiu = 1; // convergiu = 1, o método de Gauss-Seidel está convergindo
            break;
        }
    }

    free(v); // libera o vetor v
    return convergiu; // retorna o valor de convergiu
}

// funcoes auxiliares

// conta quantas colunas tem na linha, para descobrir o tamanho da matriz
int conta_colunas(FILE *file) {
    int colunas = 0;
    double temp; // variavel temporaria para ler o arquivo
    char linha[1024]; // linha do arquivo
    if (fgets(linha, sizeof(linha), file)) { // lê a linha do arquivo
        char *ptr = linha; // ponteiro para a linha
        while (sscanf(ptr, "%lf", &temp) == 1) { // lê o valor da linha
            colunas++; // incrementa o número de colunas
            while (*ptr != ' ' && *ptr != '\0') ptr++; // pula os espaços
            while (*ptr == ' ') ptr++; // pula os espaços
        }
    }
    rewind(file); // volta para o inicio do arquivo
    return colunas - 1; // retorna o número de colunas - 1, pois o b é a última coluna
}

// Lê matriz do arquivo e preenche A (matriz de coeficientes) e b (vetor de termos independentes)
int ler_matriz(const char *arquivo, int *n, double ***A, double **b) {
    FILE *f = fopen(arquivo, "r"); // abre o arquivo
    if (!f) { // se o arquivo não for encontrado
        printf("Erro ao abrir o arquivo!\n"); // imprime uma mensagem de erro
        return 0;
    }

    *n = conta_colunas(f); // conta o número de colunas
    *A = (double **)malloc(*n * sizeof(double *)); // aloca o vetor de ponteiros para a matriz de coeficientes
    *b = (double *)malloc(*n * sizeof(double)); // aloca o vetor de termos independentes


    for (int i = 0; i < *n; i++) { // percorre as linhas da matriz
        (*A)[i] = (double *)malloc(*n * sizeof(double)); // aloca o vetor de coeficientes para a linha i
        for (int j = 0; j < *n; j++) { // percorre as colunas da matriz
            fscanf(f, "%lf", &(*A)[i][j]); // lê o valor da matriz de coeficientes
        }
        fscanf(f, "%lf", &(*b)[i]); // lê o valor do vetor de termos independentes
    }

    fclose(f); // fecha o arquivo
    return 1; // retorna 1, se o arquivo for lido corretamente
}


int main() {
    clock_t inicio, fim; // variaveis para calcular o tempo de execução
    double tempo; // variavel para calcular o tempo de execução

    double **A, *b, *x; // matriz de coeficientes, vetor de termos independentes e vetor de soluções
    int n, iteracoes;

    if (!ler_matriz("matriz.txt", &n, &A, &b)) { 
        return 1; // retorna 1, se o arquivo não for lido corretamente
    }

    x = (double *)malloc(n * sizeof(double)); // aloca o vetor para a solução
 
    printf(" Solucao pelo Metodo de Gauss-Seidel \n");

    inicio = clock(); // inicia o cronômetro
    int convergiu = gauss_seidel(n, A, b, x, &iteracoes); // chama a função de Gauss-Seidel
    fim = clock(); // para o cronômetro
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC; // calcula o tempo de execução

    printf("\nResultado final:\n"); // imprime o resultado final
    for (int i = 0; i < n; i++) { // percorre o vetor de soluções
        printf("x[%d] = %.6f\n", i + 1, x[i]); // imprime o valor de x atual
    }

    printf("\nNumero de iteracoes: %d\n", iteracoes+1); // imprime o número de iterações
    printf("Convergencia: %s\n", convergiu ? "Sim" : "Nao"); // imprime se o método de Gauss-Seidel está convergindo
    printf("Tempo de execucao: %.6f segundos\n", tempo); // imprime o tempo de execução

    // Liberar memória
    for (int i = 0; i < n; i++) free(A[i]); // libera a memória de cada linha da matriz de coeficientes
    free(A); // libera a memória da matriz de coeficientes
    free(b); // libera a memória do vetor de termos independentes
    free(x); // libera a memória do vetor de soluções

    return 0;
}
