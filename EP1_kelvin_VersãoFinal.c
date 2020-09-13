#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<locale.h> // Para colocar acentuação

double Funcao (double x);
double Derivada_Funcao (double x);
double PHI(double x);
double Func_RaizQuadrada (double x, double d);
double Bisseccao_RAIZ_QUADRADA(double a, double b, double d);
double Bisseccao(double a, double b);
double Newton(double ChuteNewton);
double Secante(double Valor1Secante, double Valor2Secante);
double ORDEM_CONTASSINT(double x1,double x2, double x3,double x4);


double Funcao(double x)// O usuário deve digitar aqui a função que quer calcular a raíz. o usuário deve digitar aqui a função desejada.
{
  return(pow(x,2.0)-4*x);
}


double Derivada_Funcao (double x) // derivada da função. O usuário deve digita-la aqui.
{
    return (2*x-4);
}


double PHI(double x) //Função utilizada no método de Newton. Seu ponto fixo conincide com a raíz da função f
{
    return (x-(Funcao(x))/Derivada_Funcao(x));
}


double Func_RaizQuadrada(double x, double d)//Função na qual a raíz é a raíz quadrada de d.
{
  return (pow(x,2.0)-d);
}


double Bisseccao_RAIZ_QUADRADA(double a, double b, double d)//Função que aplica o método da bissecção no cálculo da raíz quadrada de d.
{
  double PONT_MED, TOL, FP;
  int i, N_MAX_ITER, Cont;
    {
                printf(" \n Por favor, digite a precisão desejada ( Não use ponto. Use vírgula, pois o programa está configurado para português): \n\t");
                scanf("%lf",&TOL); // Precisão pretendida.
                printf("\n Por favor, digite o número máximo de iterações: \n\t");
                scanf("%d",&N_MAX_ITER);// Número máximo de iterações.

                //A seguir calcularemos a aproximação para raíz quadrada pedida aplicando o método da bissecção
                Cont =0;
                for (i = 1; i <= N_MAX_ITER; i++){
                   Cont=Cont+1;
                   PONT_MED=((a+b)/2.0);  //Ponto médio do intervalo [a,b].
                   FP=Func_RaizQuadrada(PONT_MED,d);
                   /*printf("\n Iteração %d a aproximação da raíz quadrada é: %lf \n ", i, PONT_MED);*/ // Ative esse comando para imprimir a aproximação da raíz quadrada em cada iteração do método.

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
                   printf("\n O número máximo de iterações %d foi atingido.\n", N_MAX_ITER);
               }

               if(FP==0 || ((b-a)/2) <= TOL){
                   printf("\n A precisão desejada foi alcançada na %d_ésima iteração. \n",Cont);
               }
               else{
                   printf("\n A precisão desejada não foi alcançada.\n");
               }
                printf("\n Na iteração %d a aproximação para a raíz quadrada  foi: %6.4f \n", Cont,PONT_MED);
    }
}


double Bisseccao(double a, double b)//Função que aplica o método da bissecção no cálculo da raíz da função
{
  double PONT_MED, TOL, FP, A[4], ORD_CONV, CONS_ASSINT;
  int i,j, N_MAX_ITER, Cont;
    {
                printf(" \n Por favor, digite a precisão desejada ( Não use ponto. Use vírgula, pois o programa está configurado para português): \n\t");
                scanf("%lf",&TOL); // Precisão pretendida.
                printf("\n Por favor, digite o número máximo de iterações maior ou igual a 4, caso queira estimar ordem de convergência e constante assintótica: \n\t");
                scanf("%d",&N_MAX_ITER);// Número máximo de iterações.

                //A seguir calcularemos a aproximação para raíz quadrada pedida aplicando o método da bissecção
                Cont =0;

                for (i = 1; i <= N_MAX_ITER; i++){
                   Cont=Cont+1;
                   PONT_MED=((a+b)/2.0);  //Ponto médio do intervalo [a,b].
                   FP=Funcao(PONT_MED);
                   /*printf("\n Iteração %d a aproximação da raíz é: %lf \n ", i, PONT_MED);*/// Ative este comando para imprimir as aproximações da raíz da função em cada iteração.

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
                /*printf("\n Iteração %d o vetor A é: \n\n",i); // Aqui apenas impimimos (para verificar) o vetor utilizado no cálculo para estimativa da ordem de converg e da constl assintótica
                    for (j = 0; j <= 3; j++){
                        printf( "  %lf  ",  A[j]);
                    }*/

               }
                if(Cont>4){ // Caso tenham ocorrido pelo menos 4 iterações então podemos estimar ordem de convergência e constante assintótica.
                ORD_CONV=((log(fabs((A[3]-A[2])/(A[2]-A[1]))))/ (log(fabs((A[2]-A[1])/(A[1]-A[0])))));//Fórumula para a estimativa da ordem de converg
                CONS_ASSINT=(fabs(A[3]-A[2])/pow((fabs(A[2]-A[1])),ORD_CONV ));// Fórumla para o a estimativa da constante assintótica
                printf("\n A estimativa da ordem de convergência é: %6.4f \n", ORD_CONV);
                printf("\n A estimativa da constante assintótica é: %6.4f \n", CONS_ASSINT);
                }

               if(Cont==N_MAX_ITER){
                   printf("\n O número máximo de iterações %d foi atingido.\n", N_MAX_ITER);
               }

               if(FP==0.0 || ((b-a)/2) <TOL){
                   printf("\n A precisão desejada foi alcançada na %d_ésima iteração. \n",Cont);
               }
               else{
                   printf("\n A precisão desejada não foi alcançada.\n");
               }
                printf("\n Na iteração %d a aproximação para a raíz quadrada  foi: %6.4f \n", Cont,PONT_MED);
    }
}


double Newton(double ChuteNewton)//Função que aplica o método de Newton no cálculo da raíz da função
{
  double TOL,AproxRaiz, A[4], ORD_CONV, CONS_ASSINT;
  int i,j, N_MAX_ITER, Cont;
    {
        if(Funcao(ChuteNewton)==0)
                printf(" A raíz da função é: %lf", ChuteNewton);
                else{
                printf(" \n Por favor, digite a precisão desejada ( Não use ponto. Use vírgula, pois o programa está configurado para português): \n\t");
                scanf("%lf",&TOL); // Precisão pretendida.
                printf("\n Por favor, digite o número máximo de iterações: \n\t");
                scanf("%d",&N_MAX_ITER);// Número máximo de iterações.


                //A seguir calcularemos a aproximação para raíz quadrada pedida aplicando o método de Newton
                Cont =0;

                for (i = 1; i <= N_MAX_ITER; i++){
                   Cont=Cont+1;
                   AproxRaiz=PHI(ChuteNewton);

                   /*printf("\n Iteração %d a aproximação da raíz é: %lf \n ", i, AproxRaiz);*/ // Ative este comando para imprimir as aproximações da raíz da função em cada iteração.

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
                /*printf("\n Iteração %d o vetor A é: \n\n",i); // Aqui apenas impimimos (para verificar) o vetor utilizado no cálculo para estimativa da ordem de converg e da constl assintótica
                    for (j = 0; j <= 3; j++){
                        printf( "  %lf  ",  A[j]);
                    }*/
               }

                if(Cont>4){ // Caso tenham ocorrido pelo menos 4 iterações então podemos estimar ordem de convergência e constante assintótica.
                ORD_CONV=((log(fabs((A[3]-A[2])/(A[2]-A[1]))))/ (log(fabs((A[2]-A[1])/(A[1]-A[0])))));//Fórumula para a estimativa da ordem de converg
                CONS_ASSINT=(fabs(A[3]-A[2])/pow((fabs(A[2]-A[1])),ORD_CONV ));// Fórumla para o a estimativa da constante assintótica
                printf("\n A estimativa da ordem de convergência é: %6.4f \n", ORD_CONV);
                printf("\n A estimativa da constante assintótica é: %6.4f \n", CONS_ASSINT);
                }



               if(Cont==N_MAX_ITER){
                   printf("\n O número máximo de iterações %d foi atingido.\n", N_MAX_ITER);
               }

               if(fabs(AproxRaiz - ChuteNewton)<TOL || Funcao(AproxRaiz)==0.0){
                   printf("\n A precisão desejada foi alcançada na %d_ésima iteração. \n",Cont);
               }
               else{
                   printf("\n A precisão desejada não foi alcançada.\n");
               }
                printf("\n Na iteração %d a aproximação para a raíz quadrada  foi: %6.4f \n", Cont,AproxRaiz);
    }

}

}



double Secante(double Valor1Secante, double Valor2Secante)//Função que aplica o método da secante no cálculo da raíz da função
{
  double TOL,AproxRaiz, A[4], ORD_CONV, CONS_ASSINT;
  int i,j, N_MAX_ITER, Cont;
    {

                printf(" \n Por favor, digite a precisão desejada ( Não use ponto. Use vírgula, pois o programa está configurado para português): \n\t");
                scanf("%lf",&TOL); // Precisão pretendida.
                printf("\n Por favor, digite o número máximo de iterações: \n\n");
                scanf("%d",&N_MAX_ITER);// Número máximo de iterações.

                Cont=0;

               for (i = 1; i <= N_MAX_ITER; i++){
                   Cont=Cont+1;
                   AproxRaiz=(Valor1Secante*Funcao(Valor2Secante)-Valor2Secante*Funcao(Valor1Secante))/(Funcao(Valor2Secante)-Funcao(Valor1Secante));

                   /*printf("\n Iteração %d a aproximação da raíz é: %lf \n ", i, AproxRaiz); */// Ative este comando para imprimir as aproximações da raíz da função em cada iteração.

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
                /*printf("\n Iteração %d o vetor A é: \n\n",i); // Aqui apenas impimimos (para verificar) o vetor utilizado no cálculo para estimativa da ordem de converg e da constl assintótica
                    for (j = 0; j <= 3; j++){
                        printf( "  %lf  ",  A[j]);
                    }*/
               }


                if(Cont>4){ // Caso tenham ocorrido pelo menos 4 iterações então podemos estimar ordem de convergência e constante assintótica.
                ORD_CONV=((log(fabs((A[3]-A[2])/(A[2]-A[1]))))/ (log(fabs((A[2]-A[1])/(A[1]-A[0])))));//Fórumula para a estimativa da ordem de converg
                CONS_ASSINT=(fabs(A[3]-A[2])/pow((fabs(A[2]-A[1])),ORD_CONV ));// Fórumla para o a estimativa da constante assintótica
                printf("\n A estimativa da ordem de convergência é: %6.4f \n", ORD_CONV);
                printf("\n A estimativa da constante assintótica é: %6.4f \n", CONS_ASSINT);
                }


               if(Cont==N_MAX_ITER){
                   printf("\n O número máximo de iterações %d foi atingido.\n", N_MAX_ITER);
               }

               if(fabs(Valor2Secante-Valor1Secante)<TOL || Funcao(AproxRaiz)==0.0){
                   printf("\n A precisão desejada foi alcançada na %d_ésima iteração. \n",Cont);
               }
               else{
                   printf("\n A precisão desejada não foi alcançada.\n");
               }
                printf("\n Na iteração %d a aproximação para a raíz quadrada  foi: %6.4f \n", Cont,AproxRaiz);

}

}



int main()
{
   int Cont, Continuar, OPCAO, EscolhaMetodo;
   double a,b,d,COND_TEOR_VAL_INTERM, ChuteNewton, Valor1Secante, Valor2Secante;

   setlocale(LC_ALL, "portuguese"); // Para colocar o programa em língua portuguesa. Posso acentuar mensagens e os números decimais são com vírgula e não ponto.
   system("color E5"); // Apenas para estética. Deixa o fundo amarelo "E". e a letra roxa "5".

   printf("\n   Observações:  \n");
   printf("\n  (1) Na opção 1, a ser dada abaixo, calcularemos uma aproximação para a raíz quadrada de um número dado pelo usuário (Parte 1 do enunciado).\n");
   printf("\n  (2) Na opção 2, a ser dada abaixo, implementaremos o métodos pedidos na segunda parte do enunciado para o cálcular uma aproximação para uma raíz de uma função. \n");
   printf("\n  (3) Devemos ter no mínimo 4 iterações para o cálculo de estimativas de ordem de convergência e de constante assintótica na opção 2.  \n");


   do{
      do{
        printf("\n Por favor, digite 1 para calcular uma raíz quadrada pelo método da bissecção e digite 2 para calcular a raíz da função que foi inserida no código. \n\n \t");
        scanf("%d", &OPCAO);

        switch(OPCAO){
        case 1:
            printf("\n Para o cálculo da raíz quadarada de d, utilizaremos o método da bissecção aplicado a função f(x)=x^2-d \n");
            printf("\n A opção escolhida foi %d. Digite o valor para o qual quer calcular a raíz quadrada:\n \n\t", OPCAO);
            scanf("%lf", &d);

            do{
            printf("\n Por favor, digite o intervalo onde devemos buscar a raiz.  (ex. [1;2] = digite 1 2): \n");
            scanf("%lf %lf",&a,&b);
            COND_TEOR_VAL_INTERM = Func_RaizQuadrada(a,d)*Func_RaizQuadrada(b,d);
            if(COND_TEOR_VAL_INTERM>0){
                printf("\n Não temos garantia, pelo teorema do valor intermediário, de exitência de raíz de f no intervalo informado.\n");
            }
            }while(COND_TEOR_VAL_INTERM>0); // Condição para garantirmos uma raíz no intervalo fechado [a,b]. Seja testando a e b, seja aplicando o teorema do valor intermediario.

             if(COND_TEOR_VAL_INTERM==0){ // Aqui ou a ou b são raízes.
                    if(Func_RaizQuadrada(a,d)==0)
                    printf("A raíz quadrada de %lf é %lf", d, a);
                    else
                    printf("A raíz quadrada de %lf é %lf", d, b);
             }
             else{
                    Bisseccao_RAIZ_QUADRADA(a,b,d); // Função que irá aplicar o método da bissecção no intervalo dado para o cálculo da raíz quadrada de d.
             }
        break;

        case 2:


              do{
                printf("\n Por favor digite, respectivamente, 1 ou 2 ou 3 para aplicar o método da bissecção ou Método de Newton ou Método da Secante. \n\n\t");
                scanf("%d", &EscolhaMetodo);

                switch(EscolhaMetodo){
                case 1:

                      printf("\n\n\t\t\t\t  _____________________________________________________________________________ ");
                      printf("  \n \t\t\t\t |                                                                             | ");
                      printf("\n \t\t\t\t |A opção escolhida foi o método da bissecção para o cálculo da raíz da função | ");
                      printf("\n\t\t\t\t |_____________________________________________________________________________| \n\n" );

                      do{
                        printf("\n Por favor, digite o intervalo onde devemos buscar a raiz.  (ex. [1;2] = digite 1 2): \n");
                        scanf("%lf %lf",&a,&b);
                        COND_TEOR_VAL_INTERM = Funcao(a)*Funcao(b);

                        if(COND_TEOR_VAL_INTERM>0){
                            printf("\n Não temos garantia, pelo teorema do valor intermediário, de exitência de raíz de f no intervalo informado.\n");
                        }
                      }while(COND_TEOR_VAL_INTERM>0); // Condição para garantirmos uma raíz no intervalo fechado [a,b]. Seja testando a e b, seja aplicando o teorema do valor intermediario.

                      if(COND_TEOR_VAL_INTERM==0){ // Aqui ou a ou b são raízes.
                        if(Funcao(a)==0)
                                printf("Uma raíz da função é %lf", a);
                          else
                                printf("Uma raíz da função é %lf",  b);
                      }
                        else{
                          Bisseccao(a,b); // Função que irá aplicar o método da bissecção no intervalo dado para o cálculo da raíz quadrada de d.
                      }
                break;
                case 2:

                      printf("\n\n\t\t\t\t  _____________________________________________________________________________ ");
                      printf("  \n \t\t\t\t |                                                                             | ");
                      printf("\n \t\t\t\t | A opção escolhida foi o  método de Newton para o cálculo da raíz da função  |  ");
                      printf("\n\t\t\t\t |_____________________________________________________________________________| \n\n" );


                      printf("Por favor, digite um chute inicial para o valor da raíz da função: \n \n\t");
                      scanf("%lf", &ChuteNewton);

                      Newton(ChuteNewton);
                break;
                case 3:

                      printf("\n\n\t\t\t\t  ________________________________________________________________________________ ");
                      printf("  \n \t\t\t\t |                                                                                | ");
                      printf("\n \t\t\t\t | A opção escolhida foi o  método das secantes para o cálculo da raíz da função. | ");
                      printf("\n\t\t\t\t |________________________________________________________________________________| \n\n" );

                      do{
                      printf("Por favor, digite um dois valores iniciais para aplicarmos o método da secante: \n\n ");
                      scanf("%lf %lf", &Valor1Secante, &Valor2Secante);

                        if(Funcao(Valor1Secante) ==Funcao(Valor2Secante)){
                            printf("\n As imagens da função nos valores fornecidos coincidem. Portanto não podemos aplicar o Método da secante com esses valores.\n");
                        }

                      }while(Funcao(Valor1Secante) ==Funcao(Valor2Secante));

                      Secante(Valor1Secante, Valor2Secante);

                        break;

                        default:
                        printf("\n\n  Opção inválida. \n\n");
                }

                }while(EscolhaMetodo != 1 && EscolhaMetodo != 2 && EscolhaMetodo !=3);


        break;

        default:
        printf("\n\n  Opção inválida. \n\n");

            }
        }while(OPCAO !=1 && OPCAO != 2 );// Para que o usuário escolha uma das opções



    printf("   \n\n   Digite 1 para permanecer no progrma e outro valor para sair. \n\n \t");
    scanf("%d", & Continuar);

    } while(Continuar ==1); // para que se retorne as opções até que o usuario digite a opção 4.

    return 0;
}
