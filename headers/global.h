#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "sqlite3.h"
#include "account.h"
#include "admin.h"
#include "client.h"

struct configuration {
    char* db_name;
    char* devise;
};
typedef struct configuration Config;

extern int max_id_client;
extern int max_id_account;
extern int rc; // Database
extern sqlite3 *db; // Database
extern Config config_default;

#endif
