#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(int argc, char *argv[])
{
    if (argc == 1) {
      printf("Missing block parameter: HostsMod /path/to/block/list\n");
      exit(EXIT_FAILURE);
    }

    int total_b = 0;
    Lines **blocks = extract_lines(argv[argc-1], &total_b, NULL);

    int total_h = 0;
    Lines **hosts = extract_lines("/etc/hosts\0", &total_h, NULL);

    char *path;
    char src[] = "/etc/hosts\0";
    short length = (short)strlen(src);
    path = (char *)err_malloc(length);
    path[length] = '\0';
    strncpy(path, src, length);
    FILE *file_ptr = fopen(path, "w");
    mod_hosts(file_ptr, hosts, total_h, blocks, total_b); 
    fclose(file_ptr);
    err_free(path);
    printf("DONE\n");
    return 0;
}

Lines **extract_lines(char *path, int *n, char *stop)
{
  Lines **list = (Lines**) malloc(0 * sizeof(Lines*));
  FILE *fptr;
  char * line = NULL;
  size_t len = 0;
  size_t read;
  fptr = fopen(path,"rb");
  int nth = 0;
  while ((read = getline(&line, &len, fptr)) != -1)
  {
    if (read - 1 > 0) {
      line[read - 1] = '\0';
      char *ret = strstr(line, "#KAIOS");
      if (ret != NULL)
        break;
      list = (Lines**) realloc(list, (nth + 1) * sizeof(Lines*));
      list[nth] = (Lines*) malloc(sizeof(Lines));
      (*list[nth]).text = (char*) malloc(read * sizeof(char));
      strncpy((*list[nth]).text, line, read - 1);
      (*list[nth]).len = read - 1;
      nth++;
    }
  }
  fclose(fptr);
  if (line)
    free(line);
  *n = nth;
  return list;
}

void *err_malloc(size_t size)
{
  void *ptr = malloc(size);
  if(ptr == NULL)
  {
    perror("Couldn't allocate memory");
    exit(-1);
  }
  return ptr;
}

void err_free(void *ptr)
{
  if(ptr == NULL)
  {
      return;
  }
  free(ptr);
  ptr = NULL;
}

void mod_hosts(FILE *file_ptr, Lines **orig, int no, Lines **block, int nb)
{
  for (int x=0;x<no;x++)
  {
    fwrite(orig[x]->text, sizeof(char), orig[x]->len, file_ptr);
    fwrite("\n", sizeof(char), 1, file_ptr);
    free(orig[x]);
  }
  free(orig);

  char comment[] = "\n#KAIOS\n";
  fwrite(comment, sizeof(char), (short)strlen(comment), file_ptr);
  
  char loopback[] = "0.0.0.0 ";
  short loopback_length = (short)strlen(loopback);
  for (int x=0;x<nb;x++)
  {
    fwrite(loopback, sizeof(char), (int)loopback_length, file_ptr);
    fwrite(block[x]->text, sizeof(char), block[x]->len, file_ptr);
    fwrite("\n", sizeof(char), 1, file_ptr);
    free(block[x]);
  }
  free(block);
}
