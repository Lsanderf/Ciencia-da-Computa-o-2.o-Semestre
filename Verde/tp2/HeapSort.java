
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

    public String getShowId() { //Métodos Get's
        return show_id;
    }

    public String getType() {
        return type;
    }

    public String getTitle() {
        return title;
    }

    public String getDirector() {
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

    public void setShowId(String show_id) {//Métodos Set's
        this.show_id = show_id;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setDirector(String director) {
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
        novo.date_added = this.date_added;
        novo.release_year = this.release_year;
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
                if (array[i].compareTo(array[j]) > 0) {               //Método de ordenação
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

        this.show_id = campos[0].isEmpty() ? "NaN" : campos[0];
        this.type = campos[1].trim().isEmpty() ? "NaN"
                : campos[1].trim().equalsIgnoreCase("movie") ? "Movie" : "TV Show";
        this.title = campos[2].isEmpty() ? "NaN" : campos[2];
        this.director = campos[3].isEmpty() ? "NaN" : campos[3];

        this.cast = campos[4].isEmpty() ? new String[]{"NaN"} : campos[4].split(", ");
        if (this.cast.length > 1) {
            ordenar(this.cast);
        }

        this.country = campos[5].isEmpty() ? "NaN" : campos[5];

        try {
            this.date_added = campos[6].isEmpty() ? null : dateFormat.parse(campos[6]);
        } catch (Exception e) {
            this.date_added = null;
        }

        this.release_year = campos[7].isEmpty() ? 0 : Integer.parseInt(campos[7]);
        this.rating = campos[8].isEmpty() ? "NaN" : campos[8];
        this.duration = campos[9].isEmpty() ? "NaN" : campos[9];

        this.listed_in = campos[10].isEmpty() ? new String[]{"NaN"} : campos[10].split(", ");
        if (this.listed_in.length > 1) {
            ordenar(this.listed_in);
        }
    }

    public void imprimir() {
        String dateAdded = (getDateAdded() != null)
                ? new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH).format(getDateAdded())
                : "March 1, 1900";

        String[] casts = getCast();
        String castStr = Arrays.toString(casts);

        String[] listedIn = getListedIn();
        String listedInStr = Arrays.toString(listedIn);

        System.out.println("=> " + getShowId() + " ## " + getTitle() + " ## " + getType() + " ## "
                + getDirector() + " ## " + castStr + " ## " + getCountry() + " ## "
                + dateAdded + " ## " + getReleaseYear() + " ## " + getRating() + " ## "
                + getDuration() + " ## " + listedInStr + " ##");
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

public class HeapSort {

    private static final String matricula = "872850";
    static int comparacoes = 0;
    static int movimentacoes = 0;

    public static boolean menorShow(Show a, Show b) {
        boolean vazioA = (a.getDirector() == null || a.getDirector().isEmpty());
        boolean vazioB = (b.getDirector() == null || b.getDirector().isEmpty());

        boolean resultado = false;

        if (vazioA && !vazioB) {
            comparacoes++;
            resultado = false;
        } else if (!vazioA && vazioB) {
            comparacoes++;
            resultado = true;
        } else if (vazioA && vazioB) {
            comparacoes++;
            resultado = a.getTitle().compareToIgnoreCase(b.getTitle()) < 0;
        } else {
            comparacoes++;
            int cmpDiretor = a.getDirector().compareToIgnoreCase(b.getDirector());

            if (cmpDiretor != 0) {
                resultado = cmpDiretor < 0;
            } else {
                comparacoes++;
                resultado = a.getTitle().compareToIgnoreCase(b.getTitle()) < 0;
            }
        }

        return resultado;

    }

    public static void heap(Show[] shows, int tam, int i) {
        int raiz = i;
        int esq = (2 * i) + 1;
        int dir = (2 * i) + 2;

        if (esq < tam && menorShow(shows[raiz], shows[esq])) {
            raiz = esq;

        }

        if (dir < tam && menorShow(shows[raiz], shows[dir])) {
            raiz = dir;
        }

        if (raiz != i) {

            Show temp = shows[i];
            shows[i] = shows[raiz];
            shows[raiz] = temp;

            heap(shows, tam, raiz);
        }
    }

    public static void heapsort(Show[] shows, int tam) {
        for (int i = tam / 2 - 1; i >= 0; i--) {
            heap(shows, tam, i);
        }

        for (int i = tam - 1; i > 0; i--) {
            movimentacoes++;;
            Show temp = shows[0];
            shows[0] = shows[i];
            shows[i] = temp;
            heap(shows, i, 0);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String entrada = sc.nextLine();
        Show[] shows = new Show[1392];
        int tam_shows = 0;

        Show.leArquivo();
        List<String> linhas = Show.getCsvLines();

        while (!Show.ehFim(entrada)) {
            int indice = Show.converteStr(entrada);
            if (indice >= 0 && indice < linhas.size()) {
                Show s = new Show();
                s.ler(linhas.get(indice));
                shows[tam_shows++] = s;
            }
            entrada = sc.nextLine();
        }

        long inicio = System.currentTimeMillis();
        heapsort(shows, tam_shows);
        long fim = System.currentTimeMillis();

        long tempo = (fim - inicio);

        for (int i = 0; i < tam_shows; i++) {
            shows[i].imprimir();
        }

        try {
            FileWriter arquivo = new FileWriter("matricula_heapsort.txt");
            arquivo.write(matricula + '\t' + comparacoes + '\t' + movimentacoes + '\t' + tempo + "ms");
            arquivo.close();

        } catch (IOException e) {
            System.out.println("Error:" + e.getMessage());
        }

        sc.close();

    }

}
