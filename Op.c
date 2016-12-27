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
#include "Op.h"

#define NUMRECORDS 9

static Op OperationTable[NUMRECORDS] = {
	{"000000", "add"},
	{"000000", "and"},
	{"000000", "or"},
	{"000000", "sub"},
	{"001000", "addi"},
	{"001100", "andi"},
	{"001111", "lui"},
	{"100011", "lw"},
	{"001101", "ori"}
};

const Op* Find(const char* const op) {
	for (int i = 0; i < NUMRECORDS; i++) {
		if (strcmp(op, OperationTable[i].mnemonic) == 0) {
			return &OperationTable[i];
		}
	}
	return NULL;
}
