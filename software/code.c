#include <stdio.h>

#include <math.h>

#include <stdlib.h>


long double ** createMatrix(int size) {
    long double ** matrix;
    matrix = (long double ** ) malloc(size * sizeof(long double * ));
    for (int i = 0; i < size; i++) {
        matrix[i] = (long double * ) malloc(size * sizeof(long double));
    }
    return matrix;
}

void freeMatrix(long double ** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void scanMatrix(long double ** matrix, int size) {
    printf("Enter the values of the  matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("element (%d,%d) =", i + 1, j + 1);
            scanf("%Lf", & matrix[i][j]);
            printf("\n");
        }
    }

}

void gramSchmidt(long double ** A, long double ** Q, long double ** R, int n) {

    for (int j = 0; j < n; j++) {

        // copy columns j of A to Q
        for (int i = 0; i < n; i++) {
            Q[i][j] = A[i][j];
        }

        //normalizing w.r.t. prev columns
        for (int i = 0; i < j; i++) {
            long double dot = 0;
            for (int k = 0; k < n; k++) {
                dot += Q[k][i] * A[k][j];
            }
            R[i][j] = dot;
            for (int k = 0; k < n; k++) {
                Q[k][j] -= dot * Q[k][i];
            }
        }

        //normalize column j
        long double norm = 0;
        for (int k = 0; k < n; k++) {
            norm += Q[k][j] * Q[k][j];
        }
        norm = sqrtl(norm);
        R[j][j] = norm;

        if (norm < 1e-10) {
            for (int k = 0; k < n; k++) {
                Q[k][j] = 0;
            }
        } else {
            for (int k = 0; k < n; k++) {
                Q[k][j] /= norm;
            }
        }
    }
}

void qrAlgorithm(long double ** A, int maxIterations, int n) {
    long double ** Q = createMatrix(n);
    long double ** R = createMatrix(n);

    for (int l = 0; l < maxIterations; l++) {
        gramSchmidt(A, Q, R, n);

        for (int i = 0; i < n; i++) { //RxQ
            for (int j = 0; j < n; j++) {
                A[i][j] = 0.0;
                for (int k = 0; k < n; k++) {
                    A[i][j] += R[i][k] * Q[k][j];
                }
            }
        }
    }

    freeMatrix(Q, n);
    freeMatrix(R, n);
}

int main() {
    int size;
    printf("Enter the size of the matrix: ");
    scanf("%d", & size);

    long double ** A = createMatrix(size);
    scanMatrix(A, size);

    int maxIterations = 1000; // Adjust as needed
    qrAlgorithm(A, maxIterations, size);

    printf("\nApproximated Eigenvalues Matrix (diagonal elements):\n");
    for (int i = 0; i < size; i++) {
        printf("%10.3Lf\n", A[i][i]);
    }

    freeMatrix(A, size);
    return 0;
}
