/*
 * Filename: matrixFuncs.c
 * Author: Amritansh Gupta
 * Description: Contains crtain matrix operations necessary to make a
 *              Kalman Filter.
 * Last Update: 5/25/2017
 */

#include <stdio.h>
#include <math.h>

#include "matrix.h"

float[][] matrixMultiply(float matrix_a[][], int a_row, int a_col, 
                                  float matrix_b[][], int b_row, int b_col) {

  if(a_col != b_row) {
    printf("Wrong matrix configuration");
    return;
  }

  int i, j, k;    //loop counters

  int sum= 0;        //row wise sums

  int multiply[a_row][b_col];

  for(i= 0; i < a_row; i++) {
    for(j = 0; j < b_col; j++) {
      for(k = 0; k < b_row; k++) {
        
        sum = sum + *matrix_a[i][k] * *matrix[k][j];
 
      }

      multiply[i][j] = sum;
      sum = 0; 
    }
  }

  return multiply;
}


float determinant(float [][25], float);

void cofactor(float [][25], float);

void transpose(float [][25], float [][25], float);



float matrixInverse (float[][] matrix_a, int a_order) {

  int i, j, k;
  float d; 

  d = determinant(matrix_a, a_order);

  if (d == 0)

   printf("\nInverse of Entered Matrix is not possible\n");

  else

    float cofactor_matrix[a_order][a_order] = cofactor(matrix_a, a_order);
    float transpose_matrix[a_order][a_order] = transpose(matrix_a,
        cofactor_matrix, a_order);

  
  float inverse[r][r], d;  
  d = determinant(num, r);
  for (i = 0;i < r; i++) {
    for (j = 0;j < r; j++) {
        
      inverse[i][j] = transpose_matrix[i][j] / d;
    }
  }
  
  printf("\n\n\nThe inverse of matrix is : \n");
 
  for (i = 0;i < r; i++) {
    for (j = 0;j < r; j++) {
      printf("\t%f", inverse[i][j]);
    }
    printf("\n");
  }
  return inverse;
}
    

}

 

/*For calculating Determinant of the Matrix */

float determinant(float a[][], int k) {

  float s = 1, det = 0, b[k][2k];

  int i, j, m, n, c;

  if (k == 1) {

    return (a[0][0]);

  }

  else {

    det = 0;
    for (c = 0; c < k; c++) {

    m = 0;
    n = 0;

      for (i = 0;i < k; i++) {
       for (j = 0 ;j < k; j++) {
  
         b[i][j] = 0;
        
         if (i != 0 && j != c) {

           b[m][n] = a[i][j];

            if (n < (k - 2))
              n++;
          
            else {
              n = 0;
              m++;
            }
          }
        }
      }
      det = det + s * (a[0][c] * determinant(b, k - 1));
      s = -1 * s;
    }
  }
 
  return (det);
}
 

void cofactor(float num[][], int f) {
  float b[25][25], fac[25][25];
  int p, q, m, n, i, j;
  
  for (q = 0;q < f; q++) {
   
    for (p = 0;p < f; p++) {
     m = 0;
     n = 0;
     for (i = 0;i < f; i++) {
       for (j = 0;j < f; j++){

          if (i != q && j != p) {
            b[m][n] = num[i][j];
            
            if (n < (f - 2))
             n++;
            
            else {
              n = 0;
              m++;
            }
          }
        }
      }
      fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
    }
  }
  return fac;
}


/*Finding transpose of matrix*/ 
float[][] transpose(float num[][], float fac[][], float r)
{
  int i, j;
  float b[r][r];
 
  for (i = 0;i < r; i++) {
    for (j = 0;j < r; j++) {
      b[i][j] = fac[j][i];
    }
  }
  return b;
}
  
  
