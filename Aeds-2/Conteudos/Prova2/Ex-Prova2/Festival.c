#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int achaMaior(int S[], int N){
    int maior = 0;
    for(int i = 0;i < N; i++){
        if(S[maior] < S[i]){
            maior = i;
        }
}

return maior;
}

int achaPares(int maior){
    int digito;
    int pares = 0;
    while(maior > 0){
        digito = maior % 10;
        if(digito % 2 == 0){
            pares++;
        }
        maior /= 10; 
    }
return pares;
    }

int main(){
    int N,K;
    scanf("%d %d", &N, &K);
    int S[MAX];
    int pares = 0;
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }
    for(int i = 0; i < K; i++){
        int maior = achaMaior(S, N);
        pares = achaPares(S[maior]);
        S[maior] -= pares;  
    
    }
    printf("%d", pares);


    

}