#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 1000

int main(){
    int N;
    int K;  
    int id; 
    bool fim = false;
    int qnt;
   while(!fim && (scanf("%d %d",&N,&K) == 2) && K != 0 && N != 0){
        
        if(K == 0 || N == 0){
            fim = true;
        }else{
            qnt = 0;
            int freq[MAX+ 1] = {0};
            for(int i = 0; i < N; i++){
                scanf("%d",&id);
                freq[id]++;
            }

            for(int j = 0; j <= MAX ; j++){
                if(freq[j] >= K){
                    qnt++;
                }
            }
            printf("%d\n", qnt);
            for(int i = 0; i <= MAX; i++){
                freq[i] = 0;
            }
        }
   
          
    }
}