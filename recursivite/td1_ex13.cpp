#include <stdio.h>

void rechDichotomique(int deb, int fin, int val, int Tab [], bool &trouve, int &pos)
{
  if (deb > fin)
    trouve = false;
  else
  {
    pos = (deb+fin)/2;
    if (Tab[pos] > val)
      rechDichotomique(deb, pos-1, val, Tab, trouve, pos);
    else if (Tab[pos] < val)
      rechDichotomique(pos+1, fin, val, Tab, trouve, pos);
    else
      trouve = true;
  }
}

main ()
{
  int Tab [6]= {10, 17, 80, 88, 97, 103};
  
  printf("RECHERCHE DICHOTOMIQUE DE VALEURS DANS UN TABLEAU\n");
  
  int rech, pos;
  bool trouve;
  
  printf("Choisir la valeur à rechercher dans le tableau : ");
  scanf ("%i", &rech);
  rechDichotomique(0, 6, rech, Tab, trouve, pos);
  trouve ? printf("la valeur %i est à la position %i\n", rech, pos) : printf("pas trouve");
}
