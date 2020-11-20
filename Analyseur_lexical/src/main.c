#include "analyseurlex.h"
#include "analyseur_syntaxique.h"
char REVERSE_ENUM [50][20]={"PROGRAM_TOKEN","CONST_TOKEN","VAR_TOKEN","BEGIN_TOKEN","END_TOKEN","IF_TOKEN","THEN_TOKEN","WHILE_TOKEN","DO_TOKEN","READ_TOKEN","WRITE_TOKEN",
"PV_TOKEN","PT_TOKEN","PLUS_TOKEN","MOINS_TOKEN","MULT_TOKEN","DIV_TOKEN","VIR_TOKEN","EQ_TOKEN","AFF_TOKEN","INF_TOKEN","INFEG_TOKEN","SUP_TOKEN","SUPEG_TOKEN","DIFF_TOKEN",
"PO_TOKEN","PF_TOKEN","FIN_TOKEN","ID_TOKEN","NUM_TOKEN","ERREUR_TOKEN"};
int main(){
    setvbuf(stdout, NULL, _IONBF, 0);
    printf(">>> Enter file path : ");
    /*
    char path[100];
    
    scanf("%s",path);
     f= fopen(path,"r");
     */
    f= fopen("./tests/test0.txt","r");
    if(f==NULL){
        printf(">>>File not found!");
        exit(EXIT_FAILURE);
    }
    /*
    while (CHAR_COUR != EOF)
    {
        OUTPUT *out = analyseurLexical();
        printf("Token : %s\n",REVERSE_ENUM[out->Code]);
    }
    */
    PROGRAM();//analyseur_syntaxique.c
    if (Sym_Cour->Code ==FIN_TOKEN) printf("BRAVO: le programme est Correcte");
    else printf ("PAS BRAVO: fin de programme erronée! ");
    
    return 0;
}

