import java.util.*;

public class Exercicio9 {

    // Método que troca dois caracteres em um vetor
    public static void trocarElementos(char[] array, int indiceMenor, int indiceMaior) {
        char temporario = array[indiceMenor];
        array[indiceMenor] = array[indiceMaior];
        array[indiceMaior] = temporario;
    }

    // Método que organiza os caracteres em ordem alfabética
    public static void ordenarArray(char[] array) {
        for (int i = 0; i < array.length - 1; i++) {
            int menor = i;
            for (int j = i + 1; j < array.length; j++) {
                if (array[menor] > array[j]) {
                    menor = j;
                }
            }
            if (menor != i) {
                trocarElementos(array, menor, i);
            }
        }
    }

    // Método que verifica se dois arrays de caracteres são idênticos
    public static boolean arraysIguais(char[] array1, char[] array2) {
        boolean iguais = true;
        int i = 0;
        while (i < array1.length && iguais) {
            if (array1[i] != array2[i]) {
                iguais = false;
            } else {
                i++;
            }
        }
        return iguais;
    }

    // Método que preenche um array com a string convertendo para minúsculas
    public static void converterParaMinusculo(char[] array, String texto) {
        for (int i = 0; i < texto.length(); i++) {
            char letra = texto.charAt(i);
            if (letra >= 'A' && letra <= 'Z') {
                letra = (char) (letra + 32); // Converte para minúsculo
            }
            array[i] = letra;
        }
    }

    // Método que verifica se duas strings são anagramas
    public static boolean saoAnagramas(String texto1, String texto2) {
        boolean resultado = true;
        if (texto1.length() != texto2.length()) {
            resultado = false;
        } else {
            char[] array1 = new char[texto1.length()];
            char[] array2 = new char[texto2.length()];
            converterParaMinusculo(array1, texto1);
            converterParaMinusculo(array2, texto2);
            ordenarArray(array1);
            ordenarArray(array2);
            resultado = arraysIguais(array1, array2);
        }
        return resultado;
    }

    // Método que verifica se a entrada é "FIM"
    public static boolean entradaFim(String entrada) {
        return "FIM".equals(entrada);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in, "UTF-8");
        String entrada = scanner.nextLine();

        while (!entradaFim(entrada)) {
            String texto1 = "", texto2 = "";
            int i = 0;
            // Lê o primeiro texto até encontrar o espaço
            while (entrada.charAt(i) != ' ') {
                texto1 += entrada.charAt(i);
                i++;
            }
            i += 3; // Pula o " - " e começa a ler o segundo texto
            while (i < entrada.length()) {
                texto2 += entrada.charAt(i);
                i++;
            }

            // Verifica se são anagramas e exibe o resultado
            if (saoAnagramas(texto1, texto2)) {
                System.out.println("SIM");
            } else {
                System.out.println("NAO");
            }

            // Lê a próxima entrada
            entrada = scanner.nextLine();
        }
    }
}
