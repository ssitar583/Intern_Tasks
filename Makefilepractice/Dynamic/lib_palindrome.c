#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lib_palindrome.h"

int ispalindrome(char *b)
{
	int l = strlen(b);
	for(int i=0,j=l-1;i<l/2;i++,j--)
	{
		if(b[i]!=b[j])return 0;
	}
	return 1;
	

}
