#include <stdio.h>

void viderBuffer()
//Vide stdin pour ne pas avoir de boucle infinie si l'on tape autre chose qu'un nombre
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void menu0(){ //Affiche le menu
    printf("0: Ce menu\n1: Le nombre de naissances\n2: Le nombre de prénoms\n3: Statistiques sur un prénom\n4: Quitter\n");
}

void menu1(){ //Affiche le nombre de naissances
    printf("Le fichier recouvre n naissances.\n");
}

int menu2(){ //Affiche le nombre de prénoms
    char choix;
    printf("Voulez-vous distinguer le genre ? (O/N)\n");

    while(1){
        viderBuffer();
        scanf("%c",&choix);
        if (choix == 'N' || choix == 'n'){ //Si on ne distingue pas le genre
            return printf("Le fichier recouvre n prénoms\n");
        }
        else if (choix == 'O' || choix == 'o'){ //Si on distingue le genre
            return printf("Le fichier recouvre n prénoms masculins et n prénoms féminins\n");
        }
    }
}

int menu3(){ //Affiche les statistiques sur un prénom
    char buffer[256];
    printf("Quel prénom ?\n");

    while(1){
        viderBuffer();
        scanf("%s",buffer);
        return printf("Le prénom %s a été donné à n enfants.\nAnnée de première apparition : XXXX.\nAnnée de dernière apparition : XXXX\n",buffer);
    }
}

int main(int argc, char *argv[]){
    int i;
    while(1){
        viderBuffer(); //Si 1ère utilisation : appuyer sur entrée
        printf("\nQue voulez-vous afficher ? (0 pour le menu) > ");
        scanf("%d",&i);
        printf("\n");

        switch(i){

            case 0: menu0();break;

            case 1: menu1();break;

            case 2: menu2();break;

            case 3: menu3();break;

            case 4: return 1;

            default : printf("Le nombre doit etre compris entre 0 et 4 (0 pour le menu)\n");break;
        }
    }

}
