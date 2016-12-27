// the static lookup table for operation code part
// to determine the type of instruction (R-type or I-type)

#ifndef OP_H
#define OP_H
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

// define _Op structure

struct _Op {
	char* code;
	char* mnemonic;
};

typedef struct _Op Op;

const Op* Find(const char* const op);

#endif
