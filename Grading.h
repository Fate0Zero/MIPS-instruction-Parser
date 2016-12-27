#ifndef GRADING_H
#define GRADING_H
#include <inttypes.h>
#include <stdio.h>
#include "ParseResult.h"

uint32_t scoreResult(FILE* fp, const ParseResult* const stu, const char* const pASM);

#endif
