#ifndef HEADER_FILE_H
#define HEADER_FILE_H
typedef struct Konyv
{
    char szerzo[50];
    char cim[50];         /*Készítek egy struktúrát ami a könyv adatait tárolja majd és láncolt lista elemeként is szolgál*/
    char ev[5];
    char tema[20];
    char kolcsonben[5];
    struct Konyv *kov;
}Konyv;
#endif

Konyv* beolvas();
void rekordadatbazisba(Konyv *elso);
void menukiir(void);
