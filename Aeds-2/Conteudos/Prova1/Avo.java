
import java.util.*;

class Avo {

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        int N = 1;
        int K = 1;
        while (N != 0 && K != 0) {
            N = sc.nextInt();
            K = sc.nextInt();
            int[] candidatos = new int[100];
            int[] segundos = new int[50];
            int id = 0;

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < K; j++) {
                    candidatos[id] = sc.nextInt();
                    id++;
                }
            }

            for (int i = 0; i < N - 1; i++) {
                for (int j = 0; j < N - i - 1; j++) {
                    if (candidatos[j] > candidatos[j + 1]) {
                        int temp = candidatos[j + 1];
                        candidatos[j + 1] = candidatos[j];
                        candidatos[j] = temp;

                    }
                }
            }
            segundos[0] = candidatos[(N * K) - 2];
        }
        for (int i = 1; i <= N; i++) {
            if (candidatos[i] == segundos[0]) {
                segundos[i] = candidatos[i];
            }
        }

        sc.close();
    }
}
