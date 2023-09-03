#include <stdio.h>


char bytefromtext(unsigned char* text)
{   
    char result = 0;
    for(int i=0;i<8;i++)
    {
        if(text[i]=='1')
        {
            result |= (1 << (7-i));
        }
    }
    return result;
}

int main(int argc, char*argv[]){

FILE *ptr_txt_in;
FILE *ptr_bmp_out;
unsigned char buf[8];
int c;
int j = 0;


ptr_txt_in=fopen("Decrypt.txt","r");
ptr_bmp_out=fopen("binary-to-img-converted.bmp","wb");


if(!ptr_txt_in)
{
    printf("Unable to open file\n");
    return 1;
}

while((c=fgetc(ptr_txt_in)) != EOF)
    {
        buf[j++] = c;
        if(j==8)
        {
            fputc(bytefromtext(buf),ptr_bmp_out);
            j=0;
        }
    }


    fclose(ptr_txt_in);
    fclose(ptr_bmp_out);

    return 0;
}