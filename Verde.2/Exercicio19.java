import java.util.Scanner;

public class Exercicio19 {
  private static String substituiValores(int[] portas, String texto) {
    String novoTexto = "";

    for (int i = 0; i < texto.length(); i++) {
      if (texto.charAt(i) != ' ') {
        if (texto.charAt(i) == 'A')
          novoTexto += portas[0];
        else if (texto.charAt(i) == 'B')
          novoTexto += portas[1];
        else if (texto.charAt(i) == 'C')
          novoTexto += portas[2];
        else
          novoTexto += texto.charAt(i);
      }
    }

    return novoTexto;
  }

  private static String not(String texto) {
    String novoTexto = "";

    for (int i = 0; i < texto.length(); i++) {
      if (texto.charAt(i) == 'n' && texto.charAt(i + 2) == 't' &&
          (texto.charAt(i + 4) == '1' || texto.charAt(i + 4) == '0')) {
        novoTexto += texto.charAt(i + 4) == '1' ? 0 : 1;
        i += 5;
      } else
        novoTexto += texto.charAt(i);
    }

    return novoTexto;
  }

  private static String and(String texto) {
    String novoTexto = "";

    for (int i = 0; i < texto.length(); i++) {
      if (texto.charAt(i) == 'a' && texto.charAt(i + 1) == 'n') {
        if (texto.charAt(i + 7) == ')') {
          novoTexto += (texto.charAt(i + 4) == '1' && texto.charAt(i + 6) == '1') ? '1' : '0';
          i += 7;
        }
        else if (texto.charAt(i + 9) == ')') {
          novoTexto += (texto.charAt(i + 4) == '1' && texto.charAt(i + 6) == '1' && texto.charAt(i + 8) == '1') ? '1' : '0';
          i += 9;
        }
        else if (texto.charAt(i + 11) == ')') {
          novoTexto += (texto.charAt(i + 4) == '1' && texto.charAt(i + 6) == '1' && texto.charAt(i + 8) == '1' && texto.charAt(i + 10) == '1') ? '1' : '0';
          i += 11;
        }
        else
          novoTexto += texto.charAt(i);
      } else
        novoTexto += texto.charAt(i);
    }

    return novoTexto;
  }

  private static String or(String texto) {
    String novoTexto = "";

    for (int i = 0; i < texto.length(); i++) {
      if (texto.charAt(i) == 'o' && texto.charAt(i + 1) == 'r') {
        if (texto.charAt(i + 6) == ')') {
          novoTexto += (texto.charAt(i + 3) == '1' || texto.charAt(i + 5) == '1') ? '1' : '0';
          i += 6;
        }
        else if (texto.charAt(i + 8) == ')') {
          novoTexto += (texto.charAt(i + 3) == '1' || texto.charAt(i + 5) == '1' || texto.charAt(i + 7) == '1') ? '1' : '0';
          i += 8;
        }
        else if (texto.charAt(i + 10) == ')') {
          novoTexto += (texto.charAt(i + 3) == '1' || texto.charAt(i + 5) == '1' || texto.charAt(i + 7) == '1' || texto.charAt(i + 9) == '1') ? '1' : '0';
          i += 10;
        }
        else
          novoTexto += texto.charAt(i);
      } else
        novoTexto += texto.charAt(i);
    }

    return novoTexto;
  }

  private static String recBoolAlgebra(String texto, int inicio) {
    String novoTexto = "";
    int tam = texto.length() - 1;

    if (inicio == tam)
      novoTexto = texto;
    else if (texto.charAt(inicio) == 'n')
      novoTexto = not(recBoolAlgebra(texto, inicio + 4));
    else if (texto.charAt(inicio) == 'o')
      novoTexto = or(recBoolAlgebra(texto, inicio + 3));
    else if (texto.charAt(inicio) == 'a')
      novoTexto = and(recBoolAlgebra(texto, inicio + 4));
    else
      novoTexto = recBoolAlgebra(texto, ++inicio);
    return novoTexto;
  }

  private static String boolAlgebra(String texto) {
    return recBoolAlgebra(texto, 0);
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int qtdePortas = scanner.nextInt();
    String texto;
    int[] portas = new int[3];

    while (qtdePortas != 0) {
      for (int i = 0; i < qtdePortas; i++)
        portas[i] = scanner.nextInt();
      texto = scanner.nextLine();

      texto = substituiValores(portas, texto);

      texto = boolAlgebra(texto);

      System.out.println(texto);

      qtdePortas = scanner.nextInt();
    }

    scanner.close();
  }
}