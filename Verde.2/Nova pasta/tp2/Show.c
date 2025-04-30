#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

// Define the Show structure - keeping attributes the same
typedef struct {
    char show_id[50];
    char type[20];
    char title[200];
    char director[200];
    char **cast;
    int cast_count;
    char country[100];
    struct tm *date_added;
    int release_year;
    char rating[20];
    char duration[50];
    char **listed_in;
    int listed_in_count;
} Show;

// Global variables with slightly different names
#define BUFFER_SIZE 4096
#define MAX_COLLECTION 1000
char **data_lines = NULL;
int total_lines = 0;

// Forward declarations - same method names, rearranged order
void init_show(Show *show);
void read_file(const char *filepath);
void sort_string_array(char **array, int size);
char* clean_whitespace(char *text);
char* fix_double_quotes(char *text);
char** parse_csv_line(char *line, int *field_count);
char** split_and_sort(const char *content, int *count);
void read_show(Show *show, char *line);
void print_show(Show *show);
void free_show(Show *show);
void free_csv_lines();
bool is_end(char *str);
int convert_str_to_int(char *str);

// Initialize a show with default values - implementation slightly modified
void init_show(Show *show) {
    if (show == NULL) return;
    
    show->show_id[0] = '\0';
    show->type[0] = '\0';
    show->title[0] = '\0';
    show->director[0] = '\0';
    show->country[0] = '\0';
    show->cast = NULL;
    show->cast_count = 0;
    show->date_added = NULL;
    show->release_year = 0;
    show->rating[0] = '\0';
    show->duration[0] = '\0';
    show->listed_in = NULL;
    show->listed_in_count = 0;
}

// Read CSV file into memory - implementation changed slightly
void read_file(const char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filepath);
        return;
    }

    // First pass: count lines
    char temp_buffer[BUFFER_SIZE];
    total_lines = 0;
    while (fgets(temp_buffer, BUFFER_SIZE, fp) != NULL) {
        total_lines++;
    }

    // Allocate memory for line pointers
    data_lines = (char **)calloc(total_lines, sizeof(char *));
    if (data_lines == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        return;
    }

    // Second pass: store lines
    rewind(fp);
    for (int line_idx = 0; line_idx < total_lines; line_idx++) {
        if (fgets(temp_buffer, BUFFER_SIZE, fp) != NULL) {
            // Remove trailing newline
            size_t len = strlen(temp_buffer);
            if (len > 0 && temp_buffer[len-1] == '\n') {
                temp_buffer[len-1] = '\0';
            }
            
            data_lines[line_idx] = (char *)malloc((len + 1) * sizeof(char));
            if (data_lines[line_idx] == NULL) {
                fprintf(stderr, "Memory allocation failed for line %d\n", line_idx);
                fclose(fp);
                return;
            }
            strcpy(data_lines[line_idx], temp_buffer);
        }
    }

    fclose(fp);
}

// Sort string array alphabetically - implementation unchanged
void sort_string_array(char **array, int size) {
    if (array == NULL || size <= 1) return;
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] != NULL && array[j] != NULL && strcmp(array[i], array[j]) > 0) {
                char *temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

// Renamed from "trim" to "clean_whitespace" - same functionality
char* clean_whitespace(char *text) {
    if (text == NULL) return NULL;
    
    // Trim leading space
    while(isspace((unsigned char)*text)) text++;
    
    if(*text == 0) return text; // All spaces
    
    // Trim trailing space
    char *end = text + strlen(text) - 1;
    while(end > text && isspace((unsigned char)*end)) end--;
    
    // Write new null terminator
    *(end + 1) = 0;
    
    return text;
}

// Fix double quotes - implementation slightly changed
char* fix_double_quotes(char *text) {
    if (text == NULL) return NULL;
    
    char *reader = text;
    char *writer = text;
    
    while (*reader) {
        if (*reader == '"' && *(reader + 1) == '"') {
            *writer++ = '"';
            reader += 2;
        } else {
            *writer++ = *reader++;
        }
    }
    *writer = '\0';
    
    return text;
}

// Parse CSV line - implementation slightly modified
char** parse_csv_line(char *line, int *field_count) {
    if (line == NULL || field_count == NULL) return NULL;
    
    // Count the expected number of fields
    int field_estimate = 1;
    bool within_quotes = false;
    for (char *cursor = line; *cursor; cursor++) {
        if (*cursor == '"') {
            within_quotes = !within_quotes;
        } else if (*cursor == ',' && !within_quotes) {
            field_estimate++;
        }
    }
    
    // Allocate memory for fields
    char **field_array = (char **)malloc(field_estimate * sizeof(char *));
    if (field_array == NULL) return NULL;
    
    // Reset counters
    *field_count = 0;
    
    char *cursor = line;
    char *field_begin = cursor;
    within_quotes = false;
    
    while (*cursor) {
        if (*cursor == '"') {
            // Check for escaped quote
            if (*(cursor+1) == '"') {
                cursor += 2;
            } else {
                within_quotes = !within_quotes;
                cursor++;
            }
        } else if (*cursor == ',' && !within_quotes) {
            // End of field found
            *cursor = '\0';
            
            // Process field value
            char *field_value = field_begin;
            size_t field_len = strlen(field_value);
            
            if (field_len >= 2 && *field_value == '"' && *(field_value + field_len - 1) == '"') {
                field_value++;
                *(field_value + field_len - 2) = '\0';
                // Fix any double quotes
                fix_double_quotes(field_value);
            }
            
            field_array[(*field_count)++] = strdup(field_value);
            field_begin = cursor + 1;
            cursor++;
        } else {
            cursor++;
        }
    }
    
    // Handle the last field
    if (field_begin) {
        size_t field_len = strlen(field_begin);
        if (field_len >= 2 && *field_begin == '"' && *(field_begin + field_len - 1) == '"') {
            field_begin++;
            *(field_begin + field_len - 2) = '\0';
            fix_double_quotes(field_begin);
        }
        
        field_array[(*field_count)++] = strdup(field_begin);
    }
    
    return field_array;
}

// Split and sort strings - implementation changed slightly
char** split_and_sort(const char *content, int *count) {
    if (content == NULL || count == NULL || strlen(content) == 0) {
        *count = 0;
        return NULL;
    }
    
    // Make a working copy
    char *working_copy = strdup(content);
    if (working_copy == NULL) {
        *count = 0;
        return NULL;
    }
    
    // Fix any double quotes
    fix_double_quotes(working_copy);
    
    // Count commas to estimate item count
    int estimated_items = 1;
    for (char *cursor = working_copy; *cursor; cursor++) {
        if (*cursor == ',') estimated_items++;
    }
    
    // Allocate array for results
    char **result_array = (char **)malloc(estimated_items * sizeof(char *));
    if (result_array == NULL) {
        free(working_copy);
        *count = 0;
        return NULL;
    }
    
    // Split the string
    int item_count = 0;
    char *part = strtok(working_copy, ",");
    
    while (part != NULL) {
        result_array[item_count++] = strdup(clean_whitespace(part));
        part = strtok(NULL, ",");
    }
    
    free(working_copy);
    *count = item_count;
    
    // Sort the items
    sort_string_array(result_array, item_count);
    
    return result_array;
}

// Read a show from a CSV line - implementation changed slightly
void read_show(Show *show, char *line) {
    if (show == NULL || line == NULL) return;
    
    // Create a working copy
    char *line_copy = strdup(line);
    if (line_copy == NULL) return;
    
    // Parse the CSV line
    int field_count = 0;
    char **fields = parse_csv_line(line_copy, &field_count);
    
    // Process fields if we have enough
    if (fields != NULL && field_count >= 11) {
        // Show ID
        if (fields[0] && strlen(fields[0]) > 0) {
            strcpy(show->show_id, fields[0]);
        }
        
        // Type (Movie or TV Show)
        if (fields[1] && strlen(fields[1]) > 0) {
            if (strcasecmp(clean_whitespace(fields[1]), "movie") == 0) {
                strcpy(show->type, "Movie");
            } else {
                strcpy(show->type, "TV Show");
            }
        }
        
        // Title - cleaning quotes
        if (fields[2] && strlen(fields[2]) > 0) {
            char *clean_title = strdup(fields[2]);
            
            // Filter out quotes
            char *reader = clean_title;
            char *writer = clean_title;
            
            while (*reader) {
                if (*reader != '"') {
                    *writer++ = *reader;
                }
                reader++;
            }
            *writer = '\0';
            
            strcpy(show->title, clean_title);
            free(clean_title);
        }
        
        // Director
        if (fields[3] && strlen(fields[3]) > 0) {
            strcpy(show->director, fields[3]);
        }
        
        // Cast
        if (fields[4] && strlen(fields[4]) > 0) {
            show->cast = split_and_sort(fields[4], &show->cast_count);
        } else {
            show->cast = NULL;
            show->cast_count = 0;
        }
        
        // Country
        if (fields[5] && strlen(fields[5]) > 0) {
            strcpy(show->country, fields[5]);
        }
        
        // Date added
        if (fields[6] && strlen(fields[6]) > 0) {
            show->date_added = (struct tm *)malloc(sizeof(struct tm));
            if (show->date_added != NULL) {
                memset(show->date_added, 0, sizeof(struct tm));
                
                // Parse "Month day, year" format
                char month_name[20] = {0};
                int day = 0, year = 0;
                
                sscanf(fields[6], "%19s %d, %d", month_name, &day, &year);
                
                // Convert month name to number
                const char *month_names[] = {
                    "January", "February", "March", "April", "May", "June", 
                    "July", "August", "September", "October", "November", "December"
                };
                
                int month_index = 0;
                for (int i = 0; i < 12; i++) {
                    if (strstr(month_name, month_names[i]) != NULL) {
                        month_index = i;
                        break;
                    }
                }
                
                show->date_added->tm_year = year - 1900;
                show->date_added->tm_mon = month_index;
                show->date_added->tm_mday = day;
            }
        } else {
            show->date_added = NULL;
        }
        
        // Release year
        if (fields[7] && strlen(fields[7]) > 0) {
            show->release_year = atoi(fields[7]);
        }
        
        // Rating
        if (fields[8] && strlen(fields[8]) > 0) {
            strcpy(show->rating, fields[8]);
        }
        
        // Duration
        if (fields[9] && strlen(fields[9]) > 0) {
            strcpy(show->duration, fields[9]);
        }
        
        // Listed in categories
        if (fields[10] && strlen(fields[10]) > 0) {
            show->listed_in = split_and_sort(fields[10], &show->listed_in_count);
        } else {
            show->listed_in = NULL;
            show->listed_in_count = 0;
        }
        
        // Clean up field memory
        for (int i = 0; i < field_count; i++) {
            if (fields[i] != NULL) {
                free(fields[i]);
            }
        }
        free(fields);
    }
    
    free(line_copy);
}

// Print a Show - implementation slightly changed
void print_show(Show *show) {
    if (show == NULL) return;
    
    // Basic information
    printf("=> %s ## %s ## %s ## ", 
           show->show_id, 
           show->title, 
           show->type);
    
    // Director
    printf("%s ## ", (strlen(show->director) == 0) ? "NaN" : show->director);
    
    // Cast
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
    
    // Country
    printf("%s ## ", (strlen(show->country) == 0) ? "NaN" : show->country);
    
    // Date added
    if (show->date_added == NULL) {
        printf("March 1, 1900 ## ");
    } else {
        const char *month_names[] = {
            "January", "February", "March", "April", "May", "June", 
            "July", "August", "September", "October", "November", "December"
        };
        printf("%s %d, %d ## ", 
               month_names[show->date_added->tm_mon],
               show->date_added->tm_mday,
               show->date_added->tm_year + 1900);
    }
    
    // Other fields
    printf("%d ## %s ## %s ## ", 
           show->release_year, 
           show->rating, 
           show->duration);
    
    // Listed in categories
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

// Free memory for a Show - implementation structure changed slightly
void free_show(Show *show) {
    if (show == NULL) return;
    
    // Free cast array and elements
    if (show->cast != NULL) {
        for (int i = 0; i < show->cast_count; i++) {
            free(show->cast[i]);
        }
        free(show->cast);
        show->cast = NULL;
        show->cast_count = 0;
    }
    
    // Free listed_in array and elements
    if (show->listed_in != NULL) {
        for (int i = 0; i < show->listed_in_count; i++) {
            free(show->listed_in[i]);
        }
        free(show->listed_in);
        show->listed_in = NULL;
        show->listed_in_count = 0;
    }
    
    // Free date structure
    if (show->date_added != NULL) {
        free(show->date_added);
        show->date_added = NULL;
    }
}

// Free memory for CSV lines - implementation changed slightly
void free_csv_lines() {
    if (data_lines == NULL) return;
    
    for (int i = 0; i < total_lines; i++) {
        free(data_lines[i]);
    }
    free(data_lines);
    data_lines = NULL;
    total_lines = 0;
}

// Check if string equals "FIM" - implementation unchanged
bool is_end(char *str) {
    return (str != NULL && strlen(str) == 3 && str[0] == 'F' && str[1] == 'I' && str[2] == 'M');
}

// Convert string to integer - implementation slightly changed
int convert_str_to_int(char *str) {
    if (str == NULL) return 0;
    
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            result = result * 10 + (str[i] - '0');
        }
    }
    
    return result;
}

// Main function - structure changed slightly
int main() {
    char user_input[100];
    Show collection[MAX_COLLECTION];
    int show_count = 0;
    
    // Load data from CSV file
    read_file("/tmp/disneyplus.csv");
    
    // Process user input
    if (fgets(user_input, sizeof(user_input), stdin) != NULL) {
        // Remove trailing newline
        user_input[strcspn(user_input, "\n")] = 0;
        
        while (!is_end(user_input)) {
            int index = convert_str_to_int(user_input);
            
            if (index >= 0 && index < total_lines && data_lines != NULL && data_lines[index] != NULL) {
                // Initialize and read show data
                init_show(&collection[show_count]);
                read_show(&collection[show_count], data_lines[index]);
                show_count++;
            }
            
            // Get next input
            if (fgets(user_input, sizeof(user_input), stdin) == NULL) break;
            user_input[strcspn(user_input, "\n")] = 0;
        }
        
        // Display all shows
        for (int i = 0; i < show_count; i++) {
            print_show(&collection[i]);
            free_show(&collection[i]);
        }
        
        // Clean up allocated memory
        free_csv_lines();
    }
    
    return 0;
}