
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.*;

public class Show {

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
    private static final String dataFilePath = "/tmp/disneyplus.csv";
    private static final List<String> streamingData = new ArrayList<>();

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
        Show clonedObject = new Show();
        clonedObject.show_id = this.show_id;
        clonedObject.type = this.type;
        clonedObject.title = this.title;
        clonedObject.director = this.director;
        clonedObject.cast = this.cast.clone();
        clonedObject.country = this.country;                          //Método clone, utiliza-se do método clone já existente em java para casos como a varável "cast",
        clonedObject.date_added = this.date_added;                      //que se fosse clonada como as outras varíaveis, retornaria o local da memória qual foi armazenada.
        clonedObject.release_year = this.release_year;
        clonedObject.rating = this.rating;
        clonedObject.duration = this.duration;
        clonedObject.listed_in = this.listed_in.clone();

        return clonedObject;
    }

    public static void leArquivo() {
        try {
            BufferedReader dataReader = new BufferedReader(new FileReader(dataFilePath));
            String currentLine;

            while ((currentLine = dataReader.readLine()) != null) {
                streamingData.add(currentLine);
            }
            dataReader.close();
        } catch (IOException exception) {
            System.err.println("Erro ao carregar o arquivo: " + exception.getMessage());
        }
    }

    public static void ordenar(String[] array) {
        for (int outerIndex = 0; outerIndex < array.length - 1; outerIndex++) {
            for (int innerIndex = outerIndex + 1; innerIndex < array.length; innerIndex++) {
                if (array[outerIndex].compareTo(array[innerIndex]) > 0) {           //Método de ordenação, para posteriormente, ordenar os elementos de "cast" e "listed_in" em ordem alfabética
                    String tempValue = array[outerIndex];
                    array[outerIndex] = array[innerIndex];
                    array[innerIndex] = tempValue;
                }
            }
        }
    }

    public void ler(String linha) {
        List<String> fieldsList = new ArrayList<>();

        boolean inQuotes = false;
        StringBuilder currentField = new StringBuilder();

        for (int charIndex = 0; charIndex < linha.length(); charIndex++) {
            char currentChar = linha.charAt(charIndex);

            if (currentChar == '"') {
                inQuotes = !inQuotes;
            } else if (currentChar == ',' && !inQuotes) {
                fieldsList.add(currentField.toString());
                currentField.setLength(0);
            } else {
                currentField.append(currentChar);
            }
        }

        fieldsList.add(currentField.toString());

        String[] parsedFields = new String[fieldsList.size()];
        parsedFields = fieldsList.toArray(parsedFields);

        this.show_id = parsedFields[0];
        this.type = parsedFields[1].trim().equalsIgnoreCase("movie") ? "Movie" : "TV Show";
        this.title = parsedFields[2];
        this.director = parsedFields[3];
        this.cast = parsedFields[4].equals("") ? new String[0] : parsedFields[4].split(", ");
        if (this.cast.length > 1) {
            ordenar(this.cast);
        }
        this.country = parsedFields[5];

        try {
            this.date_added = parsedFields[6].equals("") ? null : dateFormat.parse(parsedFields[6]);
        } catch (Exception parseError) {
            this.date_added = null;
        }

        this.release_year = parsedFields[7].equals("") ? 0 : Integer.parseInt(parsedFields[7]);
        this.rating = parsedFields[8];
        this.duration = parsedFields[9];
        this.listed_in = parsedFields[10].equals("") ? new String[0] : parsedFields[10].split(", ");
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
        int resultValue = 0;
        int multiplier = 1;
        for (int idx = entrada.length() - 1; idx > 0; idx--) {
            int digit = entrada.charAt(idx) - '0';
            resultValue += digit * multiplier;
            multiplier *= 10;
        }
        return resultValue;
    }

    public static List<String> getCsvLines() {
        return streamingData;
    }

    public static void main(String[] args) {
        Scanner inputScanner = new Scanner(System.in);
        String userInput = inputScanner.nextLine();
        Show[] showCollection = new Show[302];
        int showCount = 0;

        Show.leArquivo();
        List<String> dataLines = Show.getCsvLines();

        while (!ehFim(userInput)) {
            int lineIndex = converteStr(userInput);
            if (lineIndex >= 0 && lineIndex < dataLines.size()) {
                Show currentShow = new Show();
                currentShow.ler(dataLines.get(lineIndex));
                showCollection[showCount++] = currentShow;
            }

            userInput = inputScanner.nextLine();
        }

        for (int displayIndex = 0; displayIndex < showCount; displayIndex++) {
            showCollection[displayIndex].imprimir();
        }

        inputScanner.close();
    }
}
