import java.util.Scanner;

public class Exercicio8 {
    public static int somaDigitos(int num) {
        if (num == 0) {
            return 0;
        }
        return (num % 10) + somaDigitos(num / 10);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextInt()) {
            int numero = scanner.nextInt();
            System.out.println(somaDigitos(numero));
        }
        scanner.close();
    }
}