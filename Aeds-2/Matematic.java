
public class Matematic {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Uso correto do compilador: java Matematic <número> <número>");
            return;
        }
        try {
            float numero = Float.parseFloat(args[0]);
            float numeroo = Float.parseFloat(args[1]);

            System.out.println("Número fornecido: " + numero);
            System.out.println("Dobro do número: " + (numero * 2));
            System.out.println("Número do segundo fornecido: " + numeroo);
            System.out.println("Dobro do segundo número: " + (numeroo * 2));

        } catch (NumberFormatException e) {
            System.out.println("Erro: Entrada inválida! Forneça um número válido.");
        }
    }
}
