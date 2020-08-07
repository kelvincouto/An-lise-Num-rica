#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<locale.h> // Para colocar acentua��o


double Polinomio (double x);
double romberg(double f(double), double a, double b, int n, double **R);

double Polinomio (double x)// Fun��o usada para c�lculo do polin�mio
{
  return pow(x,2); // Aqui o usu�rio deve digitar o polin�mio que quer integrar. Veja que originalmente est� a fun��o polinomial f(x) =x^2 do enunciado do EP.
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

double romberg(double f(double), double a, double b, int n, double **R) // Fun��o que aplica o m�todo de Romberg
{
  int i, j, k;
  double h,t, sum, ValorExato, SolExata;

  SolExata=1.0/3.0;
  h = b - a;
  t = 0.5 * h * (f(a) + f(b));
  R[0][0] = Trapz(f, a, b, t , 0);

  for (i = 1; i < n; i++)
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
   }

   printf("\n O valor exato da integral ocorre na itera��o %d, e �: %lf \n",n, R[n-1][n-1]);
   printf("\n De fato, a solu��o � exata. Veja que o erro cometido �: %lf \n \n\n",n, SolExata - R[n-1][n-1]);


   if(n<=6) // Imprimiremos a tabela de Romberg para valores de n compat�veis com o tamanho da tela no terminal
   {
      printf("A tabela de Romberg �: \n\n");
      printf("  R[0][0] = %e  ", R[0][0]);
      for (i = 1; i < n; i++)
      {
         printf("\n");
         printf("  R[%d][0] = %e  ", i, R[i][0]);
         for (j = 1; j <= i; j++)
         {
          printf("  R[%d][%d] = %e ", i,j, R[i][j]);
         }
       }
   }

   printf(" \n\n");

}

int main()
{
  int i,n, Grau;
  double a,b;

  setlocale(LC_ALL, "portuguese"); // Para colocar acentua��o.
  system("color E5"); // Apenas para est�tica. Deixa o fundo amarelo "E". e a letra roxa "5".

  printf(" \n Observa��es: \n \t");
  printf(" \n (1) Os n�meros decimais devem ser digitados com v�rgula e n�o ponto, pois o programa est� configurado para l�ngua portuguesa. Caso o usu�rio queira desativar o uso da l�ngua portuguesa, basta desativar a linha do c�gido que cont�m o comando: setlocale. Por�m, as mensagens ficar�o sem acentua��o. \n");
  printf(" \n (2) Este c�digo � direcionado para resolu��o de integrais em que o integrando � um polin�mio. Lembremos que no exerc�cio 3 da lista 5 foi provado que: A n-�sima coluna da tabela de Romberg apresenta solu��o exata para polin�mios em P_{2n+1}, n=0,1,2... \n");
  printf(" \n (3) O usu�rio deve digitar o polin�mio, limites de integra��o e grau do polin�mio diretamente no c�digo. Mas pode ativar o comando para digita-los no terminal caso prefira. Veja Relat�rio.  \n ");
  printf(" \n (4) O c�digo ir� gerar a tabela de Romberg para integra��o de polin�mios de grau menor ou igual a 11. \n\n");
  printf(" \n (5) As itera��es ser�o contadas em cada coluna gerada. \n\n");

  /*printf(" \n Digite o grau do polin�mio a ser integrado: \t");
  scanf("%d", &Grau);*/
  Grau = 2;

  // A seguir escolhemos um valor n de acordo com a nossa obsereva��o (2).
  if(Grau==0){
    n=1;
  }
  else if (Grau==2){
    n=2;
  }
  else if ( (Grau %2) != 0){
    n= ((Grau -1)/2) +1;
  }
  else{
    n= Grau/2 +1;
  }

  double **R;
  double Polinomio(double);

  R = calloc(n, sizeof(double *));

  if(R == NULL){// Teste para verificar se ocorreu tudo bem na aloca��o.
    printf(" \n Erro de aloca��o de mem�ria Diagonal Principal. \n");
    system("pause");
    exit(1);
               }

  /*printf(" \n Digite o valor inicial do intervalo de integra��o: \n \t");
  scanf("%lf", &a);*/ // Ative caso queira digitar no terminal o valor de a e desative a linha abaixo.
  a=0;

  /*printf(" \n Digite o valor final do intervalo de integra��o: \n \t");
  scanf("%lf", &b);*/ // Ative caso queira digitar o valor de b no teminal e destive a linha abaixo.
  b=1;

  for (i = 0; i < n; i++)
    R[i] = calloc(n, sizeof(double));
  romberg(Polinomio, a, b,n, R);

return 0;
}
