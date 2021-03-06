#ifndef STACK_H
#define STACK_H

#include <string.h> /* memcpy */

/* These PUSH and POP macros are designed to work with any data. If you are using a
 * rvalue, then you either have to create an explicit variable, or pass its datatype to
 * the push function. It is expected that when calling this macro, esp is in scope and
 * is of type *uint8_t. It may be a pointer to something else, but then its behavior is
 * undefined. PUSH_2 is used to convert rvalues to lvalues. If you are using an lvalue,
 * specifying the type of the value you want to push has no effect, unless you accidentally
 * mention the wrong type.
 * 
 * MACRO SAFETY:
 * It is safe to use these macros in a single-line if statement or while loop.
 * The macro is an if statement itself, so you can't assign to it or have it
 * assign to anything. You also can't use it in an expression.
 */

#define POP(val) if (1) {             \
    memcpy (&val, esp, sizeof(val));  \
    esp += sizeof(val);               \
    } else (void) 0

#define PUSH_1(val) if (1) {          \
    esp -= sizeof(val);               \
    memcpy (esp, &val, sizeof(val));  \
    } else (void) 0

#define PUSH_2(T, val) if (1) {       \
    T tmp = val;                      \
    esp -= sizeof(tmp);               \
    memcpy (esp, &tmp, sizeof(tmp));  \
    } else (void) 0

#define PEEK(val)                     \
    memcpy (&val, esp, sizeof(val))   \

#define FIND_PUSH(A, B, FUNC, ...) FUNC
#define PUSH(...)             \
    FIND_PUSH(__VA_ARGS__,    \
        PUSH_2(__VA_ARGS__),  \
        PUSH_1(__VA_ARGS__))

inline void dump_stack () {
  char *addr;
  char *str = NULL;
  uint64_t diff = (uint64_t) top - (uint64_t) esp;
  
  printf ("%d bytes written\n", (int) diff);
  printf ("\nAddress        Hex    Dec    Char\n");
  for (uint64_t i = 1; i <= diff; i++) {
    
    if (i != 0 && i % sizeof(uint64_t) == 0) { 
      memcpy (&addr, &top[-i], sizeof(addr));
      str = (char*) addr;
      printf ("%p \t0x%02x \t%d \t%c\t%p\t\n\n",
        &top[-i], top[-i], top[-i], (top[-i] > 128 ? top[-i]:' '), (char*) addr);
        
    } else printf ("%p \t0x%02x \t%d \t%c \n",
        &top[-i], top[-i], top[-i], (top[-i] > 128 ? top[-i]:' '));
  }
  
  printf ("Stack dump complete.\n");
}

#endif