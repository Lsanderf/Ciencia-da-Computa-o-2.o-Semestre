#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Verificapalindromo(char str[]){
    int inicio = 0;
    int ehpalindromo = 1;
    int fim = strlen(str) - 1;

    while(ehpalindromo == 1 && inicio < fim){
        if(str[inicio]!=str[fim]){
            ehpalindromo = 0;    //verifica se é ou não Palindromo
        }
        inicio++;    
        fim--;

}
    return ehpalindromo;

}
int main(){
    char str[500];
    char teste[] = "FIM";

    while (fgets(str, sizeof(str), stdin) != NULL) {  
        str[strcspn(str, "\n")] = '\0';     //recebe a entrada de dados e chama a função
        if(strcmp(teste, str) != 0){

        if(Verificapalindromo(str) == 1) printf("SIM\n");
        else printf("NAO\n");
    }
   }
  
return 0;
}