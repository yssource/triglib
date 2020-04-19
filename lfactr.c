/* lfactr.c - a routine to do long size factorials.
              Pass an int to be factorialised, and returns a long.
              This routine is recursive! The input range is to 13! 
*/
long lfactr(a)
int a;
{
  long b;
  if(a<1) return(1l);
  b = lfactr(a-1)*a;
  return(b);
}

