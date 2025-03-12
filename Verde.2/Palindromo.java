
class Palindromo {

    public static boolean Verificapalindromo(String x) {
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
        boolean ehfim = false;
        if (x.length() == 3) {
            if (x.charAt(0) == 'F' && x.charAt(1) == 'I' && x.charAt(2) == 'M') {
                ehfim = true;
            }
        }
        return ehfim;
    }

    public static void main(String args[]) {
        String texto = MyIO.readLine();
        while (!testeFim(texto)) {
            if (Verificapalindromo(texto)) {
                MyIO.println("SIM");
            } else {
                MyIO.println("NAO");
            }
            texto = MyIO.readLine();
        }
    }
}
