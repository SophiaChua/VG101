#include <stdio.h>
#include <string.h>

int main ()
{
	char str1[] = "To be or not to be";
	char str2[6]; // no initialization, values are unknown (random)
	for(int i=0; i<6; i++)
	{
		// print the numeric values of str2
		printf("%d\n", str2[i]);
	}

	str2[5] = 'a'; // fix this element rather than being random

	strncpy (str2, str1, 5);
	// str2[5] = '\0'; // try with and without this statement

	puts(str2); // print a string on the screen

	return 0;
}