#include "gvl.h"
#include<stdio.h>
#include<stdlib.h>

char* generatevariable()
{
	static int variablecount = 1;
	char vcode[20];
	char *variable = (char *)malloc(50);
	strcpy(variable,"t");
        tostring(vcode,variablecount);
	variablecount++;
	strcat(variable,vcode);
	return variable;
}


char* generatelable()
{
	static int lablecount = 1;	
	char lcode[30];
	char *lable = (char *)malloc(60);
	strcpy(lable,"Lable");
	tostring(lcode,lablecount);
	lablecount++;
	strcat(lable,lcode);
	return lable;
}
void tostring(char str[], int num)

{

        int i, rem, len = 0, n;
	 n = num;
	 while (n != 0)
         {
	        len++;
	        n /= 10;
         }
	for (i = 0; i < len; i++)
	{
        rem = num % 10;
        num = num / 10;
	str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';


}


