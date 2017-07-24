#include "headers/global.h"

int max_id_client; // Client counter
int max_id_account; // Account counter
int max_id_operation; // Account counter
int rc; // Database
sqlite3 *db; // Database

Config config_default = {
    "/Users/Sam/Desktop/ProjetBanqueC/LaBanque/labanque.db",
    "euros"
};

void openDatabase();
void closeDatabase();
char* convertToLower(char *newString);
void menu();
int getHistorique(int id_user);

int main(int argc, char* argv[]) {

    openDatabase();

    sqlite3_stmt *res;
    char *sql = "SELECT max(client.id), max(compte.id) from client, compte";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    int step = sqlite3_step(res);
    if(step == SQLITE_DONE) {
        printf("/!\ No id has been associated.\n");
    }
    if (step == SQLITE_ROW) {
        max_id_client = sqlite3_column_int(res, 0); // Gets last id client
        max_id_account = sqlite3_column_int(res, 1); // Gets last id account
    }
    menu();
}

/**
    Main functions
                    **/

/**
 * @params
 */
void openDatabase() {
    int rc = sqlite3_open(config_default.db_name, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
}

/**
 * @params
 */
void closeDatabase() {
    sqlite3_close(db);
}

/**
 * @params char *newString
 */
char* convertToLower(char *newString) {
    int i;
    for(i = 0; i < strlen(newString); i++) {
        newString[i] = tolower(newString[i]);
    }
    return newString;
}

/**
 * @params
 */
void menu() {
    int id_user;
        system("cls");
        char choice;
        do {
            printf("\n");
            printf("-----------------/ MY BANQUE /-----------------\n\n");
            printf("1 --- Customer Management \n");
            printf("2 --- Account management \n");
            printf("3 --- Operations management \n");
            printf("4 --- Historic \n");
            printf("5 --- Administration\n");
            printf("q --- Exit the program\n\n");
            printf("\nPlease choose : ");
            scanf("%s", &choice);
             switch(choice) {
                case '1':
                    clientManagement();
                    break;
                case '2':
                    accountManagement();
                    break;
                case '3':
                    operationManagement();
                    break;
                case '4':
                    printf("Please enter user id for export:");
                    scanf("%d", &id_user);
                    getHistorique(id_user);
                    break;
                case '5':
                    loginAdmin();
                    break;
                case 'q':
                    closeDatabase();
                    exit(0);
                default:
                    break;
            }
        }
        while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != 'q');
}

int getHistorique(int id) {
    sqlite3_stmt *res;
    int i;
    float montant;
    char *depuis;
    char *vers;
    FILE * fileWriter;
    fileWriter = fopen ("historique.csv", "w+");

    if(fileWriter != NULL) {

        char *sql = "SELECT operations.montant, client_from.nom as depuis, client_to.nom as vers FROM operations, compte, client client_from, client client_to WHERE client_to.id_client = operations.id_comptedest and client_from.id_client = operations.id_comptesrc and (operations.id_comptedest = compte.id OR operations.id_comptesrc = compte.id) AND compte.id_client = @id";

        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        if (rc == SQLITE_OK) {
            int id_default = sqlite3_bind_parameter_index(res, "@id");
            sqlite3_bind_int(res, id_default, id);
        } else {
            fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        }

        int step = sqlite3_step(res);
        while(step == SQLITE_ROW) {
            montant = sqlite3_column_double(res, 0);
            depuis = sqlite3_column_text(res, 1);
            vers = sqlite3_column_text(res, 2);

            fprintf(fileWriter, "%s -> %s DE : %.2f %s \n", depuis, vers, montant, config_default.devise);
            step = sqlite3_step(res);
        }
        sqlite3_finalize(res);
        fclose(fileWriter);
    }
    return 0;
}
