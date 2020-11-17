#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef enum{
    PROGRAM_TOKEN,CONST_TOKEN,VAR_TOKEN,BEGIN_TOKEN,END_TOKEN,IF_TOKEN,THEN_TOKEN,WHILE_TOKEN,DO_TOKEN,READ_TOKEN,WRITE_TOKEN,
    PV_TOKEN,PT_TOKEN,PLUS_TOKEN,MOINS_TOKEN,MULT_TOKEN,DIV_TOKEN,VIR_TOKEN,AFF_TOKEN,INF_TOKEN,INFEG_TOKEN,SUP_TOKEN,SUPEG_TOKEN,
    DIFF_TOKEN,PO_TOKEN,PF_TOKEN,FIN_TOKEN,ID_TOKEN,NUM_TOKEN,ERREUR_TOKEN
}CODES_LEX;
typedef struct {
    CODES_LEX Code;
    char NOM[20];
}OUTPUT;

char CHAR_COUR;
FILE *f;

void LireChar(){
    CHAR_COUR =fgetc(f); 
}


OUTPUT LireMot(){

}


void passer(){
    if(CHAR_COUR==' '||CHAR_COUR=='\t'||CHAR_COUR=='\n'){
            LireChar();
        }
        if(CHAR_COUR=='{'){
            while (CHAR_COUR!='}'&&CHAR_COUR!=EOF)
            {
                LireChar();
            }
        }
        
}

int main(){
    setvbuf(stdout, NULL, _IONBF, 0);
    printf(">>> Enter file path : ");
    
    char path[100];
    
    scanf("%s",path);
     f= fopen(path,"r");
    if(f==NULL){
        printf(">>>File not found!");
        exit(EXIT_FAILURE);
    }
    while (CHAR_COUR!=EOF)
    {
        LireChar();
        
        passer();
        if((CHAR_COUR>='A' && CHAR_COUR<='Z')||((CHAR_COUR>='a' && CHAR_COUR<='z'))){
            OUTPUT Mot = LireMot();
            printf("%c",CHAR_COUR);
        }
                
    }

    
    return 0;
}

