#include <iostream>

using namespace std;

void busca(int numero[],int resposta,int tam){
    bool achou = false;
    int i = 0;
    while(!achou && i < tam){
        if(numero[i] == resposta){
            achou = true;
        } 
  i++;     
} 
if(achou){ cout << "Numero achado: " << numero[i - 1]<<endl;
                   cout << "Posicao do numero achado: " << i - 1 << endl;
    }else cout<<"numero nao encontrado";
}

int main(){
    int seq[] = {2, 3, 5, 6, 7, 3, 10, 11, 54, 0, 19, 30, 40, 70, 777, 1004};
    int tam = sizeof(seq)/sizeof(seq[0]);
    int escolha;
    printf("Qual numero deseja buscar: \n");
    scanf("%d", &escolha);

    busca(seq, escolha, tam); 
}