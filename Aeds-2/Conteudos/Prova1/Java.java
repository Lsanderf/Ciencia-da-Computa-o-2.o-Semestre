
import java.util.*;

class Java {

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        int N;
        int c = 0;
        int r = 0;
        int s = 0;
        int total = 0;

        N = sc.nextInt();
        for (int i = 0; i < N; i++) {
            char A;
            int temp = sc.nextInt();
            total += temp;
            A = sc.next().charAt(0);

            switch (A) {
                case 'C':
                    c += temp;
                    break;

                case 'R':
                    r += temp;
                    break;

                case 'S':
                    s += temp;
            }
        }

        System.out.printf("Total: %d cobaias\n", total);
        System.out.printf("Total de coelhos: %d\n", c);
        System.out.printf("Total de ratos: %d\n", r);
        System.out.printf("Total de sapos: %d\n", s);
        System.out.printf("Percentual de coelhos:  %.2f %%\n", (c * 100.0 / total));
        System.out.printf("Percentual de ratos:  %.2f %% \n", (r * 100.0 / total));
        System.out.printf("Percentual de sapos:  %.2f %%\n", (s * 100.0 / total));
        sc.close();
    }
}
