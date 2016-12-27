// the static lookup table for registers

#ifndef REG_H
#define REG_H
#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// define _Reg structure

struct _Reg {
	uint8_t number;
	char* Reg;
	char* name;
};

typedef struct _Reg Reg;

const Reg* FindR(const char* const reg);

#endif
