#include "../headers/global.h"


/**
 * @params
 */
void clientManagement(){
    int id;
    int id_client = -1;
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
                if(checkIfClientExist(0, nom, prenom) == -1) {
                    newClient(id, nom, prenom, job, phone);
                } else {
                    printf("\n\nThis client already exists\n\n");
                    system("pause");
                }
                break;
            case '2':
                printf("Please enter firstname : ");
                scanf("%s", &prenom);
                printf("Please enter lastname : ");
                scanf("%s", &nom);
                id_client = checkIfClientExist(0, nom, prenom);
                if(id_client>0) {
                    system("cls");
                    printf("Please enter new firstname : ");
                    scanf("%s", &prenom);
                    printf("Please enter new lastname : ");
                    scanf("%s", &nom);
                    printf("Please enter new job : ");
                    scanf("%s", &job);
                    printf("Please enter new phone : ");
                    scanf("%s", &phone);
                    updateClient(id_client, prenom, nom, job, phone);
                } else {
                    printf("\n\nThis client doesnt exist\n\n");
                    system("pause");
                }
                break;
            case '3':
                printf("Enter lastname of the account for delete : ");
                scanf("%s", &nom);
                printf("Enter firstname of the account for delete : ");
                scanf("%s", &prenom);
                id_client = checkIfClientExist(0, nom, prenom);
                if(id_client>0) {
                    deleteClient(id_client);
                } else {
                    printf("\n\nThis client doesnt exist\n\n");
                    system("pause");
                }
                break;
            case '4':
                printf("Please enter lastname : ");
                scanf("%s", &nom);
                searchClient(nom);
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
 * @params int id_client
 */
int deleteClient(int id_client) {
    sqlite3_stmt *res;

    char *sql = "DELETE FROM client WHERE id = @id";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int id_default = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, id_default, id_client);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    if(step == SQLITE_DONE) {
        printf("\n\n Successfull deletion \n\n");
        system("pause");
    } else {
        printf("ERROR when trying to delete the user with id %d data: %s\n", id_client, sqlite3_errmsg(db));
    }
    sqlite3_finalize(res);
    return 0;
}

/**
 * @params int id, char *prenom, char *nom, char *job, char *phone
 */
int newClient(int id, char *nom, char *prenom, char *job, char *phone) {
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
 * @params int id, char *prenom, char *nom, char *job, char *phone
 */
int updateClient(int id, char *prenom, char *nom, char *job, char *phone) {
    sqlite3_stmt *res;

    char *sql = "UPDATE client SET nom = @nom, prenom = @prenom, profession = @profession, telephone = @telephone WHERE id = @id";

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
        printf("\n\n Successfull update \n\n");
        system("pause");
    } else {
        printf("ERROR updating client %s : %s\n",nom, sqlite3_errmsg(db));
    }

    sqlite3_finalize(res);
    return 0;
}

/**
 * @params int id_client
 */
void searchClient(char *nom) {
    sqlite3_stmt *res;
    const char *nom_result, *id_result, *prenom_result, *job_result, *phone_result;
    int i = 0;

    char *sql = "SELECT * FROM client WHERE nom like @nom";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int id_default = sqlite3_bind_parameter_index(res, "@nom");
        sqlite3_bind_text(res, id_default, strcat(nom, "%"), -1, SQLITE_TRANSIENT);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    int step = sqlite3_step(res);

    if(step == SQLITE_DONE) {
        printf("\nNo results found with that lastname\n\n");
    }

    while(step == SQLITE_ROW) {
        id_result = sqlite3_column_int(res, 0);
        prenom_result = sqlite3_column_text(res, 1);
        nom_result = sqlite3_column_text(res, 2);
        job_result = sqlite3_column_text(res, 3);
        phone_result = sqlite3_column_text(res, 4);
        if(!id_result) {
            break;
        }
        printf("%d | %s | %s | %s | %s \n", id_result, prenom_result, nom_result, job_result, phone_result);
        step = sqlite3_step(res);
    }

    sqlite3_finalize(res);
    system("pause");
}


/**
 * @params int id_client, char *nom, char *prenom;
 */
int checkIfClientExist(int id_client, char *nom, char *prenom) {
    sqlite3_stmt *res;
    int i = 0;
    char clause[100] = "";
    char sql[200] = "SELECT * FROM client WHERE ";

    if(id_client) {
        strcat(clause, " id = @id and ");
    }

    if(strlen(nom) > 0) {
        strcat(clause, " LOWER(nom) = @nom and ");
    }

    if(strlen(prenom) > 0) {
        strcat(clause, " LOWER(prenom) = @prenom and ");
    }

    strcat(sql, clause);
    strcat(sql, "1=1");

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        if(id_client) {
            int id_default = sqlite3_bind_parameter_index(res, "@id");
            sqlite3_bind_int(res, id_default, id_client);
        }
        if(strlen(nom) > 0) {
            int id_default_1 = sqlite3_bind_parameter_index(res, "@nom");
            sqlite3_bind_text(res, id_default_1, convertToLower(nom), -1, SQLITE_TRANSIENT);
        }
        if(strlen(prenom) > 0) {
            int id_default_2 = sqlite3_bind_parameter_index(res, "@prenom");
            sqlite3_bind_text(res, id_default_2, convertToLower(prenom), -1, SQLITE_TRANSIENT);
        }
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    int step = sqlite3_step(res);

    if(step == SQLITE_DONE) {
        return -1;
    }

    if (step == SQLITE_ROW) {
        return sqlite3_column_int(res, 0);
    }
    sqlite3_finalize(res);
    return 0;
}


