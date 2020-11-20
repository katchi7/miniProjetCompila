#include "analyseurlex.h"
#include "analyseur_syntaxique.h"
void Sym_Suiv(){
    Sym_Cour = analyseurLexical();
}
void Test_Symbole(CODES_LEX cl,CODES_ERREURS ERR){
    if(Sym_Cour->Code == cl){
        Sym_Suiv();
    }
    else{
     printf("Expected %s , Got %s",REVERSE_ENUM[cl],REVERSE_ENUM[Sym_Cour->Code]);
     Erreur(ERR);}
}

void Consts();
void Vars();
void Insts();
void Inst();
void Affec();
void IF();
void While();
void Write();
void Read();
void Express();
void Relop();
void Cond();
void Term();
void Fact();

void BLOCK(){
    Consts();
    Vars();
    Insts();
}
void PROGRAM(){
    Sym_Suiv();
    Test_Symbole(PROGRAM_TOKEN,PROGRAM_ERR);
    Test_Symbole(ID_TOKEN,ID_ERR);
    Test_Symbole(PV_TOKEN,PV_ERR);
    BLOCK();
    Test_Symbole(PT_TOKEN,PT_ERR);
}

void Consts(){
    switch (Sym_Cour->Code)
    {
    case CONST_TOKEN:
        Test_Symbole(CONST_TOKEN,CONST_ERR);
        while (Sym_Cour->Code==ID_TOKEN)
        {
            Test_Symbole(ID_TOKEN,ID_ERR);
            Test_Symbole(EQ_TOKEN,EQ_ERR);
            Test_Symbole(NUM_TOKEN,NUM_ERR);
            Test_Symbole(PV_TOKEN,PV_ERR);
            
        }
        break;
    case VAR_TOKEN: break;
    case BEGIN_TOKEN : break;
    default:
        Erreur(CONST_VAR_BEGIN_ERR);
        break;
    }
    
}
void Vars(){
    switch (Sym_Cour->Code)
    {
    case VAR_TOKEN:
        Test_Symbole(VAR_TOKEN,VAR_ERR);
        Test_Symbole(ID_TOKEN,ID_ERR);
        while (Sym_Cour->Code==VIR_TOKEN)
        {
            Test_Symbole(VIR_TOKEN,VIR_ERR);
            Test_Symbole(ID_TOKEN,ID_ERR);
        }
        Test_Symbole(PV_TOKEN,PV_ERR);
        
        break;
    
    case BEGIN_TOKEN: break;
    
    default:
        Erreur(VAR_BEGIN_ERR);
        break;
    }

}

void Insts(){
    Test_Symbole(BEGIN_TOKEN,BEGIN_ERR);
    Inst();
    while (Sym_Cour->Code==PV_TOKEN)
    {
        Sym_Suiv();
        Inst();
    }
    Test_Symbole(END_TOKEN,END_ERR);
}

void Inst(){
    switch (Sym_Cour->Code)
    {
        case BEGIN_TOKEN:
            Insts();
            break;
        case ID_TOKEN: 
            Affec();
            break;
        case IF_TOKEN: 
            IF();
            break;
        case WHILE_TOKEN: 
            While();
            break;
        case WRITE_TOKEN: 
            Write();
            break;
        case READ_TOKEN: 
            Read();
            break;
            case END_TOKEN: break;
    
        default:
            Erreur(INST_ERR);
            break;
    }   
}

void Affec(){
    Test_Symbole(ID_TOKEN,ID_ERR);
    Test_Symbole(AFF_TOKEN,AFF_ERR);
    Express();
}
void IF(){
    Test_Symbole(IF_TOKEN,IF_ERR);
    Cond();
    Test_Symbole(THEN_TOKEN,THEN_ERR);
    Inst();
}
void While(){
    Test_Symbole(WRITE_TOKEN,WHILE_ERR);
    Cond();
    Test_Symbole(DO_TOKEN,DO_ERR);
    Inst();
}
void Write(){
    Test_Symbole(WRITE_TOKEN,WRITE_ERR);
    Test_Symbole(PO_TOKEN,PO_ERR);
    Express();
    while (Sym_Cour->Code==VIR_TOKEN)
    {
        Test_Symbole(VIR_TOKEN,VIR_ERR);
        Express();
    }
    Test_Symbole(PF_TOKEN,PF_ERR);
}

void Read(){
    Test_Symbole(READ_TOKEN,READ_ERR);
    Test_Symbole(PO_TOKEN,PO_ERR);
    Test_Symbole(ID_TOKEN,ID_ERR);
    while (Sym_Cour->Code==VIR_TOKEN)
    {
        Test_Symbole(VIR_TOKEN,VIR_ERR);
        Test_Symbole(ID_TOKEN,ID_ERR);
    }
    Test_Symbole(PF_TOKEN,PF_ERR);
}

void Cond(){
    Express();
    Relop();
    Express();
}

void Relop(){
    if(Sym_Cour->Code!=EQ_TOKEN && Sym_Cour->Code!=DIFF_TOKEN &&
        Sym_Cour->Code!=INF_TOKEN && Sym_Cour->Code!=INFEG_TOKEN &&
        Sym_Cour->Code!=SUP_TOKEN && Sym_Cour->Code!=SUPEG_TOKEN){
            Erreur(RELOP_ERR);
    }
    Sym_Suiv();

}
void Express(){
    Term();
    while (Sym_Cour->Code==PLUS_TOKEN || Sym_Cour->Code==MOINS_TOKEN)
    {
        Sym_Suiv();
        Term();
    }
}
void Term(){
    Fact();
    while (Sym_Cour->Code==MULT_TOKEN || Sym_Cour->Code==DIV_TOKEN)
    {
        Sym_Suiv();
        Fact();
    }
}
void Fact(){
   switch (Sym_Cour->Code)
   {
   case ID_TOKEN:
       Test_Symbole(ID_TOKEN,ID_ERR);
       break;
   case NUM_TOKEN:
       Test_Symbole(NUM_TOKEN,NUM_ERR);
       break;
   case PO_TOKEN:
       Express();
       Test_Symbole(PF_TOKEN,PF_ERR);
       break;
   
   default:
       Erreur(FACT_ERR);
       break;
   }
}