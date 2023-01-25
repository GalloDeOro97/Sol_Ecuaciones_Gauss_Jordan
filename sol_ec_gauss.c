#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3 //cantidad de ecuaciones
// Funcion para imprimir matrices 
void imprimirMatriz(double matriz[N][N+1]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j <= N; j++) {
            printf("%.2lf ", matriz[i][j]);
        }
        printf("\n");
    }
}
// Funcion para intercambio de filas dada una matrizm y dos indices de filas
void intercambiarFilas(double matriz[N][N+1], int fila1, int fila2) {
    double temp;
    // Iteramos sde manera horizontal
    for(int i = 0; i <= N; i++) {
	// Se guarda el valor anterior de la matriz
        temp = matriz[fila1][i];
        matriz[fila1][i] = matriz[fila2][i];
        matriz[fila2][i] = temp;
    }
}
// Multiplicacion de una fila por escalar dado un indice de fila y un escalar
void multiplicarFilaporEscalar(double matriz[N][N+1], int fila, double escalar) {
	for(int i = 0; i <= N; i++ ) {
	    matriz[fila][i] = escalar * matriz[fila][i];
	} 
}
// Funcion para sumar dos filas dada una matriz y los indices de las filas por sumar tambien agregamos un escalar para no retrabajar esta operacion
void sumadeFilas(double matriz[N][N+1], int fila1, int fila2, double escalar) {
	for(int i = 0; i <= N; i++) {
	    matriz[fila1][i] += matriz[fila2][i];
	}
}
// Proceso de eliminacion Gaussiana
void eliminacionGaussiana(double matriz[N][N+1]) {
    
	// Iteramos sobre columnas primero
	for(int k = 0; k < N-1; k++) {
        int max = k;
	// Estamos buscando el maximo para ordenar las filas
        for(int i = k+1; i < N; i++) {
            if(fabs(matriz[i][k]) > fabs(matriz[max][k])) {
                max = i;
            }
        }
        if(max != k) {
            // Si ni es un maximo, intercambia
            intercambiarFilas(matriz, k, max);
        }
	// Eliminamos elementos bajo el factor
        for(int i = k+1; i < N; i++) {
            double factor = matriz[i][k] / matriz[k][k];
            for(int j = k+1; j <= N; j++) {
                matriz[i][j] = matriz[i][j] - factor * matriz[k][j];
            }
            matriz[i][k] = 0;
        }
	// Se agrega la eliminacion de lementos en la diagonal
	//if(matriz[k][k]!= 1)
	//   multiplicarFilaporEscalar(matriz,k, 1/matriz[k][k]);
	//for(int i = k+1; i < N; i++){
	//    if(matriz[i][k] != 0){
	 //      sumadeFilas(matriz,i,k,-matriz[i][k]);
	 //   }
	//}
    }
}
// Hacer una diagonal de unos
void hacerDiagonalUnos(double matriz[N][N+1]) {
	// Estamos iterando sobre columnas
	for(int i = 0; i < N; i++) {
	    double divisor = matriz[i][i]; 
	    // IMPORTANTE: Comprobar que el divisor sea distinto de cero
	    if(divisor != 0) {
	       double pivote = 1/divisor;
	       // Usamos la funcion para multiplicar por escalar
	       multiplicarFilaporEscalar(matriz, i, pivote);
	    }
	}
}
// Sustitucion de varibles para resolucion de la ecuacion simplificada
void sustitucionRegresiva(double matriz[N][N+1], double x[N]) {
    for(int i = (N-1); i >= 0; i--) {
        x[i] = matriz[i][N];
        for(int j = i+1; j < N; j++) {
            x[i] = x[i] - matriz[i][j] * x[j];
        }
        x[i] = x[i] / matriz[i][i];
    }
}
void matrizEscalonadaReducida(double matriz[N][N+1]) {
	// Iteramos sobre filas de abajo hacia arriba
	for(int i = (N-1); i > 0; i--){
             for(int k= (i-1);k >=0; k--){ 
		     if(matriz[k][i] != 0) {
	     		double pivote = matriz[k][i];
			for(int j = 0; j <= N; j++) {
		   		 matriz[k][j] -= pivote * matriz[i][j];
			}
	     	}
	     }
	}	     
}

int main() {
    
	// Se introduce un  sistema de ecuaciones en su forma matricial
	double matriz[N][N+1] = {
        {1, 0, 5, 4},
        {0, 1, 2, 5},
        {0, 0, 1, 6}
   	 };
    	double x[N];
	printf("Resolviendo la matriz:\n");
	imprimirMatriz(matriz);
    	eliminacionGaussiana(matriz);
    	hacerDiagonalUnos(matriz);
	printf("Su forma escalonada reducida: \n");
	matrizEscalonadaReducida(matriz);
    	imprimirMatriz(matriz);
    	//sustitucionRegresiva(matriz, x);
    	//printf("La solucion es: \n");
    	//for(int i = 0; i < N; i++) {
     	//   printf("x%d = %.2lf\n", i+1, x[i]);
   	// }
    	return 0;
}
