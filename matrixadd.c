#include <stdio.h>
#include <stdlib.h>

void PrintMatrix(int rows, int cols, int **matrix)
{
    for(int i = 0; i < rows; ++i)
    {
        for(int k = 0; k < cols; ++k)
        {
            if(k == 0 && i == 0)
            {
                printf("[%i ", matrix[i][k]);
            }
            else if(k == 0)
            {
                printf(" %i ", matrix[i][k]);
            }
            else if(k == cols - 1 && i == rows - 1)
            {
                printf("%i]", matrix[i][k]);
            }
            else
            {
                printf("%i ", matrix[i][k]);
            }
        }
        printf("\n");
    }
}

void AddMatrices(int rows, int cols, const int **matrix1, const int **matrix2, int **outputMatrix)
{
    for(int i = 0; i < rows; ++i)
    {
        for(int k = 0; k < cols; ++k)
        {
            outputMatrix[i][k] = matrix1[i][k] + matrix2[i][k];
        }
    }
}

void RotateMatrixClockwise(int rows, int cols, int **matrix)
{
    int ring = 0;
    while((rows/2) - ring > 0 && (cols/2) - ring > 0)
    {
        int prev = matrix[ring][ring];
        int curr;
        for(int i = ring; i < rows - ring - 1; ++i)
        {
            curr = matrix[i + 1][ring];
            matrix[i + 1][ring] = prev;
            prev = curr;
        }
        for(int i = ring; i < cols - ring - 1; ++i)
        {
            curr = matrix[rows - ring - 1][i + 1];
            matrix[rows - ring - 1][i + 1] = prev;
            prev = curr;
        }
        for(int i = rows - ring - 1; i >= ring + 1; --i)
        {
            curr = matrix[i - 1][cols - ring- 1];
            matrix[i - 1][cols - ring- 1] = prev;
            prev = curr;
        }
        for(int i = cols - ring - 1; i >= ring + 1; --i)
        {
            curr = matrix[ring][i - 1];
            matrix[ring][i - 1] = prev;
            prev = curr;
        }
        ++ring;
    }
}

int main(int argc, char *argv[])
{
    FILE *inA;
    FILE *inB;
    inA = fopen("inA.txt", "r");
    inB = fopen("inB.txt", "r");
    
    int **matrixA;
    int **matrixB;

    int aRows;
    int aCols;
    int bRows;
    int bCols;
    fscanf(inA, "%i %i\n", &aRows, &aCols);
    fscanf(inB, "%i %i\n", &bRows, &bCols);
    
    matrixA = (int **) malloc(aRows * sizeof(int *));
    for(int i = 0; i < aRows; ++i)
    {
        matrixA[i] = (int *) malloc(aCols * sizeof(int));
        for(int k = 0; k < aCols; ++k)
        {
            int num;
            fscanf(inA, "%i", &num);
            matrixA[i][k] = num;
        }
        fscanf(inA, "\n");
    }

    matrixB = (int **) malloc(bRows * sizeof(int *));
    for(int i = 0; i < bRows; ++i)
    {
        matrixB[i] = (int *) malloc(bCols * sizeof(int));
        for(int k = 0; k < bCols; ++k)
        {
            int num;
            fscanf(inB, "%i", &num);
            matrixB[i][k] = num;
        }
        fscanf(inB, "\n");
    }

    PrintMatrix(aRows, aCols, matrixA);

    RotateMatrixClockwise(aRows, aCols, matrixA);
    PrintMatrix(aRows, aCols, matrixA);

    for(int i = 0; i < aRows; ++i)
    {
        free(matrixA[i]);
    }
    free(matrixA);

    for(int i = 0; i < bRows; ++i)
    {
        free(matrixB[i]);
    }
    free(matrixB);

    return 0;
}