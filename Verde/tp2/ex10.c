
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define matricula "872857"
#define MAX_LINES 4096
#define MAX_SHOWS 1369
char **csvLines = NULL;
int total_linhas_csv = 0;
int comparacoes = 0;
int movimentacoes = 0;

typedef struct {
    int date;
    int month;
    int year;
} Date;


typedef struct {
    char *show_id;
    char *type;
    char *title;
    char *director;
    char **cast;
    int cast_count;
    char *country;
    Date date_added;
    int release_year;
    char *rating;
    char *duration;
    char **listed_in;
    int listed_in_count;

} Show;


char *itoa(int num){
    char *resp = (char *)malloc(12 * sizeof(char));

    sprintf(resp,"%d",num);

    return resp;
}



int monthToInteger(char *w){
    int resp = 0;

    if(strcmp(w,"January") == 0) resp = 1; 
    if(strcmp(w,"February") == 0) resp = 2; 
    if(strcmp(w,"March") == 0) resp = 3; 
    if(strcmp(w,"April") == 0) resp = 4; 
    if(strcmp(w,"May") == 0) resp = 5; 
    if(strcmp(w,"June") == 0) resp = 6; 
    if(strcmp(w,"July") == 0) resp = 7; 
    if(strcmp(w,"August") == 0) resp = 8; 
    if(strcmp(w,"September") == 0) resp = 9; 
    if(strcmp(w,"October") == 0) resp = 10; 
    if(strcmp(w,"November") == 0) resp = 11; 
    if(strcmp(w,"December") == 0) resp = 12; 

    return resp;
}
char *integerToMonth(int mes){
    char *resp = (char *)malloc(25 * sizeof(char));
    
    switch(mes){
        case 1:
            strcpy(resp,"January");
            break;
        case 2:
            strcpy(resp,"February");
            break;
        case 3:
            strcpy(resp,"March");
            break;
        case 4:
            strcpy(resp,"April");
            break;
        case 5:
            strcpy(resp,"May");
            break;
        case 6:
            strcpy(resp,"June");
            break;
        case 7:
            strcpy(resp,"July");
            break;
        case 8:
            strcpy(resp,"August");
            break;
        case 9:
            strcpy(resp,"September");
            break;
        case 10:
            strcpy(resp,"October");
            break;
        case 11:
            strcpy(resp,"November");
            break;
        case 12:
            strcpy(resp,"December");
            break;
        default:
            printf("ERROR: Mes nao encontrado");
            break;
    }

    return resp;
}


char* dateToString(Date date){
    char *s_date = (char *)calloc(255 , sizeof(char));
    char *month = integerToMonth(date.month);
    char *day = itoa(date.date);
    char *year = itoa(date.year);

    strcat(s_date,month);
    strcat(s_date," ");
    strcat(s_date,day);
    strcat(s_date,", ");
    strcat(s_date,year);

    free(month);
    free(day);
    free(year);

    return s_date;
}


void read_file(const char *filename);
void sort_string_array(char **array, int size);

void print_show(Show *show);
bool is_end(char *str);
int convert_str_to_int(char *str);
void free_csv_lines();


char* getTitle(Show *show) {
    return show->title;
}


void leArquivo(const char *filename, Show *shows) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }
    
    // Pula o cabeçalho
    while(fgetc(file) != '\n');
    
    // Aloca memória para uma linha
    char *line = (char *)malloc(MAX_LINES * sizeof(char));
    if (line == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return;
    }
    
    // Aloca memória para o array de ponteiros
    total_linhas_csv = 0; // Assumimos que você sabe quantas linhas tem, ou
                          // Poderia ser um valor predefinido como 1368 no seu exemplo
    csvLines = (char **)malloc(total_linhas_csv * sizeof(char *));
    if (csvLines == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        free(line);
        fclose(file);
        return;
    }
    
    // Lê cada linha e a armazena
    for (int i = 0; i < total_linhas_csv; i++) {
        if (fgets(line, MAX_LINES, file) != NULL) {
            line[strcspn(line, "\n")] = 0; // Remove '\n'
            
            csvLines[i] = (char *)malloc((strlen(line) + 1) * sizeof(char));
            if (csvLines[i] == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                // Libera a memória já alocada
                for (int j = 0; j < i; j++) {
                    free(csvLines[j]);
                }
                free(csvLines);
                free(line);
                fclose(file);
                return;
            }
            strcpy(csvLines[i], line);
            
            // Alternativamente, você pode usar uma função como 'ler' aqui
            // ler((shows + i), line);
        }
    }
    
    free(line);
    fclose(file);
}


void sort_string_array(char **array, int size) {
    if (array == NULL || size <= 1) return;
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] != NULL && array[j] != NULL && strcmp(array[i], array[j]) > 0) {            //Método de ordenação por bubblesort, a fim de organizar alfabeticamente membros do "cast"
                char *temp = array[i];                                                               //e de "listed in"
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}


char* trim(char *str) {
if (str == NULL) return NULL;
    

    while(isspace((unsigned char)*str)) str++;
    
    if(*str == 0) return str; // All spaces

    char *end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    

    *(end + 1) = 0;
    
    return str;
}

void trim_newline(char *str) {
    if (str == NULL) return;
    
    size_t len = strlen(str);
    while (len > 0 && (str[len-1] == '\n' || str[len-1] == '\r')) {
        str[--len] = '\0';
    }
}



char** split_and_sort(const char *str, int *count) {
    if (str == NULL || count == NULL || strlen(str) == 0) {
        *count = 0;
        return NULL;
    }
    

    char *str_copy = strdup(str);
    if (str_copy == NULL) {
        *count = 0;
        return NULL;
    }
    

    
    

    int max_items = 1;
    for (char *p = str_copy; *p; p++) {
        if (*p == ',') max_items++;
    }
    

    char **items = (char **)malloc(max_items * sizeof(char *));
    if (items == NULL) {
        free(str_copy);
        *count = 0;
        return NULL;
    }
    

    int item_count = 0;
    char *token = strtok(str_copy, ",");
    
    while (token != NULL) {
        items[item_count++] = strdup(trim(token));
        token = strtok(NULL, ",");
    }
    
    free(str_copy);
    *count = item_count;
    

    sort_string_array(items, item_count);
    
    return items;
}

char *copy_string(const char *origem) {
    if (origem == NULL) return NULL;

    int tamanho = strlen(origem);
    char *destino = (char *)malloc((tamanho + 1) * sizeof(char)); // +1 para o '\0'

    if (destino == NULL) {
        printf("Erro ao alocar memória em copy_string.\n");
        exit(1); // Ou trate como preferir
    }

    for (int i = 0; i <= tamanho; i++) {
        destino[i] = origem[i]; // Copia inclusive o '\0'
    }

    return destino;
}

Date CloneDate(Date d) {
    Date novo;
    novo.date = d.date;
    novo.month = d.month;
    novo.year = d.year;

    return novo;
}



Show clone(Show *original) {
    Show novo;
    novo.show_id = copy_string(original->show_id);
    novo.type = copy_string(original->type);
    novo.title = copy_string(original->title);
    novo.director = copy_string(original->director);
    novo.cast_count = original->cast_count;

    novo.cast = (char **)malloc(novo.cast_count * sizeof(char *));
    for (int i = 0; i < novo.cast_count; i++) {
        novo.cast[i] = copy_string(original->cast[i]);
    }

    novo.country = copy_string(original->country);
    novo.date_added = CloneDate(original->date_added);

    novo.release_year = original->release_year;
    novo.rating = copy_string(original->rating);
    novo.duration = copy_string(original->duration);
    novo.listed_in_count = original->listed_in_count;

    novo.listed_in = (char **)malloc(novo.listed_in_count * sizeof(char *));
    for (int i = 0; i < novo.listed_in_count; i++) {
        novo.listed_in[i] = copy_string(original->listed_in[i]);
    }

    return novo;
}



void ler(Show *a, char *line){
    int len = strlen(line);
    char *atributos[11];
    int k = 0;
    int l = 0;
    for(int i = 0; i < 11; i++){
        atributos[i] = (char *)calloc(1024,sizeof(char));
        strcpy(atributos[i],"NaN");
    }
    for(int i = 0; i < len && k < 11; i++){
        if(line[i] != ','){
            if(line[i] == '"'){
                i++;
                while(line[i] != '"'){
                    atributos[k][l++] = line[i++];
                }
            }else{
                atributos[k][l++] = line[i];
            }
        }else{
            atributos[k][l] = '\0';
            l = 0;
            k++;
            while(line[i + 1] == ','){
                atributos[k][l++] = 'N';
                atributos[k][l++] = 'a';
                atributos[k][l++] = 'N';
                atributos[k][l] = '\0';
                i++;
                if(k < 11)
                    k++;
                l = 0;
            }
            
        }
    }


    for(int i = 0; i < 11; i++){
        switch(i){
            case 0:
                {
                    size_t len = strlen(atributos[i]);
                    a->show_id =(char *)malloc((len + 1) * sizeof(char));
                    strcpy(a->show_id,atributos[i]);
                    // printf("\n%s\n",a->show_id);
                    break;
                }
            case 1:
                {
                    size_t len = strlen(atributos[i]);
                    a->type =(char *)malloc((len + 1)* sizeof(char));
                    strcpy(a->type,atributos[i]);
                    break;
                }
            case 2:
                {
                    size_t len = strlen(atributos[i]);
                    a->title =(char *)calloc((len + 1) , sizeof(char));
                    strcpy(a->title,atributos[i]);
                    break;
                }
            case 3:
                {
                    size_t len = strlen(atributos[i]);
                    a->director =(char *)malloc((len + 1) * sizeof(char));
                    strcpy(a->director,atributos[i]);
                    break;
                }
            case 4:
                {
                    // printf("\n%s, %s\n",a->show_id, atributos[i]);
                    // printf("\n%ld\n",strlen(atributos[i]));
                    if(strcmp(atributos[i],"NaN") != 0 || strlen(atributos[i]) != 0){
                        int quantidade = 1;
                        int len = strlen(atributos[i]);

                        for(int j = 0; j < len; j++)
                            if(atributos[i][j] == ',')
                                quantidade++;

                        a->cast_count = quantidade;

                        a->cast = (char **)calloc(quantidade , sizeof(char*));
                        for(int j = 0; j < quantidade;j++){
                            *(a->cast + j) = (char *)calloc(len , sizeof(char));
                        }

                        for(int j = 0,k = 0,l = 0; j < len; j++){
                            if(atributos[i][j] != ','){
                                a->cast[k][l++] = atributos[i][j];
                            }else if(atributos[i][j] == ','){
                                a->cast[k++][l] = '\0';
                                l = 0;
                                if(atributos[i][j + 1] == ' '){
                                    j++;
                                }
                            }
                        }

                        size_t s_len = a->cast_count;
                        for(int j = 0; j < s_len - 1; j++){
                            int menor = j;
                            for(int k = j + 1; k < s_len; k++){
                                if(strcmp(a->cast[k],a->cast[menor]) < 0){
                                    menor = k;
                                }
                            }
                            char *aux = a->cast[j];
                            a->cast[j] = a->cast[menor];
                            a->cast[menor] = aux;
                        }

                    }else{
                        a->cast_count = 0;
                        a->cast = NULL;
                    }

                    break;
                }
            case 5:
                {
                    size_t len = strlen(atributos[i]);
                    a->country =(char *)malloc((len + 1) * sizeof(char));
                    strcpy(a->country,atributos[i]);
                    break;
                }
            case 6:
                {
                    if(strcmp(atributos[i],"NaN") != 0){
                        int len = strlen(atributos[i]);
                        char c_month[len];
                        char c_date[len];
                        char c_year[len];

                        int k;
                        for(int j = 0; j < len; j++){
                            if(atributos[i][j] != ' '){
                                c_month[j] = atributos[i][j];
                            }else{
                                c_month[j] = '\0';
                                k = j + 1;
                                j = len;
                            }
                        }
                        for(int j = k,l = 0; j < len; j++){
                            if(atributos[i][j] != ','){
                                c_date[l++] = atributos[i][j];
                            }else{
                                c_date[l] = '\0';
                                k = j + 2;
                                j = len;
                            }
                        }
                        for(int j = k,l = 0; j < len; j++){
                            c_year[l++] = atributos[i][j];
                            if(j == len - 1)
                                c_year[l] = '\0';
                        }

                        a->date_added.month = monthToInteger(c_month);
                        a->date_added.date = atoi(c_date);
                        a->date_added.year = atoi(c_year);
                    }else{
                        a->date_added.month = 0;
                        a->date_added.date = 0;
                        a->date_added.year = 0;
                    }
                    break;
                }
            case 7:
                a->release_year = atoi(atributos[i]);
                break;
            case 8:
                {
                    size_t len = strlen(atributos[i]);
                    a->rating =(char *)malloc((len + 1) * sizeof(char));
                    strcpy(a->rating,atributos[i]);
                    break;
                }
            case 9:
                {
                    size_t len = strlen(atributos[i]);
                    a->duration =(char *)malloc((len + 1) * sizeof(char));
                    strcpy(a->duration,atributos[i]);
                    break;
                }
            case 10:
                {
                    if(strcmp(atributos[i],"NaN") != 0){
                        int quantidade = 1;
                        int len = strlen(atributos[i]);

                        for(int j = 0; j < len; j++)
                            if(atributos[i][j] == ',')
                                quantidade++;

                        a->listed_in_count = quantidade;

                        a->listed_in = (char **)malloc(quantidade * sizeof(char*));
                        for(int j = 0; j < quantidade;j++){
                            *(a->listed_in + j) = (char *)malloc(len * sizeof(char));
                        }

                        for(int j = 0,k = 0,l = 0; j < len; j++){
                            if(atributos[i][j] != ','){
                                a->listed_in[k][l++] = atributos[i][j];
                            }else if(atributos[i][j] == ','){
                                a->listed_in[k++][l] = '\0';
                                l = 0;
                                if(atributos[i][j + 1] == ' '){
                                    j++;
                                }
                            }
                        }

                    }else{
                        a->listed_in_count = 0;
                        a->listed_in = NULL;
                    }
                    break;
                }
        }
    }

}


void readLine(char *line,int maxsize, FILE *file){
    if (file == NULL) {
        fprintf(stderr, "Erro: ponteiro de arquivo NULL passado para readLine().\n");
        exit(1);
    }

    if (fgets(line, maxsize, file) == NULL) {
        fprintf(stderr, "Erro ao ler linha do arquivo ou fim do arquivo atingido.\n");
        exit(1);
    }
    size_t len = strlen(line);
    if(line[len - 1] == '\n')
        line[len - 1] = '\0';
}




void print_show(Show *show) {
    if (show == NULL) return;
    
    printf("=> %s ## %s ## %s ## ", 
        show->show_id, 
        show->title, 
        show->type);
    

    if (strlen(show->director) == 0) {
        printf("NaN ## ");
    } else {
        printf("%s ## ", show->director);
    }
    

    if (show->cast_count == 0 || show->cast == NULL) {
        printf("[NaN] ## ");
    } else {
        printf("[");
        for (int i = 0; i < show->cast_count; i++) {
            if (show->cast[i] != NULL) {
                printf("%s", show->cast[i]);
                if (i < show->cast_count - 1) printf(", ");
            }
        }
        printf("] ## ");
    }
    

    if (strlen(show->country) == 0) {
        printf("NaN ## ");
    } else {
        printf("%s ## ", show->country);
    }
    

    if (show->date_added.year == 0 && show->date_added.month == 0 && show->date_added.date == 0)  {
        printf("March 1, 1900 ## ");
    } else {
        const char *months[] = {"January", "February", "March", "April", "May", "June", 
                            "July", "August", "September", "October", "November", "December"};
        printf("%s %d, %d ## ", 
            months[show->date_added.month-1],
            show->date_added.date,
            show->date_added.year);
    }
    

    printf("%d ## %s ## %s ## ", 
        show->release_year, 
        show->rating, 
        show->duration);
    

    if (show->listed_in_count == 0 || show->listed_in == NULL) {
        printf("[NaN] ##");
    } else {
        printf("[");
        for (int i = 0; i < show->listed_in_count; i++) {
            if (show->listed_in[i] != NULL) {
                printf("%s", show->listed_in[i]);
                if (i < show->listed_in_count - 1) printf(", ");
            }
        }
        printf("] ##");
    }
    
    printf("\n");
}


void freeShow(Show *i){
    free(i->show_id);
    free(i->type);
    free(i->title);
    free(i->director);
    free(i->country);
    free(i->rating);
    free(i->duration);
    if(i->cast != NULL){
        for(int j = 0; j < i->cast_count; j++){
            free(*(i->cast + j));
        }
        free(i->cast);
    }
    if(i->listed_in != NULL){
        for(int j = 0; j < i->listed_in_count; j++){
            free(*(i->listed_in + j));
        }
        free(i->listed_in);
    }
}


void destruir(Show *show) {
    if (show == NULL) return;
    
    freeShow(show);
    free(show);
}

void free_csv_lines() {
    if (csvLines == NULL) return;
    
    for (int i = 0; i < total_linhas_csv; i++) {
        if (csvLines[i] != NULL) {
            free(csvLines[i]);
        }
    }
    free(csvLines);
    csvLines = NULL;
}


bool ehFim(char *str) {
    return(strcmp(str, "FIM") ==0);
}


int convert_str_to_int(char *str) {
    if (str == NULL || strlen(str) == 0) return 0;
    int value = 0;
    
    for (int i = 0; i < strlen(str); i++) {
        if (isdigit(str[i])) {
            value = value * 10 + (str[i] - '0');
        }
    }
    
    return value;
}




char *ToLower(char *palavra) {
    int tam = strlen(palavra);
    char *lower = (char*)malloc(sizeof(char) *(tam + 1));         //Definição de uma função que converte letras para minúsculas
    int i = 0;                                              //para evitar erros de comparações com os títulos

    for(int i=0;i<tam;i++) {
        if(palavra[i] >= 'A' && palavra[i] <= 'Z') {
            lower[i] = palavra[i] + 32;
        } else {
            lower[i] = palavra[i];
        }
    }

    lower[tam] = '\0';

    return lower;
}

void Swap(Show *shows, int i, int j) {
    Show temp = shows[i];
    shows[i] = shows[j];
    shows[j] = temp;

    movimentacoes++;
}

int comparaDatas(Date atual, Date prox) {
    int resp = 0;

    if(resp == 0 && atual.year != prox.year) {
        resp = (atual.year < prox.year) ? -1 : 1;
    }

    if(resp == 0 && atual.month != prox.month) {
        resp = (atual.month < prox.month) ? - 1 : 1;
    }

    if(resp == 0 && atual.date != prox.date) {
        resp = (atual.date < prox.date) ? -1 : 1;
    }

    return resp; 
}

int comparaShows(Show a, Show b) {
    int resp = 0;

    if(comparaDatas(a.date_added,b.date_added) != 0) {
        resp = comparaDatas(a.date_added,b.date_added);
        comparacoes++;
    } else {

        comparacoes++;

        char *titulo1 = ToLower(a.title);
        char *titulo2 = ToLower(b.title);

        resp = strcmp(titulo1,titulo2);

        free(titulo1);
        free(titulo2);

        
    }

    return resp;
}

    void ordenaQuickSort(Show *shows,int i,int j) {
        int esq = i;
        int dir = j;
        Show pivo = shows[(esq + dir) / 2];

        while(i <= j) {
            while(comparaShows(shows[i],pivo) < 0) {
                i++;
            }

            while(comparaShows(shows[j], pivo) > 0) {
                j--;

            }

            if(i <= j) {
                Swap(shows,i,j);
                i++;
                j--;
            }

        }

        if(esq < j) {
            ordenaQuickSort(shows,esq,j);
        } 

        if(i < dir) {
            ordenaQuickSort(shows,i,dir);
        }
    }

    void quickSort(Show *shows, int tam) {
        ordenaQuickSort(shows,0,tam-1);
    }

    int main() {
        Show * shows = (Show *)calloc(MAX_SHOWS,sizeof(Show));

        FILE *arquivo = fopen("/tmp/disneyplus.csv", "r");

        char *linha = (char *)malloc(1024*sizeof(char));
    while(fgetc(arquivo)!= '\n') ;

    for(int i=0;i<1368;i++) {
        readLine(linha,1024,arquivo);

        ler((shows+ i), linha);
    }

    free(linha);
    fclose(arquivo);

    char *entrada = (char *)malloc(255 * sizeof(char));
    scanf("%s",entrada);

    Show *array = (Show *)calloc(MAX_SHOWS,sizeof(Show));
    int tam = 0;

    while(!ehFim(entrada)) {
        int id = atoi((entrada + 1));
        array[tam++] = clone(&shows[--id]);
        scanf("%s",entrada);
    }



    clock_t  inicio,fim;

    inicio = clock();
    quickSort(array,tam);
    fim = clock();

    double tempo = (double)(fim-inicio) *1000.0/CLOCKS_PER_SEC;

    FILE *log = fopen("matricula_quicksort.txt","w");
    fprintf(log,"%s\t%d\t%d\t%.2f ms\n",matricula,comparacoes,movimentacoes,tempo);

    fclose(log);

    for(int i=0;i<tam;i++) {
        print_show(&array[i]);
    }

    for(int i=0;i<MAX_SHOWS;i++) {
        freeShow(shows + i);
        
    }


    for(int i = 0; i < 1368; i++){
		freeShow(array + i);
	}
	free(shows);

    

    return 0;
    }
           

    

  