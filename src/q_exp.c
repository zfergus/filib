/*********************************************************************/
/*       fi_lib  --- A fast interval library (Version 1.2)           */
/*        (For copyright and info`s see file "fi_lib.h")             */
/*********************************************************************/

#include <filib/fi_lib.h>



/* --------------------------------------------------------------------- */
/* - Computation of exp(x), table lookup method                        - */
/* - We use the idea of Mr. P.T.P. Tang                                - */
/* --------------------------------------------------------------------- */

#ifdef LINT_ARGS
local double q_exp(double x)
#else
local double q_exp(x)

double x;
#endif
{
 int j;
 long int n,m;
 double r,r1,r2,q,s;
 double res;


 /* Step 1: Special cases  */
 if NANTEST(x)                                       /* Test: x=NaN */
      res=q_abortnan(INV_ARG,&x,2);
 else {
 if ((-q_ext1<x) && (x<q_ext1))                      /* |x|<2^-54 */
   res=x+1;
 else
  { if (q_ex2a<x)
      res=q_abortr1(OVER_FLOW,&x,2);                 /* Overflow */
    else
      { if (x<q_mine)
	  res=0;                                     /* result: underflow */
	else
	  {
	    /* Step 2 */
	    if (x>0) n=CUTINT((x*q_exil)+0.5);
	    else     n=CUTINT((x*q_exil)-0.5);       /* round (x)      */
	    j=n % 32;                                /* j=n mod 32     */
	    if (j<0) j+=32;                          /* We force j>=0  */
	    m=(n-j)/32;
	    r1=x-n*q_exl1;
	    r2=-(n*q_exl2);

	    /* Step 3 */
	    r=r1+r2;
	    q=(((q_exa[4]*r+q_exa[3])*r+q_exa[2])*r+q_exa[1])*r+q_exa[0];
	    q=r*r*q;
	    q=r1+(r2+q);

	    /* Step 4 */
	    s=q_exld[j]+q_extl[j];
	    res=(q_exld[j]+(q_extl[j]+s*q));
	    POWER2(res,m);
	  }
      }
  }
  }

  return(res);
}

