import java.util.Scanner;

public class Exercicio7 {
    public static String inverterString(String str) {
        StringBuilder invertida = new StringBuilder();
        for (int i = str.length() - 1; i >= 0; i--) {
            invertida.append(str.charAt(i));
        }
        return invertida.toString();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String entrada = scanner.nextLine(); // Lê a primeira linha antes do loop
        while (!entrada.equals("FIM")) { // Continua até encontrar "FIM"
            System.out.println(inverterString(entrada));
            entrada = scanner.nextLine(); // Lê a próxima linha
        }
        scanner.close();
    }
}
