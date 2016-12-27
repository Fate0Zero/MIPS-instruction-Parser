#include "Reg.h"

#define NUMRECORDS 9

static Reg RegisterTable[NUMRECORDS] = {
	{0, "00000", "$zero"},
	{8, "01000", "$t0"},
	{9, "01001", "$t1"},
	{10, "01010", "$t2"},
	{11, "01011", "$t3"},
	{16, "10000", "$s0"},
	{17, "10001", "$s1"},
	{18, "10010", "$s2"},
	{19, "10011", "$s3"}
};

const Reg* FindR(const char* const reg) {
	for (int i = 0; i < NUMRECORDS; i++) {
		if (strcmp(reg, RegisterTable[i].name) == 0) {
			return &RegisterTable[i];
		}
	}
	return NULL;
}
