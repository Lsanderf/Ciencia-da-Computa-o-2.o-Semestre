#include <stdio.h>

int meu_strlen(char texto[]) {
    int i = 0;
    while (texto[i] != '\0') {
        i++;
    }
    return i;
}

int meu_strcmp(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            return 1;
        i++;
    }
    return (s1[i] == '\0' && s2[i] == '\0') ? 0 : 1;
}

int palindromo(char texto[], int i) {
    int tam = meu_strlen(texto);

    if (tam == i)
        return 1;
    else if (texto[i] != texto[tam - 1 - i])
        return 0;
    else
        return palindromo(texto, i + 1);
}

int ehPalindromo(char texto[]) {
    return palindromo(texto, 0);
}

int main() {
    char texto[1000];

    scanf(" %[^\n]", texto);

    while (meu_strcmp(texto, "FIM")) {
        if (ehPalindromo(texto))
            printf("SIM\n");
        else
            printf("NAO\n");

            scanf(" %[^\n]", texto);

    }

    return 0;
}
