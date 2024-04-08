#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lib_palindrome.h"

char* revString(char *b)
{
	int l = strlen(b);
	for(int i=0,j=l-1;i<l/2;i++,j--)
	{
		char t = b[i];
		b[i]=b[j];
		b[j]=t;
	}
	return b;

}
