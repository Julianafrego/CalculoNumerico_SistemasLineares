# CalculoNumerico_SistemasLineares
trabalho da disciplina de calculo numerico - para solucionar sistemas lineares, por método Gauss, Gauss-Jacobi e Gauss-Seidel

# MÉTODO DE GAUSS-SEIDEL (AQUIVO: GAUSS_S.C E MATRIZ.TXT)

-> solucionador de Sistemas Lineares com Método de Gauss-Seidel

Este é um programa em C que resolve sistemas de equações lineares do tipo Ax = b, utilizando o método iterativo de Gauss-Seidel. 

O programa lê a matriz aumentada [A|b] inserida no arquivo de texto matriz.txt,aplica o método e exibe no terminal:
 - resultado apos cada iteração,
 - resultado final,
 - o número de iterações, 
 - se houve convergência, e o tempo de execução.


-> arquivo de entrada
 o arquivo de entrada `matriz.txt` deve conter a matriz aumentada do sistema linear que deseja-se resolver.
 cada linha do arquivo representa uma equação, nela os coefientes da matriz devem ser seguidos pelo termo idenpendente, todos separados por espaços " ".

- Por exemplo, para o sistema:
    10x_1 - x_2 + 2x_3 = 6
    -x_1 + 11x_2 - x_3 + 3x_4 = 25
    2x_1 - x_2 + 10x_3 - x_4 = -11
    3x_2 - x_3 + 8x_4 = 15

- O arquivo `matriz.txt` correspondente seria:

    10 -1 2 0 6
    -1 11 -1 3 25
    2 -1 10 -1 -11
    0 3 -1 8 15

OBS: O programa determina o tamanho da matriz (número de equações/variáveis `n`) automaticamente pela contagem de colunas na primeira linha do arquivo (considerando que a última coluna é o vetor `b`).


-> como Compilar

1.  Salve o código C em um arquivo, por exemplo, `gauss_s.c`.
2.  Abra um terminal ou prompt de comando.
3.  Navegue até o diretório onde você salvou o arquivo.
4.  Compile o código usando o GCC (ou outro compilador C) com o seguinte comando:
        gcc gauss_s.c -o gauss_s -lm

`gcc`: Comando para o compilador GCC.
`gauss_s.c`: Nome do seu arquivo de código fonte.
`-o gauss_s`: Especifica o nome do arquivo executável de saída (pode ser qualquer nome que preferir).
`-lm`: Vincula a biblioteca matemática (necessária para funções como `fabs`).

-> como Executar

1.  Após a compilação bem-sucedida, certifique-se de que o arquivo `matriz.txt` está no mesmo diretório que o executável (`gauss_s`).
2.  Execute o programa a partir do terminal:
        ./gauss_s
    O programa lerá a matriz, processará os dados e imprimirá os resultados no console.


-> funcionamento do código

O programa utiliza o método iterativo de Gauss-Seidel para encontrar a solução de um sistema linear. Abaixo, uma descrição das principais partes:
 - constantes
    `MAX_ITER (1000)`: Define o número máximo de iterações que o método de Gauss-Seidel tentará realizar. Isso previne loops infinitos caso o método não convirja.
    `EPSILON (0.05)`: Define a tolerância para o critério de parada. Se a norma relativa entre a solução da iteração atual e da anterior for menor ou igual a `EPSILON`, considera-se que o método convergiu.
- funções
    `main()`:
        É a função principal. Ela chama as funções para ler a matriz, resolver o sistema, medir o tempo e imprimir os resultados. Também gerencia a alocação e liberação de memória principal.
    `ler_matriz(const char *arquivo, int *n, double ***A, double **b)`**:
        Responsável por ler a matriz de coeficientes $A$ e o vetor de termos independentes $b$ a partir do arquivo `matriz.txt`. Também determina a dimensão `n` do sistema.
    `conta_colunas(FILE *file)`:
        Função auxiliar chamada por `ler_matriz`. Ela conta o número de elementos na primeira linha do arquivo para determinar a dimensão do sistema linear.
    `gauss_seidel(int n, double **A, double *b, double *x, int *iteracoes)`:
        Implementa o núcleo do método iterativo de Gauss-Seidel para encontrar a solução do sistema $Ax=b$. Retorna se o método convergiu e o número de iterações realizadas.
    `calcula_convergencia(int n, double *x, double *v)`:
        Calcula a norma relativa entre as soluções de duas iterações consecutivas ($x$ é a atual, $v$ é a anterior) para verificar se o critério de parada do método de Gauss-Seidel foi atingido.

# MÉTODO DE GAUSS-JACOBI (AQRUIVO JACOBI.C E DADOS.TXT)
Método de Gauss-Jacobi em C

Este programa implementa o método iterativo de Gauss-Jacobi para resolver sistemas de equações lineares na linguagem C.

-> Funcionamento

 - Lê uma matriz dos coeficientes e um vetor dos termos independentes a partir de um arquivo chamado `dados.txt`.
 - Resolve o sistema utilizando o método de Gauss-Jacobi.
 - Exibe o progresso de cada iteração até atingir a convergência ou o limite máximo de iterações.
 - Exibe o tempo total de execução.

-> Estrutura do Arquivo `dados.txt`

O arquivo deve estar no mesmo diretório do programa e seguir o seguinte formato:


N
a11 a12 a13 ... a1N b1
a21 a22 a23 ... a2N b2
...
aN1 aN2 aN3 ... aNN bN

Onde:
 - `N` é a ordem da matriz.
 - `aij` são os elementos da matriz dos coeficientes.
 - `bi` são os termos independentes.

Exemplo de arquivo `dados.txt` para um sistema 3x3:

3
4 -1 0 3
-1 4 -1 5
0 -1 4 6

-> Compilação
Compile o código utilizando um compilador C como `gcc` ou pelo proprio botão `Run`.
- Comando:
        gcc gauss_jacobi.c -o gauss_jacobi -lm
        OBS: O parâmetro `-lm` é necessário porque o programa utiliza a biblioteca `math.h`.

- Execução
Após a compilação, execute o programa com:
./gauss_jacobi

-> O programa irá:

    1. Ler a matriz e o vetor do arquivo `dados.txt`.
    2. Mostrar a matriz dos coeficientes e o vetor dos termos independentes.
    3. Realizar as iterações do método Gauss-Jacobi, exibindo os valores atualizados em cada passo.
    4. Parar quando atingir a tolerância (`0.0001`) ou o número máximo de iterações (`1000`).
    5. Exibir a solução aproximada e o tempo de execução.

-> Dependências

  - Biblioteca padrão C (`stdio.h`, `stdlib.h`).
  - Biblioteca matemática (`math.h`).
  - Biblioteca de tempo (`time.h`).

-> Exemplo de Saída

            Matriz dos coeficientes (A) e vetor dos termos independentes (b):
            4.000   -1.000    0.000 |    3.000
            -1.000    4.000   -1.000 |    5.000
            0.000   -1.000    4.000 |    6.000

            Iniciando iteracoes...
            Iteracao 1: 0.750000 1.250000 1.500000 
            ...
            Convergencia atingida apos 15 iteracoes.

            Solucao aproximada:
            x[1] = 1.000000
            x[2] = 2.000000
            x[3] = 3.000000

            Tempo de execucao durante a convergencia: 0.000125 segundos

-> Observações

  - Garanta que a matriz dos coeficientes seja diagonalmente dominante para que o método de Gauss-Jacobi convirja.
  - Os parâmetros de tolerância (`TOL = 0.0001`) e máximo de iterações (`MAX_IT = 1000`) podem ser ajustados diretamente no código.


Perfeito! Aqui está o texto reescrito, sem negrito e sem fórmulas matemáticas, mantendo uma linguagem clara e objetiva:

---

# MÉTODO DE ELIMINAÇÃO DE GAUSS (ARQUIVO: GAUSS.C E DADOS.TXT)

-> Solucionador de Sistemas Lineares com Método da Eliminação de Gauss

Este é um programa em linguagem C que resolve sistemas de equações lineares do tipo Ax = b utilizando o método direto de Eliminação de Gauss (sem pivotamento).

O programa lê a matriz dos coeficientes e o vetor dos termos independentes de um arquivo de texto chamado dados.txt, aplica o método e exibe no terminal:

* A matriz dos coeficientes (A) e o vetor dos termos independentes (b) lidos;
* O vetor solução após aplicar o método;
* O tempo total de execução.


-> Arquivo de entrada

O arquivo de entrada dados.txt deve conter:

1. Na primeira linha, um número inteiro N, que representa a ordem da matriz (número de equações ou variáveis).
2. Nas N linhas seguintes, cada linha representa uma equação, contendo:

* Os N coeficientes da equação, seguidos do termo independente, separados por espaço.

Exemplo de sistema:
Equação 1: 10x1 - x2 + 2x3 = 6
Equação 2: -x1 + 11x2 - x3 + 3x4 = 25
Equação 3: 2x1 - x2 + 10x3 - x4 = -11
Equação 4: 3x2 - x3 + 8x4 = 15

O arquivo dados.txt correspondente seria:


4
10 -1 2 0 6
-1 11 -1 3 25
2 -1 10 -1 -11
0 3 -1 8 15


-> Como compilar

1. Salve o código C em um arquivo, por exemplo, gauss.c
2. Abra um terminal ou prompt de comando.
3. Navegue até o diretório onde salvou o arquivo.
4. Compile usando o GCC (ou outro compilador C) com o seguinte comando:

gcc gauss.c -o gauss -lm

O parâmetro -lm serve para incluir a biblioteca matemática.


-> Como executar

1. Verifique se o arquivo dados.txt está no mesmo diretório que o executável gauss.
2. Execute o programa no terminal com:

./gauss

O programa irá ler a matriz, resolver o sistema e exibir os resultados no console.

-> Funcionamento do código

O programa utiliza o Método Direto da Eliminação de Gauss, que funciona em duas etapas principais:

1. Eliminação progressiva (triangularização):
   Nessa etapa, o programa zera os elementos abaixo da diagonal principal, transformando a matriz A em uma matriz triangular superior.

2. Substituição regressiva:
   Após a triangularização, calcula os valores das variáveis começando da última equação até a primeira.



-> Principais partes do código

 - Leitura dos dados com fscanf:
  O programa lê o tamanho N, os coeficientes da matriz A e os termos independentes b do arquivo dados.txt.

- Impressão da matriz lida:
  Mostra no console a matriz dos coeficientes e o vetor dos termos independentes.

- Etapa de eliminação:
  Para cada linha da matriz, elimina os elementos abaixo da diagonal. Caso encontre um pivô igual a zero, o programa emite uma mensagem de erro e finaliza.

- Substituição regressiva:
  Resolve o sistema triangular superior gerado na etapa anterior, calculando o vetor solução x.

- Cálculo do tempo de execução:
  Mede o tempo total desde o início da eliminação até a obtenção da solução.

- Impressão da solução:
  Mostra no console o vetor x contendo a solução do sistema.

