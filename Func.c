//On my honor:
//
//-I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants 
// assigned to this course.
//
//-I have not used C language code obtained from another student, 
// or any other unauthorized source, either modified or unmodified.  
//
//-If any C language code or documentation used in my program 
// was obtained from another source, such as a text book or course
// notes, that has been clearly noted with a proper citation in
// the comments of my program.
//
// Yuhui Lyu
#include "Func.h"

#define NUMRECORDS 4

static Func FunctionTable[NUMRECORDS] = {
	{"100000", "add"},
	{"100100", "and"},
	{"100101", "or"},
	{"100010", "sub"}
};

const Func* FindF(const char* const code) {
	for (int i = 0; i < NUMRECORDS; i++) {
		if (strcmp(code, FunctionTable[i].mnemonic) == 0) {
			return &FunctionTable[i];
		}
	}
	return NULL;
}
char* DtoB (int number) {
	char* result = calloc(16, sizeof(char*));
	int c;
	int k;
	for (c = 15; c >= 0; c--) {
		k = number >> c;
		if(k & 1) {
			result[15 - c] = '1';
		}
		else {
			result[15 - c] = '0';
		}
	}
	return result;
}
