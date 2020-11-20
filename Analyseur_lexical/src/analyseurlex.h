#ifndef N
#define N
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//Structures

typedef enum{
    PROGRAM_TOKEN,CONST_TOKEN,VAR_TOKEN,BEGIN_TOKEN,END_TOKEN,IF_TOKEN,THEN_TOKEN,WHILE_TOKEN,DO_TOKEN,READ_TOKEN,WRITE_TOKEN,
    PV_TOKEN,PT_TOKEN,PLUS_TOKEN,MOINS_TOKEN,MULT_TOKEN,DIV_TOKEN,VIR_TOKEN,EQ_TOKEN,AFF_TOKEN,INF_TOKEN,INFEG_TOKEN,SUP_TOKEN,SUPEG_TOKEN,
    DIFF_TOKEN,PO_TOKEN,PF_TOKEN,FIN_TOKEN,ID_TOKEN,NUM_TOKEN,ERREUR_TOKEN
}CODES_LEX;
typedef struct {
    CODES_LEX Code;
    char NOM[20];
}OUTPUT;
typedef enum{
    ERR_CAR_INC, ERR_FICH_VID, ERR_ID_LONG,PROGRAM_ERR,ID_ERR,PV_ERR,PT_ERR
}CODES_ERREURS;
typedef struct { CODES_ERREURS CODE_ERR; char mes[40]; }Erreurs;
//Variables globales
char CHAR_COUR;
FILE *f;
char REVERSE_ENUM [50][20];


//PROTYPES
char *toLowerCase(char *s);
void LireChar();
OUTPUT* LireMot();
OUTPUT* LireNum();
OUTPUT* Lire_Car();
void passer();
OUTPUT* analyseurLexical();
void Erreur(CODES_ERREURS ERR);
#endif