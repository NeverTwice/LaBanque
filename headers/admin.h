#ifndef ADMIN_H
#define ADMIN_H

/* Prototypes for the functions */
void admin(char *pseudo);
void adminMenu();
void loginAdmin();
int logIn(char *name, char *password);
int displaySumAmount();
int displayAccountByClientName(char *prenom, char *nom);
int displayAmountByAccountType(int id);
int displayAmountInterests();
int dump_db (sqlite3 *db, char *filename);
int dumpDatabase(char *nameFile);
int importDatabase(char *nameFile);

#endif
