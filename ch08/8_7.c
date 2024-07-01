#include <unistd.h>
#include <stdio.h>

#define NALLOC    1024    // mem units to get from OS at once
#define MAX_ALLOC 10240   // max units to allocate
typedef double ALIGN; //on most systems if a double can start at an address, anything can, so we use double for alignment

typedef union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;
  ALIGN x;
} HEADER;

static HEADER base;
static HEADER *allocp = NULL;
static int max_allocated;

char *alloc_ex(unsigned nbytes);
static HEADER *morecore(unsigned nu);
void free_ex(char *ap);
void hexdump(const void *data, size_t size);
void ll_walk(HEADER *p);

main()
{
  int i = 50;
  char *p, *q;
  while (i-- > 0) {
    p = alloc_ex(10 * i);
    for (q=p; q-p < 10*i; q++)
      *q = 'A';
    printf("%p\n", p);
  }
  ll_walk(&base);
  return 0;
}

void ll_walk(HEADER *p)
{
  HEADER *q = p;

  do {
    printf("adr: %p size: %d next: %p\n", q, q->s.size, q->s.ptr);
    q = q->s.ptr;
  } while (q != p);
}

void hexdump(const void *data, size_t size)
{
  const unsigned char *byte_data = (const unsigned char *)data;
  size_t i, j;

  for (i = 0; i < size; i += 16) {
    // Check if the line is all zeros
    int all_zeros = 1;
    for (j = 0; j < 16 && i + j < size; j++) {
      if (byte_data[i + j] != 0) {
        all_zeros = 0;
        break;
      }
    }
    if (all_zeros) 
      continue;

    // Print address
    printf("0x%08zx: ", (size_t)(byte_data + i));
        
    // Print hex values
    for (j = 0; j < 16 && i + j < size; j++)
      printf("%02x ", byte_data[i + j]);
        
    // Print ASCII characters
    printf(" ");
    for (j = 0; j < 16 && i + j < size; j++) {
      unsigned char c = byte_data[i + j];
      if (c >= 32 && c <= 126)
        printf("%c", c);
      else
        printf(".");
    }
    printf("\n");
  }
}

char *alloc_ex(unsigned nbytes) 
{
  register HEADER *p, *q;
  register int nunits;

  if (nbytes > MAX_ALLOC) {
    fprintf(stderr, "alloc_ex: Can't allocate more than %d bytes\n", MAX_ALLOC);
    return NULL;
  }
  nunits = 1 + (nbytes + sizeof(HEADER) - 1) / sizeof(HEADER);

  if ((q = allocp) == NULL) {
    base.s.ptr = allocp = q = &base;
    base.s.size = 0;
  }  

  for (p = q->s.ptr; ; q=p, p=p->s.ptr) {
    if (p->s.size >= nunits) { // big enough
      if (p->s.size == nunits) { //exactly
        q->s.ptr = p->s.ptr;
      } else { // allocate tail end
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      allocp = q;
      return ((char *)(p+1));
    }
    if (p == allocp) // wrapped around free list
      if ((p = morecore(nunits)) == NULL)
        return NULL; // None left
  }
} 

static HEADER *morecore(unsigned nu) /* ask system for memory */
{
  register char *cp;
  register HEADER *up;
  register int rnu;

  rnu = NALLOC * ((nu+NALLOC-1) / NALLOC);
  cp = sbrk (rnu * sizeof(HEADER));
  if ((int)cp == -1) /* no space at all */
    return(NULL);
  up = (HEADER *)cp;
  up->s.size = rnu;
  max_allocated = up->s.size > max_allocated ? up->s.size : max_allocated;
  free_ex ((char *)(up+1));
  return(allocp);
}

void free_ex(char *ap) /* put block ap in free list */
{
  register HEADER *p, *q;
  
  
  p = (HEADER *)ap - 1; /* point to header */
  if (p->s.size == 0 || p->s.size > max_allocated) {
    fprintf(stderr, "free_ex: can't free %u units", p->s.size); 
    return;
  }
  for (q=allocp; !(p > q && p < q->s.ptr); q=q->s.ptr)
    if (q >= q->s.ptr && (p > q || p < q->s.ptr))
      break; /* at one end or other */

  if (p+p->s.size == q->s.ptr) { /* join to upper nbr */
    p->s.size += q->s.ptr->s.size;
    p->s.ptr = q->s.ptr->s.ptr;
  } else
    p->s.ptr = q->s.ptr;
  if (q+q->s.size == p) { /* join to lower nbr */
    q->s.size += p->s.size;
    q->s.ptr = p->s.ptr;
  } else
    q->s.ptr = p;
  allocp = q;
}
