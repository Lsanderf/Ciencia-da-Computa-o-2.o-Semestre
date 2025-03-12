import java.util.Scanner;

class Exercicio6 {
    public static boolean vogal(String x) {
        for (int i = 0; i < x.length(); i++) {
            char c = x.charAt(i);
            if (c != 'A' && c != 'a' && c != 'E' && c != 'e' && c != 'I' && c != 'i' &&
                c != 'O' && c != 'o' && c != 'U' && c != 'u') {
                return false;
            }
        }
        return true;
    }

    public static boolean consoante(String x) {
        for (int i = 0; i < x.length(); i++) {
            char c = x.charAt(i);
            if (c == 'A' || c == 'a' || c == 'E' || c == 'e' || c == 'I' || c == 'i' ||
                c == 'O' || c == 'o' || c == 'U' || c == 'u' || c == '1' || c == '2' || 
                c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || 
                c == '9' || c == '0') {
                return false;
            }
        }
        return true;
    }

    public static boolean inteiro(String x) {
        try {
            Integer.parseInt(x);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public static boolean real(String x) {
        String novo = "";
        for (int i = 0; i < x.length(); i++) {
            char c = x.charAt(i);
            if (c == ',') {
                c = '.';
            }
            novo += c;
        }
        try {
            Double.parseDouble(novo);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public static boolean testeFim(String x) {
        return x.length() == 3 && x.equals("FIM");
    }

    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        String texto = scanner.nextLine();

        while (!testeFim(texto)) {
            if (vogal(texto)) {
                System.out.print("SIM ");
            } else {
                System.out.print("NAO ");
            }
            if (consoante(texto)) {
                System.out.print("SIM ");
            } else {
                System.out.print("NAO ");
            }
            if (inteiro(texto)) {
                System.out.print("SIM ");
            } else {
                System.out.print("NAO ");
            }
            if (real(texto)) {
                System.out.println("SIM");
            } else {
                System.out.println("NAO");
            }
            texto = scanner.nextLine();
        }
        scanner.close();
    }
}
