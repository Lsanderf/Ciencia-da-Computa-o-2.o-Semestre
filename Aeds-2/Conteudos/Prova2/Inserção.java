
import java.util.*;

public class Inserção {

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        int[] seq = new int[4];
        seq[0] = 7;
        seq[1] = 2;
        seq[2] = 10;
        seq[3] = 4;

        for (int i = 1; i < 4; i++) {
            int chave = seq[i];
            int j = i - 1;

            while (j >= 0 && seq[j] > chave) {
                seq[j + 1] = seq[j];
                j--;
            }
            seq[j + 1] = chave;
        }

        for (int i = 0; i < 4; i++) {
            System.out.print(seq[i] + " ");   //Vai printar a sequencia de forma crescente
        }
    }
}
