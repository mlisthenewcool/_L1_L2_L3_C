#include <stdio.h>

int pascal(int n, int m)
{
  if (n==m || m==1)
    return 1;
  else
    return pascal(n-1, m-1) + pascal (n-1, m);
}

void dessinPascal(int n)
{
  int l,c;
  
  for (l=1; l<n+1; l++)
  {
    for (c=1; c<l+1; c++)
    {
      printf ("%i", pascal(l,c));
    }
    printf ("\n");
  }
}

main ()
{
  printf("Veuillez entrer le rang désiré pour afficher le triangle de Pascal : ");
  int rang;
  scanf ("%i", &rang);
  
  dessinPascal(rang);
}
