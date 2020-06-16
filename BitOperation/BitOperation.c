#include <stdio.h>
int main()
{
   
int a = 0x00CCAABB;
int c = a;
for (int i = 0; i < sizeof(c); ++i) 
{
	printf("\n%d byte is %x", i + 1, c & 0xFF);
	c = c >> 8;
}
a = a & 0x00DDAABB;
printf("\nChanged number is %x\n ", a );
}