#ifndef CLIENT_H
#define CLIENT_H

/* Prototypes for the functions */
void clientManagement();
int newClient(int id, char *prenom, char *nom, char *job, char *phone);
int checkIfClientExist(int id_client, char *nom, char *prenom);
void searchClient(char *nom);
int updateClient(int id, char *prenom, char *nom, char *job, char *phone);
int deleteClient(int id_client);

#endif
