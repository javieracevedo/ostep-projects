typedef struct StringArray {
    char **data;
    int length;
} StringArray;

int get_array_length(char **array);

int str_array_push_end(char ***array, char *new_element, size_t *buffer_size);

// void struct_str_array_push(struct StringArray *array, char *new_element, size_t *buffer_size);