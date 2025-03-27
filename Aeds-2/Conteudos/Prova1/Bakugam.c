#include <stdio.h>
#include <stdbool.h>
#define MAX 50

int main(){
    int R;
    int levi[MAX];
    int mark[MAX];
    int pontuacaoM = 0, pontuacaoL = 0;
    bool achou = false;
    


    while (scanf("%d", &R) == 1 && R != 0){
        pontuacaoM = 0;
        pontuacaoL = 0;
        achou = false;
        for(int i = 0; i < R; i++){
            scanf("%d", &mark[i]);
            pontuacaoM += mark[i];
        }
        for(int i = 0; i < R; i++){
            scanf("%d", &levi[i]);
            pontuacaoL += levi[i];
        }

        for(int i = 0; i < R - 2 && !achou ; i++){
            if(mark[i] == mark[i+1] && mark[i] == mark[i + 2] && levi[i] != levi[i+1] && levi[i] != levi[i+2] && levi[i+1] != levi[i+2]){
                pontuacaoM += 30;
                achou = true;
            }else if(levi[i] == levi[i+1] && levi[i] == levi[i + 2] && mark[i] != mark[i+1] && mark[i] != mark[i+2] && mark[i+1] != mark[i+2]){
                pontuacaoL += 30;
                achou = true;
            }
        }
        if(pontuacaoM > pontuacaoL){
             printf("M\n M = %d\n L = %d", pontuacaoM, pontuacaoL);
        }if(pontuacaoM < pontuacaoL){
            printf("L\n M = %d\n L = %d", pontuacaoM, pontuacaoL);
        }else{
            printf("T\n M = %d\n L = %d", pontuacaoM, pontuacaoL);
        }

    }

}