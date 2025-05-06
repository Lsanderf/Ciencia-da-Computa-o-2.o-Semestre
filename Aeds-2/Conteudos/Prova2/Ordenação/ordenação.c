#include <stdio.h>

int escolha(){
    int escolha;
    printf("Deseja ordenar de qual forma?\n");
    printf("1-Crescente\n2-Decrescente\n");
    scanf("%d", &escolha);
    
return escolha;
}

void ordena(int lista[], int tam){
    int aux;
    for(int j = 0; j < tam - 1; j++){
        for(int i = 0; i < tam - 1; i++){
            if(lista[i+1] < lista[i]){
            aux = lista[i+1];
            lista[i+1] = lista[i];
            lista[i] = aux;
        }
    }
  }
}
void ordenaDC(int numeros[], int tam){
    int aux;

    for (int j = 0; j < tam-1; j++){
        for(int i = 0; i < tam-1; i++){
            if(numeros[i] < numeros[i+1]){
                aux = numeros[i+1];
                numeros[i+1] = numeros[i];
                numeros[i] = aux;
            }
        }
    }
}

int main(){

    int numeros[] = {9, 6, 5, 3, 9, 0, 12 , 32 ,100, 76, 40, 90};
    int tam = sizeof(numeros)/sizeof(numeros[0]);
    int forma = escolha();
    
    if(forma == 1) ordena(numeros, tam);
    else if (forma == 2)ordenaDC(numeros, tam);
    
    for(int i = 0; i < tam; i++){
        printf("%d, ", numeros  [i]);
    }

return 0;
}