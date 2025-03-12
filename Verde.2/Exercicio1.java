import java.util.Scanner;

class Exercicio1 {
    public static boolean palindromo(String x) {
        int esq = 0;
        int dir = x.length() - 1;
        while (esq < dir) {
            if (x.charAt(esq) != x.charAt(dir)) {
                return false;
            }
            esq++;
            dir--;
        }
        return true;
    }

    public static boolean testeFim(String x) {
        return x.equals("FIM");
    }

    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        String texto = scanner.nextLine();
        
        while (!testeFim(texto)) {
            if (palindromo(texto)) {
                System.out.println("SIM");
            } else {
                System.out.println("NAO");
            }
            texto = scanner.nextLine();
        }

        scanner.close();
    }
}
