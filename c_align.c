#include "stdio.h" // printf
#include "stdlib.h" // malloc and rand for instance. Rand not thread safe!
#include "time.h"   // time(0) to get random seed
#include "math.h"  // sine and cosine
#include "omp.h"   // openmp library like timing
#include <omp.h>
#include <math.h>



// two pi
#define PI2 6.283185307179586476925286766559
#define R_ERROR 0.01

int DFT(int idft, double* xr, double* xi, double* Xr_o, double* Xi_o, int N);
int fillInput(double* xr, double* xi, int N);
int setOutputZero(double* Xr_o, double* Xi_o, int N);
int checkResults(double* xr, double* xi, double* xr_check, double* xi_check, double* Xr_o, double* Xi_r, int N);
int printResults(double* xr, double* xi, int N);


int main(int argc, char* argv[]){
// size of input array
    int N = 10000;
    //printf("DFTW calculation with N = %d \n",N);

    double xr[N] __attribute__((aligned(64)));
    double xi[N] __attribute__((aligned(64)));
    fillInput(xr,xi,N);


    double xr_check[N] __attribute__((aligned(64)));
    double xi_check[N] __attribute__((aligned(64)));
    setOutputZero(xr_check,xi_check,N);

    double Xr_o[N] __attribute__((aligned(64)));
    double Xi_o[N] __attribute__((aligned(64)));
    setOutputZero(Xr_o,Xi_o,N);

    // start timer
    double start_time = omp_get_wtime();

    // DFT
    int idft = 1;
    DFT(idft,xr,xi,Xr_o,Xi_o,N);
    // IDFT
    idft = -1;
    DFT(idft,Xr_o,Xi_o,xr_check,xi_check,N);

    // stop timer
    double run_time = omp_get_wtime() - start_time;
    printf("\n%f",run_time);

    // check the results: easy to make correctness errors with openMP
    //checkResults(xr,xi,xr_check,xi_check,Xr_o, Xi_o, N);
    // print the results of the DFT
    #ifdef DEBUG
      printResults(Xr_o,Xi_o,N);
      #endif

      // take out the garbage
      /*
      free(xr); free(xi);
      free(Xi_o); free(Xr_o);
      free(xr_check); free(xi_check);
      */
      return 1;
}

// DFT/IDFT routine
// idft: 1 direct DFT, -1 inverse IDFT (Inverse DFT)
int DFT(int idft, double xr[restrict], double xi[restrict], double Xr_o[restrict], double Xi_o[restrict], int N){
    #pragma omp parallel for
    for (int k = 0; k < N; k++) {
        __assume_aligned(xr,64);
        __assume_aligned(xi,64);
        __assume_aligned(Xr_o,64);
        __assume_aligned(Xi_o,64);
        double sum_r = 0.0;
        double sum_i = 0.0;

        for (int n = 0; n < N; n++) {
            double angle = n * k * PI2 / N;
            sum_r += xr[n] * cos(angle) + idft * xi[n] * sin(angle);
            sum_i += -idft * xr[n] * sin(angle) + xi[n] * cos(angle);
        }
        Xr_o[k] = sum_r;
        Xi_o[k] = sum_i;
    }

    if (idft == -1) {
        #pragma omp parallel for
        for (int n = 0; n < N; n++) {
            Xr_o[n] /= N;
            Xi_o[n] /= N;
        }
    }
    return 1;
}

// set the initial signal
// be careful with this
// rand() is NOT thread safe in case
int fillInput(double* xr, double* xi, int N){
  int n;
  srand(time(0));
  for(n=0; n < 100000;n++) // get some random number first
    rand();
  for(n=0; n < N;n++){
     // Generate random discrete-time signal x in range (-1,+1)
     //xr[n] = ((double)(2.0 * rand()) / RAND_MAX) - 1.0;
     //xi[n] = ((double)(2.0 * rand()) / RAND_MAX) - 1.0;
     // constant real signal
     xr[n] = 1.0;
     xi[n] = 0.0;
  }
  return 1;
}

// set to zero the output vector
int setOutputZero(double* Xr_o, double* Xi_o, int N){
  int n;
  for(n=0; n < N;n++){
     Xr_o[n] = 0.0;
     Xi_o[n] = 0.0;
  }
  return 1;
}

// check if x = IDFT(DFT(x))
int checkResults(double* xr, double* xi, double* xr_check, double* xi_check, double* Xr_o, double* Xi_r, int N){
  int n;
  for(n=0; n < N;n++){
    if (fabs(xr[n] - xr_check[n]) > R_ERROR)
      printf("ERROR - x[%d] = %f, inv(X)[%d]=%f \n",n,xr[n], n,xr_check[n]);
      if (fabs(xi[n] - xi_check[n]) > R_ERROR)
      printf("ERROR - x[%d] = %f, inv(X)[%d]=%f \n",n,xi[n], n,xi_check[n]);

    }
    printf("Xre[0] = %f \n",Xr_o[0]);
    return 1;
}

// print the results of the DFT
int printResults(double* xr, double* xi, int N){
  int n;
  for(n=0; n < N;n++)
      printf("Xre[%d] = %f, Xim[%d] = %f \n", n, xr[n], n, xi[n]);
  return 1;
}