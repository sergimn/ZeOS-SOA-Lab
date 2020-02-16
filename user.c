#include <libc.h>

char buff[24];

int pid;

int add(int a, int b)
{
    return a + b;
}

int addASM(int, int);

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */


  while(1)
  {
    int a = add(0x42, 0x666);
    int b = addASM (a, 0x1);
  }
}
