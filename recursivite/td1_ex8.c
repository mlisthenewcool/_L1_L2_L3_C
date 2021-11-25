#include <stdio.h>

int nb_op = 0;

int fibo (int n)
{
	if (n == 0 || n == 1) return 1;
	else 
	{
		nb_op++;
		return fibo(n-1) + fibo(n-2);
	}
}

int fibo2 (int n)
{
	if (n == 0 || n == 1)
		return 1;
	
	else
	{
		int i, temp, res;
		for(i = 2; i < n+1; i++)
		{
			temp = i + temp;
		}
	}
}

int main(int argc, char** argv)
{
	int rang = 0;
	printf("\n\t*** Suite de fibonnacci ***\nSaisir le rang : ");

	while(rang >= 0)
	{
		nb_op = 0;
		//rang = 0;
		scanf("%d", &rang);
		printf ("Rang (%d) Opérations (%d) Valeur (%d)\n", rang, nb_op, fibo(rang));
	}
	
	return 0;
}
  