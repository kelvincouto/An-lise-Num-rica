#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<locale.h> // Para colocar acentuação

double Func(double x);
double romberg(double f(double), double a, double b, int IT,  double **R);

double Func(double x)
{
  return (1.0/(1.0-x));
}

double Trapz(double f(double), double a, double b, double t, int i) // Função para o cálculo dos elementos da primeira coluna
{
  int k;
  double h, sum;

  h = (b - a)/pow(2,i);
  if(i!=0)
        {
        sum = 0;
        for (k = 1; k <= pow(2,i)-1; k+=2)
            {
            sum += f(a + k * h);
            }
        t = 0.5 * t + sum * h;
        }
   return t;
}

double romberg(double f(double), double a, double b, int IT,  double **R)
{
  int i, j, k;
  double h,t, sum, ERRO[15];
 FILE *arqERRO; 
  
  h = b - a;
  t = 0.5 * h * (f(a) + f(b));
  R[0][0] = Trapz(f, a, b, t , 0);
     printf(" %lf ", R[0][0]);
      for (i = 1; i < 15; i++)
      {
         h *= 0.5;
         sum = 0;
      
         for (k = 1; k <= pow(2,i)-1; k+=2)
         {
           sum += f(a + k * h);
         }
         R[i][0] = Trapz(f, a, b, R[i-1][0] , i);
         printf("\n");
         printf(" %lf ",  R[i][0]);
         for (j = 1; j <= i; j++)
         {
           R[i][j] = R[i][j-1] + (R[i][j-1] - R[i-1][j-1]) / (pow(4,j)-1);
           printf(" %lf ",  R[i][j]);

         }

       }
       
    arqERRO= fopen("ERRO.txt", "w+");
        if(arqERRO == NULL)//testo a agertura do arquivo.
         {
            printf("\n File can not be opened.\n");
            printf("\n Press any key to close.");
            getchar();
		    exit(1);
        }
  

      printf("\n\n Os erros cometidos são: \n\n");

      for (i = 0; i < 15; i++)
      {
         printf("\n");
         ERRO[i] = ( 5.298317367)- R[i][i]; // Aqui o usuário deve digitar o valor exato da integral.
         printf("  R[%d][%d] = %lf  ",i,i, ERRO[i]);
         fprintf(arqERRO, "%d, %lf\n", i+1, ERRO[i]);

       }
                   fclose(arqERRO);//fecho o arquivo.

   
   printf("\n");
}

int main()
{
  int i, codigoAcao;
  double a,b;

  /*setlocale(LC_ALL, "portuguese"); // Para colocar acentuação.*/
  system("color E5"); // Apenas para estética. Deixa o fundo amarelo "E". e a letra roxa "5".

  printf(" \n O propósito deste código é não deixar os outros com muita informação e possibilitar que o usuário escolha o código que fará somente o que ele realemtne precisa \n \t");
  printf(" \n Aqui exibiremos uma tabela de Romberg para n=15, E exibiremos os 15 primeiros erros cometidos na iteração. \n");
  printf(" \n Também será gerado um arquivo .txt para fazermos o gráfico do erro em função de n\n");


  double **R;
  double Func_1(double), Func_2(double), Func_Runge(double);

  R = calloc(15, sizeof(double *));

  if(R == NULL){// Teste para verificar se ocorreu tudo bem na alocação.
    printf(" \n Erro de alocação de memória Diagonal Principal. \n");
    system("pause");
    exit(1);
               }

  /*printf(" \n Digite o valor inicial do intervalo:  \t");
  scanf("%lf", &a);*/ // Ative este comentário e desative a linha abaixo para escolher o valor a diretamente no terminal.
  a=-0;

  /*printf(" \n Digite o valor final do intervalo:  \t");
  scanf("%lf", &b);*/ //Ative este comentário e desative a linha abaixo para escolher o valor b diretamente no terminal.
  b=0.995;
  
  for (i = 0; i < 15; i++)
    R[i] = calloc(15, sizeof(double));
  printf("\n A tabela de Romberg até a iteração 15 para a funçao dada é: \n \n");
  romberg(Func, a, b,15, R);

return 0;
}
