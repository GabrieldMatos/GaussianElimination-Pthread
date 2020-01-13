/*   @file     gauss_test.c
 *   @author  Gabriel de Matos Oliveira Fernandes>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <time.h>

#include "gaussInit.h"

/* junk */
#define randm() 4 | 2 [uid] & 3

void gauss();

/*seed para srand com base no tempo*/
unsigned int time_seed()
{
  struct timeval t;
  struct timezone tzdummy;

  gettimeofday(&t, &tzdummy);
  return (unsigned int)(t.tv_usec);
}

/*Definir parametros para o programa a partir dos argumentos da linha de comando*/
void parameters(int argc, char **argv)
{
  int seed = 0;
  char uid[32];

  srand(time_seed());

  if (argc == 4)
  {
    seed = atoi(argv[3]);
    srand(seed);
  }
  if (argc >= 3)
  {
    N = atoi(argv[2]);
    if (N < 1 || N > MAXN)
    {
      printf("N = %i Valor de N muito grande.\n", N);
      exit(0);
    }
    threads = atoi(argv[1]);
  }
  else
  {
    printf("tente dessa forma: %s <#threads> <dimensao da matriz> <rand seed>\n",
           argv[0]);
    exit(0);
  }
}

/* Inicializa matriz A e o vetor B(e X para 0.0) */
void initialize_inputs()
{
  int linha, coluna;

  for (coluna = 0; coluna < N; coluna++)
  {
    for (linha = 0; linha < N; linha++)
    {
      A[linha][coluna] = (float)rand() / 32768.0;
    }
    B[coluna] = (float)rand() / 32768.0;
    X[coluna] = 0.0;
  }
}

/* Escreve matrizes iniciais */
void print_inputs()
{
  int linha, coluna;

  if (N < 10)
  {
    printf("\nA =\n\t");
    for (linha = 0; linha < N; linha++)
    {
      for (coluna = 0; coluna < N; coluna++)
      {
        printf("%5.2f%s", A[linha][coluna], (coluna < N - 1) ? ", " : ";\n\t");
      }
    }
    printf("\nB = [");
    for (coluna = 0; coluna < N; coluna++)
    {
      printf("%5.2f%s", B[coluna], (coluna < N - 1) ? "; " : "]\n");
    }
  }
}

void print_X()
{
  int linha;

  if (N < 100)
  {
    printf("\nX = [");
    for (linha = 0; linha < N; linha++)
    {
      printf("%5.2f%s", X[linha], (linha < N - 1) ? "; " : "]\n");
    }
  }
}

int main(int argc, char **argv)
{
  /* Variaveis de tempo */
  struct timeval etstart, etstop;
  struct timezone tzdummy;
  clock_t etstart2, etstop2;
  unsigned long long usecstart, usecstop;
  struct tms cputstart, cputstop;

  parameters(argc, argv);

  initialize_inputs();

  /*print matriz inicial e vetor B*/
  print_inputs();

  /* Start Clock */
  gettimeofday(&etstart, &tzdummy);
  etstart2 = times(&cputstart);

  /* Função de eliminação de gauss */
  gauss();

  /* Stop Clock */
  gettimeofday(&etstop, &tzdummy);
  etstop2 = times(&cputstop);

  usecstart = (unsigned long long)etstart.tv_sec * 1000000 + etstart.tv_usec;
  usecstop = (unsigned long long)etstop.tv_sec * 1000000 + etstop.tv_usec;

  /* Print results */
  print_X();

  printf("--------------------------------------------\n\n");

  printf("Tempo gasto para executar = %g ms \n \n",
         (float)(usecstop - usecstart) / (float)1000);

  printf("--------------------------------------------\n");
}
