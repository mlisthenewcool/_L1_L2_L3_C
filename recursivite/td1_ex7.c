#include <stdio.h>

int suite (int n)
{
  if (n==0)
  {
    return 1;
  }
  else
  {
    return 2 * suite(n-1) + 3;
  }
}

main()
{
  printf ("Veuillez entrer le rang désiré de la suite : ");
  int rang;
  scanf("%i",&rang);
  
  printf ("Valeur de la suite au rang %i : %i\n", rang, suite(rang));
}