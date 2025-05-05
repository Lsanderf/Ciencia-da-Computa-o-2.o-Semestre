import java.util.Scanner;
public class Merge{
    public static void mergeSort(int[] array, int inicio, int fim){
        if(inicio < fim){
           int meio = (inicio + fim) / 2;

           mergeSort(array, inicio, meio);
           mergeSort(array, meio + 1,fim);

           merge(array, inicio, meio, fim);
        }
    }

    public static void merge(int[] array, int inicio, int meio, int fim){
        int n1 = meio - inicio +1;
        int n2 = fim - meio;

        int[] L = new int[n1];
        int[] R = new int[n2];

        for(int i = 0; i <n1; i++) L[i] = array[inicio + i];
        for(int j = 0; j <n2; j++) R[j] = array[meio + 1 + j];

        int i = 0, j = 0, k = inicio;
        while(i < n1 && j < n2){
            if(L[i] <= R[j]){
                array[k] = L[i];
                i++;
               }else{
                array[k] = R[j];
                j++;
            }
            k++;    
           } 
           while(i < n1) array[k++] = L[i++];
           while(j < n2) array[k++] = R[j++];
        
    }
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        int[] numeros = {7, 3, 5, 2};
        
        System.out.print("Antes: ");
        for (int num : numeros) System.out.print(num + " ");
        System.out.println();

        mergeSort(numeros, 0, numeros.length - 1);

        System.out.print("Depois: ");
        for (int num : numeros) System.out.print(num + " ");
    }
}