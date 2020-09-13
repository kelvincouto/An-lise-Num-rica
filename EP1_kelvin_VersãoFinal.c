#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<locale.h> // Para colocar acentua��o

double Funcao (double x);
double Derivada_Funcao (double x);
double PHI(double x);
double Func_RaizQuadrada (double x, double d);
double Bisseccao_RAIZ_QUADRADA(double a, double b, double d);
double Bisseccao(double a, double b);
double Newton(double ChuteNewton);
double Secante(double Valor1Secante, double Valor2Secante);
double ORDEM_CONTASSINT(double x1,double x2, double x3,double x4);


double Funcao(double x)// O usu�rio deve digitar aqui a fun��o que quer calcular a ra�z. o usu�rio deve digitar aqui a fun��o desejada.
{
  return(pow(x,2.0)-4*x);
}


double Derivada_Funcao (double x) // derivada da fun��o. O usu�rio deve digita-la aqui.
{
    return (2*x-4);
}


double PHI(double x) //Fun��o utilizada no m�todo de Newton. Seu ponto fixo conincide com a ra�z da fun��o f
{
    return (x-(Funcao(x))/Derivada_Funcao(x));
}


double Func_RaizQuadrada(double x, double d)//Fun��o na qual a ra�z � a ra�z quadrada de d.
{
  return (pow(x,2.0)-d);
}


double Bisseccao_RAIZ_QUADRADA(double a, double b, double d)//Fun��o que aplica o m�todo da bissec��o no c�lculo da ra�z quadrada de d.
{
  double PONT_MED, TOL, FP;
  int i, N_MAX_ITER, Cont;
    {
                printf(" \n Por favor, digite a precis�o desejada ( N�o use ponto. Use v�rgula, pois o programa est� configurado para portugu�s): \n\t");
                scanf("%lf",&TOL); // Precis�o pretendida.
                printf("\n Por favor, digite o n�mero m�ximo de itera��es: \n\t");
                scanf("%d",&N_MAX_ITER);// N�mero m�ximo de itera��es.

                //A seguir calcularemos a aproxima��o para ra�z quadrada pedida aplicando o m�todo da bissec��o
                Cont =0;
                for (i = 1; i <= N_MAX_ITER; i++){
                   Cont=Cont+1;
                   PONT_MED=((a+b)/2.0);  //Ponto m�dio do intervalo [a,b].
                   FP=Func_RaizQuadrada(PONT_MED,d);
                   /*printf("\n Itera��o %d a aproxima��o da ra�z quadrada �: %lf \n ", i, PONT_MED);*/ // Ative esse comando para imprimir a aproxima��o da ra�z quadrada em cada itera��o do m�todo.

                   if(FP==0.0 || ((b-a)/2) <=TOL){
                     break;
                   }
                     else if (Func_RaizQuadrada(PONT_MED,d)*Func_RaizQuadrada(a,d) < 0){
                        b = PONT_MED;
                    }
                        else{
                             a = PONT_MED;
                        }
               }

               if(Cont==N_MAX_ITER){
                   printf("\n O n�mero m�ximo de itera��es %d foi atingido.\n", N_MAX_ITER);
               }

               if(FP==0 || ((b-a)/2) <= TOL){
                   printf("\n A precis�o desejada foi alcan�ada na %d_�sima itera��o. \n",Cont);
               }
               else{
                   printf("\n A precis�o desejada n�o foi alcan�ada.\n");
               }
                printf("\n Na itera��o %d a aproxima��o para a ra�z quadrada  foi: %6.4f \n", Cont,PONT_MED);
    }
}


double Bisseccao(double a, double b)//Fun��o que aplica o m�todo da bissec��o no c�lculo da ra�z da fun��o
{
  double PONT_MED, TOL, FP, A[4], ORD_CONV, CONS_ASSINT;
  int i,j, N_MAX_ITER, Cont;
    {
                printf(" \n Por favor, digite a precis�o desejada ( N�o use ponto. Use v�rgula, pois o programa est� configurado para portugu�s): \n\t");
                scanf("%lf",&TOL); // Precis�o pretendida.
                printf("\n Por favor, digite o n�mero m�ximo de itera��es maior ou igual a 4, caso queira estimar ordem de converg�ncia e constante assint�tica: \n\t");
                scanf("%d",&N_MAX_ITER);// N�mero m�ximo de itera��es.

                //A seguir calcularemos a aproxima��o para ra�z quadrada pedida aplicando o m�todo da bissec��o
                Cont =0;

                for (i = 1; i <= N_MAX_ITER; i++){
                   Cont=Cont+1;
                   PONT_MED=((a+b)/2.0);  //Ponto m�dio do intervalo [a,b].
                   FP=Funcao(PONT_MED);
                   /*printf("\n Itera��o %d a aproxima��o da ra�z �: %lf \n ", i, PONT_MED);*/// Ative este comando para imprimir as aproxima��es da ra�z da fun��o em cada itera��o.

                   if(FP==0.0 || ((b-a)/2) <TOL){
                     break;
                   }
                     else if (Funcao(PONT_MED)*Funcao(a) < 0){
                        b = PONT_MED;
                    }
                        else{
                             a = PONT_MED;
                        }

                if(i<=4){
                    A[i-1]=PONT_MED;
                }
                    else{
                         for (j = 0; j <=2; j++){
                              A[j]=A[j+1];
                         }
                         A[3]=PONT_MED;

                         }
                /*printf("\n Itera��o %d o vetor A �: \n\n",i); // Aqui apenas impimimos (para verificar) o vetor utilizado no c�lculo para estimativa da ordem de converg e da constl assint�tica
                    for (j = 0; j <= 3; j++){
                        printf( "  %lf  ",  A[j]);
                    }*/

               }
                if(Cont>4){ // Caso tenham ocorrido pelo menos 4 itera��es ent�o podemos estimar ordem de converg�ncia e constante assint�tica.
                ORD_CONV=((log(fabs((A[3]-A[2])/(A[2]-A[1]))))/ (log(fabs((A[2]-A[1])/(A[1]-A[0])))));//F�rumula para a estimativa da ordem de converg
                CONS_ASSINT=(fabs(A[3]-A[2])/pow((fabs(A[2]-A[1])),ORD_CONV ));// F�rumla para o a estimativa da constante assint�tica
                printf("\n A estimativa da ordem de converg�ncia �: %6.4f \n", ORD_CONV);
                printf("\n A estimativa da constante assint�tica �: %6.4f \n", CONS_ASSINT);
                }

               if(Cont==N_MAX_ITER){
                   printf("\n O n�mero m�ximo de itera��es %d foi atingido.\n", N_MAX_ITER);
               }

               if(FP==0.0 || ((b-a)/2) <TOL){
                   printf("\n A precis�o desejada foi alcan�ada na %d_�sima itera��o. \n",Cont);
               }
               else{
                   printf("\n A precis�o desejada n�o foi alcan�ada.\n");
               }
                printf("\n Na itera��o %d a aproxima��o para a ra�z quadrada  foi: %6.4f \n", Cont,PONT_MED);
    }
}


double Newton(double ChuteNewton)//Fun��o que aplica o m�todo de Newton no c�lculo da ra�z da fun��o
{
  double TOL,AproxRaiz, A[4], ORD_CONV, CONS_ASSINT;
  int i,j, N_MAX_ITER, Cont;
    {
        if(Funcao(ChuteNewton)==0)
                printf(" A ra�z da fun��o �: %lf", ChuteNewton);
                else{
                printf(" \n Por favor, digite a precis�o desejada ( N�o use ponto. Use v�rgula, pois o programa est� configurado para portugu�s): \n\t");
                scanf("%lf",&TOL); // Precis�o pretendida.
                printf("\n Por favor, digite o n�mero m�ximo de itera��es: \n\t");
                scanf("%d",&N_MAX_ITER);// N�mero m�ximo de itera��es.


                //A seguir calcularemos a aproxima��o para ra�z quadrada pedida aplicando o m�todo de Newton
                Cont =0;

                for (i = 1; i <= N_MAX_ITER; i++){
                   Cont=Cont+1;
                   AproxRaiz=PHI(ChuteNewton);

                   /*printf("\n Itera��o %d a aproxima��o da ra�z �: %lf \n ", i, AproxRaiz);*/ // Ative este comando para imprimir as aproxima��es da ra�z da fun��o em cada itera��o.

                   if(fabs(AproxRaiz - ChuteNewton)<TOL || Funcao(AproxRaiz)==0.0){
                     break;
                   }
                     else ChuteNewton=AproxRaiz;

                if(i<=4){
                    A[i-1]=AproxRaiz;
                }
                    else{
                         for (j = 0; j <=2; j++){
                              A[j]=A[j+1];
                         }
                         A[3]=AproxRaiz;

                         }
                /*printf("\n Itera��o %d o vetor A �: \n\n",i); // Aqui apenas impimimos (para verificar) o vetor utilizado no c�lculo para estimativa da ordem de converg e da constl assint�tica
                    for (j = 0; j <= 3; j++){
                        printf( "  %lf  ",  A[j]);
                    }*/
               }

                if(Cont>4){ // Caso tenham ocorrido pelo menos 4 itera��es ent�o podemos estimar ordem de converg�ncia e constante assint�tica.
                ORD_CONV=((log(fabs((A[3]-A[2])/(A[2]-A[1]))))/ (log(fabs((A[2]-A[1])/(A[1]-A[0])))));//F�rumula para a estimativa da ordem de converg
                CONS_ASSINT=(fabs(A[3]-A[2])/pow((fabs(A[2]-A[1])),ORD_CONV ));// F�rumla para o a estimativa da constante assint�tica
                printf("\n A estimativa da ordem de converg�ncia �: %6.4f \n", ORD_CONV);
                printf("\n A estimativa da constante assint�tica �: %6.4f \n", CONS_ASSINT);
                }



               if(Cont==N_MAX_ITER){
                   printf("\n O n�mero m�ximo de itera��es %d foi atingido.\n", N_MAX_ITER);
               }

               if(fabs(AproxRaiz - ChuteNewton)<TOL || Funcao(AproxRaiz)==0.0){
                   printf("\n A precis�o desejada foi alcan�ada na %d_�sima itera��o. \n",Cont);
               }
               else{
                   printf("\n A precis�o desejada n�o foi alcan�ada.\n");
               }
                printf("\n Na itera��o %d a aproxima��o para a ra�z quadrada  foi: %6.4f \n", Cont,AproxRaiz);
    }

}

}



double Secante(double Valor1Secante, double Valor2Secante)//Fun��o que aplica o m�todo da secante no c�lculo da ra�z da fun��o
{
  double TOL,AproxRaiz, A[4], ORD_CONV, CONS_ASSINT;
  int i,j, N_MAX_ITER, Cont;
    {

                printf(" \n Por favor, digite a precis�o desejada ( N�o use ponto. Use v�rgula, pois o programa est� configurado para portugu�s): \n\t");
                scanf("%lf",&TOL); // Precis�o pretendida.
                printf("\n Por favor, digite o n�mero m�ximo de itera��es: \n\n");
                scanf("%d",&N_MAX_ITER);// N�mero m�ximo de itera��es.

                Cont=0;

               for (i = 1; i <= N_MAX_ITER; i++){
                   Cont=Cont+1;
                   AproxRaiz=(Valor1Secante*Funcao(Valor2Secante)-Valor2Secante*Funcao(Valor1Secante))/(Funcao(Valor2Secante)-Funcao(Valor1Secante));

                   /*printf("\n Itera��o %d a aproxima��o da ra�z �: %lf \n ", i, AproxRaiz); */// Ative este comando para imprimir as aproxima��es da ra�z da fun��o em cada itera��o.

                   if(fabs(Valor2Secante-Valor1Secante)<TOL || Funcao(AproxRaiz)==0.0){
                     break;
                   }
                     else{
                         Valor1Secante=Valor2Secante;
                         Valor2Secante=AproxRaiz;
                     }

                if(i<=4){
                    A[i-1]=AproxRaiz;
                }
                    else{
                         for (j = 0; j <=2; j++){
                              A[j]=A[j+1];
                         }
                         A[3]=AproxRaiz;

                         }
                /*printf("\n Itera��o %d o vetor A �: \n\n",i); // Aqui apenas impimimos (para verificar) o vetor utilizado no c�lculo para estimativa da ordem de converg e da constl assint�tica
                    for (j = 0; j <= 3; j++){
                        printf( "  %lf  ",  A[j]);
                    }*/
               }


                if(Cont>4){ // Caso tenham ocorrido pelo menos 4 itera��es ent�o podemos estimar ordem de converg�ncia e constante assint�tica.
                ORD_CONV=((log(fabs((A[3]-A[2])/(A[2]-A[1]))))/ (log(fabs((A[2]-A[1])/(A[1]-A[0])))));//F�rumula para a estimativa da ordem de converg
                CONS_ASSINT=(fabs(A[3]-A[2])/pow((fabs(A[2]-A[1])),ORD_CONV ));// F�rumla para o a estimativa da constante assint�tica
                printf("\n A estimativa da ordem de converg�ncia �: %6.4f \n", ORD_CONV);
                printf("\n A estimativa da constante assint�tica �: %6.4f \n", CONS_ASSINT);
                }


               if(Cont==N_MAX_ITER){
                   printf("\n O n�mero m�ximo de itera��es %d foi atingido.\n", N_MAX_ITER);
               }

               if(fabs(Valor2Secante-Valor1Secante)<TOL || Funcao(AproxRaiz)==0.0){
                   printf("\n A precis�o desejada foi alcan�ada na %d_�sima itera��o. \n",Cont);
               }
               else{
                   printf("\n A precis�o desejada n�o foi alcan�ada.\n");
               }
                printf("\n Na itera��o %d a aproxima��o para a ra�z quadrada  foi: %6.4f \n", Cont,AproxRaiz);

}

}



int main()
{
   int Cont, Continuar, OPCAO, EscolhaMetodo;
   double a,b,d,COND_TEOR_VAL_INTERM, ChuteNewton, Valor1Secante, Valor2Secante;

   setlocale(LC_ALL, "portuguese"); // Para colocar o programa em l�ngua portuguesa. Posso acentuar mensagens e os n�meros decimais s�o com v�rgula e n�o ponto.
   system("color E5"); // Apenas para est�tica. Deixa o fundo amarelo "E". e a letra roxa "5".

   printf("\n   Observa��es:  \n");
   printf("\n  (1) Na op��o 1, a ser dada abaixo, calcularemos uma aproxima��o para a ra�z quadrada de um n�mero dado pelo usu�rio (Parte 1 do enunciado).\n");
   printf("\n  (2) Na op��o 2, a ser dada abaixo, implementaremos o m�todos pedidos na segunda parte do enunciado para o c�lcular uma aproxima��o para uma ra�z de uma fun��o. \n");
   printf("\n  (3) Devemos ter no m�nimo 4 itera��es para o c�lculo de estimativas de ordem de converg�ncia e de constante assint�tica na op��o 2.  \n");


   do{
      do{
        printf("\n Por favor, digite 1 para calcular uma ra�z quadrada pelo m�todo da bissec��o e digite 2 para calcular a ra�z da fun��o que foi inserida no c�digo. \n\n \t");
        scanf("%d", &OPCAO);

        switch(OPCAO){
        case 1:
            printf("\n Para o c�lculo da ra�z quadarada de d, utilizaremos o m�todo da bissec��o aplicado a fun��o f(x)=x^2-d \n");
            printf("\n A op��o escolhida foi %d. Digite o valor para o qual quer calcular a ra�z quadrada:\n \n\t", OPCAO);
            scanf("%lf", &d);

            do{
            printf("\n Por favor, digite o intervalo onde devemos buscar a raiz.  (ex. [1;2] = digite 1 2): \n");
            scanf("%lf %lf",&a,&b);
            COND_TEOR_VAL_INTERM = Func_RaizQuadrada(a,d)*Func_RaizQuadrada(b,d);
            if(COND_TEOR_VAL_INTERM>0){
                printf("\n N�o temos garantia, pelo teorema do valor intermedi�rio, de exit�ncia de ra�z de f no intervalo informado.\n");
            }
            }while(COND_TEOR_VAL_INTERM>0); // Condi��o para garantirmos uma ra�z no intervalo fechado [a,b]. Seja testando a e b, seja aplicando o teorema do valor intermediario.

             if(COND_TEOR_VAL_INTERM==0){ // Aqui ou a ou b s�o ra�zes.
                    if(Func_RaizQuadrada(a,d)==0)
                    printf("A ra�z quadrada de %lf � %lf", d, a);
                    else
                    printf("A ra�z quadrada de %lf � %lf", d, b);
             }
             else{
                    Bisseccao_RAIZ_QUADRADA(a,b,d); // Fun��o que ir� aplicar o m�todo da bissec��o no intervalo dado para o c�lculo da ra�z quadrada de d.
             }
        break;

        case 2:


              do{
                printf("\n Por favor digite, respectivamente, 1 ou 2 ou 3 para aplicar o m�todo da bissec��o ou M�todo de Newton ou M�todo da Secante. \n\n\t");
                scanf("%d", &EscolhaMetodo);

                switch(EscolhaMetodo){
                case 1:

                      printf("\n\n\t\t\t\t  _____________________________________________________________________________ ");
                      printf("  \n \t\t\t\t |                                                                             | ");
                      printf("\n \t\t\t\t |A op��o escolhida foi o m�todo da bissec��o para o c�lculo da ra�z da fun��o | ");
                      printf("\n\t\t\t\t |_____________________________________________________________________________| \n\n" );

                      do{
                        printf("\n Por favor, digite o intervalo onde devemos buscar a raiz.  (ex. [1;2] = digite 1 2): \n");
                        scanf("%lf %lf",&a,&b);
                        COND_TEOR_VAL_INTERM = Funcao(a)*Funcao(b);

                        if(COND_TEOR_VAL_INTERM>0){
                            printf("\n N�o temos garantia, pelo teorema do valor intermedi�rio, de exit�ncia de ra�z de f no intervalo informado.\n");
                        }
                      }while(COND_TEOR_VAL_INTERM>0); // Condi��o para garantirmos uma ra�z no intervalo fechado [a,b]. Seja testando a e b, seja aplicando o teorema do valor intermediario.

                      if(COND_TEOR_VAL_INTERM==0){ // Aqui ou a ou b s�o ra�zes.
                        if(Funcao(a)==0)
                                printf("Uma ra�z da fun��o � %lf", a);
                          else
                                printf("Uma ra�z da fun��o � %lf",  b);
                      }
                        else{
                          Bisseccao(a,b); // Fun��o que ir� aplicar o m�todo da bissec��o no intervalo dado para o c�lculo da ra�z quadrada de d.
                      }
                break;
                case 2:

                      printf("\n\n\t\t\t\t  _____________________________________________________________________________ ");
                      printf("  \n \t\t\t\t |                                                                             | ");
                      printf("\n \t\t\t\t | A op��o escolhida foi o  m�todo de Newton para o c�lculo da ra�z da fun��o  |  ");
                      printf("\n\t\t\t\t |_____________________________________________________________________________| \n\n" );


                      printf("Por favor, digite um chute inicial para o valor da ra�z da fun��o: \n \n\t");
                      scanf("%lf", &ChuteNewton);

                      Newton(ChuteNewton);
                break;
                case 3:

                      printf("\n\n\t\t\t\t  ________________________________________________________________________________ ");
                      printf("  \n \t\t\t\t |                                                                                | ");
                      printf("\n \t\t\t\t | A op��o escolhida foi o  m�todo das secantes para o c�lculo da ra�z da fun��o. | ");
                      printf("\n\t\t\t\t |________________________________________________________________________________| \n\n" );

                      do{
                      printf("Por favor, digite um dois valores iniciais para aplicarmos o m�todo da secante: \n\n ");
                      scanf("%lf %lf", &Valor1Secante, &Valor2Secante);

                        if(Funcao(Valor1Secante) ==Funcao(Valor2Secante)){
                            printf("\n As imagens da fun��o nos valores fornecidos coincidem. Portanto n�o podemos aplicar o M�todo da secante com esses valores.\n");
                        }

                      }while(Funcao(Valor1Secante) ==Funcao(Valor2Secante));

                      Secante(Valor1Secante, Valor2Secante);

                        break;

                        default:
                        printf("\n\n  Op��o inv�lida. \n\n");
                }

                }while(EscolhaMetodo != 1 && EscolhaMetodo != 2 && EscolhaMetodo !=3);


        break;

        default:
        printf("\n\n  Op��o inv�lida. \n\n");

            }
        }while(OPCAO !=1 && OPCAO != 2 );// Para que o usu�rio escolha uma das op��es



    printf("   \n\n   Digite 1 para permanecer no progrma e outro valor para sair. \n\n \t");
    scanf("%d", & Continuar);

    } while(Continuar ==1); // para que se retorne as op��es at� que o usuario digite a op��o 4.

    return 0;
}
