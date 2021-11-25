#include <stdio.h>

int pgcd (int a, int b)
{
  if (a==b)
    return a;
  else if (a<b)
    return pgcd (a, b-a);
  else
    return pgcd (a-b, a);
}

main()
{
  printf("Calcul du pgcd de deux nombres\n");
  int a, b;
  printf("Veuillez saisir la valeur du premier nombre : ");
  scanf ("%i", &a);
  printf("Veuillez saisir la valeur du deuxième nombre : ");
  scanf ("%i", &b);
  
  printf ("Le pgcd de %i et %i est : %i\n", a, b, pgcd(a,b));
}
