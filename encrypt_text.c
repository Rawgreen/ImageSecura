#include "stdio.h"
#include "stdlib.h"

#define BUZZ_SIZE 1024
unsigned long long int modpow(int base, int power, int mod)
{
        int i;
        unsigned long long int result = 1;
        for (i = 0; i < power; i++)
        {
                result = (result * base) % mod;
        }
        return result;
}

int main (int argc, char *argv[])
{
        int m, n, e;
        unsigned long long int c;

        FILE *inp = fopen("public.txt", "r");
        fscanf(inp, "%d %d", &n, &e);
        fclose(inp);

	printf("ciphertext c = ");

	int i;
	FILE *outp = fopen("ciphertext.txt", "w");
        FILE *input = fopen("key.txt", "r");
        char key [BUZZ_SIZE];
        fscanf(input, "%s",key);
        fclose(input);
       

	for (i = 0; key[i] != '\0'; i++)
	{
        	c = modpow(key[i],e,n);
		printf("%llu ", c);
		fprintf(outp, "%llu\n", c);
	}

        printf("\n");
        fclose(outp);

        return 0;
}
