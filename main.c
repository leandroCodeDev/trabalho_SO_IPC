#include <stdio.h>
#include <stdlib.h>

int main (void) {
   int a, b;
   printf("informe o primeiro valor \n");
   scanf ("%d %d ",&a, &b);


   double media;
   media = (a + b)/2.0;
   printf ("A média de %d e %d é %f\n", a, b, media);
   return EXIT_SUCCESS;
}