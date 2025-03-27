#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


int Soma(int n){
    if( n != 0){
   return (n % 10) + Soma(n/10);
    }
}   

int main(){
    char entrada[30];
    bool naoterminou = true;
    while (scanf("%s", &entrada) == 1){
        
        if(strcmp(entrada, "FIM") == 0) naoterminou = true;
        else{
        int num = atoi(entrada);
        printf("%d\n", Soma(num));
    }
        }
return 0;
}

