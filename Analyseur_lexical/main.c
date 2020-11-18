#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef enum{
    PROGRAM_TOKEN,CONST_TOKEN,VAR_TOKEN,BEGIN_TOKEN,END_TOKEN,IF_TOKEN,THEN_TOKEN,WHILE_TOKEN,DO_TOKEN,READ_TOKEN,WRITE_TOKEN,
    PV_TOKEN,PT_TOKEN,PLUS_TOKEN,MOINS_TOKEN,MULT_TOKEN,DIV_TOKEN,VIR_TOKEN,EQ_TOKEN,AFF_TOKEN,INF_TOKEN,INFEG_TOKEN,SUP_TOKEN,SUPEG_TOKEN,
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


OUTPUT* LireMot(){
    int i=0;
    OUTPUT *output = malloc(sizeof(OUTPUT));
    while((CHAR_COUR>='A' && CHAR_COUR<='Z')||(CHAR_COUR>='a' && CHAR_COUR<='z')||(CHAR_COUR>='0' && CHAR_COUR<='9')){
        if(i==20){
            output->Code = ERREUR_TOKEN;
            return output;
        }
        output->NOM[i] = CHAR_COUR;
        i++;
        LireChar();
    }
    fseek(f,-1,SEEK_CUR);
    output->NOM[i] = '\0';
    if(strcmp(output->NOM,"program")==0){
        output->Code=PROGRAM_TOKEN;
        return output;
    }if(strcmp(output->NOM,"const")==0){
        output->Code=CONST_TOKEN;
        return output;
    }if(strcmp(output->NOM,"var")==0){
        output->Code=VAR_TOKEN;
        return output;
    }if(strcmp(output->NOM,"begin")==0){
        output->Code=BEGIN_TOKEN;
        return output;
    }if(strcmp(output->NOM,"end")==0){
        output->Code=END_TOKEN;
        return output;
    }if(strcmp(output->NOM,"if")==0){
        output->Code=IF_TOKEN;
        return output;
    }if(strcmp(output->NOM,"then")==0){
        output->Code=THEN_TOKEN;
        return output;
    }if(strcmp(output->NOM,"while")==0){
        output->Code=WHILE_TOKEN;
        return output;
    }if(strcmp(output->NOM,"do")==0){
        output->Code=DO_TOKEN;
        return output;
    }if(strcmp(output->NOM,"write")==0){
        output->Code=WRITE_TOKEN;
        return output;
    }if(strcmp(output->NOM,"read")==0){
        output->Code=READ_TOKEN;
        return output;
    }
    output->Code = ID_TOKEN;
   
    return output;
}
OUTPUT* LireNum(){
    int i=0;
    OUTPUT *output = malloc(sizeof(OUTPUT));
    while((CHAR_COUR>='0' && CHAR_COUR<='9')){
        if(i==12){
            output->Code = ERREUR_TOKEN;
            return output;
        }
        output->NOM[i] = CHAR_COUR;
        i++;
        LireChar();
    }
    fseek(f,-1,SEEK_CUR);
    output->NOM[i] = '\0';
    output->Code = NUM_TOKEN;
    return output;
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

void analyseurSyntaxique(){
    while (CHAR_COUR!=EOF)
    {
        //Separateur
        LireChar();
        passer();
        //MOT
        if((CHAR_COUR>='A' && CHAR_COUR<='Z')||((CHAR_COUR>='a' && CHAR_COUR<='z'))){
            OUTPUT *Mot = LireMot();
            //printf("%d\n",Mot->Code);
            free(Mot);
        }
        else{
            //Numero
            if(CHAR_COUR>='0' && CHAR_COUR<='9'){
                OUTPUT *Num = LireNum();
                printf("%s\n",Num->NOM);
                free(Num);
            }else{
                Lire_Car();
            }
        }

                
    }

}

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
    analyseurSyntaxique();
    
    return 0;
}

