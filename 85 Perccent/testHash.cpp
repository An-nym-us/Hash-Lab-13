/***********************************************************************
 * Header:
 *    Test
 * Summary:
 *    Driver to test hash.h
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef DEBUG
#define DEBUG   
#endif
 //#undef DEBUG  // Remove this comment to disable unit tests

#include "testHash.h"       // for the hash unit tests

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
#ifdef DEBUG
   // unit tests
   TestHash().run();
#endif // DEBUG
   
   // driver
   return 0;
}
