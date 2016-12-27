#ifndef GENERATE_H
#define GENERATE_H
#include <inttypes.h>

/**  Generates input data for testing MIPS32 machine code translations.
 * 
 *   Pre:  fName is a valid file name
 *         nCases == 0 or > 16 means generate 16 test cases (one for each
 *            specified instruction)
 *         1 <= nCases <= 16 means generate nCases tests
 *   Post: A file, named fName, has been created and holds the number of
 *            valid test cases described above. 
 */
uint32_t GenerateInput(char* fName, uint32_t nCases);

#endif
