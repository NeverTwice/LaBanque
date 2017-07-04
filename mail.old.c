/*
 PROJET BRANQUE C
*/

//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
const char* os = "Windows";
#else
#ifdef __linux
const char* os = "Linux";
#else
#ifdef __APPLE__
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
const char* os = "Mac os";
#else
const char* os = "Unknown";
#endif
#endif
#endif

//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////

void adminMenu();
void admin(char *pseudo);
void loginAdmin();
void menu();
void getMac();


int main(int argc, const char * argv[]) {
    char mac;
    FILE *fp = popen("ifconfig en0 | awk '/ether/{print $2}'", "r");
    fscanf(fp, "%s", &mac);
    printf("%s\n", &mac);
    pclose(fp);
    //getMac();
    //printf("\033[031m This text is red \033[0m This text has default color\n");
    printf("os = %s\n", os);
    menu();
    return 0;
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
    } while(choice < 1 || choice > 6);

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

            break;
        case 6:
            menu();
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
    } while(choice < 1 || choice > 6);

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




void getMac() {


    //system("ifconfig | grep -o -E '^[^\t:]+:([^\n]|\n\t)*status: active' | egrep -o -m 1 '^[^\t:]+'");

    system("ifconfig en0 | grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}'");
}

