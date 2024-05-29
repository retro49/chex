#include <stdio.h>
#include <stdlib.h>

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

c_stream* c_open(i8*);
void c_close(c_stream*);



#endif

