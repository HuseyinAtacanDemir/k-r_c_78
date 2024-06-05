#include <stdio.h>
#define NULL 0 /* pointer value for error report */
#define ALLOCSIZE 1000 /* size of available space */

/*
  If p is a ptr, then p++ increments p to the next element
  of whatever kind of object p points to.
  And p += 1 increments p to point i elements beyond
  it currently does.
*/

/*
  C guarantees that no ptr that validly points at data qill contain zero
  so a return value of zero can be used to signal an abnormal event
  We write NULL instead of zero, to indicate more clearly that this is a
  special value for a pointer
  In general, integers cannot meaningfully be assigned to ptrs, 
  zero is a special case
*/

/*
  PTRs can be compared under certain circumstances:
    if p and q point to members of the same array, then < > == != work properly

    any ptrs can be meaningfully compared for equality or inequality with NULL.

    All bets are off if ptrs pointing to different arrs are compared or done arithmetic with.

    It might run and produce meaningless data on one machine but crash on another.

    p + n is the nth object beyond the one p currently points to, regardless of the kind of
    object p is declared to point at, the compiler scales n according to the size of the objs
    that p points to, which is determined by the declaration of p.

    Other than the ops mentioned here, all other ptr arithmetic is illegal:
      adding two ptrs
      multiply / divide / mask / shift ptrs
      adding float or double to ptrs
*/

/*
  This alloc/free implementation is rudimentary because 
  the alloc and free commands must be called in pairs
  in a LIFO manner.

  The standard C library implementation has no such restrictions.
*/

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */
// static char *allocp = &allocbuf[0] is equivalent, 
// since the name of the array is the addr of the zeroth element

/*
  returns a pointer p, which points to the start of an allocated block of
  n consecutive character positions on the allocbuf, to the caller.

  returns NULL if there is not enough space in the allocbuf for the
  requested allocation
  
  increments the next free position pointer (aka allocp) to the next
  character position after the end of the newly allocated
  consecutive char positions as a side effect

*/
char* alloc(int n)
{
  if (allocp + n <= allocbuf + ALLOCSIZE) { //fits
    allocp += n;
    return (allocp - n); // old p
  } else // not enough room
    return (NULL);
}

/*
  no return

  sets the next free position pointer to the start address
  of the block that is being free'd

  disregards if the address to which the pointer given
  is outside the bounds of the allocbuf

*/
void free(char *p) // free the storage pointed to by p
{
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}

/*
  ptr subtraction is also valid
  if p and q point to the members of the same array, p-q is the num od elems between p and q
  
  Because p points to chars, p++ advances p to the next char each time, and p-s gives the num
  of chars advanced over, that is, the string length,

  ptr arithmetic is consistent, if the arr had been dealing with floats, which will occupy more
  storage than chars, and if p were a ptr to float, p++ would have advanced to the next float.
*/
int str_len(char *s)
{
  char *p = s;

  while (*p != '\0')
    p++;
  return (p-s);
}
/*
  this is eqivalent to the one above, since '\0' is zero, 
  it will be evaluated as 0 in the condition check of the while loop
*/
int str_len_equivalent(char *s)
{
  char *p = s;

  while (*p)
    p++;
  return (p-s);
}


