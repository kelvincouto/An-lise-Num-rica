#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<locale.h> // Para colocar acentua��o


double Func_1 (double x);
double Func_2 (double x);
double Func_Runge (double x);
double romberg(double f(double), double a, double b, int ITMAX, double Precisao, double **R);

double Func_1 (double x)
{
  return pow(x,2);
}

double  Func_2(double x) // Calcula f(x)=1/(1-x)
{
   return 1.0/(1.0-x);
}

double  Func_Runge(double x) // Calcula f(x)=1/(1-x)
{
   return (1.0/(1.0+pow(x,2)));
}

double Trapz(double f(double), double a, double b, double t, int i) // Fun��o para o c�lculo dos elementos da primeira coluna
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

double romberg(double f(double), double a, double b, int ITMAX, double Precisao, double **R)
{
  int i, j, k, Cont;
  double h,t, sum, DIF, Melhor_APRX;
  
  h = b - a;
  t = 0.5 * h * (f(a) + f(b));
  R[0][0] = Trapz(f, a, b, t , 0);
  /*printf("  R[0][0] = %f  ", R[0][0]);*/ // Ative para verificar a tabela de Romberg
  Melhor_APRX = R[0][0];
  Cont=1;

      for (i = 1; i < ITMAX; i++)
      {
         h *= 0.5;
         sum = 0;
         for (k = 1; k <= pow(2,i)-1; k+=2)
         {
           sum += f(a + k * h);
         }
         R[i][0] = Trapz(f, a, b, R[i-1][0] , i);
         for (j = 1; j <= i; j++)
         {
           R[i][j] = R[i][j-1] + (R[i][j-1] - R[i-1][j-1]) / (pow(4,j)-1);
         }
         Melhor_APRX = R[i][i];
         DIF= fabs(R[i][i]-R[i][i-1])/fabs(R[i][i]);
         Cont=Cont+1;

         if(DIF <= Precisao){
            break;
         }
       }
      if(Cont==ITMAX){
        printf("\n O n�mero m�ximo de itera��es %d foi atingido.\n", ITMAX);
      }
      if(DIF <= Precisao){
        printf("\n A precis�o desejada foi alcan�ada. O erro relativo foi: %1lf. \n", DIF);
      }
      if(DIF > Precisao){
        printf("\n A precis�o desejada n�o foi alcan�ada. O erro relativo foi: %1lf. \n", DIF);
      }
      printf("\n Na itera��o %d ocorreu uma melhor aproxima��o para a integral da fun��o, de %lf a %lf. Que foi: %.10lf \n", Cont,a, b, Melhor_APRX);
      
     
	  if(ITMAX<=6|| Cont <=6) // Imprimiremos a tabela de Romberg para valores de n compat�veis com o tamanho da tela no terminal
   {
      printf("A tabela de Romberg �: \n\n");
      printf("  R[0][0] = %lf  ", R[0][0]);
      for (i = 1; i < Cont; i++)
      {
         printf("\n");
         printf("  R[%d][0] = %lf  ", i, R[i][0]);
         for (j = 1; j <= i; j++)
         {
          printf("  R[%d][%d] = %lf ", i,j, R[i][j]);
         }
       }
   }
   printf("\n");
}


int main()
{
  int i,ITMAX, codigoAcao;
  double a,b, Precisao, TOL;

  setlocale(LC_ALL, "portuguese"); // Para colocar acentua��o.
  system("color E5"); // Apenas para est�tica. Deixa o fundo amarelo "E". e a letra roxa "5".

  printf(" \n Observa��es: \n \t");
  printf(" \n (1) Os n�meros decimais devem ser digitados com v�rgula e n�o ponto, pois o programa est� configurado para l�ngua portuguesa. Caso o usu�rio queira desativar o uso da l�ngua portuguesa, basta desativar a linha do c�gido que cont�m o comando: setlocale. Por�m, as mensagens ficar�o sem acentua��o. \n");
    printf(" \n (2) As fun��es trabalhadas neste c�digo s�o as originais do enunciado do EP, mas o usu�rio pode altera-las diretamente no c�digo de acordo com seu interesse.\n\n ");
  /*printf(" \n Digite o n�mero m�ximo de itera��es:  \t");
  scanf("%d", &ITMAX);*/ // Ative este coment�rio e desative a linha abaixo para escolher o valor ITMAX diretamente no terminal.
  ITMAX=28;
  /*printf(" \n Digite a precis�o desejada:  \t");
  scanf("%lf", &Precisao);*/ //Ative este coment�rio e desative a linha abaixo para escolher o valor Precisao diretamente no terminal.
  Precisao=0,0000001;

  double **R;
  double Func_1(double), Func_2(double), Func_Runge(double);

  R = calloc(ITMAX, sizeof(double *));

  if(R == NULL){// Teste para verificar se ocorreu tudo bem na aloca��o.
    printf(" \n Erro de aloca��o de mem�ria Diagonal Principal. \n");
    system("pause");
    exit(1);
               }

  /*printf(" \n Digite o valor inicial do intervalo:  \t");
  scanf("%lf", &a);*/ // Ative este coment�rio e desative a linha abaixo para escolher o valor a diretamente no terminal.
  a=-5;

  /*printf(" \n Digite o valor final do intervalo:  \t");
  scanf("%lf", &b);*/ //Ative este coment�rio e desative a linha abaixo para escolher o valor b diretamente no terminal.
  b=5;

  for (i = 0; i < ITMAX; i++)
    R[i] = calloc(ITMAX, sizeof(double));
  printf("\n --> Para fun��o f(x)= x^2. Temos: \n");
  romberg(Func_1, a, b,ITMAX,Precisao, R);
  printf("\n --> Para fun��o f(x)= 1/(1-x). Temos: \n");
  romberg(Func_2, a, b,ITMAX,Precisao, R);
  printf("\n -->Para fun��o Runge f(x)= 1/(1+x^2). Temos: \n");
  romberg(Func_Runge, a, b,ITMAX,Precisao, R);


return 0;
}
