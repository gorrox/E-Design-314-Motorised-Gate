/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  GateController                         */
/*      FILE         :  GateController.c                       */
/*      DESCRIPTION  :  Main Program                           */
/*      CPU SERIES   :  RL78 - G14                             */
/*      CPU TYPE     :  R5F104LE                               */
/*                                                             */
/*      This file is generated by e2 studio.                   */
/*                                                             */
/***************************************************************/                                   
                                                                                            
                                                                                            
/************************************************************************/
/*    File Version: V1.00                                               */
/*    Date Generated: 10/09/2013                                        */
/************************************************************************/

#include "iodefine.h"

#ifdef CPPAPP
//Initialize global constructors
extern "C" void __main()
{
  static int initialized;
  if (! initialized)
    {
      typedef void (*pfunc) ();
      extern pfunc __ctors[];
      extern pfunc __ctors_end[];
      pfunc *p;

      initialized = 1;
      for (p = __ctors_end; p > __ctors; )
    (*--p) ();

    }
}
#endif 

int main(void)
{
    // TODO: add application code here

    while (1) {
    }
  return 0;
}
