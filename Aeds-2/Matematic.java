public class Matematic{

    public static void main(String[] args){
        if(args.length != 1){
            System.out.println("Por favor forneça um número.");
            return;
        }
        try {
            float numero = Float.parseFloat(args[0]);
           
            System.out.println("Número fornecido é: " + numero);
            System.out.println("O dobro do número é: " + numero * 2);

        } catch(NumberFormatException e){
            System.out.println("Error!");
        }
    }
}