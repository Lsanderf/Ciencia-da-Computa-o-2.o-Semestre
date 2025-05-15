
import java.util.Scanner;

public class JogadoresTP {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String input = sc.nextLine();
        int count = 0;
        Jogadores jogadores[] = new Jogadores[1000];
        boolean fim = false;

        while (!fim) {
            input = sc.nextLine();
            if (input.equals("FIM")) {
                fim = true;
            } else {
                jogadores[count] = new Jogadores();
                jogadores[count].ler(input);
                count++;

            }
        }
        for (int i = 1; i < count; i++) {
            Jogadores atual = jogadores[i];
            int j = i - 1;
            while (j >= 0 && jogadores[j].id > atual.id) {
                jogadores[j + 1] = jogadores[j];
                j--;
            }
            jogadores[j + 1] = atual;
        }

    }
}

class Date {

    String dia;

    String mes;

    String ano;

}

class Jogadores {

    public String nome;
    public String foto;
    public Date nascimento;
    public int id;
    public int[] times;

    public void imprimir() {
        System.out.print(this.id + " " + this.nome + " " + this.nascimento.dia + "/" + this.nascimento.mes + "/" + this.nascimento.ano + " " + this.foto + " (");
        for (int i = 0; i < times.length - 1; i++) {
            System.out.print(times[i] + ", ");
        }
        System.out.println(times[times.length - 1] + ")");
    }

    public void ler(String input) {
        int i = 0;

        // Ignorar o primeiro campo vazio
        String index = separar(input, i, ',');
        i += index.length() + 1;

        this.nome = separar(input, i, ',');
        i += nome.length() + 1;

        this.foto = separar(input, i, ',');
        i += foto.length() + 1;

        this.nascimento = new Date();
        this.nascimento.dia = separar(input, i, '/');
        i += nascimento.dia.length() + 1;

        this.nascimento.mes = separar(input, i, '/');
        i += nascimento.mes.length() + 1;

        this.nascimento.ano = separar(input, i, ',');
        i += nascimento.ano.length() + 1;

        // Pula campo vazio antes do ID
        index = separar(input, i, ',');
        i += index.length() + 1;

        String idString = separar(input, i, ',');
        this.id = Integer.parseInt(idString);
        i += idString.length() + 1;

        // Pega os times
        int n = contarTimes(input, i);

        // Se estiver entre aspas
        if (input.charAt(i) == '"') {
            i += 2;
        } else {
            i++;
        }

        this.times = new int[n];
        for (int j = 0; j < n - 1; j++) {
            String timeString = separar(input, i, ',');
            this.times[j] = Integer.parseInt(timeString);
            i += timeString.length() + 2; // pula vírgula e espaço
        }

        String timeString = separar(input, i, ']');
        this.times[n - 1] = Integer.parseInt(timeString);
    }

    public String separar(String input, int i, char delimiter) {
        String resultado = "";
        while (i < input.length() && input.charAt(i) != delimiter) {
            resultado += input.charAt(i);
            i++;
        }
        return resultado;
    }

    public int contarTimes(String input, int i) {
        int times = 1;
        while (i < input.length() && input.charAt(i) != ']') {
            if (input.charAt(i) == ',') {
                times++;
            }
            i++;
        }
        return times;
    }
}
