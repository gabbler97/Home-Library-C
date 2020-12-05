#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include "rekordkezeles.h"
#include "fajlkezeles_fomenu.h"

int main()
{
    Konyv *Head = NULL;
    char szerzo[50];
    char cim[50];
    char ev[5];
    char tema[20];
    int menuelem=0;
    char kolcsonben[5];
    char kriterium[20];
    char arg[50];
    char modosito[20];
    char mire[50];

    Head = beolvas(Head);
    menukiir();
    while (scanf("%d",&menuelem)!=0 && menuelem!=7)
    {
        if(menuelem==1)
        {
            printf("Kerelek add meg a szerzot!\n");
            fflush(stdin);                /*Mindig torlom a bemenetet hogy az entert ne vegye karakternek*/
            gets(szerzo);                 /*bekerem a stringet*/
            printf("Add meg a konyv cimet\n");
            gets(cim);
            printf("Add meg a kiadasi evet\n");
            scanf("%s",&ev);
            fflush(stdin);
            printf("Add meg a temat\n");
            fflush(stdin);
            gets(tema);
            printf("kolcson adtad? Igen vagy Nem?\n");
            gets(kolcsonben);
            if(Head==NULL)
            {
                Head = rekordfelvesz(szerzo, cim, ev, tema, kolcsonben);
            }
            else
            {
                Konyv *temp=Head;
                while(temp->kov!=NULL)                         /*Végigmegyek a listán*/
                    temp=temp->kov;
                temp->kov = rekordfelvesz(szerzo,cim,ev,tema,kolcsonben);
            }
            system("cls");               /*Torlom a kepernyot a jobb atlathatosag erdekeben*/
            printf("Felveve.Kerlek mentsd a modositasokat!");
            menukiir();
        }
        else if (menuelem==2)
        {
            printf("Mi alapjan keresel?\n Szerzo,cim,kiadasi ev,tema,kolcsonben\n");
            fflush(stdin);
            gets(kriterium);
            printf("Mit/kit keres\n");
            gets(arg);
            keres(Head, kriterium,arg);


        }
        else if (menuelem==3)
        {
            printf("Adja meg a konyv szerzojet es cimet amit torolni szeretne\n");
            printf("szerzo: ");
            fflush(stdin);
            gets(szerzo);
            printf("cim: ");
            gets(cim);
            rekordtorol(Head, szerzo,cim);

        }
        else if(menuelem==4)
        {
            printf("Ird be a modositando konyv szerzojet majd cimet!\n");
            printf("cim: ");
            fflush(stdin);
            gets(cim);
            printf("szerzo: ");
            gets(szerzo);
            rekordmodosit(Head, szerzo,cim);
            system("cls");
            printf("Modositva!");
            menukiir();


        }
        else if(menuelem==5)
        {
            rekordadatbazisba(Head);
        }

        else if(menuelem==6)
        {
            rekordkiir(Head);
        }

    }
    printf("\nJo olvasast!");
    return 0;
    }
