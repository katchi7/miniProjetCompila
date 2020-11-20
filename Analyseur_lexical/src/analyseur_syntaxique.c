#include "analyseurlex.h"
#include "analyseur_syntaxique.h"
void Sym_Suiv(){
    Sym_Cour = analyseurLexical();
}
void Test_Symbole(CODES_LEX cl,CODES_ERREURS ERR){
    if(Sym_Cour->Code == cl){
        Sym_Suiv();
    }
    else Erreur(ERR);
}
void BLOCK(){
    
}
void PROGRAM(){
    Sym_Suiv();
    Test_Symbole(PROGRAM_TOKEN,PROGRAM_ERR);
    Test_Symbole(ID_TOKEN,ID_ERR);
    Test_Symbole(PV_TOKEN,PV_ERR);
    BLOCK();
    Test_Symbole(PT_TOKEN,PT_ERR);
}