#include <libc.h>
#include <types.h>

char buff[24];

int pid;

int add(int a, int b)
{
    return a + b;
}

int addASM(int, int);

#define NUM_COLUMNS 80
#define NUM_ROWS    25

Byte x, y=19;

void printc(char c)
{
  __asm__ __volatile__ ( "movb %0, %%al; outb $0xe9" ::"a"(c)); /* Magic BOCHS debug: writes 'c' to port 0xe9 */
  if (c=='\n')
  {
    x = 0;
    y=(y+1)%NUM_ROWS;
  }
  else
  {
    Word ch = (Word) (c & 0x00FF) | 0x0200;
    Word *screen = (Word *)0xb8000;
    screen[(y * NUM_COLUMNS + x)] = ch;
    if (++x >= NUM_COLUMNS)
    {
      x = 0;
      y=(y+1)%NUM_ROWS;
    }
  }
}

void printk(char *string)
{
  int i;
  for (i = 0; string[i]; i++)
    printc(string[i]);
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */


  while(1)
  {
    int a = add(0x42, 0x666);
    int b = addASM (a, 0x1);
    printk ("This shouldn\'t  work"); /* This call will throw a Page Fault exception because we are trying to acces the
                                         mem region near 0xb8000 (we have to take into account the offset of the variable y).
                                         This region in memory is the region related to the screen but is protected by the mmu*/
  }
}
