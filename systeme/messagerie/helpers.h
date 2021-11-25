#define BUFFER_SIZE 255

/**
 * *************************************
 * Perror + exit(1)
 * 
 * @param char *msg : the error message
 * *************************************
 */
void error(char *msg)
{
	char buffer[BUFFER_SIZE];

	strcpy(buffer, msg);

	printf("\n");
	perror(buffer);
	printf("**********************************************************************\n\n");

	exit(1);
}