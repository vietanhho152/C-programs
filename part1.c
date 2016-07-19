#include <ctype.h>
#include <stdio.h>

int main(int argc, char **argv) // Display each word in the obj file of a program in hexadecimal form
{
	int a;
 	int b;
	FILE *file1 = fopen(argv[1], "r");
	while (!feof(file1))
	{
		a = fgetc(file1);
		b = fgetc(file1);
		if (feof(file1)){break;}
		printf("0x");
		printf("%02x", a);
		printf("%02x", b);
		printf("\n");
	}
	fclose(file1);
	return 0;
}
