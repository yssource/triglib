/* dabs(x) - absolute value of a real number. */
/* Argument must be a double */
double dabs(x) /* compute absolute vale of a real number */
double x;
{
   if ( x < 0.0 )
      x = -x;
   return(x);
}
