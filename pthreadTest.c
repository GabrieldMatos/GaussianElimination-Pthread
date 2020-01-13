/*   @file     pthread_gauss.c
 *   @author   Gabriel de Matos Oliveira Fernandes,
 *   @date     14 November 2019
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "gaussInit.h"

void *pthread_calculate(void *args)
{

  int tcoluna;
  int tlinha = ((int *)args)[0];
  int tnorm = ((int *)args)[1];

  float mult;

  for (tlinha; tlinha < N; tlinha += threads)
  {
    mult = A[tlinha][tnorm] / A[tnorm][tnorm];
    for (tcoluna = tnorm; tcoluna < N; tcoluna++)
    {
      A[tlinha][tcoluna] -= A[tnorm][tcoluna] * mult;
    }
    B[tlinha] -= B[tnorm] * mult;
  }
  free(args);
}

void gauss()
{

  int i, norm, coluna, linha;
  pthread_t ID[threads];

  for (norm = 0; norm < N - 1; norm++)
  {
    for (i = 0; i < threads; i++)
    {
      int *param = (int *)malloc(2 * sizeof(int));
      param[0] = i + norm + 1;
      param[1] = norm;
      pthread_create(&ID[i], NULL, pthread_calculate, (void *)param);
    }
    for (i = 0; i < threads; i++)
      pthread_join(ID[i], NULL);
  }

  for (linha = N - 1; linha >= 0; linha--)
  {
    X[linha] = B[linha];
    for (coluna = N - 1; coluna > linha; coluna--)
    {
      X[linha] -= A[linha][coluna] * X[coluna];
    }
    X[linha] /= A[linha][linha];
  }

  return;
}
