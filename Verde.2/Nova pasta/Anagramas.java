
import java.util.Scanner;

public class Anagramas {

    public static boolean saoAnagramas(String palavra1, String palavra2) {
        boolean saoIguais = true;

        if (palavra1.length() != palavra2.length()) {     // Verificação inicial: se os tamanhos forem diferentes, não são anagramas.
            saoIguais = false;
        }

        int[] frequenciaLetras = new int[26];           // Array para contar a ocorrência de cada letra.

        for (int indice = 0; indice < palavra1.length(); indice++) {
            char caractere = palavra1.charAt(indice);
            if (caractere >= 'a' && caractere <= 'z') {          // Incremento na contagem de caracteres da primeira palavra.
                frequenciaLetras[caractere - 'a']++;
            } else if (caractere >= 'A' && caractere <= 'Z') {
                frequenciaLetras[caractere - 'A']++;
            }
        }

        for (int indice = 0; indice < palavra2.length(); indice++) {
            char caractere = palavra2.charAt(indice);
            if (caractere >= 'a' && caractere <= 'z') {
                frequenciaLetras[caractere - 'a']--;            // Decremento na contagem de caracteres da segunda palavra.
            } else if (caractere >= 'A' && caractere <= 'Z') {
                frequenciaLetras[caractere - 'A']--;
            }
        }

        for (int indice = 0; indice < 26; indice++) {
            if (frequenciaLetras[indice] != 0) {
                // Após o processamento, se todas as posições do array forem 0, significa que as palavras têm as mesmas letras
                // com a mesma quantidade de aparições, ou seja, são anagramas.
                saoIguais = false;
            }
        }

        return saoIguais;
    }

    public static boolean chegouAoFim(String texto) {
        return (texto.length() == 3 && texto.charAt(0) == 'F' && texto.charAt(1) == 'I' && texto.charAt(2) == 'M');
    }

    public static void main(String[] args) {
        Scanner leitor = new Scanner(System.in, "UTF-8");
        String linha = leitor.nextLine();

        while (!chegouAoFim(linha)) {
            String palavra1 = "", palavra2 = "";
            int indice = 0;
            while (indice < linha.length() && linha.charAt(indice) != ' ') {
                palavra1 += linha.charAt(indice);
                indice++;
            }

            indice += 3;
            while (indice < linha.length()) {
                palavra2 += linha.charAt(indice);
                indice++;
            }

            if (saoAnagramas(palavra1, palavra2)) {
                System.out.println("SIM");
            } else {
                System.out.println("NÃO");
            }

            linha = leitor.nextLine();
        }

        leitor.close();
    }
}
