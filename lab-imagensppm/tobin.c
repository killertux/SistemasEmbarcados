#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *pointer;
	char buffer[60];
	int i = 0, n;
	pointer = fopen(argv[1], "r");
	//reads header
	fgets(buffer, 50, pointer);
	fgets(buffer, 50, pointer);
	fgets(buffer, 50, pointer);
	fgets(buffer, 50, pointer);
	
	while( fgets(buffer, 50, pointer) != NULL) {
		if(!(i % 3)) {
			n = atoi(buffer);
			printf("%c", n);
		}
		i++;
	}
	return 0;
}
