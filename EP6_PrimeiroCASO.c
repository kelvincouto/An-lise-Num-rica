#include <stdio.h>
#include<locale.h> // Para colocar acentua��o
#include <conio.h>
#include<math.h>
#include <stdlib.h> // Necess�rio para gerar n�meros aleat�rios
#include <time.h>  // Necess�rio para gerar n�meros aleat�rios

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

double Func(double y)
{
  return (12*(y-1)-2);
}

double  Calculo_ERRO(double a,double b,double lambda, int n)
{
    double DiagPrincipalA[n], SubDiagoalA[n-1], VetorL[n], VetorD[n], B[n], U[n], V[n], C[n], DIFERENCA[10*n+1], Sol_EXATA[10*n+1], PHI[n], SOL_NUMERICA[10*n+1];; // Aqui fazemos a declara��o dos ponteiros para a aloca��o din�mica dos vetores.
    double h,y, DIFF,Precisao;
    int i,j,ITMAX;
    FILE *arqAPR15, *arqAPR31,*arqAPR63, *arqAPR127,*arqAPR255, *arqEXT15, *arqEXT31,*arqEXT63, *arqEXT127,*arqEXT255;
    ITMAX=28; // N�mero m�ximo de itera��ees no m�todo de Romberg para c�lculo das integrais do nosso sistema.
    Precisao=0,0000001; // A precis�o desejada no m�tdo de Romberg

    double **R;
    double Func(double);

    R = calloc(ITMAX, sizeof(double *));

    if(R == NULL){// Teste para verificar se ocorreu tudo bem na aloca��o.
       printf(" \n Erro de aloca��o de mem�ria Diagonal Principal. \n");
       system("pause");
       exit(1);
    }
        h=(b-a)/(n+1.000);

        for(i=0; i<n; i++){ // Determino o vetor diagonal principal da Matriz dos coeficientes do sistema 14.
            DiagPrincipalA[i]=(2.00/h)+lambda*h*(2/3.00);
        }

        for(i=0; i<n-1; i++){ // Determino o vetor subdiagonal principal da Matriz dos coeficientes do sistema 14.
            SubDiagoalA[i]=(-1.00/h)+lambda*(h/6.00);
        }


        // Agora definiremos os vetores diagonal de D, denominado VetorD, e o vetor subdiagonal de L, denominado VetorL
        VetorD[0]=DiagPrincipalA[0];

        for(i=0; i<=n-2; i++){
            VetorL[i]=(SubDiagoalA[i])/VetorD[i];
            VetorD[i+1]=DiagPrincipalA[i+1]-VetorL[i]*SubDiagoalA[i];
        }

        for(i=1; i<=n; i++){// Declaro a matriz dos termos independentes do sistema (14).
                B[i-1]=(h*(-12*h*h*i*i-2*h*h+12*h*i-2));
        }


        //A seguir resolveremos o sistema (10) pela t�cnica usada no EP2.

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
                printf("\n\n  PHI_%d(x_%d)=%lf   \n \t", j, i,PHI[j-1] );/Conferi que a PHI est� correta.
                */
            SOL_NUMERICA[i]=SOL_NUMERICA[i] + C[j-1]*PHI[j-1];
            }
        }


        /*
        printf("\n\n  Vetor Solu��o num�rica:  \n \n \t");
        for(i=0; i<10*n; i++){//Calcularemos o m�dulo da diferen�a, em cada coordenada, da solu��o com a solu��o coordenada.
            printf("\n \t SOL_NUM [ %d ] = %e   \n",i, SOL_NUMERICA[i]);
        }*/


        for(i=0; i<n+2; i++){//Calcularemos o m�dulo da diferen�a, em cada coordenada, da solu��o com a solu��o coordenada.
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

        for(i=0; i<=10*n; i++){//Calcularemos o m�dulo da diferen�a, em cada coordenada, da solu��o com a solu��o coordenada.
            y=i/(10.0*n);
            DIFERENCA[i]=y*y*(y-1.0)*(y-1.0)- SOL_NUMERICA[i];
        }


        /*
        printf("\n\n O vetor diferen�a entre a solu��o exata e a n�merica em cada x_i �:  \n \n \t");
        for(i=0; i<=n; i++){//Impress�o para verifica��o da solu��o do sistema (1).
            printf("\n \t Diferen�a_%d = %lf   \n",i, DIFERENCA[i]);
        }
        */

        DIFF= NORM_INF(n,DIFERENCA);


   return DIFF;
}

double  Calculo_ERRO_NOS(double a,double b,double lambda, int n)
{
    double DiagPrincipalA[n], SubDiagoalA[n-1], VetorL[n], VetorD[n], B[n], U[n], V[n], C[n], DIFERENCA[n], Sol_EXATA[n+2], PHI[n], SOL_NUMERICA[n+2];; // Aqui fazemos a declara��o dos ponteiros para a aloca��o din�mica dos vetores.
    double h,y, DIFF,Precisao;
    int i,j, ITMAX;
    ITMAX=28; // N�mero m�ximo de itera��ees no m�todo de Romberg para c�lculo das integrais do nosso sistema.
    Precisao=0,0000001; // A precis�o desejada no m�tdo de Romberg

    double **R;
    double Func(double);

    R = calloc(ITMAX, sizeof(double *));

    if(R == NULL){// Teste para verificar se ocorreu tudo bem na aloca��o.
       printf(" \n Erro de aloca��o de mem�ria Diagonal Principal. \n");
       system("pause");
       exit(1);
    }
        h=(b-a)/(n+1.000);
        /*printf("\n O valor de h �: %lf \n",h); // Teste leitura de h*/


        for(i=0; i<n; i++){ // Determino o vetor diagonal principal da Matriz dos coeficientes do sistema 10.
            DiagPrincipalA[i]=(2.00/h)+lambda*h*(2/3.00);
        }

        for(i=0; i<n-1; i++){ // Determino o vetor subdiagonal principal da Matriz dos coeficientes do sistema 10.
            SubDiagoalA[i]=(-1.00/h)+lambda*(h/6.00);
        }

        // Agora definiremos os vetores diagonal de D, denominado VetorD, e o vetor subdiagonal de L, denominado VetorL
        VetorD[0]=DiagPrincipalA[0];

        for(i=0; i<=n-2; i++){
            VetorL[i]=(SubDiagoalA[i])/VetorD[i];
            VetorD[i+1]=DiagPrincipalA[i+1]-VetorL[i]*SubDiagoalA[i];
        }


        for(i=1; i<=n; i++){// Declaro a matriz dos termos independentes do sistema (10), na quest�o 1.
                B[i-1]=(h*(-12*h*h*i*i-2*h*h+12*h*i-2));
        }

        //A seguir resolveremos o sistema (10) pela t�cnica usada no EP2.

        U[0]=B[0];
        for(i=1; i<n; i++){
            U[i]= B[i]-VetorL[i-1]*U[i-1];
        }


        /*
        printf("\n\n Resolveremos a segunda parte do exerc�cio. Se LU=B. Ent�o o vetor U �:  \n \n \t", i+1);
        for(i=0; i<n; i++){ // Confer�ncia do vetor U
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
                printf("\n\n  PHI_%d(x_%d)=%lf   \n \t", j, i,PHI[j-1] );/Conferi que a PHI est� correta.
                */
            SOL_NUMERICA[i]=SOL_NUMERICA[i] + C[j-1]*PHI[j-1];
            }
        }

        /*
        printf("\n\n  Vetor Solu��o num�rica:  \n \n \t");
        for(i=0; i<n+2; i++){//Calcularemos o m�dulo da diferen�a, em cada coordenada, da solu��o com a solu��o coordenada.
            printf("\n \t SOL_NUM [ %d ] = %e   \n",i, SOL_NUMERICA[i]);
        }
        */
        /*
        for(i=0; i<n+2; i++){//Calcularemos o m�dulo da diferen�a, em cada coordenada, da solu��o com a solu��o coordenada.
            Sol_EXATA[i]=(a+i*h)*(a+i*h)*((a+i*h)-1.0)*((a+i*h)-1.0);
            printf("\n \t SOL_EXATA [ %d ] = %e   \n", i, Sol_EXATA [i]);

        }
        */




        for(i=0; i<n+2; i++){//Calcularemos o m�dulo da diferen�a, em cada coordenada, da solu��o com a solu��o coordenada.
            DIFERENCA[i]=(a+i*h)*(a+i*h)*((a+i*h)-1.0)*((a+i*h)-1.0)- SOL_NUMERICA[i];
        }


        /*
        printf("\n\n O vetor diferen�a entre a solu��o exata e a n�merica em cada x_i �:  \n \n \t");
        for(i=0; i<=n; i++){//Impress�o para verifica��o da solu��o do sistema (1).
            printf("\n \t Diferen�a_%d = %lf   \n",i, DIFERENCA[i]);
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


    setlocale(LC_ALL, "portuguese"); // Para colocar acentua��o.*/
    /*system("color E5"); // Apenas para est�tica. Deixa o fundo amarelo "E". e a letra roxa "5".*/

    do{


        do{
            printf("\n\n Digite 1 para analisar o caso k(x)=1, e g(x)=lambda, e escolher os valores de n, da constante lambda, e dos pontos inicial e final do intervalo.\n ");
            printf("\n Digite 2 para escolher a lista de n�s: 15,31,63,127,255 com lambda zero e intervalo [0,1]. \n\n \t");
            scanf("%d", &OPCAO_n);

            switch(OPCAO_n){
                case 1:
                    printf("\n Digite o valor n: \n\n \t");
                    scanf("%d", &n);

                    printf("\n Digite o valor de lambda: \n\n \t");
                    scanf("%lf", &lambda);

                    printf("\n Digite o in�cio do intervalo: \n\n \t");
                    scanf("%lf", &a);

                    printf("\n Digite o fim do intervalo: \n\n \t");
                    scanf("%lf", &b);
                    h=(b-a)/(n+1.00);

                    printf("\n \n A respeito da an�lise em y_i, o erro cometido �: %e. E ERRO/h^2 = %e.   \n \t", Calculo_ERRO(a,b,lambda,n),Calculo_ERRO(a,b,lambda,n)/(h*h) );
                    printf("\n \n A respeito da an�lise nos n�s, o erro cometido �: %e. E ERRO/h^2 = %e.   \n \t", Calculo_ERRO_NOS(a,b,lambda,n),Calculo_ERRO(a,b,lambda,n)/(h*h) );


                    break;
                case 2: a=0; b=1; lambda=0;
                    printf("                               +----------------------------------------------------------+\n");
                    printf("                               |                         An�lise em y_i*                  |\n");
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
                    printf(" *Veja que constatamos ent�o a converg�ncia de segunda ordem com o uso dos splines lineares.\n\n\n");



                    printf("                               +-----------------------------------------+\n");
                    printf("                               |              An�lise nos n�s**          |\n");
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

                    printf(" **Como o m�todo c�lcula a solu��o exatamente nos n�s, ent�o o erro observado � muito pequeno e � devido aos erros de arredondamento. \n\n" );

                    break;
                default:
                    printf("\n\n  Op��o inv�lida. \n\n");

            }
        }while(OPCAO_n !=1 && OPCAO_n != 2 );// Para que o usu�rio escolha uma das op��es




    printf("   \n\n   Digite 1 para permanecer no progrma e outro valor para sair. \n\n \t");
    scanf("%d", & codigoAcao);

    } while(codigoAcao ==1); // para que se retorne as op��es at� que o usuario digite a op��o 4.

    return 0;
}
