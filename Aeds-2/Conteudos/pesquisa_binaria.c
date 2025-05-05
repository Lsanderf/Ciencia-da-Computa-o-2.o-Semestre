#include <stdio.h>
#include <stdbool.h>

void busca(int seq[], int resposta, int tam){
    int inicio = 0;
    int fim = tam - 1;
    int meio; 
    bool achou = false;
    int contador= 1;

    while(fim >= inicio && !achou){
        meio = (inicio + fim) / 2;
        if(seq[meio] == resposta){
            achou = true;
        }else if(seq[meio] < resposta){
            inicio = meio + 1;
        }else if(seq[meio] > resposta){
            fim = meio - 1;
        }   
    contador++;
    }
    if(achou){
    printf("Numero escolhido: %d\n", resposta);
    printf("Numero achado: %d\n", seq[meio]);
    printf("Posicao do numero achado: %d\n", meio);
    printf("Quantidade de vezes que o arranjo foi dividido: %d\n", contador);
    }
 else {
    printf("Numero %d nao encontrado.\n", resposta);
}

}




int main(){

    int seq[] = {0,1,2,3,5,6,9,12,32,40,60,90,100};
    int tam = sizeof(seq)/sizeof(seq[0]);
    int numero;
    printf("Qual numero deseja buscar: \n");
    scanf("%d", &numero);

    busca(seq, numero, tam); 
return 0;
}
