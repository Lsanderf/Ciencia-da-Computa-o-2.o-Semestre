#include <stdio.h>

// Função para calcular o tamanho da string manualmente
int tamanhoString(char *str) {
    int tamanho = 0;
    while (str[tamanho] != '\0') {
        tamanho++;
    }
    return tamanho;
}

// Função recursiva para inverter a string
void inverterString(char *str, int inicio, int fim) {
    if (inicio >= fim) return;
    char temp = str[inicio];
    str[inicio] = str[fim];
    str[fim] = temp;
    inverterString(str, inicio + 1, fim - 1);
}

// Função recursiva para processar a entrada
void processarEntrada() {
    char entrada[100];

    // Lendo a string com scanf (sem espaços, apenas uma palavra por vez)
    if (scanf("%s", entrada) == EOF) return;

    if (entrada[0] == 'F' && entrada[1] == 'I' && entrada[2] == 'M' && entrada[3] == '\0') {
        return;
    }

    int tamanho = tamanhoString(entrada);
    inverterString(entrada, 0, tamanho - 1);
    printf("%s\n", entrada);
    
    processarEntrada(); // Chamada recursiva
}

int main() {
    processarEntrada();
    return 0;
}
