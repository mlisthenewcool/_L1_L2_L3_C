#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void trim(char *str)
{
    char *start, *end;

    for (start = str; *start; start++)
    {
        if (!isspace((unsigned char)start[0]))
            break;
    }

    for (end = start + strlen(start); end > start + 1; end--)
    {
        if (!isspace((unsigned char)end[-1]))
            break;
    }

    *end = 0;

    if (start > str)
        memmove(str, start, (end - start) + 1);
}

bool palindrome (int deb, int fin, char *ch) {

	trim(ch);

	if (deb > fin)
		return true;
	else if (ch[deb] == ch[fin])
		palindrome (deb+1, fin-1, ch);
	else
		return false;
}

main()
{
    char str[5];
	int length = strlen(str);
    int start=0,end=length-1;
    int result;
    printf("Enter the String.\n");
    fgets( str, sizeof( str ), stdin );
    length = strlen(str);

    if(palindrome(start,end,str))
        printf("palindrome!\n");
    else
        printf("pas palindrome!\n");
}