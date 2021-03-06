/* nlog(x) -natural log of a real number
            Argument x must be a double
            the type returned is of type doubl
*/

#include <stdio.h>

#define ENLOGVAL 44 /*  X <= 0  */
#define INDEX     9 /* number of precalculated constants
                       for the nlog(x) power series */
#define LN2      6.931471805599453e-01
#define R21      4.761904761904762e-02
#define LN1_4375 3.629054936893685e-01

double nlog(x)
double x;
{
union  {
        double a;
        char c[8];
       } z;

   double x2,ln;
   static double r[INDEX] = {
      3.333333333333333e-01,
      2.000000000000000e-01,
      1.428571428571429e-01,
      1.111111111111111e-01,
      9.090909090909091e-02,
      7.692307692307692e-02,
      6.666666666666667e-02,
      5.882352941176471e-02,
      5.263157894736842e-02 };

   register int n;
   int exp;
   extern int errno;

/* check for argument error */
   if ( x <= 0.0 )
   {  for ( n = 0; n < 8; ++n )
         z.c[n] = 0xff;
      errno = ENLOGVAL;
      return(z.a);
   }

/* check for values which are 
obvious 
*/
   if ( x == 1.0 )
      return(0.0);

/* reduce to range 0.5 <= x < 1.0
*/
   z.a = x;
   exp = ( z.c[7] & 0xff ) - 0x80;
   z.c[7] = 0x80;

/* calculate nlog(x) 
*/
   if ( z.a == 0.5 ) /* bypass obvious value */
      ln = -LN2;
   else /* compute power series */
   {
      z.a *= 1.4375;  /* shift range to relax the series */
      x = ( z.a - 1.0 ) / ( z.a + 1.0 );
      x2 = x * x;
      ln = x2 * R21;
      for ( n = INDEX - 1; n >= 0; --n )
         ln = ( ln + r[n] ) * x2;
      ln = ( ln + 1.0 ) * x;
      ln += ln - LN1_4375;
   }
   return(ln+exp*LN2);
}


