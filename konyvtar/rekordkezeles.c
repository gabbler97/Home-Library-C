#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include "fajlkezeles_fomenu.h"


Konyv *rekordfelvesz(char* szerzo,char* cim,char* ev,char* tema, char* kolcsonben){
    Konyv *temp2=(Konyv*) malloc(sizeof(Konyv));   /*Lefoglalom a követezõ elem helyét a memóriában*/
    if(temp2==NULL){
                printf("Nem sikerult a helyfoglalas\n");
        return;
    }

    strcpy(temp2->szerzo, szerzo);
    strcpy(temp2->cim, cim);
    strcpy(temp2->tema, tema);                /*Beletöltöm a felett adatokat*/
    strcpy(temp2->ev, ev);
    strcpy(temp2->kolcsonben,kolcsonben);
    temp2->kov= NULL;
    return temp2;
}


void rekordkiir(Konyv *elso){
    Konyv *atmeneti=elso;                    /*Minden rekord kiírásánál végigmegyek a listán és minden eemét kiírom*/
    if(atmeneti!=NULL)
    {
    while (atmeneti!=NULL){
           printf("%s %s %s %s Kolcsonben? :%s\n", atmeneti->szerzo, atmeneti->cim,atmeneti->ev,atmeneti->tema,atmeneti->kolcsonben);
           atmeneti=atmeneti->kov;
    }
    }
    else printf("Ures a konyvtar! \n");
}



void konyvkiir(Konyv *elem){                  /*Egy segédfüggvény mely segít majd kiírni egy bzonyos elemet keresésnél/módosításnál*/
    printf("%s-%s %s. %s-Kolcsonben?: %s\n", elem->szerzo,elem->cim,elem->ev,elem->tema,elem->kolcsonben);
}

void keres(Konyv* Head, char *kriterium, char *arg)  /*Keresésnél bekérem mit és mire szeretne módosítani a user*/
{
    Konyv *temp=Head;

    if(strcmp(kriterium, "szerzo")==0){
            if(temp!=NULL)     /*Ha pl a szerzõt végigmegy a listán a szerzõvel megegyezõ rekordokat kiírja. Hasonlóan a többinél is így jár el.*/
            {
                if(strcmp(temp->szerzo,arg)==0)
                konyvkiir(temp);
                temp=temp->kov;
            }
            }
            else if (strcmp(kriterium, "cim")==0)
            {
            while(temp!=NULL){
            if(strcmp(temp->cim,arg)==0)
            konyvkiir(temp);
            temp=temp->kov;
            }
            }
            else if (strcmp(kriterium,"kolcsonben")==0)
            {
            while(temp!=NULL){
                if(strcmp(temp->kolcsonben,arg)==0)
                    konyvkiir(temp);
                temp=temp->kov;

            }
            }
     else if (strcmp(kriterium, "kiadasi ev")==0)
            {
            while(temp!=NULL){
            if(strcmp(temp->ev,arg)==0)
            konyvkiir(temp);
            temp=temp->kov;
            }
            }

      else if (strcmp(kriterium, "tema")==0)
            {
            while(temp!=NULL){
            if(strcmp(temp->tema,arg)==0)
            konyvkiir(temp);
            temp=temp->kov;
            }
            }

    else
    {                           /*ha olyan kritériumot kapok ami nincs a felsorolásban hibaüzenetet küldök*/
    printf("Rossz a keresesi feltetel! Valassz a felsorolt listabol!\n");
    return;
    }
}


void rekordtorol(Konyv* Head, char* szerzo, char* cim)
{

if(Head==NULL)
{
        printf("Ures a konyvtarad!\n"); /*Ha üres a lista akkkor már felesleges végezni a törlést visszatérhetünk hibaüzenettel*/
        return;
}
if(Head->kov==NULL) /*ha egy listaelem van csak azt kell összehasonlitani  a keresettel*/
{
        char c;
        if(strcmp(Head->szerzo,szerzo)==0 && strcmp(Head->cim,cim)==0)
        {
            konyvkiir(Head);
            printf("Biztosan Torli? I\\N\n");
            scanf("%c", &c);
            if(c=='I' || c=='i')
            {
                free(Head);    /*Ilyenkor elég törölni a head-et és beállítani oda egy Null pointer*/
                Head=NULL;
                system("cls");
                printf("Torolve!");
                menukiir();
            }
                return;

         }
         else
         {
             system("cls");
             printf("Nincs ilyen konyv"); /*Ha nincs találat hibaüzenettel térünk vissza */
             menukiir();
             return;
         }
}
else if (Head->kov!=NULL){            /*Ha több listaelem van végig kll mennünk és minden elemet megvizsgálunk*/
    if(strcmp(Head->szerzo,szerzo)==0 && (strcmp(Head->cim,cim))==0){
        Head=Head->kov;
        Konyv *tmp = Head; Head = Head->kov; free(tmp);
return;
    }
}



Konyv *temp=Head;  /*A pointerek átcsatolásánál szükséges a törlendõre mutató és az õt követõ pointer megjegyzése*/
Konyv *elozo=NULL;
char c;
    do
    {
        elozo=temp;
        temp=temp->kov;
    }
    while(strcmp(temp->szerzo,szerzo)!=0 && strcmp(temp->cim,cim)!=0);

    konyvkiir(temp);
    printf("Biztosan Torli? I\\N\n");
    scanf("%c", &c);
    if(c=='I' || c=='i'){
            elozo->kov=temp->kov; /*HA törlünk egy kiválasztott elemet akkor megtörténik az átkötés*/
            free(temp); /*Az aktuális elem kikerült a listából így már felszabadíthatjuk*/
            system("cls");
            printf("Torolve!");
            menukiir();
    }
    return;
}



void rekordmodosit(Konyv *Head, char *szerzo, char *cim) /*Módosításnál szerzõ és cím alpján kereshetünk pontosan*/
{
    if(Head == NULL)            /*Ha a lista Head NULL akkor nincs elem.*/
    {
        printf("Ures a konyvtar!\n");
        return;
    }

    Konyv *temp = Head;    /*Egyébként végezhetjük a keresést*/
    char modosito[20] = {0};
    char mire[50] = {0};

    while(strcmp(temp->szerzo, szerzo) != 0 && strcmp(temp->cim, cim) != 0) /*Bevisszük, hgy mit és mire szeretne módosítani a user*/
        temp = temp->kov; /*És addig megyünk is míg me nem találtuk*/

    printf("Melyik reszet szeretned modositani?\nLehetosegek:szerzo, cim, kiadasi ev, tema,kolcsonben\n");
    gets(modosito);
    printf("Mire szeretned modositani?\n");
    gets(mire);
    if(strcmp(modosito, "szerzo") == 0) /*A listából kiválasztva megadjuk mit akarunk módosítani*/
    {
        temp->szerzo[0] = '\0';
        strcpy(temp->szerzo, mire);
    }
    else if(strcmp(modosito, "cim") == 0)
    {
        temp->cim[0] = '\0';
        strcpy(temp->cim, mire);
    }
    else if(strcmp(modosito, "kolcsonben")==0)
    {
        strcpy(temp->kolcsonben, mire);
    }
    else if(strcmp(modosito, "kiadasi ev") == 0)
    {
        temp->ev[0] = '\0';
        strcpy(temp->ev, mire);
    }
    else if(strcmp(modosito, "tema") == 0)
    {
        temp->tema[0] = '\0';
        strcpy(temp->tema, mire);
    }
    else
    {
        printf("Ilyen modositasi lehetoseg nincs!\n"); /*Ha nem adunk meg olyan lehetõséget ami a listában van, jelezzük*/
        return;
    }
    return;
}
