/*
 * Simpe code to illustrate Buffer Overflow Attack for security training purpose.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static int secure_logic()
{
    printf("doing secure logic. if you know you might be killed...\n");
    return 0x8888;
}

int handle_data(char * input, int size)
{
    char buf[10];
    
    printf("got data %s\n",input);
    memcpy(buf, input, size);
    //
    // process data in buffer
    //    
    
    return 0;
}

int process_file(const char* filename)
{
    struct stat file_status;
    int ret;
    FILE *datafile;
    char * buf = NULL;

    if (stat(filename, &file_status) < 0) {
	printf("bad file name %s\n", filename);
        return -EBADF;
    }
    
    datafile = fopen(filename, "r");
    if(datafile == NULL) {
	printf("failed to open %s\n", filename);
        return -EACCES;
    }
    buf = malloc(file_status.st_size);
    
    fread(buf, file_status.st_size, 1, datafile);

    ret = handle_data(buf, file_status.st_size);
    free(buf);
        
    fclose(datafile);
    
    return ret;
}

int main(int argc, char **argv)
{
    const char* file_name = "datafile";
    if(argc > 1) {
        file_name = argv[1];
    }
    int ret = process_file(file_name);
    
    return ret;
}

