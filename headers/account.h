#ifndef ACCOUNT_H
#define ACCOUNT_H

/* Prototypes for the functions */
int deleteAccount(int id_account);
void accountManagement();
int newAccount(float solde, int day, float taux, int id_client);
int checkIfAccoutExist(int id_account);

#endif
