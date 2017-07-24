PRAGMA foreign_keys=OFF;

BEGIN TRANSACTION;

DELETE FROM 'sqlite_sequence';

INSERT INTO "sqlite_sequence" VALUES('client',4);

INSERT INTO "sqlite_sequence" VALUES('admin',1);

INSERT INTO "sqlite_sequence" VALUES('compte',5);

INSERT INTO "sqlite_sequence" VALUES('operations',1);

DROP TABLE 'client';

CREATE TABLE "client"

(

    id INTEGER PRIMARY KEY AUTOINCREMENT,

    prenom VARCHAR DEFAULT 100,

    nom VARCHAR DEFAULT 100,

    profession VARCHAR DEFAULT 100,

    telephone VARCHAR DEFAULT 14

);

INSERT INTO "client" VALUES(1,'Jean','Dupond','Professeur','1042345235');

INSERT INTO "client" VALUES(2,'Clara','Duponne','Pompier','345234523456');

INSERT INTO "client" VALUES(3,'Yann','Nouve','Developpeur','2345235');

INSERT INTO "client" VALUES(4,'Frederic','Sananes','President de la banque','345345345345');

DROP TABLE 'admin';

CREATE TABLE admin

(

    id INTEGER PRIMARY KEY AUTOINCREMENT,

    id_client INT UNIQUE,

    mdp VARCHAR DEFAULT 60

);

INSERT INTO "admin" VALUES(1,4,'test');

DROP TABLE 'compte';

CREATE TABLE "compte"

(

    id INTEGER PRIMARY KEY AUTOINCREMENT,

    solde FLOAT,

    duree_minimale INT,

    taux FLOAT,

    id_client INT

);

INSERT INTO "compte" VALUES(1,1.0,1,1.0,1);

INSERT INTO "compte" VALUES(2,4.0,6,5.0,3);

INSERT INTO "compte" VALUES(4,6.0,8,7.0,5);

INSERT INTO "compte" VALUES(5,6.0,8,7.0,5);

DROP TABLE 'operations';

CREATE TABLE "operations"

(

    id INTEGER PRIMARY KEY AUTOINCREMENT,

    id_comptesrc INT,

    id_comptedest INT,

    montant FLOAT,

    date_operation DATE

);

INSERT INTO "operations" VALUES(1,2,3,100.0);

COMMIT;