#include <stdio.h>
#include <ctype.h>
void printRegister(int regArray[], int IR, char CC, int PC, int memArray[]);

/* C program that implement LC-3 instructions. That will execute the binary code generated by LC-3 assembler*/
int main(int argc, char **argv)
{
    FILE *file2 = fopen(argv[1], "r");
    int mem[65536];
    int reg[9];
    reg[0] = 0x0000;
    reg[1] = 0x0000;
    reg[2] = 0x0000;
    reg[3] = 0x0000;
    reg[4] = 0x0000;
    reg[5] = 0x0000;
    reg[6] = 0x0000;
    reg[7] = 0x0000;
    reg[8] = 0x0000;
    int IR = 0x0000;
    int PC = 0x0000;
    char CC = 'Z';
    int a;
    int b;
    int i;
    int d;
    i = 0;
    while(!feof(file2)){
    a = fgetc(file2);
    b = fgetc(file2);
    a = a<<8;
    d = a|b;
    mem[i]= d;
    i=i++;
    }
    int checkval;
    int sr1;
    int sr2;
    int number;
    int value;
    int signval;
    int x;
    x = 0;
    int dr;
    dr = 0;
    int offset;
    offset = 0;
    int val;
    int index;
    for (x = 0; x < i; x++)
    {
        index = x;
        a = mem[x] >>12;
      if (a==15){break;}
        IR = mem[x];
      if ( a==2){	// Executing instruction "LD"
        dr = mem[x] & 0xdfff;
        dr = dr >> 9;
        offset = mem[x] & 0x1ff;
        val = PC + offset;
        index = 1 + val;
        reg[dr] = mem[index];
	value = reg[dr];
	signval = value >> 15;
	if (value ==0) {CC = 'Z';}
	else if (signval ==1) {CC = 'N';}
	else {CC = 'P';}
      }

     if (a==14){	// Executing instruction "LEA"
	dr = mem[x] & 0x1fff;
	dr = dr >> 9;
	offset = mem[x] & 0x1ff;
	val = PC + offset;
	index = 1 + val;
	reg[dr] = mem[0] + val;
	value = reg[dr];
	signval = value >> 15;
	if (value == 0) {CC = 'Z';}
	else if(signval == 1) {CC = 'N';}
	else {CC = 'P';}
     }
     if (a == 10){	//Executing instruction "LDI"
	dr = mem[x] & 0x5fff;
	dr = dr >> 9;
	offset = mem[x] & 0x1ff;
	val = PC + offset;
	index = 1 + val;
	reg[dr] = mem[1 + mem[index] - mem[0]];
	value = reg[dr];
	signval = value >> 15;
	if (value == 0) {CC = 'Z';}
	else if(signval == 1) {CC = 'N';}
	else {CC = 'P';}
     }
     if (a == 5){	//Executing instruction "AND"
     	dr = mem[x] & 0xafff;
	dr = dr >> 9;
	checkval = mem[x] & 0x3f;
	checkval = checkval >> 5;
	sr1 = mem[x] & 0x1ff;
	sr1 = sr1 >> 6;
	if(checkval == 0)
	{
	sr2 = mem[x] & 0x0007;
	reg[dr] = reg[sr1] & reg[sr2];
	value = reg[dr];
	signval = value >> 15;
	if (value == 0) {CC = 'Z';}
	else if(signval == 1) {CC = 'N';}
	else {CC = 'P';}
	}
	if(checkval == 1)
	{
	number = mem[x] & 0x1f;
	reg[dr] = reg[sr1] & number;
	value = reg[dr];
	signval = value >> 15;
	if (value == 0) {CC = 'Z';}
	else if(signval == 1) {CC = 'N';}
	else {CC = 'P';}
	}
     }
     if (a==9){		 // Executing instruction "NOT"
	unsigned short sr;
	dr = mem[x] & 0x6fff;
	dr = dr >> 9;
	sr1 = mem[x] & 0x1ff;
	sr1 = sr1 >> 6;
	sr = ~reg[sr1];
	reg[dr] = sr;
	value = reg[dr];
	signval = value >> 15;
	if (value == 0) {CC = 'Z';}
	else if(signval == 1) {CC = 'N';}
	else {CC = 'P';}
    }
    if(a == 1){		//Executing instruction "ADD"
	short num;
	dr = mem[x] & 0xafff;
	dr = dr >> 9;
	checkval = mem[x] & 0x3f;
	checkval = checkval >> 5;
	sr1 = mem[x] & 0x1ff;
	sr1 = sr1 >> 6;
        if(checkval == 0)
	{
	sr2 = mem[x] & 0x7;
	reg[dr] = reg[sr1] + reg[sr2];
	num = reg[dr];
	reg[dr] = num;
	value = reg[dr];
	signval = value >> 15;
	if (value == 0) {CC = 'Z';}
	else if(signval == 1) {CC = 'N';}
	else {CC = 'P';}
	}
	if(checkval ==1)
	{
	number = mem[x] & 0x7;
	reg[dr] = reg[sr1] + number;
	num = reg[dr];
	reg[dr] = num;
	value = reg[dr];
	signval = value >> 15;
	if (value == 0) {CC = 'Z';}
	else if(signval == 1) {CC = 'N';}
	else {CC = 'P';}
	}
    }
    if(a ==0){		//Executing instruction "BR"
	int n;
	n=0;
	int z;
	z=0;
	int p;
	p=0;
	offset = mem[x] & 0x1ff;
	n = mem[x] >> 11;
	z = mem[x] & 0x7ff;
	z = z >> 10;
	p = mem[x] & 0x3ff;
	p = p >> 9;
	if ((n !=0 && CC =='N')||(z!=0 && CC=='Z')||(p!=0 && CC == 'P')){PC = PC + offset;}
	printRegister(reg, IR, CC, PC , mem);
    }
    PC = PC ++;
   }
    fclose(file2);
    return 0;
}
void printRegister(int regArray[], int IR, char CC, int PC, int memArray[])

{
    printf("after executing instruction\t0x%04x\n", IR);
    printf("R0\t0x%04x\n", regArray[0]);
    printf("R1\t0x%04x\n", regArray[1]);
    printf("R2\t0x%04x\n", regArray[2]);
    printf("R3\t0x%04x\n", regArray[3]);
    printf("R4\t0x%04x\n", regArray[4]);
    printf("R5\t0x%04x\n", regArray[5]);
    printf("R6\t0x%04x\n", regArray[6]);
    printf("R7\t0x%04x\n", regArray[7]);
    printf("PC\t0x%04x\n", memArray[0] + PC);
    printf("IR\t0x%04x\n",IR);
    printf("CC\t%c\n", CC);
    puts("==================");
}
