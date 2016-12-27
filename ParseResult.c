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


// Add any needed include directives here
#include "ParseResult.h"
#include <stdlib.h>
// Add declarations of any static helper functions here.


/**  Frees the dynamic content of a ParseResult object.
 * 
 *   Pre:  pPR points to a proper ParseResult object.
 *   Post: All of the dynamically-allocated arrays in *pPR have been
 *         deallocated; pointers are NULL, static fields are reset to
 *         default values.
 * 
 *   Comments:
 *     -  The function has no information about whether *pPR has been
 *        allocated dynamically, so it cannot risk attempting to 
 *        deallocate *pPR.
 *     -  The function is intended to provide the user with a simple
 *        way to free memory; the user may or may not reuse *pPR.  So,
 *        the function does set the pointers in *pPR to NULL.
 */
void clearResult(ParseResult* const pPR) {
	free(pPR->ASMInstruction);
	pPR->ASMInstruction = NULL;
	free(pPR->Mnemonic);
	pPR->Mnemonic = NULL;
	free(pPR->rdName);
	pPR->rdName = NULL;
	free(pPR->rsName);
	pPR->rsName = NULL;
	free(pPR->rtName);
	pPR->rtName = NULL;
	free(pPR->Opcode);
	pPR->Opcode = NULL;
	free(pPR->Funct);
	pPR->Funct = NULL;
	free(pPR->RD);
	pPR->RD = NULL;
	free(pPR->RS);
	pPR->RS = NULL;
	free(pPR->RT);
	pPR->RT = NULL;
	free(pPR->IMM);
	pPR->IMM = NULL;
	pPR->rd = 0;
	pPR->rs = 0;
	pPR->rt = 0;
	pPR->Imm = 0;
}

/**  Prints the contents of a ParseResult object.
 * 
 *   Pre:  Log is open on an output file.
 *         pPR points to a proper ParseResult object.
 */
void printResult(FILE* Log, const ParseResult* const pPR) {
   
      fprintf(Log, "%s\n", pPR->ASMInstruction);
      fprintf(Log, "   %s   %s\n", pPR->Opcode, pPR->Mnemonic);
      fprintf(Log, "   %2"PRIu8"   %s", pPR->rd, pPR->rdName);
      if ( pPR->RD != NULL ) {
			fprintf(Log, "   %s", pPR->RD);
		}
		fprintf(Log, "\n");
      fprintf(Log, "   %2"PRIu8"   %s", pPR->rs, pPR->rsName);
      if ( pPR->RS != NULL ) {
			fprintf(Log, "   %s", pPR->RS);
		}
		fprintf(Log, "\n");
      fprintf(Log, "   %2"PRIu8"   %s", pPR->rt, pPR->rtName);
      if ( pPR->RT != NULL ) {
			fprintf(Log, "   %s", pPR->RT);
		}
		fprintf(Log, "\n");
      fprintf(Log, "   %s\n", pPR->Funct);
      fprintf(Log, "   %"PRId16"\n", pPR->Imm);
      if ( pPR->IMM != NULL ) {
			fprintf(Log, "   %s", pPR->IMM);
		}
		fprintf(Log, "\n");
		fprintf(Log, "\n");
}
