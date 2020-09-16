#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double romberg(double f(double), double a, double b, int n, double **R, int l);

double F (double y)
{
  return (12*y*(1-y)-2);
}

double  Chapeu(int j, double y, double h)
{
    double phi_y;
    if(y>= (j-1)*h && y <= j*h){
        phi_y=(y-(j-1)*h)/h;
    }
    else if(y>= j*h && y <= (j+1)*h){
            phi_y=((j+1)*h-y)/h;
            }
        else
            phi_y=0;
   return phi_y;
}

double romberg(double f(double), double a, double b, int n, double **R, int l)
{
  int i, j, k;
  double h, sum;


  h = b - a;
  R[0][0] = 0.5 * h * (f(a)*Chapeu(l,a,h) + f(b)*Chapeu(l,b,h));
  /*printf(" R[0][0] = %f\n", R[0][0]);*/

  for (i = 1; i <= n; i++)
  {
     h *= 0.5;
     sum = 0;
     for (k = 1; k <= pow(2,i)-1; k+=2)
     {
       sum += f(a + k * h)*Chapeu(l,a+k*h,h);
     }
     R[i][0] = 0.5 * R[i-1][0] + sum * h;
     /*printf(" R[%d][0] = %f\n", i, R[i][0]);*/
     for (j = 1; j <= i; j++)
     {
       R[i][j] = R[i][j-1] + (R[i][j-1] - R[i-1][j-1]) / (pow(4,j)-1);
       /*printf(" R[%d][%d] = %f\n", i,j, R[i][j]);*/
     }
   }
   return R[n][n];
}

int main()
{
  int n = 10;
  int i,l;
  double **R;
  double F(double);
  double B[5];

  R = calloc((n+1), sizeof(double *));
  for (i = 0; i <= n; i++)
    R[i] = calloc((n+1), sizeof(double));
  printf("The first function is F(x) = 1/(1 + x)\n");
  printf("\n melhor aprox em 1 %lf \n",   romberg(F, 0.0, 2.0,10, R,1));
  printf("\n  melhor aprox %lf em 2 \n",   romberg(F, 0.0, 2.0,10, R,2));

  printf("\n melhor aprox em 3 %lf \n",   romberg(F, 0.0, 2.0,10, R,3));

        for(i=1; i<=5; i++){// Declaro a matriz dos termos independentes do sistema (10), na questão 1.
                B[i-1]=romberg(F, 0.0, 2.0,10, R,i);
        }

        printf("\n\n O vetor de termos independentes do nosso sistema (14) é:  \n \n \t", i+1);
        for(i=0; i<n; i++){ // Conferência do vetor B
            printf("   %lf   ", B[i]);
        }

return 0;

}
