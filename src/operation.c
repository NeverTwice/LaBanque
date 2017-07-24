#include "../headers/global.h"

/**
 * @params
 */
void operationManagement(){
    int id;
    int from;
    int to;
    float money;

    int end = 0;
    system("cls");
    while(!end) {
        system("cls");
        int choice;
        printf("-----------------/ MY BANQUE - Operation management /-----------------\n\n");
        printf("1 --- Deposit \n");
        printf("2 --- Withdraw \n");
        printf("3 --- Make a Transfert \n");
        printf("6 --- Back to the main menu ---- \n\n");
        printf("\nPlease choose : ");

        choice = getchar();

        if(choice != '\n' && choice != EOF) {
            int d;
            while((d = getchar()) != '\n' && d != EOF);
        }

        switch (choice) {
            case '1':
                printf("Please enter the account number : ");
                scanf("%d", &to);
                printf("Please enter money quantity : ");
                scanf("%f", &money);
                if(checkIfAccountExist(to) == 1) {
                    singleOperation(money, to);
                } else {
                    printf("\n\nThis account doesnt exist\n\n");
                    system("pause");
                }
                break;
            case '2':
                printf("Please enter the account number : ");
                scanf("%d", &from);
                printf("Please enter money quantity : ");
                scanf("%f", &money);
                if(checkIfAccountExist(from) == 1) {
                    singleOperation(-money, from);
                } else {
                    printf("\n\nThis account doesnt exist\n\n");
                    system("pause");
                }
                break;
            case '3':
                printf("Please enter the account number FROM : ");
                scanf("%d", &from);
                printf("Please enter the account number TO : ");
                scanf("%d", &to);
                printf("Please enter money quantity : ");
                scanf("%f", &money);
                if(checkIfAccountExist(from) == 1 && checkIfAccountExist(to) == 1) {
                    transfertOperation(money, from, to);
                } else {
                    printf("\n\nOne of the accounts doesnt exist\n\n");
                    system("pause");
                }
                break;
            case '6':
                menu();
                break;
            default:
                break;

        }
    }
}

void singleOperation(float money, int to) {
    sqlite3_stmt *res;

    char *sql = "INSERT INTO operations(id, id_comptesrc, id_comptedest, montant, date_operation) VALUES(@id, @from, @to, ROUND(@money, 2), date('now'))";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int id_default = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, id_default, ++max_id_account);
        int id_default_1 = sqlite3_bind_parameter_index(res, "@from");
        sqlite3_bind_int(res, id_default_1, 0);
        int id_default_2 = sqlite3_bind_parameter_index(res, "@to");
        sqlite3_bind_int(res, id_default_2, to);
        int id_default_3 = sqlite3_bind_parameter_index(res, "@money");
        sqlite3_bind_double(res, id_default_3, money);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if(step == SQLITE_DONE) {
        sql = "UPDATE compte SET solde = ROUND(solde, 2) + ROUND(@solde, 2) WHERE id_client = @client";

        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

        if (rc == SQLITE_OK) {
            int id_default = sqlite3_bind_parameter_index(res, "@client");
            sqlite3_bind_int(res, id_default, to);
            int id_default_1 = sqlite3_bind_parameter_index(res, "@solde");
            sqlite3_bind_double(res, id_default_1, money);
        } else {
            fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        }

        int step = sqlite3_step(res);

        if(step == SQLITE_DONE) {
            printf("\n\nSuccessfull operation of %.2f to account number %d \n\n", money, to);
            system("pause");
            return 0;
        } else {
            printf("ERROR inserting data: %s\n", sqlite3_errmsg(db));
        }
    } else {
        printf("ERROR inserting data: %s\n", sqlite3_errmsg(db));
    }
    system("pause");
    sqlite3_finalize(res);
    return 0;
}

void transfertOperation(double money, int from, int to) {
    sqlite3_stmt *res;

    char *sql = "INSERT INTO operations(id, id_comptesrc, id_comptedest, montant, date_operation) VALUES(@id, @from, @to, ROUND(@money, 2), date('now'))";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int id_default = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, id_default, ++max_id_account);
        int id_default_1 = sqlite3_bind_parameter_index(res, "@from");
        sqlite3_bind_int(res, id_default_1, from);
        int id_default_2 = sqlite3_bind_parameter_index(res, "@to");
        sqlite3_bind_int(res, id_default_2, to);
        int id_default_3 = sqlite3_bind_parameter_index(res, "@money");
        sqlite3_bind_double(res, id_default_3, money);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if(step == SQLITE_DONE) {
        sql = "UPDATE compte SET solde = ROUND(solde, 2) + ROUND(@solde, 2) WHERE id_client = @client";

        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

        if (rc == SQLITE_OK) {
            int id_default = sqlite3_bind_parameter_index(res, "@client");
            sqlite3_bind_int(res, id_default, from);
            int id_default_1 = sqlite3_bind_parameter_index(res, "@solde");
            sqlite3_bind_double(res, id_default_1, -money);
        } else {
            fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        }

        int step = sqlite3_step(res);

        if(step == SQLITE_DONE) {
            sql = "UPDATE compte SET solde = ROUND(solde, 2) + ROUND(@solde, 2) WHERE id_client = @client";

            rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

            if (rc == SQLITE_OK) {
                int id_default = sqlite3_bind_parameter_index(res, "@client");
                sqlite3_bind_int(res, id_default, to);
                int id_default_1 = sqlite3_bind_parameter_index(res, "@solde");
                sqlite3_bind_double(res, id_default_1, money);
            } else {
                fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
            }

            int step = sqlite3_step(res);

            if(step == SQLITE_DONE) {
                printf("\n\nSuccessfull operation of %.2f from account %d to account number %d \n\n", money, from, to);
                system("pause");
                return 0;
            } else {
                printf("ERROR inserting data: %s\n", sqlite3_errmsg(db));
            }
        } else {
            printf("ERROR inserting data: %s\n", sqlite3_errmsg(db));
        }
    } else {
        printf("ERROR inserting data: %s\n", sqlite3_errmsg(db));
    }
    system("pause");
    sqlite3_finalize(res);
    return 0;
}
