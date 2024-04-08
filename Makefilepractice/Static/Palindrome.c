#include<stdio.h>
#include "lib_palindrome.h"

int main()
{
	char b[100];
	scanf("%s",b);
	//printf("%s",revString(b));
	if(ispalindrome(b))
	{
		printf("%s is a palindrome",revString(b));
	}
	else
	{
		printf("%s is not a palindrome",b);
	}
}
