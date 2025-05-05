import java.util.HashSet;
import java.util.Scanner;

public class Exercicio11 {
    public static int lengthOfLongestSubstring(String s) {
        if (s == null || s.isEmpty()) {
            return 0; // Corrige caso de entrada vazia
        }

        int maxLength = 0;
        int left = 0;
        HashSet<Character> set = new HashSet<>();

        for (int right = 0; right < s.length(); right++) {
            while (set.contains(s.charAt(right))) {
                set.remove(s.charAt(left));
                left++;
            }
            set.add(s.charAt(right));
            maxLength = Math.max(maxLength, right - left + 1);
        }

        return maxLength;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine().trim(); // Lê a primeira entrada

        while (!input.equals("FIM")) { // Continua enquanto input NÃO for "FIM"
            System.out.println(lengthOfLongestSubstring(input));
            input = scanner.nextLine().trim(); // Lê a próxima entrada
        }

        scanner.close();
    }
}
