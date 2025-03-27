#include <stdio.h>

// Função recursiva para calcular a soma dos dígitos de um número
int somaDigitos(int num) {
    if (num < 0) num = -num; // Garantir que o número seja positivo
    if (num == 0) {
        return 0;
    }
    return (num % 10) + somaDigitos(num / 10);
}

int main() {
    int numero;
    while (scanf("%d", &numero) == 1) {
        printf("%d\n", somaDigitos(numero));
    }
    return 0;
}
