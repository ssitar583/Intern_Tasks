#include<stdio.h>
#include<stdlib.h>


int main()
{
	char b[1000];
	scanf("%s",b);
	if(ispalindrome(b))
	{
		printf("YES");
	}
	else
	{
		printf("NO");
	}
}
