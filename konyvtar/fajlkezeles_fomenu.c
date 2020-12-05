#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "rekordkezeles.h"

Konyv *beolvas()
{
    Konyv *Head = NULL;
    FILE *Fs=NULL;              /*megprobalom megnyitni az adatbazisom*/
    Fs=fopen("konyvtar.txt", "r+");
    if(Fs==NULL)
    {
        printf("Meg ures a konyvtarad!"); /*Ha null pointert kapok akkor még nem létezik az adatbázis és kiléphetek a függvényből*/
        return NULL;
    }

    char szerzo[50]={0}, cim[50]={0}, ev[5]={0}, tema[20]={0}, kolcsonben[5]={0}; /*Lenullázva megadom a változókat amikbe beolvasok majd*/
    char c[2];                                                                    /*És ebből építem majd fel a láncolt listát is*/

    while(!feof(Fs))
    {
        szerzo[0]='\0';  /*Minden bevitel elott torlom az elozo adatokata valtozokbol*/
        cim[0]='\0';
        ev[0]='\0';
        tema[0]='\0';
        kolcsonben[0]='\0';
        fscanf(Fs,"%[^\n]s",&szerzo);/*A sor végéig beolvasok*/
        fgets(c, sizeof(c), Fs); /*következő sor elejére ugrás*/
        fscanf(Fs, "%[^\n]s", &cim);
        fgets(c, sizeof(c), Fs);
        fscanf(Fs, "%[^\n]s", &ev);
        fgets(c, sizeof(c), Fs);
        fscanf(Fs, "%[^\n]s", &tema);
        fgets(c, sizeof(c), Fs);
        fscanf(Fs, "%[^\n]s", &kolcsonben);
        fgets(c, sizeof(c), Fs);
        if(Head == NULL)
            rekordfelvesz(szerzo,cim,ev,tema,kolcsonben); /*Megvan minden valtozom keszithetem a lancolt listat*/
        else
        {
            Konyv *temp = Head;
            while(temp->kov != NULL)
                temp = temp->kov;
            temp->kov = rekordfelvesz(szerzo, cim, ev, tema, kolcsonben);
        }
    }

    fclose(Fs);
    return Head;
}



void rekordadatbazisba(Konyv *elso)
{
    if(elso==NULL){                      /*Üres listá felesleges adatbázisba írni.Feleslees mûveletet nem végzünk*/
            printf("Ures az adatbazis\n");
            return;
    }
    FILE *Fs=NULL;
    Fs=fopen("konyvtar.txt", "w+");  /*Egyébként létrehozunk egy fájlt*/
    if(Fs==NULL)
    {
        printf("Nem sikerult letrehozni az adabazist!"); /*Ha ezután is nullpointert kapunk akkor nem sikerült a létrehozás*/
        return;
    }
    Konyv * temp=elso;   /*Egyébként minden elemet beleírhatunk a fájlba*/
    while (temp!=NULL){
            if(temp->kov!=NULL){
            fprintf(Fs, "%s\n%s\n%s\n%s\n%s\n",temp->szerzo,temp->cim,temp->ev,temp->tema,temp->kolcsonben);/*minden adatot külön sorba írok*/
            temp=temp->kov;                                                                                 /*megkonnyitve ezzel a beolvasast*/
            }
            else{
            fprintf(Fs, "%s\n%s\n%s\n%s\n%s",temp->szerzo,temp->cim,temp->ev,temp->tema,temp->kolcsonben);
            temp=temp->kov; /*Ha az utolsó rekordhoz érek már nem kell a végére enter mert ez belezavar a fájl beolvasásánál és elcsúsznak az adatok*/
            }


    }
    printf("A mentes megtortent!");
 fclose(Fs);
 return;
}




void menukiir(void){
         printf("\nMenu\n"
           "1. Uj konyv hozzaadasa\n"
           "2. Kereses a konyek kozott\n"
           "3. Konyv torlese\n"
           "4. Konyv adatainak modositasa\n"
           "5. Modositasok mentese\n"
           "6. Teljes konyvtar kiirasa\n"
           "7. Kilepes\n");
    }
