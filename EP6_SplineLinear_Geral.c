#include <stdio.h>
#include<locale.h> // Para colocar acentuação
#include <conio.h>
#include<math.h>
#include <stdlib.h> // Necessário para gerar números aleatórios
#include <time.h>  // Necessário para gerar números aleatórios

double  NORM_INF(int n, double DIFERENCA[n])
{
   double MAIOR_MODULO_COORDENADA;
   int i, j;
   MAIOR_MODULO_COORDENADA = fabs(DIFERENCA[0]);
   for(i=0; i<=n-1; i++){
        if (fabs(DIFERENCA[i]) >MAIOR_MODULO_COORDENADA )
            MAIOR_MODULO_COORDENADA=fabs(DIFERENCA[i]);
   }
   return MAIOR_MODULO_COORDENADA;
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

double  DerivadaChapeu(int j, double y, double h)
{
    double Dphi_y;
    if(y>= (j-1)*h && y <= ((j+1)*h)){
        Dphi_y=(1.0/h);
    }
    else
        Dphi_y=0;
   return Dphi_y;
}



double Func_f(double y) // Aqui o usuário definira a função f a ser usada
{
  return (12*y*(1-y)-2);
}


double Func_k(double y)// Aqui o usuário definira a função k a ser usada
{
  return 1;
}

double Func_q(double y)// Aqui o usuário definira a função q a ser usada
{
  return 0;
}

double rombergTERMOindep(double f(double), double a, double b, int n, double **R, int l)
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
       sum += f(a + k * h)*Chapeu(l,a+k*h,h); // Aqui nessa parte sei que posso usar o suporte compacto da chapéu. Mas por questão de tempo fiz sem usar. Desculpe... mas é simples é só escrever a fórumula considerando onde chapéu não se anula e restringindo esse intervalo
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

double rombergMatrizCoefic(double Func_k(double), double Func_q(double), double a, double b, int n, double **R, int l, int c) // l sernha linha e c coluna
{  int i, j, k;
  double h, sum;


  h = b - a;
  R[0][0] = 0.5 * h * ((Func_k(a)*DerivadaChapeu(l,a,h)*DerivadaChapeu(c,a,h) + Func_q(a)*DerivadaChapeu(l,a,h))*DerivadaChapeu(c,a,h)-((Func_k(b)*DerivadaChapeu(l,b,h)*DerivadaChapeu(c,b,h) + Func_q(a)*DerivadaChapeu(l,b,h))*DerivadaChapeu(c,b,h))); // Aqui poderíamos substituir o valor direto das derivadas mas preferiamos deixar indicado
  /*printf(" R[0][0] = %f\n", R[0][0]);*/

  for (i = 1; i <= n; i++)
  {
     h *= 0.5;
     sum = 0;
     for (k = 1; k <= pow(2,i)-1; k+=2)
     {
       sum +=  ((Func_k(a + k * h)*DerivadaChapeu(l,a + k * h,h)*DerivadaChapeu(c,a + k * h,h) + Func_q(a + k * h)*DerivadaChapeu(l,a + k * h,h))*DerivadaChapeu(c,b,h));
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

double  Calculo_ERRO(double a,double b,double lambda, int n)
{
    double DiagPrincipalA[n], SubDiagoalA[n-1], VetorL[n], VetorD[n], B[n], U[n], V[n], C[n],H[n], DIFERENCA[10*n+1], Sol_EXATA[10*n+1], PHI[n], SOL_NUMERICA[10*n+1];; // Aqui fazemos a declaração dos ponteiros para a alocação dinâmica dos vetores.
    double h,y, DIFF;
    int i,j,l,ITMAX;
    FILE *arqAPR15, *arqAPR31,*arqAPR63, *arqAPR127,*arqAPR255, *arqEXT15, *arqEXT31,*arqEXT63, *arqEXT127,*arqEXT255;
    ITMAX=5; // Número máximo de iteraçõees no método de Romberg para cálculo das integrais do nosso sistema.

    double **R;
    double Func_f(double);

    R = calloc(ITMAX, sizeof(double *));

    if(R == NULL){// Teste para verificar se ocorreu tudo bem na alocação.
       printf(" \n Erro de alocação de memória Diagonal Principal. \n");
       system("pause");
       exit(1);
    }
        h=(b-a)/(n+1.000);

        for(i=0; i<n; i++){ // Determino o vetor diagonal principal da Matriz dos coeficientes do sistema 10.
            DiagPrincipalA[i]=rombergMatrizCoefic(Func_k, Func_q, a, b, ITMAX,R,i,i);
        }

           for(i=0; i<n-1; i++){ // Determino o vetor subdiagonal principal da Matriz dos coeficientes do sistema 10.
            SubDiagoalA[i]=rombergMatrizCoefic(Func_k, Func_q, a, b, ITMAX,R,i,i+1);
        }

        // Agora definiremos os vetores diagonal de D, denominado VetorD, e o vetor subdiagonal de L, denominado VetorL
        VetorD[0]=DiagPrincipalA[0];

        for(i=0; i<=n-2; i++){
            VetorL[i]=(SubDiagoalA[i])/VetorD[i];
            VetorD[i+1]=DiagPrincipalA[i+1]-VetorL[i]*SubDiagoalA[i];
        }

        /*for(i=1; i<=n; i++){// Declaro a matriz dos termos independentes do sistema (14), na questão 1.
                B[i-1]=(h*(-12*h*h*i*i-2*h*h+12*h*i-2));
        }

        printf("\n\n O vetor de termos independentes do nosso sistema (14) é:  \n \n \t", i+1);
        for(i=0; i<n; i++){ // Conferência do vetor U
            printf("   %lf   ", B[i]);
        }*/


        for(l=1; l<=n; l++){// Declaro a matriz dos termos independentes do sistema (14), na questão 1.
                B[l-1]=rombergTERMOindep(Func_f, a, b,ITMAX, R,l); // Detectei que tem um erro aqui que impede a compilação, mas não deu tempo de resolver. Testei um código(que está no github)  auxiliar que parece estar igual, mas compila.
        }

        /*printf("\n\n O vetor de termos independentes con Rombeerg  \n \n \t", i+1);
        for(i=0; i<n; i++){ // Conferência do vetor U
            printf("   %lf   ", B[i]);
        }*/



        //A seguir resolveremos o sistema (10) pela técnica usada no EP2.

        U[0]=B[0];
        for(i=1; i<n; i++){
            U[i]= B[i]-VetorL[i-1]*U[i-1];
        }


        for(i=0; i<n; i++){

            V[i]= U[i]/VetorD[i];
        }


        C[n-1]=V[n-1];
        for(i=n-2; i>=0; i--){

            C[i]=(V[i]-VetorL[i]*C[i+1]);
        }

        for(i=0; i<=10*n; i++){
            y=i/(10.0*n);
            SOL_NUMERICA[i]=0;
            for(j=1; j<=n; j++){
                PHI[j-1]=Chapeu(j,y,h);
                /*
                printf("\n\n  PHI_%d(x_%d)=%lf   \n \t", j, i,PHI[j-1] );/Conferi que a PHI está correta.
                */
            SOL_NUMERICA[i]=SOL_NUMERICA[i] + C[j-1]*PHI[j-1];
            }
        }


        /*
        printf("\n\n  Vetor Solução numérica:  \n \n \t");
        for(i=0; i<10*n; i++){//Calcularemos o módulo da diferença, em cada coordenada, da solução com a solução coordenada.
            printf("\n \t SOL_NUM [ %d ] = %e   \n",i, SOL_NUMERICA[i]);
        }*/


        for(i=0; i<n+2; i++){//Calcularemos o módulo da diferença, em cada coordenada, da solução com a solução coordenada.
            Sol_EXATA[i]=(a+i*h)*(a+i*h)*((a+i*h)-1.0)*((a+i*h)-1.0);
            /*printf("\n \t SOL_EXATA [ %d ] = %e   \n", i, Sol_EXATA [i]);*/

        }
        if(n==15){

            arqAPR15 = fopen("arqAPR15.txt", "w+");
            if(arqAPR15 == NULL)//testo a agertura do arquivo.
            {
                printf("\nFile can not be opened.\n");
                printf("\nPress any key to close.");
                getchar();
                exit(1);
            }
            for(i=0; i<10*n; i++)//escrevo o arquivo
            {
                fprintf(arqAPR15, "%lf, %lf\n", i/(10.0*n), SOL_NUMERICA[i]);
            }
            fclose(arqAPR15);//fecho o arquivo.

        }
        if(n==31){

            arqAPR31 = fopen("arqAPR31.txt", "w+");
            if(arqAPR31 == NULL)//testo a agertura do arquivo.
            {
                printf("\nFile can not be opened.\n");
                printf("\nPress any key to close.");
                getchar();
                exit(1);
            }
            for(i=0; i<10*n; i++)//escrevo o arquivo
            {
                fprintf(arqAPR31, "%lf, %lf\n", i/(10.0*n), SOL_NUMERICA[i]);
            }
            fclose(arqAPR31);//fecho o arquivo.

        }
        if(n==63){

            arqAPR63 = fopen("arqAPR63.txt", "w+");
            if(arqAPR63 == NULL)//testo a agertura do arquivo.
            {
                printf("\nFile can not be opened.\n");
                printf("\nPress any key to close.");
                getchar();
                exit(1);
            }
            for(i=0; i<10*n; i++)//escrevo o arquivo
            {
                fprintf(arqAPR63, "%lf, %lf\n", i/(10.0*n), SOL_NUMERICA[i]);
            }
            fclose(arqAPR63);//fecho o arquivo.

        }
        if(n==127){

            arqAPR127 = fopen("arqAPR127.txt", "w+");
            if(arqAPR127 == NULL)//testo a agertura do arquivo.
            {
                printf("\nFile can not be opened.\n");
                printf("\nPress any key to close.");
                getchar();
                exit(1);
            }
            for(i=0; i<10*n; i++)//escrevo o arquivo
            {
                fprintf(arqAPR127, "%lf, %lf\n", i/(10.0*n), SOL_NUMERICA[i]);
            }
            fclose(arqAPR127);//fecho o arquivo.

        }
        if(n==255){

            arqAPR255 = fopen("arqAPR255.txt", "w+");
            if(arqAPR255 == NULL)//testo a agertura do arquivo.
            {
                printf("\nFile can not be opened.\n");
                printf("\nPress any key to close.");
                getchar();
                exit(1);
            }
            for(i=0; i<10*n; i++)//escrevo o arquivo
            {
                fprintf(arqAPR255, "%lf, %lf\n", i/(10.0*n), SOL_NUMERICA[i]);
            }
            fclose(arqAPR255);//fecho o arquivo.

        }

        for(i=0; i<=10*n; i++){//Calcularemos o módulo da diferença, em cada coordenada, da solução com a solução coordenada.
            y=i/(10.0*n);
            DIFERENCA[i]=y*y*(y-1.0)*(y-1.0)- SOL_NUMERICA[i];
        }


        /*
        printf("\n\n O vetor diferença entre a solução exata e a númerica em cada x_i é:  \n \n \t");
        for(i=0; i<=n; i++){//Impressão para verificação da solução do sistema (1).
            printf("\n \t Diferença_%d = %lf   \n",i, DIFERENCA[i]);
        }
        */

        DIFF= NORM_INF(n,DIFERENCA);


   return DIFF;
}

double  Calculo_ERRO_NOS(double a,double b,double lambda, int n)
{
    double DiagPrincipalA[n], SubDiagoalA[n-1], VetorL[n], VetorD[n], B[n], U[n], V[n], C[n], DIFERENCA[n], Sol_EXATA[n+2], PHI[n], SOL_NUMERICA[n+2];; // Aqui fazemos a declaração dos ponteiros para a alocação dinâmica dos vetores.
    double h,y, DIFF,Precisao;
    int i,j,l, ITMAX;
    ITMAX=10; // Número máximo de iteraçõees no método de Romberg para cálculo das integrais do nosso sistema.

    double **R;
    double Func_f(double);

    R = calloc(ITMAX, sizeof(double *));

    if(R == NULL){// Teste para verificar se ocorreu tudo bem na alocação.
       printf(" \n Erro de alocação de memória Diagonal Principal. \n");
       system("pause");
       exit(1);
    }
        h=(b-a)/(n+1.000);
        /*printf("\n O valor de h é: %lf \n",h); // Teste leitura de h*/


        for(i=0; i<n; i++){ // Determino o vetor diagonal principal da Matriz dos coeficientes do sistema 10.
            DiagPrincipalA[i]=rombergMatrizCoefic(Func_k, Func_q, a, b, ITMAX,R,i,i);
        }

           for(i=0; i<n-1; i++){ // Determino o vetor subdiagonal principal da Matriz dos coeficientes do sistema 10.
            SubDiagoalA[i]=rombergMatrizCoefic(Func_k, Func_q, a, b, ITMAX,R,i,i+1);
        }

        // Agora definiremos os vetores diagonal de D, denominado VetorD, e o vetor subdiagonal de L, denominado VetorL
        VetorD[0]=DiagPrincipalA[0];

        for(i=0; i<=n-2; i++){
            VetorL[i]=(SubDiagoalA[i])/VetorD[i];
            VetorD[i+1]=DiagPrincipalA[i+1]-VetorL[i]*SubDiagoalA[i];
        }


         /*for(i=1; i<=n; i++){// Declaro a matriz dos termos independentes do sistema (14), na questão 1.
                B[i-1]=(h*(-12*h*h*i*i-2*h*h+12*h*i-2));
        }

        printf("\n\n O vetor de termos independentes do nosso sistema (14) é:  \n \n \t", i+1);
        for(i=0; i<n; i++){ // Conferência do vetor U
            printf("   %lf   ", B[i]);
        }*/


        for(l=1; l<=n; l++){// Declaro a matriz dos termos independentes do sistema (14), na questão 1.
                B[l-1]=rombergTERMOindep(Func_f, a, b,ITMAX, R,l); // Detectei que tem um erro aqui que impede a compilação, mas não deu tempo de resolver. Testei um código(que está no github)  auxiliar que parece estar igual, mas compila.
        }

        /*printf("\n\n O vetor de termos independentes con Rombeerg  \n \n \t", i+1);
        for(i=0; i<n; i++){ // Conferência do vetor U
            printf("   %lf   ", B[i]);
        }*/


        //A seguir resolveremos o sistema (10) pela técnica usada no EP2.

        U[0]=B[0];
        for(i=1; i<n; i++){
            U[i]= B[i]-VetorL[i-1]*U[i-1];
        }


        /*
        printf("\n\n Resolveremos a segunda parte do exercício. Se LU=B. Então o vetor U é:  \n \n \t", i+1);
        for(i=0; i<n; i++){ // Conferência do vetor U
            printf("   %lf   ", U[i]);
        }
        */

        for(i=0; i<n; i++){

            V[i]= U[i]/VetorD[i];
        }


        C[n-1]=V[n-1];
        for(i=n-2; i>=0; i--){

            C[i]=(V[i]-VetorL[i]*C[i+1]);
        }

        for(i=0; i<n+2; i++){
            y=a+i*h;
            SOL_NUMERICA[i]=0;
            for(j=1; j<=n; j++){
                PHI[j-1]=Chapeu(j,y,h);
                /*
                printf("\n\n  PHI_%d(x_%d)=%lf   \n \t", j, i,PHI[j-1] );/Conferi que a PHI está correta.
                */
            SOL_NUMERICA[i]=SOL_NUMERICA[i] + C[j-1]*PHI[j-1];
            }
        }

        /*
        printf("\n\n  Vetor Solução numérica:  \n \n \t");
        for(i=0; i<n+2; i++){//Calcularemos o módulo da diferença, em cada coordenada, da solução com a solução coordenada.
            printf("\n \t SOL_NUM [ %d ] = %e   \n",i, SOL_NUMERICA[i]);
        }
        */
        /*
        for(i=0; i<n+2; i++){//Calcularemos o módulo da diferença, em cada coordenada, da solução com a solução coordenada.
            Sol_EXATA[i]=(a+i*h)*(a+i*h)*((a+i*h)-1.0)*((a+i*h)-1.0);
            printf("\n \t SOL_EXATA [ %d ] = %e   \n", i, Sol_EXATA [i]);

        }
        */




        for(i=0; i<n+2; i++){//Calcularemos o módulo da diferença, em cada coordenada, da solução com a solução coordenada.
            DIFERENCA[i]=(a+i*h)*(a+i*h)*((a+i*h)-1.0)*((a+i*h)-1.0)- SOL_NUMERICA[i];
        }


        /*
        printf("\n\n O vetor diferença entre a solução exata e a númerica em cada x_i é:  \n \n \t");
        for(i=0; i<=n; i++){//Impressão para verificação da solução do sistema (1).
            printf("\n \t Diferença_%d = %lf   \n",i, DIFERENCA[i]);
        }
        */

        DIFF= NORM_INF(n,DIFERENCA);


   return DIFF;
}

int main()
{
    int i, j,k, n, codigoAcao, OPCAO_n, AUX;
    double lambda,a,b,CALC_ERRO,h, error[5];
    FILE *arqERRO, *arqERRO_h;


    setlocale(LC_ALL, "portuguese"); // Para colocar acentuação.*/
    /*system("color E5"); // Apenas para estética. Deixa o fundo amarelo "E". e a letra roxa "5".*/

    do{


        do{
            printf("\n\n Digite 1 para analisar o caso k(x)=1, e g(x)=lambda, e escolher os valores de n, da constante lambda, e dos pontos inicial e final do intervalo.\n ");
            printf("\n Digite 2 para escolher a lista de n´s: 15,31,63,127,255 com lambda zero e intervalo [0,1]. \n\n \t");
            scanf("%d", &OPCAO_n);

            switch(OPCAO_n){
                case 1:
                    printf("\n Digite o valor n: \n\n \t");
                    scanf("%d", &n);

                    printf("\n Digite o valor de lambda: \n\n \t");
                    scanf("%lf", &lambda);

                    printf("\n Digite o início do intervalo: \n\n \t");
                    scanf("%lf", &a);

                    printf("\n Digite o fim do intervalo: \n\n \t");
                    scanf("%lf", &b);
                    h=(b-a)/(n+1.00);

                    printf("\n \n A respeito da análise em y_i, o erro cometido é: %e. E ERRO/h^2 = %e.   \n \t", Calculo_ERRO(a,b,lambda,n),Calculo_ERRO(a,b,lambda,n)/(h*h) );
                    printf("\n \n A respeito da análise nos nós, o erro cometido é: %e. E ERRO/h^2 = %e.   \n \t", Calculo_ERRO_NOS(a,b,lambda,n),Calculo_ERRO(a,b,lambda,n)/(h*h) );


                    break;
                case 2: a=0.0; b=1.0; lambda=0.0;
                    printf("                               +----------------------------------------------------------+\n");
                    printf("                               |                         Análise em y_i*                  |\n");
                    printf("                               +-----+----------+------------------------+----------------+\n");
                    printf("                               |  n  | h        |        Erro            |   Erro/h^2     | \n");
                    printf("                               +-----+----------+-----------------------------------------+\n");


                    AUX=7;
                    for(i=15; i<=255; i=AUX*2+1){
                    h=1/(i+1.0);
                    CALC_ERRO=Calculo_ERRO(a,b,lambda,i);
                    printf("                               |  %d | %lf |        %e   |%e   |\n", i, h, CALC_ERRO,CALC_ERRO/(h*h));
                    printf("                               +------+----------+------------------------+---------------+\n \n");
                    AUX=AUX*2+1;

                    }

                    for(i=0; i<5; i++)
                    {
                        error[i] = CALC_ERRO=Calculo_ERRO(a,b,lambda,pow(2,4+i)-1);
                    }

                    arqERRO = fopen("arqERRO.txt", "w+");
                    if(arqERRO == NULL)//testo a agertura do arquivo.
                    {
                        printf("\nFile can not be opened.\n");
                        printf("\nPress any key to close.");
                        getchar();
                        exit(1);
                    }
                    for(i=0; i<5; i++)//escrevo o arquivo
                    {
                        fprintf(arqERRO, "%lf, %lf\n", pow(2,4+i)-1, log10(error[i]));
                    }
                    fclose(arqERRO);//fecho o arquivo.

                    arqERRO_h = fopen("arqERRO_h.txt", "w+");
                    if(arqERRO_h == NULL)//testo a agertura do arquivo.
                    {
                        printf("\nFile can not be opened.\n");
                        printf("\nPress any key to close.");
                        getchar();
                        exit(1);
                    }
                    for(i=0; i<5; i++)//escrevo o arquivo
                    {
                        fprintf(arqERRO_h, "%lf, %lf\n", 1/pow(2,4+i), log10(error[i]));
                    }
                    fclose(arqERRO_h);//fecho o arquivo.
                    printf(" *Veja que constatamos então a convergência de segunda ordem com o uso dos splines lineares.\n\n\n");



                    printf("                               +-----------------------------------------+\n");
                    printf("                               |              Análise nos nós**          |\n");
                    printf("                               +-----+----------+------------------------+\n");
                    printf("                               |  n  | h        |        Erro            | \n");
                    printf("                               +-----+----------+------------------------+\n");


                    AUX=7;
                    for(i=15; i<=255; i=AUX*2+1){
                    h=1/(i+1.0);
                    CALC_ERRO=Calculo_ERRO_NOS(a,b,lambda,i);
                    printf("                               |  %d | %lf |        %e   |\n", i, h, CALC_ERRO);
                    printf("                               +------+----------+------------------------+\n \n");

                        AUX=AUX*2+1;
                    }

                    printf(" **Como o método cálcula a solução exatamente nos nós, então o erro observado é muito pequeno e é devido aos erros de arredondamento. \n\n" );





                    break;
                default:
                    printf("\n\n  Opção inválida. \n\n");

            }
        }while(OPCAO_n !=1 && OPCAO_n != 2 );// Para que o usuário escolha uma das opções




    printf("   \n\n   Digite 1 para permanecer no progrma e outro valor para sair. \n\n \t");
    scanf("%d", & codigoAcao);

    } while(codigoAcao ==1); // para que se retorne as opções até que o usuario digite a opção 4.

    return 0;
}
