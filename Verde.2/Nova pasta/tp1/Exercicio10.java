import java.util.Scanner;

public class Exercicio10 {
    public static int contarPalavras(String texto) {
        if (texto == null || texto.trim().isEmpty()) {
            return 0;
        }
        
        String[] palavras = texto.trim().split("\\s+"); // Divide a string por espaços
        return palavras.length;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String entrada = scanner.nextLine();

        while (!entrada.equals("FIM")) { // Continua enquanto entrada NÃO for "FIM"
            System.out.println(contarPalavras(entrada));
            entrada = scanner.nextLine(); // Lê a próxima entrada
        }

        scanner.close();
    }
}
