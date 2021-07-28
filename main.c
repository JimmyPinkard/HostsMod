#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Really just is not windows
int isPosixComplient = 1;

#ifdef WIN32
isPosixComplient = 0;
#elif UNIX
isPosixComplient = 1;
#endif

typedef struct string
{
    char *val;
    int length;
}string;

void *err_malloc(size_t size);
void err_free(void *ptr);
void string_cpy(string *dest, char *src);
void destory_string(string *str);
void mod_hosts();

int main(int argc, char *argv[])
{
    string path = {};
    if(isPosixComplient)
    {
        string_cpy(&path, "/etc/hosts\0");
    }
    else
    {
        string_cpy(&path, "\\Windows\\System32\\Drivers\\etc\\hosts\0");
    }
    FILE *file_ptr = fopen(path.val, "a");
    destory_string(&path);
    mod_hosts(file_ptr); 
    fclose(file_ptr);
    return 0;
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
    if(ptr != NULL)
    {
        return;
    }
    free(ptr);
    ptr = NULL;
}
void string_cpy(string *dest, char *src)
{
    int length = strlen(src);
    dest->length = length;
    dest->val = (char *)err_malloc(length);
    strncpy(dest->val, src, dest->length);
}
void destory_string(string *str)
{
    err_free(str->val);
    str->length = 0;
}
void mod_hosts(FILE *file_ptr)
{
    char comment[] = "\n\n#These sites were blocked from you for a reason, please don't unblock them\n\n\0";
    fwrite(comment, sizeof(char), (short)strlen(comment), file_ptr);
    char loopback[] = "127.0.0.1\t";
    short loopback_length = (short)strlen(loopback);
    const char *sites[] = {"www.pornhub.com", "www.rule34.xxx", "www.xvideos.com", "www.nehentai.net", "www.hanime.tv", "www.xhamster.com", "www.hentaihaven.com", "www.redtube.com", "www.chaturbate.com", "www.livejasmin.com", "www.slutroulette.com", "www.onlyfans.com", "www.8tube.xxx", "www.youjizz.com", "www.hentaihaven.xxx", NULL};
    //We need a part 2 in order to block non wwww versions
    const char *sites2[] = {"pornhub.com", "rule34.xxx", "xvideos.com", "nehentai.net", "hanime.tv", "xhamster.com", "hentaihaven.com", "redtube.com", "chaturbate.com", "livejasmin.com", "slutroulette.com", "onlyfans.com", "8tube.xxx", "youjizz.com", "hentaihaven.xxx", NULL};
    int i = 0;
    while(sites[i] != NULL)
    {
        fwrite(loopback, sizeof(char), (int)loopback_length, file_ptr);
        fwrite(sites[i], sizeof(char), strlen(sites[i]), file_ptr);
        fwrite("\n", sizeof(char), 1, file_ptr);
        fwrite(loopback, sizeof(char), (int)loopback_length, file_ptr);
        fwrite(sites2[i], sizeof(char), strlen(sites2[i]), file_ptr);
        fwrite("\n", sizeof(char), 1, file_ptr);
        ++i;
    }
}
