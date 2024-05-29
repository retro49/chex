// Simple and basic hex viewer program.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#ifndef CHEX
#define CHEX
/// type representation
typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;
typedef unsigned long   u64;

typedef char  i8;
typedef short i16;
typedef int   i32;
typedef long  i64;

/// file representation for opening and closing.
typedef FILE* c_stream;
#define RBIN "rb"

/// hexadecimal types and defs
#define BSIZE 16 
#endif

typedef struct c_opt{
    bool with_ascii;
}opt;

// deal with opening and closing files
c_stream* c_open(i8*);
void c_close(c_stream*);
void c_hex(c_stream*);

// hexadecimal representation utils
void c_show(u8 buff[BSIZE]);


static struct c_opt options;

int main(int argc, char** argv)
{
    if(argc < 2){
        printf("usage: <FILE>\n");
        return 1;
    }
    if(strncmp(argv[1], "-h", 2) == 0 ||
       strncmp(argv[1], "--help", 6) == 0){
        printf("usage: <FILE>\n");
        return 0;
    }

    // reset
    options.with_ascii = false;

    for(size_t i = 0; i < argc; i++){
        if(strncmp("-A", argv[i], 2) == 0)options.with_ascii = true;
        if(strncmp("--ascii", argv[i], 6) == 0)options.with_ascii = true;
    }

    c_stream* file = c_open(argv[argc - 1]);
    if(file == NULL){
        printf("error: unable to open file: %s\n",
                argv[1]);
        return 1;
    }
    c_hex(file);
    c_close(file);

}

void c_hex(c_stream* strm)
{
    if(strm == NULL)return;
    int c;
    u8 buff[BSIZE];
    size_t count = 0;
    while((c = fgetc(*strm)) != EOF){
        if(count == BSIZE){
            c_show(buff);
            count = 0;
            memset(buff, 0, BSIZE * sizeof(u8));
        } else {
            buff[count] = c;
            count += 1;
        }
    }
}

c_stream* c_open(i8* fname)
{
    if(fname == NULL)return NULL;
    c_stream* file = (c_stream*)malloc(sizeof(c_stream));
    if(file == NULL)return NULL;
    *file = fopen(fname, RBIN);
    if(*file == NULL)return NULL;
    return file;
}

void c_close(c_stream* strm)
{
    if(strm == NULL)return;
    if(*strm == NULL)return;
    fclose(*strm);
}

void c_show(u8 buff[BSIZE])
{
    if(buff == NULL)return;
    static u64 row = 0;
    printf("%08lx  ", row);
    for(i8 i = 0; i < BSIZE; i++){
        if(i == BSIZE/2)printf(" ");
        printf("%02X ", buff[i]);
    }
    if(options.with_ascii){

        printf("| ");
        for(i8 i = 0; i < BSIZE; i++){
            if(isalnum(buff[i]) || ispunct(buff[i])){
                printf("%c", buff[i]);
            } else {
                printf(".");
            }
        }
        printf(" |");

    }

    printf("\n");
    row += BSIZE;
}
