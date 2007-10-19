#include <string.h>
#include <stdio.h>

static const short int	inttostr[10] = {
0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39
};

static void exptostr(char * str, int exp) {
	int idx = 0;
	int fidx = 0;
	int digit;
	int reduce = exp;
	int until;
	while(reduce >= 10)
	{
		digit = reduce % 10;
		reduce = reduce/10;
		str[idx++]=inttostr[digit];
	}
	str[idx++]=inttostr[reduce];
	str[idx] = '\0';

	/* Process half the string.  */
	until = idx/2;
	--idx;
	/* Reverse the string.  */
	for (fidx=0; fidx<until; fidx++,idx--) {
		str[idx]=str[idx]+str[fidx];
		str[fidx]=str[idx]-str[fidx];
		str[idx]=str[idx]-str[fidx];
	}
}

int main() {
	char str[32];
	int exp=123;
	exptostr(&str[0], exp);
	printf("%s\n", &str[0]);

	exptostr(&str[0], 10);
	printf("%s\n", &str[0]);

	exptostr(&str[0], 3);
	printf("%s\n", &str[0]);

	memset(&str[0],0x40,32);
	exptostr(&str[10], 1238348);
	printf("%s\n", &str[0]);

	exptostr(&str[0], 0);
	printf("%s\n", &str[0]);

	exptostr(&str[0], 83746578);
	printf("%s\n", &str[0]);
	return 0;
}
