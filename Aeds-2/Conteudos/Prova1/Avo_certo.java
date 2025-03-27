import java.util.*;

class Avo_certo {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        while (true) {
            int N = sc.nextInt();
            int K = sc.nextInt();
            
            if (N == 0 && K == 0) break; // Condição de parada

            Map<Integer, Integer> freq = new HashMap<>(); // Mapa para contar ocorrências

            for (int i = 0; i < N * K; i++) {
                int num = sc.nextInt();
                freq.put(num, freq.getOrDefault(num, 0) + 1);
            }

            // Encontrar o maior e segundo maior número de ocorrências
            int maxFreq = 0, secondFreq = 0;
            for (int f : freq.values()) {
                if (f > maxFreq) {
                    secondFreq = maxFreq;
                    maxFreq = f;
                } else if (f > secondFreq && f < maxFreq) {
                    secondFreq = f;
                }
            }

            // Coletar os números que possuem a segunda maior frequência
            List<Integer> segundos = new ArrayList<>();
            for (Map.Entry<Integer, Integer> entry : freq.entrySet()) {
                if (entry.getValue() == secondFreq) {
                    segundos.add(entry.getKey());
                }
            }

            // Ordenar e imprimir o resultado
            Collections.sort(segundos);
            for (int num : segundos) {
                System.out.print(num + " ");
            }
            System.out.println();
        }

        sc.close();
    }
}
