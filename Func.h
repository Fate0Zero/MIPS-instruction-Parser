// the static lookup table for function part
// to determine the type of R-type instruction

#ifndef FUNC_H
#define FUNC_H
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

// define _Func structure

struct _Func {
	char* function;
	char* mnemonic;
};

typedef struct _Func Func;

const Func* FindF(const char* const code);
char* DtoB(int number);
#endif
