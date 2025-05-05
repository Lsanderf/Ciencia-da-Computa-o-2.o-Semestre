import java.util.Scanner;

public class Exercicio9 {
    public static boolean saoAnagramas(String str1, String str2) {
        if (str1.length() != str2.length()) {
            return false;
        }

        // Convertendo para array de caracteres e ordenando manualmente
        char[] arr1 = str1.toCharArray();
        char[] arr2 = str2.toCharArray();

        ordenar(arr1);
        ordenar(arr2);

        // Comparando os arrays ordenados manualmente
        for (int i = 0; i < arr1.length; i++) {
            if (arr1[i] != arr2[i]) {
                return false;
            }
        }

        return true;
    }

    // Implementação do Bubble Sort para ordenar o array manualmente
    public static void ordenar(char[] arr) {
        int n = arr.length;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    char temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextLine()) {
            String linha = scanner.nextLine().trim();
            if (linha.equals("FIM")) { // Para a execução ao encontrar "FIM"
                break;
            }

            String[] entrada = linha.split("\\s+"); // Divide por espaços
            if (entrada.length == 2) { // Garante que tem exatamente duas palavras
                System.out.println(saoAnagramas(entrada[0], entrada[1]) ? "SIM" : "NAO");
            }
        }

        scanner.close();
    }
}
