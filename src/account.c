#include "../headers/global.h"

/**
 * @params
 */
void accountManagement(){
    int id;
    float solde;
    int day;
    float taux;
    int id_client;
    char prenom[255];
    char nom[255];
    int id_account;
    char choice;
    system("cls");
        do {
            printf("\n");
           printf("-----------------/ MY BANQUE - Account management /-----------------\n\n");
            printf("1 --- New account \n");
            printf("2 --- Consultation \n");
            printf("3 --- Close account \n");
            printf("6 --- Back to the main menu ---- \n\n");
            printf("\nPlease choose : ");
            scanf("%s", &choice);
            switch (choice) {
                case '1':
                    do {
                        printf("Please enter the client ID : ");
                        scanf("%d", &id_client);
                        printf("Please enter the solde : ");
                        scanf("%f", &solde);
                        printf("Please enter the taux : ");
                        scanf("%f", &taux);
                        printf("Please enter the duration : ");
                        scanf("%d", &day);
                        if(checkIfClientExist(id_client, NULL, NULL) == -1) {
                            printf("\nError : client does not exist.\n\n");
                        }
                    } while(checkIfClientExist(id_client, NULL, NULL) == -1);
                     newAccount(solde, day, taux, id_client);
                    break;
                case '2':
                    printf("Please enter firstname : ");
                    scanf("%s", prenom);
                    printf("Please enter lastname : ");
                    scanf("%s", nom);
                    printf("\n---------------------------------------\n");
                    displayAccountByClientName(prenom, nom);
                    printf("\n---------------------------------------\n");
                    break;
                case '3':
                    do {
                        printf("Enter the id of the account for delete : ");
                        scanf("%d", &id_account);
                        if(checkIfAccountExist(id_account) == -1) {
                            printf("Error : client does not exist.\n");
                        }
                    } while(checkIfAccountExist(id_account) == -1);
                    deleteAccount(id_account);
                    break;
                case '6':
                    menu();
                    choice = 'q';
                    break;
                default:

                    break;

            }
        }
        while (choice != 'q');
}


/**
 * @params int id, float solde, int day, float taux, int id_client
 */
int newAccount(float solde, int day, float taux, int id_client) {
    sqlite3_stmt *res;

    char *sql = "INSERT INTO compte(solde, duree_minimale, taux, id_client) VALUES(@solde,@duree_minimale,@taux,@id_client)";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int id_default_2 = sqlite3_bind_parameter_index(res, "@solde");
        sqlite3_bind_int(res, id_default_2, solde);
        int id_default_3 = sqlite3_bind_parameter_index(res, "@duree_minimale");
        sqlite3_bind_int(res, id_default_3, day);
        int id_default_4 = sqlite3_bind_parameter_index(res, "@taux");
        sqlite3_bind_int(res, id_default_4, taux);
        int id_default_5 = sqlite3_bind_parameter_index(res, "@id_client");
        sqlite3_bind_int(res, id_default_5, id_client);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if(step == SQLITE_DONE) {
        printf("\n\n Successfull new entry \n\n");
        system("pause");
    } else {
        printf("ERROR inserting data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(res);
    return 0;
}

/**
 * @params int id_account
 */
int deleteAccount(int id_account) {
    sqlite3_stmt *res;

    char *sql = "DELETE FROM compte WHERE id = @id";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int id_default = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, id_default, id_account);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    if(step == SQLITE_DONE) {
        printf("\n\n Successfull deleted \n\n");
        system("pause");
    } else {
        printf("ERROR inserting data: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_finalize(res);
    return 0;
}

/**
 * @params int id_account
 */
int checkIfAccountExist(int id_account) {
    sqlite3_stmt *res;
    int i = 0;

    char *sql = "SELECT * FROM compte WHERE id = @id";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int id_default = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, id_default, id_account);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    int step = sqlite3_step(res);

    if(step == SQLITE_DONE) {
        return -1;
    }

    if (step == SQLITE_ROW) {
        return 1;
    }

    sqlite3_finalize(res);
    return 0;
}
