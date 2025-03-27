#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void combina(char str1[], int tam1, int tam2, char str2[]) {
    int i = 0;
    char *maior;
    bool Sao_iguais = false;
    int j = 0;

    if (tam1 > tam2) {
        maior = str1;
    } else if (tam2 > tam1) {
        maior = str2;
    } else {
        Sao_iguais = true;
    }

    while (str1[i] != '\0' && str2[j] != '\0') {
            printf("%c", str1[i]);
            i++;
            printf("%c", str2[j]);
             j++;
         }
         

   
    if (!Sao_iguais) {
        while (maior[i] != '\0') {
            printf("%c", maior[i]);
            i++;
        }
    }
}

int main() {
    char str1[20];
    char str2[20];
    
    
    printf("primeira palavra: \n");
    fgets(str1, sizeof(str1), stdin);
    remove_newline(str1);

    printf("Segunda palavra: \n");
    fgets(str2, sizeof(str2), stdin);
    remove_newline(str2);

    combina(str1, strlen(str1), strlen(str2), str2);
    return 0;
}