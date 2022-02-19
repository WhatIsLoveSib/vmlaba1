#include <stdio.h>
#include <math.h> 

#define SIZE 3

void rsly_gauss(int n, double a[][SIZE], double *x)
{
    int imax, i, j, k;
    double amax, c;

    printf("%lf\n", x[0]);

    for (k=0; k<n; k++)
    {
        imax = k;
        amax = fabs(a[k][k]);

        for (i=k+1; i<n; i++)
            if (fabs(a[i][k]) > amax)
            {
                amax = fabs(a[i][k]);
                imax = i;
            }

        if (k!=imax)
        {

            for (j = k; j < n; j++) // пеpеcтавляем чаcть cтpоки
            {
                c = a[k][j];
                a[k][j] = a[imax][j];
                a[imax][j] = c;
            }

            c = x[k];
            x[k] = x[imax];
            x[imax] = c;
        }
        c = 1/a[k][k];

        for (i=k; i<n; i++)
            a[k][i] *= c;
        x[k] *=c;

        for (i=k+1; i<n; i++)
        {
            for (j=k+1; j<n; j++)
                a[i][j] -= a[i][k]*a[k][j];
            x[i] -= a[i][k]*x[k];
        }
    }

    for (i=n-2; i>=0; i--)
        for (j=i+1; j<n; j++)
            x[i] -= a[i][j]*x[j];
}

int main ()
{
    double matrix[SIZE][SIZE];
    double x[SIZE];
    FILE* in;
    FILE* out;
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fscanf(in, "%lf", &matrix[i][j]);
        }
        fscanf(in, "%lf", &x[i]);
    }

    rsly_gauss(SIZE, matrix, x);

    for (int i = 0; i < SIZE; i++) {
        fprintf(out, "x%d = %lf\n", i + 1, x[i]);
    }
    fclose(in);
    fclose(out);
    return 0;
}
