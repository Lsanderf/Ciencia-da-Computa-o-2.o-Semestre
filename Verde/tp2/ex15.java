
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.*;

class Show {

    private String show_id;
    String type;
    String title;
    String director;
    String[] cast;
    String country;
    Date date_added;
    int release_year;
    String rating;
    String duration;
    String[] listed_in;

    private static final SimpleDateFormat dateFormat = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH);
    private static final String arquivo = "/tmp/disneyplus.csv";
    private static final List<String> CsvLines = new ArrayList<>();

    public Show() {
        show_id = "Nan";
        type = "Nan";
        title = "Nan";
        director = "Nan";
        country = "Nan";
        cast = null;
        date_added = null;
        release_year = 0;
        rating = "Nan";
        duration = "Nan";
        listed_in = new String[0];

    }

    public String getShowId() {
        return show_id;
    }

    public String getType() {
        return type;
    }

    public String getTitle() {
        return title;
    }

    public String getDirector() {               //Métodos Get's
        return director;
    }

    public String[] getCast() {
        return cast;
    }

    public String getCountry() {
        return country;
    }

    public Date getDateAdded() {
        return date_added;
    }

    public int getReleaseYear() {
        return release_year;
    }

    public String getRating() {
        return rating;
    }

    public String getDuration() {
        return duration;
    }

    public String[] getListedIn() {
        return listed_in;
    }

    public void setShowId(String show_id) {
        this.show_id = show_id;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setDirector(String director) {             //Métodos Set's
        this.director = director;
    }

    public void setCast(String[] cast) {
        this.cast = cast;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public void setDateAdded(Date date_added) {
        this.date_added = date_added;
    }

    public void setReleaseYear(int release_year) {
        this.release_year = release_year;
    }

    public void setRating(String rating) {
        this.rating = rating;
    }

    public void setDuration(String duration) {
        this.duration = duration;
    }

    public void setListedIn(String[] listed_in) {
        this.listed_in = listed_in;
    }

    public Show clone() {
        Show novo = new Show();
        novo.show_id = this.show_id;
        novo.type = this.type;
        novo.title = this.title;
        novo.director = this.director;
        novo.cast = this.cast.clone();
        novo.country = this.country;
        novo.date_added = this.date_added;                          //Método clone, utiliza-se do método clone já existente em java para casos como a varável "cast",
        novo.release_year = this.release_year;                      //que se fosse clonada como as outras varíaveis, retornaria o local da memória qual foi armazenada.
        novo.rating = this.rating;
        novo.duration = this.duration;
        novo.listed_in = this.listed_in.clone();

        return novo;
    }

    public static void leArquivo() {
        try {

            BufferedReader br = new BufferedReader(new FileReader(arquivo));
            String linha;

            while ((linha = br.readLine()) != null) {
                CsvLines.add(linha);
            }
            br.close();
        } catch (IOException e) {
            System.err.println("Erro ao carregar o arquivo: " + e.getMessage());
        }
    }

    public static void ordenar(String[] array) {
        for (int i = 0; i < array.length - 1; i++) {
            for (int j = i + 1; j < array.length; j++) {
                if (array[i].compareTo(array[j]) > 0) {               //Método de ordenação, para posteriormente, ordenar os elementos de "cast" e "listed_in" em ordem alfabética
                    String temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }

    public void ler(String linha) {
        List<String> camposList = new ArrayList<>();

        boolean aspas = false;
        StringBuilder atual = new StringBuilder();

        for (int i = 0; i < linha.length(); i++) {
            char c = linha.charAt(i);

            if (c == '"') {
                aspas = !aspas;
            } else if (c == ',' && !aspas) {
                camposList.add(atual.toString());
                atual.setLength(0);
            } else {
                atual.append(c);
            }
        }

        camposList.add(atual.toString());

        String[] campos = new String[camposList.size()];
        campos = camposList.toArray(campos);

        this.show_id = campos[0];
        this.type = campos[1].trim().equalsIgnoreCase("movie") ? "Movie" : "TV Show";
        this.title = campos[2];
        this.director = campos[3];
        this.cast = campos[4].equals("") ? new String[0] : campos[4].split(", ");
        if (this.cast.length > 1) {
            ordenar(this.cast);
        }
        this.country = campos[5];

        try {
            this.date_added = campos[6].equals("") ? null : dateFormat.parse(campos[6]);
        } catch (Exception e) {
            this.date_added = null;
        }

        this.release_year = campos[7].equals("") ? 0 : Integer.parseInt(campos[7]);
        this.rating = campos[8];
        this.duration = campos[9];
        this.listed_in = campos[10].equals("") ? new String[0] : campos[10].split(", ");
        if (this.listed_in.length > 1) {
            ordenar(this.listed_in);
        }

    }

    public void imprimir() {
        System.out.println(
                "=> "
                + this.show_id + " ## "
                + this.title + " ## "
                + this.type + " ## "
                + (this.director.isEmpty() ? "NaN" : this.director) + " ## "
                + (this.cast.length == 0 ? "[NaN]" : Arrays.toString(this.cast)) + " ## "
                + (this.country.isEmpty() ? "NaN" : this.country) + " ## "
                + (this.date_added != null ? new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH).format(this.date_added) : "March 1, 1900") + " ## "
                + this.release_year + " ## "
                + this.rating + " ## "
                + this.duration + " ## "
                + (this.listed_in.length == 0 ? "[NaN]" : Arrays.toString(this.listed_in)) + " ##"
        );
    }

    public static boolean ehFim(String str) {
        return (str.length() == 3 && str.charAt(0) == 'F' && str.charAt(1) == 'I' && str.charAt(2) == 'M');
    }

    public static int converteStr(String entrada) {
        int valor = 0;
        int multiplicador = 1;
        for (int i = entrada.length() - 1; i > 0; i--) {
            int numero = entrada.charAt(i) - '0';
            valor += numero * multiplicador;
            multiplicador *= 10;
        }
        return valor;
    }

    public static List<String> getCsvLines() {
        return CsvLines;
    }

}

public class ex15 {

    private static final String matricula = "872850";

    public static int ordenaPorSelecaoParcial(Show[] shows, int tam, int[] movements) {
        int comparacoes = 0;
        for (int i = 0; i < 10; i++) {
            int minimo = i;                    //Se define um indice que funcionará como o menor elemento do vetor,
            //estabelecido no começo, para determinar as trocas consequentes.
            for (int j = i + 1; j < tam; j++) {
                comparacoes++;
                if (shows[j].getTitle().compareToIgnoreCase(shows[minimo].getTitle()) < 0) {
                    minimo = j;                      //Após percorrer o vetor e determinar o menor elemento,
                    //realiza a troca do mesmo com o índice inicial.
                }

            }

            if (minimo != i) {
                movements[0]++;
                Show temp = shows[i];
                shows[i] = shows[minimo];
                shows[minimo] = temp;
            }

        }

        return comparacoes;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String entrada = sc.nextLine();
        Show[] shows = new Show[302];
        int contador = 0;

        Show.leArquivo();
        List<String> linhas = Show.getCsvLines();

        while (!Show.ehFim(entrada)) {
            int index = Show.converteStr(entrada);
            if (index >= 0 && index < linhas.size()) {
                Show s = new Show();
                s.ler(linhas.get(index));
                shows[contador++] = s;
            }

            entrada = sc.nextLine();
        }

        int comparacoes = 0;
        int[] movimentos = new int[1];

        long inicioTimer = System.nanoTime();
        comparacoes = ordenaPorSelecaoParcial(shows, contador, movimentos);

        long fimTimer = System.nanoTime();

        double tempo = (fimTimer - inicioTimer) / 10e6;

        for (int i = 0; i < 10; i++) {
            shows[i].imprimir();
        }

        try {
            FileWriter arquivo = new FileWriter("matricula_selecao.txt");
            arquivo.write(matricula + "\t" + comparacoes + "\t" + movimentos[0] + "\t" + tempo);
            arquivo.close();

        } catch (IOException e) {
            System.out.println("Erro" + e.getMessage());

        }

        sc.close();

    }
}
