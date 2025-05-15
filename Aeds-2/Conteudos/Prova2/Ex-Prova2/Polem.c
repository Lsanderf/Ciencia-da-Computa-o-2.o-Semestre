#include <stdio.h>
#define MAX 1000

int achaMaior(int I[], int tam){
    int maior = 0;
    for(int i = 0; i < tam; i++){
    if(I[maior] < I[i]){
    maior = i;
    }
}
return maior;
}

int achaQnt(int I[], int pos){  
    int soma = 0;
    int digito = I[pos];
    while(digito > 0){
    soma += digito % 10;
    digito /= 10;
    }
    return soma;
}

int main(){
    int K,N;
    int I[MAX];
    int qnt;
    int maior;

    scanf("%d %d", &N,&K);
    
    for(int i = 0; i < N; i++){
        scanf("%d", &I[i]);
    }

    for(int i = 0; i < K; i++){
        maior = achaMaior(I,N);
        qnt = achaQnt(I,maior);

        I[maior] -= qnt;
    }
    printf("%d", qnt);

}