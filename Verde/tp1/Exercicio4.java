import java.util.Random;
import java.util.Scanner;

class Exercicio4 {
    public static String cifraAleatoria(String x, char letra1, char letra2) {
        int tamanho = x.length();
        String resp = "";
        for (int i = 0; i < tamanho; i++) {
            char c = x.charAt(i);
            if (c == letra1) {
                resp += letra2;
            } else {
                resp += c;
            }
        }
        return resp;
    }

    public static boolean testeFim(String x) {
        return x.equals("FIM");
    }

    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        Random gerador = new Random();
        gerador.setSeed(4);

        String texto = scanner.nextLine();

        while (!testeFim(texto)) {
            char letra1 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
            char letra2 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
            String cifra = cifraAleatoria(texto, letra1, letra2);
            System.out.println(cifra);
            texto = scanner.nextLine();
        }

        scanner.close();
    }
}
