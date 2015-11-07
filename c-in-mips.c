#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// The last 0 in the RegisterFile is for the registers $0, $zero
static int RegisterFile[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static char RegisterFileNames[31][4] = {"$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$gp", "$sp", "$fp", "$ra"};
static int data_memory[1024];
static char* string_memory[1024];
static char* instructions[1000000];

int main() {
    int i=0;
    readmips("bubble.asm");
    while(instructions[i]!=NULL){
        printf("%s\n",instructions[i]);
        ++i;
    }
    while(instructions[i]!=NULL){
        free(instructions[i]);
        i++;
    }
    return 0;
}

int readmips(char* filename){
    FILE * assembly = fopen(filename, "r");
    int lineno=0; int charno=0; int i =0; int spacebreak=0;
    char buffer[256];
    char* temp;
    if (assembly == 0)
    {
        //fopen returns 0, the NULL pointer, on failure
        perror("Cannot open input file\n");
        exit(-1);
    }
    else {
        while(fgets(buffer,256,assembly)!=NULL){
            charno=0;
            while(buffer[charno]!='#' && buffer[charno]!='\n'){
                charno++;
            } 
            temp = (char*)malloc(charno+1);
            i=0; spacebreak=0;
            while(isspace(buffer[i])){
                i++;
            }
            spacebreak=i;
            while(i<charno){
                *(temp+i-spacebreak)=buffer[i];
                i++;
            }
            //printf("%s\n",temp);
            instructions[lineno]=temp;
            if (charno!=0){
                lineno++;
            }
        }
    }
}


//ALU function

int alu(int operandA, int operandB, int Operation) {
	int result;
	if (Operation == "add") {
		result = add(operandA, operandB);
	}
	else if (Operation == "addi") {
		result = addi(operandA, operandB);
	}
	else if (Operation == "addu") {
		result = addu(operandA, operandB);
	}
	else if (Operation == "addiu") {
		result = addiu(operandA, operandB);
	}
	else if (Operation == "sub") {
		result = sub(operandA, operandB);
	}
	else if (Operation == "subu") {
		result = subu(operandA, operandB);
	}
	else if (Operation == "and") {
		result = and(operandA, operandB);
	}
	else if (Operation == "andi") {
		result = andi(operandA, operandB);
	}
	else if (Operation == "or") {
		result = or(operandA, operandB);
	}
	else if (Operation == "ori") {
		result = ori(operandA, operandB);
	}
	else if (Operation == "xor") {
		result = xor (operandA, operandB);
	}
	else if (Operation == "nor") {
		result = nor(operandA, operandB);
	}
	else if (Operation == "slt") {
		result = slt(operandA, operandB);
	}
	else if (Operation == "slti") {
		result = slti(operandA, operandB);
	}
	else if (Operation == "sltu") {
		result = sltu(operandA, operandB);
	}
	else {
		perror("Command Not Found");
		exit(-1);
	}
	return result;
}

// Start of Arithmetic functions
//TODO: Mult and Divide, all operations with 'u' have to use unsigned values, others ahve to check for overflow
int add(register2, register3) {
	return RegisterFile[register2] + RegisterFile[register3];
}

unsigned int addu(register2, register3) {
	return RegisterFile[register2] + RegisterFile[register3];
}

int sub(register2, register3) {
	return RegisterFile[register2] - RegisterFile[register3];
}

unsigned int subu(register2, register3) {
	return RegisterFile[register2] - RegisterFile[register3];
}

int addi(register2, number) {
	return RegisterFile[register2] + number;
}

unsigned int addiu(register2, number) {
	return RegisterFile[register2] + number;
}

//Mult and Divide left, have to use LO and HI

// Start of Logical functions

int and(register2, register3) {
	if (RegisterFile[register2] == 1 && RegisterFile[register3] == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int andi(register2, number) {
	if (RegisterFile[register2] == 1 && number == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int or(register2, register3) {
	if (RegisterFile[register2] == 1 || RegisterFile[register3] == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int ori(register2, number) {
	if (RegisterFile[register2] == 1 || number == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int xor(register2, register3) {
	if ((RegisterFile[register2] == 1 && RegisterFile[register3] != 1) || (RegisterFile[register2] != 1 && RegisterFile[register3] == 1)) {
		return 1;
	}
	else {
		return 0;
	}
}

int nor(register2, register3) {
	if (!(RegisterFile[register2] == 1 || RegisterFile[register3] == 1)) {
		return 1;
	}
	else {
		return 0;
	}
}

int slt(register2, register3) {
	if (RegisterFile[register2] < RegisterFile[register3]) {
		return 1;
	}
	else {
		return 0;
	}
}

unsigned int sltu(register2, register3) {
	if (RegisterFile[register2] < RegisterFile[register3]) {
		return 1;
	}
	else {
		return 0;
	}
}

int slti(register2, number) {
	if (RegisterFile[register2] < number) {
		return 1;
	}
	else {
		return 0;
	}
}