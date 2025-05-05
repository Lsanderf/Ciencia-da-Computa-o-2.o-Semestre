
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.*;

class Show {

    private String showId;
    String tipo;
    String titulo;
    String diretor;
    String[] elenco;
    String pais;
    Date dataAdicionada;
    int anoLancamento;
    String classificacao;
    String duracao;
    String[] categorias;

    private static final SimpleDateFormat dateFormat = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH);
    private static final String caminhoArquivo = "/tmp/disneyplus.csv";
    private static final List<String> linhasCsv = new ArrayList<>();

    public Show() {
        showId = "Nan";
        tipo = "Nan";
        titulo = "Nan";
        diretor = "Nan";
        pais = "Nan";
        elenco = null;
        dataAdicionada = null;
        anoLancamento = 0;
        classificacao = "Nan";
        duracao = "Nan";
        categorias = new String[0];
    }

    public String getShowId() {       //Métodos Get's
        return showId;
    }

    public String getTipo() {
        return tipo;
    }

    public String getTitulo() {
        return titulo;
    }

    public String getDiretor() {
        return diretor;
    }

    public String[] getElenco() {
        return elenco;
    }

    public String getPais() {
        return pais;
    }

    public Date getDataAdicionada() {
        return dataAdicionada;
    }

    public int getAnoLancamento() {
        return anoLancamento;
    }

    public String getClassificacao() {
        return classificacao;
    }

    public String getDuracao() {
        return duracao;
    }

    public String[] getCategorias() {
        return categorias;
    }

    public void setShowId(String showId) {       //Métodos Set's
        this.showId = showId;
    }

    public void setTipo(String tipo) {
        this.tipo = tipo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public void setDiretor(String diretor) {
        this.diretor = diretor;
    }

    public void setElenco(String[] elenco) {
        this.elenco = elenco;
    }

    public void setPais(String pais) {
        this.pais = pais;
    }

    public void setDataAdicionada(Date dataAdicionada) {
        this.dataAdicionada = dataAdicionada;
    }

    public void setAnoLancamento(int anoLancamento) {
        this.anoLancamento = anoLancamento;
    }

    public void setClassificacao(String classificacao) {
        this.classificacao = classificacao;
    }

    public void setDuracao(String duracao) {
        this.duracao = duracao;
    }

    public void setCategorias(String[] categorias) {
        this.categorias = categorias;
    }

    public Show clone() {                               //Método clone, utiliza-se do método clone já existente em java para casos como a varável "cast"
        Show copia = new Show();
        copia.showId = this.showId;
        copia.tipo = this.tipo;
        copia.titulo = this.titulo;
        copia.diretor = this.diretor;
        copia.elenco = this.elenco.clone();
        copia.pais = this.pais;
        copia.dataAdicionada = this.dataAdicionada;
        copia.anoLancamento = this.anoLancamento;
        copia.classificacao = this.classificacao;
        copia.duracao = this.duracao;
        copia.categorias = this.categorias.clone();

        return copia;
    }

    public static void lerArquivo() {
        try {
            BufferedReader leitor = new BufferedReader(new FileReader(caminhoArquivo));
            String linha;

            while ((linha = leitor.readLine()) != null) {
                linhasCsv.add(linha);
            }
            leitor.close();
        } catch (IOException e) {
            System.err.println("Erro ao carregar o arquivo: " + e.getMessage());
        }
    }

    public static void ordenar(String[] array) {
        for (int i = 0; i < array.length - 1; i++) {                //Método de ordenação, para posteriormente, ordenar os elementos de "cast" e "listed_in" em ordem alfabética
            for (int j = i + 1; j < array.length; j++) {
                if (array[i].compareTo(array[j]) > 0) {
                    String temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }

    public void ler(String linha) {
        List<String> camposList = new ArrayList<>();
        boolean entreAspas = false;
        StringBuilder campoAtual = new StringBuilder();

        for (int i = 0; i < linha.length(); i++) {
            char caractere = linha.charAt(i);

            if (caractere == '"') {
                entreAspas = !entreAspas;
            } else if (caractere == ',' && !entreAspas) {
                camposList.add(campoAtual.toString());
                campoAtual.setLength(0);
            } else {
                campoAtual.append(caractere);
            }
        }

        camposList.add(campoAtual.toString());
        String[] campos = camposList.toArray(new String[0]);

        this.showId = campos[0];
        this.tipo = campos[1].trim().equalsIgnoreCase("movie") ? "Movie" : "TV Show";
        this.titulo = campos[2];
        this.diretor = campos[3];
        this.elenco = campos[4].equals("") ? new String[0] : campos[4].split(", ");
        if (this.elenco.length > 1) {
            ordenar(this.elenco);
        }
        this.pais = campos[5];

        try {
            this.dataAdicionada = campos[6].equals("") ? null : dateFormat.parse(campos[6]);
        } catch (Exception e) {
            this.dataAdicionada = null;
        }

        this.anoLancamento = campos[7].equals("") ? 0 : Integer.parseInt(campos[7]);
        this.classificacao = campos[8];
        this.duracao = campos[9];
        this.categorias = campos[10].equals("") ? new String[0] : campos[10].split(", ");
        if (this.categorias.length > 1) {
            ordenar(this.categorias);
        }
    }

    public void imprimir() {
        System.out.println(
                "=> "
                + showId + " ## "
                + titulo + " ## "
                + tipo + " ## "
                + (diretor.isEmpty() ? "NaN" : diretor) + " ## "
                + (elenco.length == 0 ? "[NaN]" : Arrays.toString(elenco)) + " ## "
                + (pais.isEmpty() ? "NaN" : pais) + " ## "
                + (dataAdicionada != null ? new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH).format(dataAdicionada) : "March 1, 1900") + " ## "
                + anoLancamento + " ## "
                + classificacao + " ## "
                + duracao + " ## "
                + (categorias.length == 0 ? "[NaN]" : Arrays.toString(categorias)) + " ##"
        );
    }

    public static boolean ehFim(String str) {
        return str.equals("FIM");
    }

    public static int converteIndice(String entrada) {
        int valor = 0;
        int multiplicador = 1;
        for (int i = entrada.length() - 1; i > 0; i--) {
            int digito = entrada.charAt(i) - '0';
            valor += digito * multiplicador;
            multiplicador *= 10;
        }
        return valor;
    }

    public static List<String> getLinhasCsv() {
        return linhasCsv;
    }
}

public class ex3 {

    public static boolean buscaSequencial(String titulo, Show[] listaShows, int[] contadorComparacoes) {
        boolean encontrado = false;
        contadorComparacoes[0] = 0;

        for (int i = 0; i < listaShows.length && !encontrado; i++) {
            contadorComparacoes[0]++;
            if (listaShows[i].getTitulo().equals(titulo)) {
                encontrado = true;
            }
        }
        return encontrado;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String entrada = scanner.nextLine();
        Show[] listaShows = new Show[300];
        int totalShows = 0;

        Show.lerArquivo();
        List<String> linhas = Show.getLinhasCsv();

        while (!Show.ehFim(entrada)) {
            int indice = Show.converteIndice(entrada);
            if (indice >= 0 && indice < linhas.size()) {
                Show s = new Show();
                s.ler(linhas.get(indice));
                listaShows[totalShows++] = s;
            }
            entrada = scanner.nextLine();
        }

        entrada = scanner.nextLine();
        long inicio = System.nanoTime();
        int[] comparacoes = new int[1];

        while (!Show.ehFim(entrada)) {
            boolean achado = buscaSequencial(entrada, listaShows, comparacoes);
            System.out.println(achado ? "SIM" : "NAO");
            entrada = scanner.nextLine();
        }

        long fim = System.nanoTime();
        double tempoExecucao = (fim - inicio) / 1e6;

        try {
            FileWriter arquivo = new FileWriter("matricula_sequencial.txt");
            arquivo.write("872857" + '\t' + tempoExecucao + '\t' + comparacoes[0]);
            arquivo.close();
        } catch (IOException e) {
            System.out.println("Erro: " + e.getMessage());
        }

        scanner.close();
    }
}
