
import java.util.Scanner;

public class Fila {

    private int fim = 0;
    private int MAX = 10;
    private Pessoa pessoas[] = new Pessoa[MAX];

    public class Pessoa {

        String nome;

        Pessoa(String nome) {
            this.nome = nome;
        }

    public void test() {
    
    }
        void setNome(String nome) {
            this.nome = nome;
        }

        String getNome() {
            return nome;
        }
    }

    public void pop() {
        if (fim > 0) {
            Pessoa removida = pessoas[0];
            for (int i = 0; i < fim - 1; i++) {
                pessoas[i] = pessoas[i + 1];
            }
            pessoas[fim - 1] = null;
            fim--;
            System.out.println("Pessoa " + removida.getNome() + " removida com sucesso!");
        } else {
            System.out.println("Fila vazía!");
        }
    }

    public void push(String nome) {
        if (fim < MAX) {
            pessoas[fim] = new Pessoa(nome);
            fim++;
            System.out.println(nome + " Foi inserido(a) com sucesso!");
        } else {
            System.out.println("Fila cheia!");
        }
    }

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        Fila fila = new Fila();
        fila.push("Lucca");
        fila.push("Clarinha");
        fila.push("Pato Donald");
        fila.pop();

        sc.close();
    }

}
