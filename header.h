typedef struct Lines {
  char *text;
  size_t len;
} Lines;

void *err_malloc(size_t size);
void err_free(void *ptr);
void mod_hosts(FILE *file_ptr, Lines **orig, int no, Lines **block, int nb);
Lines **extract_lines(char *path, int *n, char *stop);
