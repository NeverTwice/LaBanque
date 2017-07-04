#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

void adminMenu();
void admin(char *pseudo);
void loginAdmin();
void menu();


int main(int argc, char** argv) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("labanque.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      menu();
   }
   sqlite3_close(db);
}

void menu() {

    int choice;
    do {
        printf("-----------------/ MY BANQUE /-----------------\n\n");
        printf("1 --- Gestion des clients \n");
        printf("2 --- Gestion des comptes \n");
        printf("3 --- Gestion des opérations \n");
        printf("4 --- Historique \n");
        printf("5 --- Administration\n");
        printf("6 --- Quitter le programme\n\n");
        printf("Veuillez choisir ce que vous voulez faire : ");
        scanf("%d", &choice);
    } while(choice != 6);

    switch (choice) {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:
            loginAdmin();
            break;
        case 6:
            exit(0);
            break;

        default:
            break;

    }
}


void admin(char *pseudo) {
    printf("Welcome : %s\n\n", pseudo);
    adminMenu();
}

void loginAdmin() {

    char pseudo[10] = "salut";
    char password[10] = "lol";
    char getPseudo[10] = "";
    char getPassword[10] = "";
    int resultPseudo;
    int resultPassword;
    int cptCo = 0;


    printf("-----------------/ MY BANQUE : ADMIN /-----------------\n\n");
    printf("Si vous voulez entrer dans l'administrateur\n merci d'entrer le pseudo et le mot de passe\n\n");

    while(1) {
        if(cptCo == 3) {
            printf("Trop de tentative.\n -> Tentative max : 3\n\n");
            menu();
        } else {
            printf("Entrez le pseudo : ");
            scanf("%s", getPseudo);
            printf("Entre le mot de passe : ");
            scanf("%s", getPassword);

            resultPseudo = strcmp(pseudo, getPseudo);
            resultPassword = strcmp(password, getPassword);

            if(resultPseudo != 0 && resultPassword != 0) {
                printf("\n --- > Erreur dans l'identification\n\n");
                cptCo++;
            } else {
                break;
            }
        }
    }

    admin(pseudo);
}

void adminMenu() {
     int choice;
    do {
        printf("1 --- Afficher la somme des montants de tous les comptes \n");
        printf("2 --- Afficher la somme des montants par type de compte \n");
        printf("3 --- Afficher le montant d’intérêts total et par type de compte que devra verser la banque a la fin de l’années \n");
        printf("4 --- Exporter l’ensemble des données de l’application \n");
        printf("5 --- Importer des données dans l’application\n");
        printf("6 --- Revenir au menu principal ---\n\n");
        printf("Veuillez choisir ce que vous voulez faire : ");
        scanf("%d", &choice);
    } while(choice != 6);
}
