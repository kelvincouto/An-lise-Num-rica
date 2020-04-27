#include <stdio.h>
#include<locale.h> // Para colocar acentuação

int main()
{
    int i, j,k, ORDEM, n, codigoAcao;

    setlocale(LC_ALL, "portuguese"); // Para colocar acentuação.
    system("color E5"); // Apenas para estética. Deixa o fundo amarelo "E". e a letra roxa "5".

    printf("\n  Atenção: Aqui consideraremos A uma matriz tridiagonal Simétrica. Faremos o seguinte: \n");
    printf("\n  (1) Receberemos a matriz A e iremos mostra-la para que o usuário veja se está correta. \n");
    printf("\n  (2) Encontraremos uma fatoração A=LDL^t, com L Matriz triangular inferior Unitária e D matriz diagonal. \n");
    printf("\n  (3) Exibiremos as matrizes L, D e L^t. \n");
    printf("\n  (4) Receberemos um vetor B e obteremos o sistema Ax=B.  \n");
    printf("\n  (5) Resolveremos o sistema e exibiremos sua solução. \n");

    do{



    printf("\n Digite a ordem da matriz A: \n\n \t");
    scanf("%d", &ORDEM);

    n=ORDEM;
    float DiagPrincipalA[ORDEM], SubDiagoalA[ORDEM-1], D[n][n], L[n][n], A[n][n], B[n], U[n], V[n], X[n];

    printf("\n Procederemos agora com a leitura dos vetores da diagonal e subdiagonal de A, respectivametne. \n");

    for(i=0; i<ORDEM; i++){
            printf("\n Digite o elemento de posicao %d da Diagonal de A, da primeira linha para última. \n \n \t", i+1);
            scanf("%f", &DiagPrincipalA[i]);
        }

    for(i=0; i<ORDEM-1; i++){
            printf("\n Digite o elemento de posicao %d da SubDiagonal de A, da primeira linha para última. \n \n \t", i+1);
            scanf("%f", &SubDiagoalA[i]);
        }

    printf("\n\n O vetor diagonal principal de A, da primeira linha para última é:  \n \n \t", i+1);

        for(i=0; i<ORDEM; i++){
            printf("   %2.f   ", DiagPrincipalA[i]);
        }

    printf("\n\n O vetor Subdiagonal de A, da primeira linha para última é:  \n \n \t", i+1);


        for(i=0; i<ORDEM-1; i++){
            printf("   %2.f   ", SubDiagoalA[i]);
        }


    // Nesta parte iremos imprimir A

        for(i=0; i<ORDEM; i++){
            for(j=0; j<ORDEM; j++){

                A[i][j]=0;
            }
        }
        A[n-1][n-1]=DiagPrincipalA[n-1];

        for(i=0; i<ORDEM-1; i++){

                A[i][i]= DiagPrincipalA[i];
                A[i+1][i]=SubDiagoalA[i];
                A[i][i+1]=SubDiagoalA[i];
            }


        printf("\n\n A Matriz A tridiagonal simétrica é: \n\n");

        for(i=0; i<ORDEM; i++){
           printf("\n");
           for(j=0; j<ORDEM; j++){
            printf("   %2.f  ", A[i][j]);
           }
                               }


        // Nesta parte iremos calcular U e L

        for(i=0; i<ORDEM; i++){
            for(j=0; j<ORDEM; j++){

                L[i][j]=0;
                D[i][j]=0;
            }
        }



        D[0][0]=DiagPrincipalA[0];
        L[0][0]=1;


        for(i=1 ; i< n ; i++){ // Calculo da Matriz L

                L[i][i-1]=(SubDiagoalA[i-1])/D[i-1][i-1];
                D[i ][i]=DiagPrincipalA[i] - L[i][i-1]*SubDiagoalA[i-1];
                L[i][i]=1;
        }

        // Imprimiremos a seguir as matrizes L , D e L^t.

        printf("\n \n A Matriz L da fatoração A=LDL^t é: \n\n");

        for(i=0; i<ORDEM; i++){
           printf("\n");
           for(j=0; j<ORDEM; j++){
            printf("   %f  ", L[i][j]);
           }
                               }

        printf("\n \n A Matriz L^t da fatoração A=LDL^t é: \n\n");

        for(i=0; i<ORDEM; i++){
           printf("\n");
           for(j=0; j<ORDEM; j++){
            printf("   %f  ", L[j][i]);
           }
                               }

        printf("\n\n A Matriz D da fatoração A=LDL^t é: \n\n");

        for(i=0; i<ORDEM; i++){
           printf("\n");
           for(j=0; j<ORDEM; j++){
            printf("   %f  ", D[i][j]);
           }
                               }
        printf("\n\n Digite as coordenadas do vetor B para obtermos o sistema Ax=B: \n\n");

        for(i=0; i<ORDEM; i++){
            printf("\n Digite a %d-ésima coordenada do vetor B: \n \n \t", i+1);
            scanf("%f", &B[i]);
        }

        printf("\n\n O vetor B digitado foi:  \n \n \t", i+1);

        for(i=0; i<ORDEM; i++){
            printf("   %2.f   ", B[i]);
        }

        printf("\n\n Resolveremos a segunda parte do exercício. Se LU=B. Então o vetor U é:  \n \n \t", i+1);


        U[0]=B[0];
        for(i=1; i<ORDEM; i++){

            U[i]= B[i]-L[i][i-1]*U[i-1];
        }


        for(i=0; i<ORDEM; i++){
            printf("   %2.f   ", U[i]);
        }

        printf("\n\n Se DV=U. Então o vetor V é:  \n \n \t", i+1);



        for(i=0; i<ORDEM; i++){

            V[i]= U[i]/D[i][i];
        }



        for(i=0; i<ORDEM; i++){
            printf("   %2.f   ", V[i]);
        }


        printf("\n\n Se L^tX=V. Então o vetor X, ou seja, a solução do sistema AX=B é:  \n \n \t", i+1);


        X[n-1]=V[n-1];
        for(i=n-2; i>=0; i--){

            X[i]=(V[i]-L[i+1][i]*X[i+1])/SubDiagoalA[i];
        }



        for(i=0; i<ORDEM; i++){
            printf("   %2.f   ", X[i]);
        }

    printf("   \n\n   Digite 1 para permanecer no progrma e outro valor para sair. \n\n \t");
    scanf("%d", & codigoAcao);

    } while(codigoAcao ==1); // para que se retorne as opções até que o usuario digite a opção 4.

    return 0;
}
