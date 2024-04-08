#include<stdio.h>
#include<dlfcn.h>
#include "lib_palindrome.h"

int main()
{
	void *palindrome = dlopen("./lib_all.so", RTLD_LAZY);
    	if (!palindrome) {
    		fprintf(stderr, "Error loading libraries\n");
		return 1;
	}
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
	dlclose(palindrome);
}
