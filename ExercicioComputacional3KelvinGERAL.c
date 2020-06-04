#include <stdio.h>
#include<locale.h> // Para colocar acentuação
#include<math.h>
#include <stdlib.h> // Necessário para gerar números aleatórios
#include <time.h>  // Necessário para gerar números aleatórios

/*Resolução itens c e d do EP3*. Observação: Alguns comandos foram deixados desativados para facilitar a conferência do programa */

/* T será a matriz de variáveis  */

/* A seguinte função calcula a norma infinito de um vetor, que no nosso caso é visto como uma matriz*/

double  NORM_INF(int n, double D[n][n])
{
   double MAIOR_MODULO_COORDENADA;
   int i, j;
   MAIOR_MODULO_COORDENADA = fabs(D[0][0]);
   for(i=0; i<=n-1; i++){
      for(j=0; j<=n-1; j++){
        if (fabs(D[i][j]) >MAIOR_MODULO_COORDENADA )
            MAIOR_MODULO_COORDENADA=fabs(D[i][j]);
      }
   }
   return MAIOR_MODULO_COORDENADA;
}

/*A próxima função encontra a menor coordenada de um vetor */

int  Menor_COORDENADA(int VETOR_ITERACOES[ ]){
   int MENORV;
   MENORV=VETOR_ITERACOES[0];
   int i;
   for(i=0; i<=99; i++){
      if(VETOR_ITERACOES[i]<=MENORV)
          MENORV=VETOR_ITERACOES[i];
   }
   return MENORV;
}

/*A próxima função encontra a posição da menor coordenada de um vetor */

int  POSICAO_Menor_COORDENADA(int V[])
{
   int MENORV;
   int POSICAO;
   POSICAO= 0;
   MENORV=V[0];
   int i;
   for(i=1; i<100; i++){
      if(V[i]<MENORV){
          MENORV=V[i];
          POSICAO=i;
      }
   }
   return POSICAO;
}

int main()
{
    int  i,j,k, codigoAcao, ORDEM, CONTADOR_ITERACOES, OP, QTDADE_MAX_ITERACOES, VETOR_ITERACOES[100];
    double  TOL, ERRO, MAIORMODULOCOORDENADA;
    setlocale(LC_ALL, "portuguese"); // Para colocar acentuação.
    do{
        printf("\n Digite n dado no enunciado:  \t");
        scanf("%d", &ORDEM);/*ORDEM será a variável n denotada na lista. A vantagem é que o usuário escolher o n desejado*/
        double  SOLUCAO_ITERACAO [ORDEM+1][ORDEM+1][1],w[100],T[ORDEM+1][ORDEM+1], T_INICIAL[ORDEM-1][ORDEM-1], INICIAL[ORDEM-1][ORDEM-1], T_ANTERIOR[ORDEM-1][ORDEM-1], DIFERENCA[ORDEM-1][ORDEM-1];

    /* Agora começaremos a implementar o método SOR*/

        printf("\n Digite 1 para matriz inicial ser nula; e outro valor inteiro para matriz inicial ser composta por números aleatórios entre zero e um: \t");
        scanf("%d", &OP);/* A Matriz que definiremos agora T_INICIAL  será o ponto de partida para as iterações geradas pelo SOR*/

        if(OP==1){
            for(i=0; i<ORDEM-1; i++){ /* Elemento inicial do método SOR, caso entradas nulas*/
                for(j=0; j<ORDEM-1; j++){
                    T_INICIAL[i][j]=0;
                }
            }
        }
            else{
                for(i=0; i<ORDEM-1; i++){
                    for(j=0; j<ORDEM-1; j++){
                        T_INICIAL[i][j]= (double) rand() / (double) RAND_MAX;
                    }
                }
            }

        printf("\n Digite a quantidade máxima de iterações que o método deve ser aplicado para cada parâmetro w:\t");
        scanf("%d", &QTDADE_MAX_ITERACOES);/* Essa variável, como próprio nome já diz, será a quantidade máxima em que aplicaremos SOR para cada w*/

        printf("\n Digite a tolerância para a aplicação do método e não use ponto. Use vírgula: \t");
        scanf("%lf", &TOL);/* A variável TOL será a tolerância a ser adotada em SOR*/

        for(k=0; k< 100; k++){ /* Geraremos o método de SOR com 100 paramêtros w´s que serão descritos a baixo*/

            /* Primeiramente definimos a matriz T como foi dada na lista*/

            for(i=0; i<=ORDEM; i++){ /* Valores para T no bordo da placa*/
                T[0][i]=-3;
                T[i][0]=-3;
                T[ORDEM][i]= (6.00*i)/ORDEM -3.0;
                T[i][ORDEM]= ((6.0*i)/ORDEM) - 3.0;
            }

            for(i=1; i<ORDEM; i++){ /* Adotaremos valores iniciais nulos para T no interior da malha */
                for(j=1; j<ORDEM; j++){
                    T[i][j]=0;
                }
            }
            /*Na sequência abaixo pode ser conferida a matriz T*/
            /*printf("\n \n A Matriz T é: \n\n");

            for(i=0; i<=ORDEM; i++){ /* imprime T para conferirmos se está correta*/
                /*printf("\n");
                for(j=0; j<=ORDEM; j++){
                    printf("   %lf  ", T[i][j]);
                }
            }*/

            w[k]=1.0+((k+1.0)/100); /*Forma que serão tomados os w´s no método SOR*/
            /*printf(" \n O %d - ésim coordenada do vetor w é: %lf.  \n\n\n", k+1, w[k]); /* Aqui apenas testei os w´s*/

            CONTADOR_ITERACOES = 0; /* Será usado para contar as iterações em cada aplicação de SOR para cada w*/

            for(i=0; i<=ORDEM-2; i++){ /* T_ANTERIOR é  a Matriz anterior a cada iteração em SOR. A matriz anterior ao primeiro passo é a matriz inicial*/
                for(j=0; j<=ORDEM-2; j++){
                    T_ANTERIOR[i][j]= T_INICIAL[i][j];
                }
            }

            /*Com todos os dados anteriores coletados e definidos. Agora podemos executar o método SOR para cada w_k*/

            do{

                CONTADOR_ITERACOES=CONTADOR_ITERACOES +1; /* Aqui contamos as iterações do Método para cada w*/

                /*printf("\n\n Iteração: %d \n", CONTADOR_ITERACOES); Aqui apenas conferimos o contador*/

                /*printf(" \n  A matriz T_ANTERIOR  é \n\n"); Nesta parte podemos conferir que as matrizes anteriores estão corretas

                for(i=0; i<=ORDEM-2; i++){
                    printf("\n");
                    for(j=0; j<=ORDEM-2; j++){
                        printf("   %lf  ", T_ANTERIOR[i][j]);
                    }
                } */

                for(i=1; i<=ORDEM-1; i++){/*Aqui implementamos a ação do método de SOR*/
                    for(j=1; j<=ORDEM-1; j++){
                        T[i][j]= (1-w[k])*T[i][j]+(w[k]/4)*(T[i-1][j]+T[i][j-1]+T[i][j+1]+T[i+1][j]);
                    }
                }

                /*printf(" \n\n  A matriz T da iteração %d é: \n\n", CONTADOR_ITERACOES); /*Aqui verificamos se a sequecia de variáveis T estava sendo gerada corretamente.*/

                /*for(i=1; i<=ORDEM-1; i++){ /* imprime T para conferirmos se está correta*/
                    /*printf("\n");
                    for(j=1; j<=ORDEM-1; j++){
                        printf("   %lf  ", T[i][j]);
                    }
                }*/

                for(i=0; i<=ORDEM-2; i++){ /* Aqui verificamos a diferença entre o elemento atual da sequencia de T´s e do anterior. Será usado para calcular o erro relativo*/
                    for(j=0; j<=ORDEM-2; j++){
                        DIFERENCA[i][j]=T[i+1][j+1]-T_ANTERIOR[i][j];
                    }
                }

                /*printf(" \n  A matriz DIFERENCA de cada iteração é \n\n"); Aqui imprimimos a matriz DIFERENÇA e verificamos que está correta

                for(i=0; i<=ORDEM-2; i++){ /* imprime A Diferença para conferirmos se está correta*/
                    /*printf("\n");
                    for(j=0; j<=ORDEM-2; j++){
                        printf("   %lf  ", DIFERENCA[i][j]);
                    }
                }*/

                for(i=0; i<=ORDEM-2; i++){ /* Atualizando a Matriz da iteração, para o próximo passo*/
                    for(j=0; j<=ORDEM-2; j++){
                        T_ANTERIOR[i][j]= T[i+1][j+1];
                    }
                }

                ERRO= NORM_INF(ORDEM-1,DIFERENCA)/NORM_INF(ORDEM-1, T_ANTERIOR); /*Aqui calculamos (|T^(m) - T(m-1)|)/T^(m)| na norma infinito. Tomaremos tal variação como condição de parada*/

                /*printf(" \n \n   Norma infinito da Matriz diferença é: %lf \n\n", NORM_INF(ORDEM-1,DIFERENCA)); Aqui conferi a norma inginito da Matriz DIFERENÇA*/
                /*printf(" \n \n   A Norma infinito de T é: %lf \n\n", NORM_INF( ORDEM-1, T_ANTERIOR)); Aqui verifiquei que a norma infinito de T estava correta*/
                /*printf(" \n \n   (|T^(%d) - T(%d)|)/T^(%d) = %lf \n\n",CONTADOR_ITERACOES, CONTADOR_ITERACOES-1, CONTADOR_ITERACOES, ERRO);/* Pode-se colocar esse comando se se quiser deixar claro para o usuário o cálculo indicado*/
                VETOR_ITERACOES[k]= CONTADOR_ITERACOES;/*Será usado para guardar a informação do número de iterações do método de SOR para cada um dos w´s*/

            } while( CONTADOR_ITERACOES <QTDADE_MAX_ITERACOES && ERRO>TOL);

            /*printf("\n \n A solução do sistema n %d-ésima aplicação do método é: \n\n", k+1); /*Aqui se pode imprimir a solução aproximada, quando w está no intervalo aberto em (1,2), do sistema na k-ésima aplicação do método.*/
            /*for(i=0; i<ORDEM+1; i++){ /* imprime a solução aproximada do método na késima aplicação*/
                /*printf("\n");
                for(j=0; j<ORDEM+1; j++){
                    printf("   %lf  ", T[i][j]);
                }
            }*/

            /*printf("\n\n A %d - ésima coordenada do vetor iterações é: %d \n\n", k+1, VETOR_ITERACOES[k]); Aqui conferi que as iterações em cada aplicação de SOR estavam sendo guardadas corretametne*/
            }
        printf("\n Abaixo podemos verificaar a quantidade de iterações em cada aplicação do método, bem como o valor de w correspondente:  \n\n");
        for(k=0; k<100; k++){
            printf(" %d-ésima aplicação de SOR,  com w_%d = %lf Obtivemos %d iteraões. \n", k+1, k+1, w[k], VETOR_ITERACOES[k]);

        }

        printf(  "\n\n Na %d-ésima aplicação do método ocorre um menor número de iterações.  \n", POSICAO_Menor_COORDENADA(VETOR_ITERACOES) +1);
        printf(  "\n O menor número de iteraçõe foi %d, e pode ser atingida com w = %lf   \n", Menor_COORDENADA(VETOR_ITERACOES) ,  w[POSICAO_Menor_COORDENADA(VETOR_ITERACOES)]);

        /*printf("\n\n E a respectiva solução aproxima para o sistema é: \n\n");/*Abaixo verificaremos a solução aproximada para menor número de iterações. Basta usar o w correspondente. Mas só é viável para enxergar para n pequeno.*/

                /*for(i=0; i<=ORDEM; i++){ /*Precisamos retornar a T aos seus valores originis.*/
                    /*T[0][i]=-3;
                    T[i][0]=-3;
                    T[ORDEM][i]= (6.00*i)/ORDEM -3.0;
                    T[i][ORDEM]= ((6.0*i)/ORDEM) - 3.0;
                }

                for(i=1; i<ORDEM; i++){ /* Adotaremos valores iniciais nulos para T no interior da malha */
                    /*for(j=1; j<ORDEM; j++){
                        T[i][j]=0;
                    }
                }

                CONTADOR_ITERACOES = 0; /* Será usado para contar as iterações em cada aplicação de SOR para cada w*/

                /*for(i=0; i<=ORDEM-2; i++){ /* T_ANTERIOR é  a Matriz anterior a cada iteração em SOR. A matriz anterior ao primeiro passo é a matriz inicial*/
                    /*for(j=0; j<=ORDEM-2; j++){
                        T_ANTERIOR[i][j]= T_INICIAL[i][j];
                    }
                }

                /*Com todos os dados anteriores coletados e definidos. Agora podemos executar o método SOR para cada w_k*/

                /*do{

                    CONTADOR_ITERACOES=CONTADOR_ITERACOES +1; /* Aqui contamos as iterações do Método para cada w*/

                    /*for(i=1; i<=ORDEM-1; i++){/*Aqui implementamos a ação do método de SOR*/
                        /*for(j=1; j<=ORDEM-1; j++){
                            T[i][j]= (1-w[k])*T[i][j]+(w[POSICAO_Menor_COORDENADA(VETOR_ITERACOES)]/4)*(T[i-1][j]+T[i][j-1]+T[i][j+1]+T[i+1][j]);
                        }
                    }

                    for(i=0; i<=ORDEM-2; i++){ /* Aqui verificamos a diferença entre o elemento atual da sequencia de T´s e do anterior. Será usado para calcular o erro relativo*/
                        /*for(j=0; j<=ORDEM-2; j++){
                            DIFERENCA[i][j]=T[i+1][j+1]-T_ANTERIOR[i][j];
                        }
                    }

                    for(i=0; i<=ORDEM-2; i++){ /* Atualizando a Matriz da iteração, para o próximo passo*/
                        /*for(j=0; j<=ORDEM-2; j++){
                            T_ANTERIOR[i][j]= T[i+1][j+1];
                        }
                    }

                    ERRO= NORM_INF(ORDEM-1,DIFERENCA)/NORM_INF(ORDEM-1, T_ANTERIOR); /*Aqui calculamos (|T^(m) - T(m-1)|)/T^(m)| na norma infinito. Tomaremos tal variação como condição de parada*/

                    /*VETOR_ITERACOES[k]= CONTADOR_ITERACOES;/*Será usado para guardar a informação do número de iterações do método de SOR para cada um dos w´s*/

                /*} while( CONTADOR_ITERACOES <QTDADE_MAX_ITERACOES && ERRO>TOL);

               for(i=0; i<ORDEM+1; i++){ /* imprime a solução aproximada do método na késima aplicação*/
                    /*printf("\n");
                    for(j=0; j<ORDEM+1; j++){
                        printf("   %lf  ", T[i][j]);
                    }
                }*/


    printf("   \n\n   Digite 1 para permanecer no progrma e outro valor para sair. \n\n \t");
    scanf("%d", & codigoAcao);

    } while(codigoAcao ==1); // para que se retorne as opções até que o usuario digite a opção 4.
    return 0;
}
