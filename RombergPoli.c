#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<locale.h> // Para colocar acentuação


double Polinomio (double x);
double romberg(double f(double), double a, double b, int n, double **R);

double Polinomio (double x)// Função usada para cálculo do polinômio
{
  return pow(x,2); // Aqui o usuário deve digitar o polinômio que quer integrar. Veja que originalmente está a função polinomial f(x) =x^2 do enunciado do EP.
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

double romberg(double f(double), double a, double b, int n, double **R) // Função que aplica o método de Romberg
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

   printf("\n O valor exato da integral ocorre na iteração %d, e é: %lf \n",n, R[n-1][n-1]);
   printf("\n De fato, a solução é exata. Veja que o erro cometido é: %lf \n \n\n",n, SolExata - R[n-1][n-1]);


   if(n<=6) // Imprimiremos a tabela de Romberg para valores de n compatíveis com o tamanho da tela no terminal
   {
      printf("A tabela de Romberg é: \n\n");
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

  setlocale(LC_ALL, "portuguese"); // Para colocar acentuação.
  system("color E5"); // Apenas para estética. Deixa o fundo amarelo "E". e a letra roxa "5".

  printf(" \n Observações: \n \t");
  printf(" \n (1) Os números decimais devem ser digitados com vírgula e não ponto, pois o programa está configurado para língua portuguesa. Caso o usuário queira desativar o uso da língua portuguesa, basta desativar a linha do cógido que contém o comando: setlocale. Porém, as mensagens ficarão sem acentuação. \n");
  printf(" \n (2) Este código é direcionado para resolução de integrais em que o integrando é um polinômio. Lembremos que no exercício 3 da lista 5 foi provado que: A n-ésima coluna da tabela de Romberg apresenta solução exata para polinômios em P_{2n+1}, n=0,1,2... \n");
  printf(" \n (3) O usuário deve digitar o polinômio, limites de integração e grau do polinômio diretamente no código. Mas pode ativar o comando para digita-los no terminal caso prefira. Veja Relatório.  \n ");
  printf(" \n (4) O código irá gerar a tabela de Romberg para integração de polinômios de grau menor ou igual a 11. \n\n");
  printf(" \n (5) As iterações serão contadas em cada coluna gerada. \n\n");

  /*printf(" \n Digite o grau do polinômio a ser integrado: \t");
  scanf("%d", &Grau);*/
  Grau = 2;

  // A seguir escolhemos um valor n de acordo com a nossa obserevação (2).
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

  if(R == NULL){// Teste para verificar se ocorreu tudo bem na alocação.
    printf(" \n Erro de alocação de memória Diagonal Principal. \n");
    system("pause");
    exit(1);
               }

  /*printf(" \n Digite o valor inicial do intervalo de integração: \n \t");
  scanf("%lf", &a);*/ // Ative caso queira digitar no terminal o valor de a e desative a linha abaixo.
  a=0;

  /*printf(" \n Digite o valor final do intervalo de integração: \n \t");
  scanf("%lf", &b);*/ // Ative caso queira digitar o valor de b no teminal e destive a linha abaixo.
  b=1;

  for (i = 0; i < n; i++)
    R[i] = calloc(n, sizeof(double));
  romberg(Polinomio, a, b,n, R);

return 0;
}
