#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3 //cantidad de ecuaciones

void imprimirMatriz(double matriz[N][N+1]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j <= N; j++) {
            printf("%.2lf ", matriz[i][j]);
        }
        printf("\n");
    }
}

void intercambiarFilas(double matriz[N][N+1], int fila1, int fila2) {
    double temp;
    for(int i = 0; i <= N; i++) {
        temp = matriz[fila1][i];
        matriz[fila1][i] = matriz[fila2][i];
        matriz[fila2][i] = temp;
    }
}

void eliminacionGaussiana(double matriz[N][N+1]) {
    for(int k = 0; k < N-1; k++) {
        int max = k;
        for(int i = k+1; i < N; i++) {
            if(fabs(matriz[i][k]) > fabs(matriz[max][k])) {
                max = i;
            }
        }
        if(max != k) {
            intercambiarFilas(matriz, k, max);
        }
        for(int i = k+1; i < N; i++) {
            double factor = matriz[i][k] / matriz[k][k];
            for(int j = k+1; j <= N; j++) {
                matriz[i][j] = matriz[i][j] - factor * matriz[k][j];
            }
            matriz[i][k] = 0;
        }
    }
}

void sustitucionRegresiva(double matriz[N][N+1], double x[N]) {
    for(int i = N-1; i >= 0; i--) {
        x[i] = matriz[i][N];
       for(int j = i+1; j < N; j++) {
            x[i] = x[i] - matriz[i][j] * x[j];
        }
        x[i] = x[i] / matriz[i][i];
    }
}

int main() {
    double matriz[N][N+1] = {
        {8, -10, -1, 7},
        {-2, -79, 4, -5},
        {-1, 1/2, -1, 1}
    };
    double x[N];
    eliminacionGaussiana(matriz);
    imprimirMatriz(matriz);
    sustitucionRegresiva(matriz, x);
    printf("La solucion es: \n");
    for(int i = 0; i < N; i++) {
        printf("x%d = %.2lf\n", i+1, x[i]);
    }
    return 0;
  }
