//Laborator6

//Aplicatia 6.1
    /*
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void err(int conditie, const char *fmt, ...)
{
    if(conditie == 0)
        return;
    va_list va;
    va_start(va, fmt);
    fprintf(stderr, "eroare: ");
    vfprintf(stderr, fmt, va);
    va_end(va);
    exit(EXIT_FAILURE);
}

int main()
{
    int n;
    scanf("%d", &n);
    err(n<=0 || n>100 , "invalid : %d", n);
    return 0;
}
    */

//Aplicatia 6.2
    /*
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

float *alloc(int n, ...)
{
    float *v = malloc(n * sizeof(float));
    if(v == NULL)
    {
        perror("Eroare la alocarea dinamica\n");
        exit(-1);
    }
    va_list va;
    va_start(va, n);
    for(int i=0; i<n; i++)
        v[i] =  va_arg(va, double);
    va_end(va);
    return v;
}

int main()
{
    float *a = alloc(3, 7.2, -1.0, 9.0);
    for(int i=0; i < 3; i++)
        printf("%f ", a[i]);
    free(a);
    return 0;
}
    */

//Aplicatia 6.3
    /*
#include <stdio.h>
#include <math.h>
#include <stdarg.h>

void absN(int n, ...)
{
    va_list args;
    va_start(args, n);

    for(int i=0; i<n; i++)
    {
        float *ptr = va_arg(args, float*);
        *ptr = fabs(*ptr);
    }
    va_end(args);
}

int main()
{
    float x = -3.5, y= 2.4;
    absN(2, &x, &y);
    printf("x = %.2f, y=%.2f\n" , x, y);
    return 0;
}
    */

//Aplicatia 6.4
    /*
#include <stdio.h>
#include <stdarg.h>

int crescator(int n, char tip, ...)
{
    va_list va;
    va_start(va, tip);

    if(n<=1)
    {
        va_end(va);
        return 1;
    }

    if(tip == 'd')
    {
        int prev = va_arg(va, int);
        for(int i=1; i<n; i++)
        {
            int current = va_arg(va, int);
            if( current <= prev)
            {
                va_end(va);
                return 0;
            }
            prev = current;
        }
    }
    else if(tip == 'f')
    {
        double prev = va_arg(va,double);
        for(int i = 1; i < n; i++)
        {
            double current = va_arg(va, double);
            if(current <= prev)
            {
                va_end(va);
                return 0;
            }
            prev = current;
        }
    }
    va_end(va);
    return 1;
}

int main()
{
    int result = crescator(3, 'd', -1, 7, 9);
    printf("%d\n", result);

    result = crescator(3, 'f', 1.2, 3.4, 2.3);
    printf("%d\n", result);
    return 0;
}
    */

//Aplicatia 6.5

    /*
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void input(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while(*fmt)
    {
        if(*fmt == '%' && *(fmt+1))
        {
            fmt++;
            switch(*fmt)
            {
                case 'd':
                {
                    int *ptr = va_arg(args, int *);
                    if(scanf("%d", ptr) != 1)
                    {
                        fprintf(stderr, "Eroare la citire!\n");
                        exit(-1);
                    }
                    while(getchar() != '\n');
                    break;
                }
                case 'f':
                {
                    float *ptr = va_arg(args, float*);
                    if(scanf("%f", ptr) != 1)
                    {
                        fprintf(stderr, "Eroare la citire!\n");
                        exit(-1);
                    }
                    while(getchar() != '\n');
                    break;
                }
                case 'c':
                {
                    char *ptr = va_arg(args, char *);
                    scanf(" %c", ptr);
                    break;
                }
                default:
                    putchar('%');
                    putchar(*fmt);
            }
        }
        else
            fmt++;
    }
    va_end(args);
}

int main()
{
    int n;
    char ch;

    input("n=%d ch=%c", &n, &ch);
    printf("Ai introdus: n = %d, ch = %c\n", n, ch);
    return 0;
}
    */

//Aplicatia 6.6
    /*
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

char *concat(int n, ...)
{
    if(n <= 0)
        return NULL;

    va_list va;
    va_start(va , n);

    int length = 0;
    for(int i=0; i<n; i++)
        length += strlen(va_arg(va, char*));
    length += n;

    va_end(va);

    char *result = (char*)malloc(length * sizeof(char));
    if(result == NULL)
    {
        perror("Eroare la alocarea dinamica\n");
        exit(-1);
    }

    va_start(va, n);
    strcpy(result, va_arg(va, char*));
    for(int i=1; i<n; i++)
    {
        strcat(result , " ");
        strcat(result, va_arg(va, char*));
    }
    va_end(va);
    return result;
}

int main()
{
    char *rezultat = concat(3, "ION", "si", "Ana");
    if(rezultat)
    {
        printf("%s\n", rezultat);
        free(rezultat);
    }
    return 0;
}
    */

//Aplicatia 6.7
    /*
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int comune(int nVec, ... )
{
    if(nVec < 1)
        return 0;

    va_list va;
    va_start(va, nVec);

    int n = va_arg(va, int);
    int *pre = va_arg(va, int*);

    int *intersectie = malloc(n * sizeof(int));
    if(intersectie == NULL)
    {
        perror("Eroare alocare dinamica!\n");
        exit(-1);
    }

    for(int i = 0; i < n; i++)
        intersectie[i] = pre[i];
    int nr = n;

    for(int i=1; i<nVec ; i++)
    {
        int ncurrent = va_arg(va, int);
        int *current = va_arg(va, int*);

        int nNou = 0;

        int *temp = malloc(nr * sizeof(int));
        if(temp == NULL)
        {
            perror("Eroare la alocarea dinamica!\n");
            exit(-1);
        }

        for(int j=0; j<n; j++)
        {
            for(int k=0; k<ncurrent; k++)
            {
                if(intersectie[j] == current[k])
                {
                    temp[nNou] = intersectie[j];
                    nNou++;
                    break;
                }
            }
        }
        free(intersectie);
        intersectie = temp;
        nr = nNou;

        if(nr == 0)
            break;
    }
    free(intersectie);
    va_end(va);
    return nr;
}

int main()
{
    int v1[] = {5, 8}, v2[] = {8, 3, 5}, v3[] = {5,  0 , 8};
    printf("%d\n", comune(3, 2, v1,3, v2, 3, v3));
    return 0;
}
    */

//Aplicatia 6.8
    /*
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void sortare(int n, ...)
{
    va_list va;
    va_start(va, n);

    int *values = malloc(n * sizeof(int));
    if(values == NULL)
    {
        perror("Eroare la alocarea dinamica!\n");
        exit(-1);
    }

    for(int i=0; i<n; i++)
        values[i] = *va_arg(va, int*);

    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(values[i] > values[j])
            {
                int aux = values[i];
                values[i] = values[j];
                values[j] = aux;
            }
        }
    }

    va_end(va);
    va_start(va, n);

    for(int i=0; i<n; i++)
        *va_arg(va, int*) = values[i];

    free(values);
}

int main()
{
    int i = 3, j = 1, k = 2;

    printf("Înainte de sortare: i = %d, j = %d, k = %d\n", i, j, k);

    sortare(3, &i, &j, &k);

    printf("După sortare: i = %d, j = %d, k = %d\n", i, j, k);

    return 0;
}
    */
