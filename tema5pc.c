
    /*
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        perror("Eroare argumente in linia de comanda\n");
        exit(-1);
    }

    FILE *src = fopen(argv[1], "r");
    if(src == NULL)
    {
        perror("Eroare la deschiderea fisierului sursa\n");
        exit(-1);
    }
    FILE *dst = fopen(argv[2], "w");
    if(dst == NULL)
    {
        perror("Eroare la deschiderea fisierului destinatie\n");
        fclose(src);
        exit(-1);
    }

    char buffer[BUFFER_SIZE];
    size_t bytesread;
    while((bytesread = fread(buffer, 1, BUFFER_SIZE, src)) > 0)
    {
        size_t byteswrite = fwrite(buffer , 1, bytesread, dst);
        if(bytesread != byteswrite)
        {
            perror("Eroare la scriere\n");
            fclose(src);
            fclose(dst);
            exit(-1);
        }
    }
    if (ferror(src))
    {
        perror("Eroare la citire");
        fclose(src);
        fclose(dst);
        return 1;
    }

    fclose(src);
    fclose(dst);

    printf("Copiere finalizata cu succes!\n");

    return 0;
}
    */

//Aplicatia 5.3
    /*
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    int a[m][n];
    for(int i=0; i < m; i++)
        for(int j=0; j < n; j++)            //citire matrice de la tastatura
            scanf("%d", &a[i][j]);

    FILE *fout = fopen("matrice.bin", "wb");
    if(fout == NULL)
    {
        perror("Eroare la deschiderea fisierului binar\n");     //deschidere fisier
        exit(-1);
    }

    if(fwrite(a, sizeof(int), m*n, fout) != m*n)
    {
        perror("Eroare la scrierea in fisier\n");
        fclose(fout);
        exit(-1);
    }        //scriere matrice in fisier

    fclose(fout);
    fout = fopen("matrice.bin", "rb");
    if(fout == NULL)
    {
        perror("Eroare deschidere fisier citire\n");    //redeschiderea fisierului pt citire
        exit(-1);
    }

    int b[m][n];
    if(fread(b, sizeof(int), m*n, fout) != m*n)
    {
        perror("Eroare citire fisier\n");
        fclose(fout);
        exit(-1);
    }

    fclose(fout);

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
            printf("%d ", b[i][j]);     //afisare matricea b
        printf("\n");
    }
    return 0;
}
    */

//Aplicatia 5.4
    /*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *nume;
    float pret;
}Produs;

Produs produse[100];
int nProduse = 0;

void eliberare()
{
    for(int i=0 ;i<nProduse; i++)
        free(produse[i].nume);
}

void citire()
{
    FILE *fis;
    unsigned short nNume;

    if((fis = fopen("produse.dat", "rb")) == NULL)
        return;

    fread(&nProduse, sizeof(int), 1 , fis);
    for(int i=0; i<nProduse; i++)
    {
        fread(&nNume, sizeof(unsigned short), 1, fis);
        char *pNume = (char*)malloc((nNume + 1) *sizeof(char));
        if(pNume == NULL)
        {
            printf("Memorie insuficienta\n");
            fclose(fis);
            eliberare();
            exit(-1);
        }

        fread(pNume, sizeof(char), nNume, fis);
        pNume[nNume] = '\0';
        produse[i].nume=pNume;
        fread(&produse[i].pret, sizeof(float) , 1 , fis);
    }
    fclose(fis);
}

void scriere()
{
    FILE *fis;
    if((fis = fopen("produse.dat", "wb")) == NULL)
    {
        perror("Eroare la deschiderea fisierului");
        exit(-1);
    }
    fwrite(&nProduse, sizeof(int), 1, fis);

    for(int i=0; i<nProduse; i++)
    {
        unsigned short nNume = (unsigned short)strlen(produse[i].nume);
        fwrite(&nNume, sizeof(unsigned short), 1, fis);
        fwrite(produse[i].nume, sizeof(char), nNume , fis);
        fwrite(&produse[i].nume, sizeof(float), 1, fis);
    }
    fclose(fis);
}

void adaugare() {
    char nume[100];
    float pret;

    printf("Nume produs: ");
    fgets(nume, sizeof(nume), stdin);
    nume[strcspn(nume, "\n")] = '\0';

    printf("Pret produs: ");
    scanf("%f", &pret);
    getchar();

    produse[nProduse].nume = (char*)malloc(strlen(nume) + 1);
    if (produse[nProduse].nume == NULL) {
        printf("Memorie insuficienta\n");
        eliberare();
        exit(EXIT_FAILURE);
    }
    strcpy(produse[nProduse].nume, nume);
    produse[nProduse].pret = pret;

    nProduse++;
}

void afisare() {
    if (nProduse == 0) {
        printf("Nu există produse înregistrate.\n");
        return;
    }

    for (int i = 0; i < nProduse; i++) {
        printf("%s - %.2f RON\n", produse[i].nume, produse[i].pret);
    }
}

int main() {
    int optiune;

    citire();

    do {
        printf("\n1. Adauga produs\n2. Afiseaza produse\n3. Iesire\n");
        printf("Opțiune: ");
        scanf("%d", &optiune);
        getchar();
        switch (optiune) {
            case 1:
                adaugare();
                break;
            case 2:
                afisare();
                break;
            case 3:
                scriere();
                eliberare();
                break;
            default:
                printf("Optiune invalida!\n");
                break;
        }
    } while (optiune != 3);

    return 0;
}
    */

//Aplicatia 5.5
    /*
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 16

void hexdump(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if(file == NULL)
    {
        perror("Eroare la deschiderea fisierului\n");
        exit(-1);
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t offset = 0;
    size_t bytesRead;

    while((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {
        printf("%08zx ", offset);
        for(int i=0; i < BUFFER_SIZE; i++)
        {
            if(i < bytesRead)
                printf("%02x ", buffer[i]);
            else
                printf("    ");
        }

        printf("|");
        for(int i=0; i < bytesRead; i++)
        {
            if(isprint(buffer[i]))
                printf("%c", buffer[i]);
            else
                printf(".");
        }
        for(size_t i=bytesRead; i< BUFFER_SIZE; i++)
            printf(" ");
        printf("|\n");

        offset+=bytesRead;
    }
    fclose(file);
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        perror("Eroare in linia de comanda");
        exit(-1);
    }

    hexdump(argv[1]);

    return 0;
}
    */

//Aplicatai 5.6
    /*
#include <stdio.h>
#include <stdlib.h>

void compare(const char *fisier1, const char *fisier2)
{
    FILE *f1 = fopen(fisier1, "rb");
    FILE *f2 = fopen(fisier2, "rb");

    if(f1 == NULL || f2 == NULL)
    {
        perror("Eroare la deschiderea fisierelor\n");
        exit(-1);
    }

    unsigned char octet1, octet2;
    size_t offset = 0;
    int diferit = 0;
    while(fread(&octet1, 1, 1, f1) == 1 && fread(&octet2, 1, 1, f2) == 1)
    {
        if(octet1 != octet2)
        {
            printf("%08zx: %02x %02x\n", offset, octet1, octet2);
            diferit = 1;
        }
        offset++;
    }
    while(fread(&octet1, 1, 1, f1) == 1)
    {
        printf("%08zx: %02x -- \n", offset, octet1);
        diferit = 1;
        offset++;
    }
    while(fread(&octet2, 1, 1, f2) == 1)
    {
        printf("%08zx: -- %02x\n", offset, octet2);
        diferit = 1;
        offset++;
    }
    fclose(f1);
    fclose(f2);

    if(!diferit)
        exit(0);
}

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        perror("Eroare in linia de comanda\n");
        exit(-1);
    }
    compare(argv[1], argv[2]);
    return 0;
}
    */

//Aplicatia 5.7
    /*
#include <stdio.h>
#include <stdlib.h>

void inlocuire(const char *fisier, size_t offset, unsigned char *octeti, size_t n)
{
    FILE *f = fopen(fisier, "rb+");
    if(f == NULL)
    {
        perror("Eroare deschidere fisier\n");
        exit(-1);
    }

    if(fseek(f, offset, SEEK_SET) != 0)
    {
        perror("Eroare la setarea offset-ului\n");
        fclose(f);
        exit(-1);
    }

    if(fwrite(octeti , 1 , n, f ) != n)
    {
        perror("Eroare la scrierea octetilor\n");
        fclose(f);
        exit(-1);
    }
    fclose(f);
}

int hex_to_byte(const char *s)
{
    int value;
    if(sscanf(s, "%x", &value) != 1)
    {
        perror("Eroare la conversia hexazecimala\n");
        exit(-1);
    }
    return value;
}


int main(int argc, int **argv)
{
    if(argc != 4)
    {
        perror("Eroare in linia de comanda\n");
        exit(-1);
    }

    size_t offset = hex_to_byte(argv[2]);
    size_t n = argc - 3;
    unsigned char *octeti = (unsigned char*)malloc(n);
    if(octeti == NULL)
    {
        perror("Eroare la alocarea dinamica\n");
        exit(-1);
    }

    for(int i=0; i < n; i++)
        octeti[i]=(unsigned char)hex_to_byte(argv[i+1]);
    inlocuire(argv[1], offset, octeti, n);

    free(octeti);
    return 0;
}
    */

//Aplicatia 5.8

    /*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

unsigned char hex_to_byte(const char *hex)
{
    unsigned int byte;
    sscanf(hex, "%2x", &byte);                  //functie pentru convertirea unui hexa intr un byte
    return (unsigned char)byte;
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        perror("Eroare in linia de comanda!\n");    //verificare argumente
        exit(-1);
    }

    FILE *f = fopen(argv[1], "rb");
    if(f == NULL)
    {
        perror("Eroare la deschiderea fisierului!\n");      //dechidere fisier binar
        exit(-1);
    }

    int npattern = argc - 2;
    unsigned char *pattern = malloc(npattern);
    if(pattern == NULL)
    {
        perror("Eroare la alocarea dinamica!\n");       //alocare dinamica a patternului dat de numerele hexa in linia de comanda
        exit(-1);
    }

    for(int i=0; i < npattern; i++)
        pattern[i]=hex_to_byte(argv[i+2]);  //umplerea vectorului pattern cu fiecare hexa transformat in byte


    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;
    long position = 0;
    int found = 0;

    while((bytesRead = fread(buffer, 1, BUFFER_SIZE, f))  > 0)      //citim din fiiser in buffer cate 4096 biti
    {
        for(size_t i = 0; i <=bytesRead - npattern; i++)            //parcurgem pana la ultimul - lungimea patternului bit citit
        {
            if(memcmp(buffer + i, pattern, npattern) == 0)          //comparam patternul cu elemntele din buffer+i de lungimea patternului
            {
                printf("gasit la pozitia : %lld\n", position + i);
                found = 1;
            }
        }
        position += bytesRead - npattern + 1;       //pozitia devine urmatoare pozitie neverificata
        fseek(f, position, SEEK_SET);               //mutam cursorul la noua pozitie pentru urmatoarea citire
    }

    if(found == 0)
        printf("Secventa nu a fost gasita\n");

    free(pattern);  //eliberare memorie
    fclose(f);      //inchidere fisier
    return 0;
}
    */

//Aplicatia 5.9

#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 4096

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        perror("Eroare in linia de comanda!\n");
        exit(-1);
    }

    int n = argc - 1;

    FILE *output = fopen(argv[n-1], "wb");
    if(output == NULL)
    {
        perror("Eroare deschiderea fisierului de output!\n");
        exit(-1);
    }

    for(int i=0; i<n-1; i++)
    {
        FILE *f = fopen(argv[i+1], "rb");
        if(f == NULL)
        {
            perror("Eroare la deschiderea fisierului!\n");
            exit(-1);
        }

        char buffer[BUFFER_SIZE];
        size_t bytesRead;
        unsigned long position = 0;
        while((bytesRead = fread(buffer, 1, BUFFER_SIZE, f)) > 0)
        {
            fwrite(buffer, 1, bytesRead, output);
        }
        fclose(f);
    }

    fclose(output);
    printf("FIsierele au fost concatenate cu succes!\n");
    return 0;
}

