#include <stdio.h>

int main()
{

	printf("ispravno: \n");
	printf("%d\n", 0b1111000);
	printf("%x\n", 0b1111000);

	printf("datasheet: \n");
	printf("%d\n", 0b0111100);
	printf("%x\n", 0b0111100);

	printf("datasheet shiftano: \n");
	printf("%d\n", 0b0111100 << 1);
	printf("%x\n", 0b0111100 << 1);

	return 0;
}
