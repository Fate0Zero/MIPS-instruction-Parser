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
#include "ASMParser.h"
#include <stdlib.h>
#include "Op.h"
#include "Func.h"
#include "Reg.h"
#include "ParseResult.h"
#include <string.h>


/**  Breaks up the given MIPS32 assembly instruction and creates a proper 
 *   ParseResult object storing information about that instruction.
 * 
 *   Pre:  pASM points to an array holding the bits (as chars) of a
 *         syntactically valid assembly instruction, whose mnemonic is
 *         one of the following:
 *             add  addi  and  andi  lui  lw  or  ori  sub
 * 
 *   Returns:
 *         A pointer to a proper ParseResult object whose fields have been
 *         correctly initialized to correspond to the target of pASM.
 */
ParseResult* parseASM(const char* const pASM) {
	char* curr = pASM;
	char* pch;
	ParseResult* result = (ParseResult*) calloc(1000, sizeof(ParseResult));
	
	result->ASMInstruction = (char*) calloc(1000, sizeof(char*));
	
	strcpy(result->ASMInstruction, pASM);
	pch = strtok (curr, " ,\t()");
	result->Mnemonic = (char*) calloc(1000, sizeof(char*));
	
	strcpy(result->Mnemonic, pch);
	if (strcmp(result->Mnemonic, "add") == 0 
		|| strcmp(result->Mnemonic, "and") == 0
		|| strcmp(result->Mnemonic, "or") == 0
		|| strcmp(result->Mnemonic, "sub") == 0) {
		result->Funct = (char*) calloc(1000, sizeof(char*));
		strcpy(result->Funct, FindF(result->Mnemonic)->function);
		result->Opcode = (char*) calloc(1000, sizeof(char*));
		strcpy(result->Opcode, Find(result->Mnemonic)->code);		
		pch = strtok (NULL, " ,\t()");
		result->rdName = (char*) calloc(1000, sizeof(char*));
		strcpy(result->rdName, pch);
		result->rd = FindR(result->rdName)->number;
		result->RD = (char*) calloc(1000, sizeof(char*));
		strcpy(result->RD, FindR(result->rdName)->Reg);
		pch = strtok (NULL, " ,\t()");
		result->rsName = (char*) calloc(1000, sizeof(char*));
		strcpy(result->rsName, pch);
		result->rs = FindR(result->rsName)->number;
		result->RS = (char*) calloc(1000, sizeof(char*));
		strcpy(result->RS, FindR(result->rsName)->Reg);
		pch = strtok (NULL, " ,\t()");
		result->rtName = (char*) calloc(1000, sizeof(char*));
		strcpy(result->rtName, pch);
		result->rt = FindR(result->rtName)->number;
		result->RT = (char*) calloc(1000, sizeof(char*));
		strcpy(result->RT, FindR(result->rtName)->Reg);
		result->Imm = 0;
		result->IMM = NULL;
	}
	else if (strcmp(result->Mnemonic, "addi") == 0
			|| strcmp(result->Mnemonic, "andi") == 0
			|| strcmp(result->Mnemonic, "ori") == 0) {
		result->Opcode = (char*) calloc(1000, sizeof(char*));
		strcpy(result->Opcode, Find(result->Mnemonic)->code);
		pch = strtok (NULL, " ,\t()");
		result->rtName = (char*) calloc(1000, sizeof(char*));
		strcpy(result->rtName, pch);
		result->rt = FindR(result->rtName)->number;
		result->RT = (char*) calloc(1000, sizeof(char*));
		strcpy(result->RT, FindR(result->rtName)->Reg);		
		pch = strtok (NULL, " ,\t()");
		result->rsName = (char*) calloc(1000, sizeof(char*));
		strcpy(result->rsName, pch);
		result->rs = FindR(result->rsName)->number;
		result->RS = (char*) calloc(1000, sizeof(char*));
		strcpy(result->RS, FindR(result->rsName)->Reg);
		
		result->rdName = NULL;
		result->RD = NULL;
		result->rd = 255;
		pch = strtok (NULL, " ,\t()");
		result->Imm = atoi(pch);
		result->IMM = (char*) calloc(16, sizeof(char*));
		strcpy(result->IMM, DtoB(atoi(pch)));
	}
    
    else if (strcmp(result->Mnemonic, "lui") == 0) {
		result->rtName = (char*) calloc(10, sizeof(char*));
		pch = strtok(NULL, " ,\t()");
		strcpy(result->rtName, pch);
		result->rsName = NULL;
		result->rdName = NULL;
		result->RD = NULL;
		result->Funct = NULL;
		result->rs = 0;
		result->rd = 255;
		result->rt = FindR(result->rtName)->number;
		result->IMM = (char*) calloc(10, sizeof(char*));
		pch = strtok(NULL, " ,\t()");
		result->Imm = atoi(pch);
		result->IMM = (char*) calloc(16, sizeof(char*));
		result->Opcode = (char*) calloc(10, sizeof(char*));
		result->RT = (char*) calloc(10, sizeof(char*));
		result->RS = (char*) calloc(10, sizeof(char*));
		strcpy(result->RS,"00000");
		strcpy(result->Opcode, Find(result->Mnemonic)->code);
		strcpy(result->RT, FindR(result->rtName)->Reg);
		strcpy(result->IMM, DtoB(atoi(pch)));

	}
    else {
	result->rdName = NULL;

			result->rsName = (char*) calloc(10, sizeof(char*));
			result->rtName = (char*) calloc(10, sizeof(char*));
			pch = strtok(NULL, " ,\t()");
			strcpy(result->rtName, pch);
			pch = strtok(NULL, " ,\t()");
			result->IMM = (char*) calloc(16, sizeof(char*));
			result->Imm = atoi(pch);
			strcpy(result->IMM, DtoB(atoi(pch)));	
			pch = strtok(NULL, " ,\t()");
			strcpy(result->rsName, pch);
			result->rd = 255;
			result->rs = FindR(result->rsName)->number;
			result->rt = FindR(result->rtName)->number;
			result->Funct = NULL;
			result->Opcode = (char*) calloc(10, sizeof(char*));
			result->RS = (char*) calloc(10, sizeof(char*));
			result->RT = (char*) calloc(10, sizeof(char*));
			
			strcpy(result->Opcode, Find(result->Mnemonic)->code);
			strcpy(result->RS, FindR(result->rsName)->Reg);
			strcpy(result->RT, FindR(result->rtName)->Reg);
				
	}
    
   return result;
}


