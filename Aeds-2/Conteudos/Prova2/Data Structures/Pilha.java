
import java.util.Scanner;

public class Pilha {

    private int tam = 50;
    private Pratos[] pratos;
    private int topo;

    public Pilha() {
        pratos = new Pratos[tam];
        topo = 0;
    }

    public void push(String cor, int tamanho, boolean limpo) {
        if (topo < tam) {
            pratos[topo++] = new Pratos(cor, tamanho, limpo);
        } else {
            System.out.println("Pilha cheia!");
        }
    }

    public Pratos pop() {
        if (topo > 0) {
            return pratos[--topo];
        } else {
            System.out.println("Pilha vazía!");
            return null;
        }
    }

    private class Pratos {

        String cor;
        int tamanho;
        boolean limpo;

        public Pratos(String cor, int tamanho, boolean limpo) {
            this.cor = cor;
            this.tamanho = tamanho;
            this.limpo = limpo;
        }

        public void setCor(String cor) {
            this.cor = cor;
        }

        public void setTamanho(int tamanho) {
            this.tamanho = tamanho;
        }

        public void setLimpo(boolean limpo) {
            this.limpo = limpo;
        }

        public String getCor() {
            return cor;
        }

        public int getTamanho() {
            return tamanho;
        }

        public boolean getLimpo() {
            return limpo;
        }

    }

    public static void main(String args[]) {
        int x = -1;
        String cor;
        int tamanho;
        boolean limpo;
        Pilha pilha = new Pilha();

        Scanner sc = new Scanner(System.in);

        while (x != 0) {
            System.out.println("\nEscolha uma opção:");
            System.out.println("1 - Adicionar prato");
            System.out.println("2 - Remover prato");
            System.out.println("0 - Sair");
            x = sc.nextInt();
            switch (x) {
                case 0:
                    System.out.println("Obrigado!");
                    break;

                case 1:
                    System.out.println("Cor:");
                    cor = sc.next();

                    System.out.println("tamanho:");
                    tamanho = sc.nextInt();

                    System.out.println("Ja foi limpo:");
                    limpo = sc.nextBoolean();

                    pilha.push(cor, tamanho, limpo);
                    break;

                case 2:
                    Pratos remover = pilha.pop();
                    if (remover != null) {
                        System.out.println("Prato removido com sucesso!");
                        System.out.println("Cor: " + remover.getCor());
                        System.out.println("Tamanho: " + remover.getTamanho());
                        System.out.println("Limpo: " + remover.getLimpo());
                        break;
                    }
                default:
                    System.out.println("Opção inválida! Tente novamente.");

            }

        }
        sc.close();

    }

}
