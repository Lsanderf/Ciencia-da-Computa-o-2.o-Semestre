
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define matricula "872857"
#define MAX_LINES 4096
#define MAX_SHOWS 1000
char **csvLines = NULL;
int total_linhas_csv = 0;

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
char *integerToMonth(int x){
    char *resp = (char *)malloc(25 * sizeof(char));
    
    switch(x){
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
void read_show(Show *show, char *line);
void print_show(Show *show);
bool is_end(char *str);
int convert_str_to_int(char *str);
void free_csv_lines();


char* getTitle(Show *show) {
    return show->title;
}


void leArquivo(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "   Error opening file: %s\n", filename);        
        return;
    }

    char buffer[MAX_LINES];
    total_linhas_csv = 0;

    // Contar número total de linhas (inclusive cabeçalho)
    while (fgets(buffer, MAX_LINES, file) != NULL) {
        total_linhas_csv++;
    }

    // Subtrai 1 para ignorar o cabeçalho
    total_linhas_csv--;

    csvLines = (char **)malloc(total_linhas_csv * sizeof(char *));
    if (csvLines == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return;
    }

    // Volta ao início do arquivo e ignora a primeira linha
    rewind(file);
    fgets(buffer, MAX_LINES, file); // Pula o cabeçalho

    for (int i = 0; i < total_linhas_csv; i++) {
        if (fgets(buffer, MAX_LINES, file) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;  // Remove '\n'

            csvLines[i] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
            if (csvLines[i] == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                fclose(file);
                return;
            }
            strcpy(csvLines[i], buffer);
        }
    }

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
            show->date_added.year + 1900);
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

Show clone(Show show){
    Show clone = show;
    return clone;
}








//Elementos de implementação da busca binária, demandados pela questão 4.

void ordenaPorTitulo(Show *show, int tam) {
    for(int i=0;i<tam - 1;i++) {
        for(int j=0;j<tam - i - 1;j++) {
            if(strcmp((show + j)->title, (show + j + 1)->title) > 0) {
                Show temp = *(show + j);
                *(show + j) = *(show + j + 1);
                *(show + j + 1 ) = temp;
            
            }
        }
    }
}


bool pesquisaBinaria(Show *show, int tam,char *titulo, int *comparacoes) {
    int esq = 0;
    int dir = tam - 1;
    bool encontrado = false;

    while(esq <= dir && !encontrado) {
        
        int meio = (esq + dir) / 2;
        int compara = strcmp(titulo,(show + meio)->title);

        if(compara == 0) {
            (*comparacoes)++;
            encontrado = true;
        }else if(compara > 0) {
            (*comparacoes) += 2;
            esq = meio + 1;
        }else {
            (*comparacoes) += 3;
            dir = meio -1;
        }
    }

    return encontrado;
}




int main() {
   
    
    
    Show *shows = (Show *) calloc(1368,sizeof(Show));

   FILE *arquivo = fopen("/tmp/disneyplus.csv", "r");

    char *linha  = (char *)malloc(1024*sizeof(char));

    while(fgetc(arquivo) != '\n');

for(int i = 0; i < 1368; i++){
    readLine(linha, 1024,arquivo);

    ler((shows + i),linha);

}
free(linha);
fclose(arquivo);


char *entry = (char *)malloc(255 * sizeof(char));
Show *array = (Show *)calloc(1368,sizeof(Show));
int tam_array = 0;

scanf("%s",entry);

while(strcmp(entry,"FIM") != 0){
    int id = atoi((entry + 1));
    *(array + tam_array++) = clone(*(shows + --id));
    scanf("%s",entry);
}

ordenaPorTitulo(array,tam_array);
readLine(entry,255,stdin);

int compara = 0;
clock_t inicio = clock();
while(strcmp(entry,"FIM") != 0){
    bool achado = pesquisaBinaria(array,tam_array,entry, &compara);

    if(achado) {
        printf("SIM\n");
    }else {
        printf("NAO\n");
    }


    readLine(entry,255,stdin);
}
clock_t fim = clock();

double tempo_ms = ((double) (fim - inicio) / CLOCKS_PER_SEC) * 1000;

FILE *info = fopen("./matricula_binaria.txt","w");
fprintf(info,"872850\t%.6lf\t%d",tempo_ms,compara);
fclose(info);

free(array);
free(entry);
for(int i = 0; i < 1368; i++)
    freeShow(shows + i);
free(shows);

return 0;
}
 
  
    
 

        
    
    
    