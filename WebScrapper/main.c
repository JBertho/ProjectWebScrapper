#include "sources/headers/header.h"
#include "sources/headers/structure.h"


int main()
{
    int choice = 0;
    do{
        system("cls");
        printf("====================================== \n");
        printf("              WEB SCRAPPER             \n");
        printf("====================================== \n");
        printf("\n\n\n\n");
        printf("Le fichier de configuration se situe dans le dossier resource. \n\n");

        if(choice < 0 || choice > 2 ){
            printf("/!\\ Selectionner une valeur parmis les choix possibles. \n\n");
        }

        printf("1 - Lancer le webScrapper\n");
        printf("2 - Quitter\n");
        printf("Choix : ");
        scanf("%d",&choice);
    }while(choice < 1 || choice > 2);

    if(choice == 1){
        system("cls");
        printf("====================================== \n");
        printf("              WEB SCRAPPER             \n");
        printf("====================================== \n");
        printf("\n\n");
        printf("======================== \n");
        printf("======= EN COURS =======\n");
        printf("======================== \n");
        startParseConf();
    }

    return 0;
}
