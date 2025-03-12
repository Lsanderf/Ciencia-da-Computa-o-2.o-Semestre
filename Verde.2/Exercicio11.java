import java.util.*;

public class Exercicio11 {

    // Função que verifica se a entrada é "FIM"
    public static boolean ehFim(String entrada) {
        return "FIM".equals(entrada);
    }

    // Função que conta as substrings únicas em um texto
    public static int contarLetrasUnicas(String texto) {
        int contadorUnicas = 0;
        int contadorRepetidas = 0;
        // Vetor para armazenar letras que já foram verificadas
        char[] letrasVerificadas = new char[texto.length()];

        for (int i = 0; i < texto.length(); i++) {
            int j = 0;
            while (j < i) {
                // Se encontrar uma letra repetida, aumenta o contador de repetidas
                if (letrasVerificadas[j] == texto.charAt(i)) {
                    contadorRepetidas++;
                    j = i; // Encerra o loop interno
                } else {
                    j++;
                }
            }
            // Se não houver repetições registradas, adiciona a letra e incrementa o contador
            if (contadorRepetidas == 0) {
                letrasVerificadas[i] = texto.charAt(i);
                contadorUnicas++;
            } else {
                // Se houve repetições, reinicia o contador de repetidas
                contadorRepetidas = 0;
                i = texto.length();
            }
        }
        return contadorUnicas;
    }

    public static void main(String[] args) {
        // Inicializa o scanner para ler entradas
        Scanner scanner = new Scanner(System.in, "UTF-8");
        String entrada = scanner.nextLine();

        while (!ehFim(entrada)) {
            // Chama a função que retorna o número de letras únicas
            System.out.println(contarLetrasUnicas(entrada));
            entrada = scanner.nextLine(); // Lê a próxima entrada
        }
    }
}
