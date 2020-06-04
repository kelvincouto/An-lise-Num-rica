#include <stdio.h>
#include<locale.h> // Para colocar acentua��o
#include<math.h>
#include <stdlib.h> // Necess�rio para gerar n�meros aleat�rios
#include <time.h>  // Necess�rio para gerar n�meros aleat�rios

/*Resolu��o itens c e d do EP3*. Observa��o: Alguns comandos foram deixados desativados para facilitar a confer�ncia do programa */

/* T ser� a matriz de vari�veis  */

/* A seguinte fun��o calcula a norma infinito de um vetor, que no nosso caso � visto como uma matriz*/

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

/*A pr�xima fun��o encontra a menor coordenada de um vetor */

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

/*A pr�xima fun��o encontra a posi��o da menor coordenada de um vetor */

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
    setlocale(LC_ALL, "portuguese"); // Para colocar acentua��o.
    do{
        printf("\n Digite n dado no enunciado:  \t");
        scanf("%d", &ORDEM);/*ORDEM ser� a vari�vel n denotada na lista. A vantagem � que o usu�rio escolher o n desejado*/
        double  SOLUCAO_ITERACAO [ORDEM+1][ORDEM+1][1],w[100],T[ORDEM+1][ORDEM+1], T_INICIAL[ORDEM-1][ORDEM-1], INICIAL[ORDEM-1][ORDEM-1], T_ANTERIOR[ORDEM-1][ORDEM-1], DIFERENCA[ORDEM-1][ORDEM-1];

    /* Agora come�aremos a implementar o m�todo SOR*/

        printf("\n Digite 1 para matriz inicial ser nula; e outro valor inteiro para matriz inicial ser composta por n�meros aleat�rios entre zero e um: \t");
        scanf("%d", &OP);/* A Matriz que definiremos agora T_INICIAL  ser� o ponto de partida para as itera��es geradas pelo SOR*/

        if(OP==1){
            for(i=0; i<ORDEM-1; i++){ /* Elemento inicial do m�todo SOR, caso entradas nulas*/
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

        printf("\n Digite a quantidade m�xima de itera��es que o m�todo deve ser aplicado para cada par�metro w:\t");
        scanf("%d", &QTDADE_MAX_ITERACOES);/* Essa vari�vel, como pr�prio nome j� diz, ser� a quantidade m�xima em que aplicaremos SOR para cada w*/

        printf("\n Digite a toler�ncia para a aplica��o do m�todo e n�o use ponto. Use v�rgula: \t");
        scanf("%lf", &TOL);/* A vari�vel TOL ser� a toler�ncia a ser adotada em SOR*/

        for(k=0; k< 100; k++){ /* Geraremos o m�todo de SOR com 100 param�tros w�s que ser�o descritos a baixo*/

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
            /*Na sequ�ncia abaixo pode ser conferida a matriz T*/
            /*printf("\n \n A Matriz T �: \n\n");

            for(i=0; i<=ORDEM; i++){ /* imprime T para conferirmos se est� correta*/
                /*printf("\n");
                for(j=0; j<=ORDEM; j++){
                    printf("   %lf  ", T[i][j]);
                }
            }*/

            w[k]=1.0+((k+1.0)/100); /*Forma que ser�o tomados os w�s no m�todo SOR*/
            /*printf(" \n O %d - �sim coordenada do vetor w �: %lf.  \n\n\n", k+1, w[k]); /* Aqui apenas testei os w�s*/

            CONTADOR_ITERACOES = 0; /* Ser� usado para contar as itera��es em cada aplica��o de SOR para cada w*/

            for(i=0; i<=ORDEM-2; i++){ /* T_ANTERIOR �  a Matriz anterior a cada itera��o em SOR. A matriz anterior ao primeiro passo � a matriz inicial*/
                for(j=0; j<=ORDEM-2; j++){
                    T_ANTERIOR[i][j]= T_INICIAL[i][j];
                }
            }

            /*Com todos os dados anteriores coletados e definidos. Agora podemos executar o m�todo SOR para cada w_k*/

            do{

                CONTADOR_ITERACOES=CONTADOR_ITERACOES +1; /* Aqui contamos as itera��es do M�todo para cada w*/

                /*printf("\n\n Itera��o: %d \n", CONTADOR_ITERACOES); Aqui apenas conferimos o contador*/

                /*printf(" \n  A matriz T_ANTERIOR  � \n\n"); Nesta parte podemos conferir que as matrizes anteriores est�o corretas

                for(i=0; i<=ORDEM-2; i++){
                    printf("\n");
                    for(j=0; j<=ORDEM-2; j++){
                        printf("   %lf  ", T_ANTERIOR[i][j]);
                    }
                } */

                for(i=1; i<=ORDEM-1; i++){/*Aqui implementamos a a��o do m�todo de SOR*/
                    for(j=1; j<=ORDEM-1; j++){
                        T[i][j]= (1-w[k])*T[i][j]+(w[k]/4)*(T[i-1][j]+T[i][j-1]+T[i][j+1]+T[i+1][j]);
                    }
                }

                /*printf(" \n\n  A matriz T da itera��o %d �: \n\n", CONTADOR_ITERACOES); /*Aqui verificamos se a sequecia de vari�veis T estava sendo gerada corretamente.*/

                /*for(i=1; i<=ORDEM-1; i++){ /* imprime T para conferirmos se est� correta*/
                    /*printf("\n");
                    for(j=1; j<=ORDEM-1; j++){
                        printf("   %lf  ", T[i][j]);
                    }
                }*/

                for(i=0; i<=ORDEM-2; i++){ /* Aqui verificamos a diferen�a entre o elemento atual da sequencia de T�s e do anterior. Ser� usado para calcular o erro relativo*/
                    for(j=0; j<=ORDEM-2; j++){
                        DIFERENCA[i][j]=T[i+1][j+1]-T_ANTERIOR[i][j];
                    }
                }

                /*printf(" \n  A matriz DIFERENCA de cada itera��o � \n\n"); Aqui imprimimos a matriz DIFEREN�A e verificamos que est� correta

                for(i=0; i<=ORDEM-2; i++){ /* imprime A Diferen�a para conferirmos se est� correta*/
                    /*printf("\n");
                    for(j=0; j<=ORDEM-2; j++){
                        printf("   %lf  ", DIFERENCA[i][j]);
                    }
                }*/

                for(i=0; i<=ORDEM-2; i++){ /* Atualizando a Matriz da itera��o, para o pr�ximo passo*/
                    for(j=0; j<=ORDEM-2; j++){
                        T_ANTERIOR[i][j]= T[i+1][j+1];
                    }
                }

                ERRO= NORM_INF(ORDEM-1,DIFERENCA)/NORM_INF(ORDEM-1, T_ANTERIOR); /*Aqui calculamos (|T^(m) - T(m-1)|)/T^(m)| na norma infinito. Tomaremos tal varia��o como condi��o de parada*/

                /*printf(" \n \n   Norma infinito da Matriz diferen�a �: %lf \n\n", NORM_INF(ORDEM-1,DIFERENCA)); Aqui conferi a norma inginito da Matriz DIFEREN�A*/
                /*printf(" \n \n   A Norma infinito de T �: %lf \n\n", NORM_INF( ORDEM-1, T_ANTERIOR)); Aqui verifiquei que a norma infinito de T estava correta*/
                /*printf(" \n \n   (|T^(%d) - T(%d)|)/T^(%d) = %lf \n\n",CONTADOR_ITERACOES, CONTADOR_ITERACOES-1, CONTADOR_ITERACOES, ERRO);/* Pode-se colocar esse comando se se quiser deixar claro para o usu�rio o c�lculo indicado*/
                VETOR_ITERACOES[k]= CONTADOR_ITERACOES;/*Ser� usado para guardar a informa��o do n�mero de itera��es do m�todo de SOR para cada um dos w�s*/

            } while( CONTADOR_ITERACOES <QTDADE_MAX_ITERACOES && ERRO>TOL);

            /*printf("\n \n A solu��o do sistema n %d-�sima aplica��o do m�todo �: \n\n", k+1); /*Aqui se pode imprimir a solu��o aproximada, quando w est� no intervalo aberto em (1,2), do sistema na k-�sima aplica��o do m�todo.*/
            /*for(i=0; i<ORDEM+1; i++){ /* imprime a solu��o aproximada do m�todo na k�sima aplica��o*/
                /*printf("\n");
                for(j=0; j<ORDEM+1; j++){
                    printf("   %lf  ", T[i][j]);
                }
            }*/

            /*printf("\n\n A %d - �sima coordenada do vetor itera��es �: %d \n\n", k+1, VETOR_ITERACOES[k]); Aqui conferi que as itera��es em cada aplica��o de SOR estavam sendo guardadas corretametne*/
            }
        printf("\n Abaixo podemos verificaar a quantidade de itera��es em cada aplica��o do m�todo, bem como o valor de w correspondente:  \n\n");
        for(k=0; k<100; k++){
            printf(" %d-�sima aplica��o de SOR,  com w_%d = %lf Obtivemos %d itera�es. \n", k+1, k+1, w[k], VETOR_ITERACOES[k]);

        }

        printf(  "\n\n Na %d-�sima aplica��o do m�todo ocorre um menor n�mero de itera��es.  \n", POSICAO_Menor_COORDENADA(VETOR_ITERACOES) +1);
        printf(  "\n O menor n�mero de itera��e foi %d, e pode ser atingida com w = %lf   \n", Menor_COORDENADA(VETOR_ITERACOES) ,  w[POSICAO_Menor_COORDENADA(VETOR_ITERACOES)]);

        /*printf("\n\n E a respectiva solu��o aproxima para o sistema �: \n\n");/*Abaixo verificaremos a solu��o aproximada para menor n�mero de itera��es. Basta usar o w correspondente. Mas s� � vi�vel para enxergar para n pequeno.*/

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

                CONTADOR_ITERACOES = 0; /* Ser� usado para contar as itera��es em cada aplica��o de SOR para cada w*/

                /*for(i=0; i<=ORDEM-2; i++){ /* T_ANTERIOR �  a Matriz anterior a cada itera��o em SOR. A matriz anterior ao primeiro passo � a matriz inicial*/
                    /*for(j=0; j<=ORDEM-2; j++){
                        T_ANTERIOR[i][j]= T_INICIAL[i][j];
                    }
                }

                /*Com todos os dados anteriores coletados e definidos. Agora podemos executar o m�todo SOR para cada w_k*/

                /*do{

                    CONTADOR_ITERACOES=CONTADOR_ITERACOES +1; /* Aqui contamos as itera��es do M�todo para cada w*/

                    /*for(i=1; i<=ORDEM-1; i++){/*Aqui implementamos a a��o do m�todo de SOR*/
                        /*for(j=1; j<=ORDEM-1; j++){
                            T[i][j]= (1-w[k])*T[i][j]+(w[POSICAO_Menor_COORDENADA(VETOR_ITERACOES)]/4)*(T[i-1][j]+T[i][j-1]+T[i][j+1]+T[i+1][j]);
                        }
                    }

                    for(i=0; i<=ORDEM-2; i++){ /* Aqui verificamos a diferen�a entre o elemento atual da sequencia de T�s e do anterior. Ser� usado para calcular o erro relativo*/
                        /*for(j=0; j<=ORDEM-2; j++){
                            DIFERENCA[i][j]=T[i+1][j+1]-T_ANTERIOR[i][j];
                        }
                    }

                    for(i=0; i<=ORDEM-2; i++){ /* Atualizando a Matriz da itera��o, para o pr�ximo passo*/
                        /*for(j=0; j<=ORDEM-2; j++){
                            T_ANTERIOR[i][j]= T[i+1][j+1];
                        }
                    }

                    ERRO= NORM_INF(ORDEM-1,DIFERENCA)/NORM_INF(ORDEM-1, T_ANTERIOR); /*Aqui calculamos (|T^(m) - T(m-1)|)/T^(m)| na norma infinito. Tomaremos tal varia��o como condi��o de parada*/

                    /*VETOR_ITERACOES[k]= CONTADOR_ITERACOES;/*Ser� usado para guardar a informa��o do n�mero de itera��es do m�todo de SOR para cada um dos w�s*/

                /*} while( CONTADOR_ITERACOES <QTDADE_MAX_ITERACOES && ERRO>TOL);

               for(i=0; i<ORDEM+1; i++){ /* imprime a solu��o aproximada do m�todo na k�sima aplica��o*/
                    /*printf("\n");
                    for(j=0; j<ORDEM+1; j++){
                        printf("   %lf  ", T[i][j]);
                    }
                }*/


    printf("   \n\n   Digite 1 para permanecer no progrma e outro valor para sair. \n\n \t");
    scanf("%d", & codigoAcao);

    } while(codigoAcao ==1); // para que se retorne as op��es at� que o usuario digite a op��o 4.
    return 0;
}
