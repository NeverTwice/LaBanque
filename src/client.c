#include "../headers/global.h"


/**
 * @params
 */
void clientManagement(){
    int id;
    char prenom[25];
    char nom[40];
    char job[20];
    char phone[11];

    int end = 0;
    system("cls");
    while(!end) {
        system("cls");
        int choice;
        printf("-----------------/ MY BANQUE - Client management /-----------------\n\n");
        printf("1 --- Add a client \n");
        printf("2 --- Edit a client \n");
        printf("3 --- Delete a client \n");
        printf("4 --- Search a client \n");
        printf("6 --- Back to the main menu ---- \n\n");
        printf("\nPlease choose : ");

        choice = getchar();

        if(choice != '\n' && choice != EOF) {
            int d;
            while((d = getchar()) != '\n' && d != EOF);
        }

        switch (choice) {
            case '1':
                id = max_id_client+1; // Last id client added +1
                printf("Please enter firstname : ");
                scanf("%s", &prenom);
                printf("Please enter lastname : ");
                scanf("%s", &nom);
                printf("Please enter job : ");
                scanf("%s", &job);
                printf("Please enter phone number : ");
                scanf("%s", &phone);

                newClient(id, nom, prenom, job, phone);
                break;
            case '2':

                printf("\n---------------------------------------\n");
                displayAccountByClientName(prenom, nom);
                printf("\n---------------------------------------\n");
                break;
            case '3':
                printf("Enter the id of the account for delete : ");
                //scanf("%d", &id_account);
                //deleteAccount(config_default, db, id_account);
                break;
            case '4':

                break;
            case '6':
                menu();
                break;
            default:
                break;

        }
    }
}

/**
 * @params int id, char *prenom, char *nom, char *job, char *phone
 */
int newClient(int id, char *prenom, char *nom, char *job, char *phone) {
    //char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql = "INSERT INTO client(id, nom, prenom, profession, telephone) VALUES(@id, @nom, @prenom, @profession, @telephone)";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int id_default = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, id_default, id);
        int id_default_2 = sqlite3_bind_parameter_index(res, "@nom");
        sqlite3_bind_text(res, id_default_2, nom, -1, SQLITE_TRANSIENT);
        int id_default_3 = sqlite3_bind_parameter_index(res, "@prenom");
        sqlite3_bind_text(res, id_default_3, prenom, -1, SQLITE_TRANSIENT);
        int id_default_4 = sqlite3_bind_parameter_index(res, "@profession");
        sqlite3_bind_text(res, id_default_4, job, -1, SQLITE_TRANSIENT);
        int id_default_5 = sqlite3_bind_parameter_index(res, "@telephone");
        sqlite3_bind_text(res, id_default_5, phone, -1, SQLITE_TRANSIENT);
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
 * @params int id_client
 */
int checkIfClientExist(int id_client) {
    sqlite3_stmt *res;
    int i = 0;

    char *sql = "SELECT * FROM client WHERE id = @id";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int id_default = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, id_default, id_client);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    int step = sqlite3_step(res);

    if(step == SQLITE_DONE) {
        return 2;
    }

    if (step == SQLITE_ROW) {
        return 1;
    }
    sqlite3_finalize(res);
    return 0;
}
