import java.util.Scanner;

public class Exercicio12 {
    public static boolean senhaValida(String senha) {
        if (senha == null || senha.length() < 8) {
            return false;
        }
        
        boolean temMaiuscula = false;
        boolean temMinuscula = false;
        boolean temNumero = false;
        boolean temEspecial = false;
        
        for (char c : senha.toCharArray()) {
            if (Character.isUpperCase(c)) {
                temMaiuscula = true;
            } else if (Character.isLowerCase(c)) {
                temMinuscula = true;
            } else if (Character.isDigit(c)) {
                temNumero = true;
            } else {
                temEspecial = true;
            }
        }
        
        return temMaiuscula && temMinuscula && temNumero && temEspecial;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String senha = scanner.nextLine().trim();

        while (!senha.equals("FIM")) { // Continua enquanto senha NÃO for "FIM"
            if (!senha.isEmpty()) { // Evita processar linhas vazias
                System.out.println(senhaValida(senha) ? "SIM" : "NAO");
            }
            senha = scanner.nextLine().trim(); // Lê a próxima entrada
        }

        scanner.close();
    }
}
