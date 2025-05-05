import java.util.Scanner;
    public class QuickSort{
   
   
         int part(int[] arr,int right,int left){
            int pivot = arr[right];
            int i;
            i = left - 1;

            for(int j = left; j < right; j++){
                if(arr[j] <= pivot){
                    int temp;
                    i = i + 1;
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;

                    temp = arr[i+1];
                    arr[i+1] = arr[right];
                    arr[right] = temp;
                }
            }
    return i+1;
    }

        void Quick(int[] arr, int inicio, int fim ){
        if(inicio < fim){
            int pivot = part(arr,inicio,fim);
            Quick(arr,inicio,pivot-1);
            Quick(arr,pivot+1,fim);


        }

        


        }
        public static void main(String args[]){
            Scanner sc = new Scanner(System.in);
            int arr[] = {5, 1, 6, 2, 4};
            Quick(arr, 0, 4);
            
        }
}