#include "analyseurlex.h"

Erreurs MES_ERR[100]={{ERR_CAR_INC,"Uknown caracter"},{ERR_FICH_VID,"Empty File"},
                    {ERR_ID_LONG,"Long Id"},{PROGRAM_TOKEN,"Expected a Program token"},
                    {ID_ERR,"Expected an Id"},{PV_ERR,"; Expected"},{PT_ERR,". Expected"},{CONST_ERR,"CONST expected"},
                    {EQ_ERR,"Expected ="},{NUM_ERR,"A num expected"},{CONST_VAR_BEGIN_ERR,"Unexpected Token recieved"},
                    {VAR_BEGIN_ERR,"Unexpected Token recieved"},{VAR_ERR,"Expected a var"},{VIR_ERR,", Expected"},
                    {BEGIN_ERR,"Expected Begin token"},{END_ERR,"Expected an End token"},{INST_ERR,"Ecpected Inst token"},
                    {AFF_ERR,"Expected :="},{IF_ERR,"Expected If token"},{THEN_ERR,"Expected Then toke"},{WHILE_ERR,"Expected WHILE token"},
                    {DO_ERR,"Do token expected"},{WRITE_ERR,"Write token expected"},{PO_ERR,"( Expected"},{PF_ERR,") Expected"},
                    {READ_ERR,"Read token expected"},{RELOP_ERR,"got an unexpected token "},{FACT_ERR,"got an unexpected token "}};

char *toLowerCase(char *s){
    for(int i = 0; s[i]; i++){
    s[i] = tolower(s[i]);
}
return s;
}

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
    strcpy(output->NOM,toLowerCase(output->NOM));
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
OUTPUT* Lire_Car(){
    int i=0;
    OUTPUT *output = malloc(sizeof(OUTPUT));
    output->NOM[i] = CHAR_COUR;
    i++;
    switch (CHAR_COUR)
    {
    case ';':
        output->Code = PV_TOKEN;
        break;
        
    case '.':
        output->Code = PT_TOKEN;
        break;
        
    case '+':
        output->Code = PLUS_TOKEN;
        break;
        
    case '-':
        output->Code = MOINS_TOKEN;
        break;
        
    case '*':
        output->Code = MULT_TOKEN;
        break;
        
    case '/':
        output->Code = DIV_TOKEN;
        break;
        
    case ',':
        output->Code = VIR_TOKEN;
        break;
        
    case ':':
        LireChar();
        if(CHAR_COUR=='='){
            output->Code = AFF_TOKEN;
            output->NOM[i]=CHAR_COUR;
            i++;
        }else{
            output->Code = ERREUR_TOKEN;
            output->NOM[i]=CHAR_COUR;
            i++;
        }
        break;
        
    case '<':
        LireChar();
        if(CHAR_COUR=='='){
            output->Code = INFEG_TOKEN;
            output->NOM[i]=CHAR_COUR;
            i++;
            
        }else if(CHAR_COUR=='>'){
            output->Code = DIFF_TOKEN;
            output->NOM[i]=CHAR_COUR;
            i++;

        }else{
            output->Code = INF_TOKEN;

        }

        break;
        
     case '>':
        LireChar();
        if(CHAR_COUR=='='){
            output->Code = SUPEG_TOKEN;
            output->NOM[i]=CHAR_COUR;
            i++;
            
        }else{
            output->Code = INF_TOKEN;
        }
        break;
    
    case '(':
        output->Code = PO_TOKEN;
        break;
        
    case ')':
        output->Code = PF_TOKEN;
        break; 
    case '=':
        output->Code = EQ_TOKEN;
        break; 
    case EOF:
        output->Code = FIN_TOKEN;
        break;    
    default:
        output->Code = ERREUR_TOKEN;
        break;
    }
    output->NOM[i] = '\0';
    return output;
}

//Passer les separateurs et les commentaires
void passer(){
    while(CHAR_COUR==' '||CHAR_COUR=='\t'||CHAR_COUR=='\n'){//Passer les separateurs
            LireChar();
        while(CHAR_COUR=='{'){//Passer les commentaires
            LireChar();
            if(CHAR_COUR=='*'){
                while (CHAR_COUR!='}'&&CHAR_COUR!=EOF)
                {

                    while (CHAR_COUR!='*'&&CHAR_COUR!=EOF) LireChar();
                    LireChar();
                }
            }else{
                fseek(f,-1,SEEK_CUR);
                break;
            }
            LireChar();
        }
    }
    if(CHAR_COUR==EOF){
        Erreur(ERR_FICH_VID);
    }
        
}

OUTPUT* analyseurLexical(){
    OUTPUT *output = NULL;
    while (output==NULL)
    {
        //Separateur
        LireChar();
        passer();
        //MOT
        if((CHAR_COUR>='A' && CHAR_COUR<='Z')||((CHAR_COUR>='a' && CHAR_COUR<='z'))){
            output = LireMot();
        }
        else{
            //Numero
            if(CHAR_COUR>='0' && CHAR_COUR<='9'){
                output = LireNum();
            }else{
                output = Lire_Car();
            }
        }
    }
    return output;

}

void Erreur(CODES_ERREURS ERR){
    int ind_err = ERR;
    printf( "Erreur numéro %d, %s\n", ind_err,MES_ERR[ERR].mes);
    exit(1);
}