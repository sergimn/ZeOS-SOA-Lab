/*
 * io.c - 
 */

#include <io.h>

#include <types.h>

/**************/
/** Screen  ***/
/**************/

#define NUM_COLUMNS 80
#define NUM_ROWS    25

Byte x, y=19;
Word *screen = (Word *)0xb8000;

/* Read a byte from 'port' */
Byte inb (unsigned short port)
{
  Byte v;

  __asm__ __volatile__ ("inb %w1,%0":"=a" (v):"Nd" (port));
  return v;
}

void scroll_screen()
{
  /* This function will move every line in the current screen one
   * position upwards and leave the last line blank ready to write on it
   */
  Word blank_char = (Word) (' ' & 0x00FF) | 0x0200;
  for (int i = 0; i < NUM_ROWS - 1; i++) // The treatment for the last line will be different
  {
    for (int j = 0; j < NUM_COLUMNS; ++j)
    {
      screen[(i * NUM_COLUMNS + j)] = screen[((i + 1) * NUM_COLUMNS + j)];
      //Moving all lines up one position except the last one
    }
  }
  for (int i = 0; i < NUM_COLUMNS; ++i)
  {
    screen[((NUM_ROWS - 1) * NUM_COLUMNS + i)] = blank_char;
  }
}

void check_scroll_need_and_apply()
{
  if (y + 1 == NUM_ROWS)
  {
    scroll_screen ();
  }
  else
  {
    y++;
  }
}

void printc(char c)
{
     __asm__ __volatile__ ( "movb %0, %%al; outb $0xe9" ::"a"(c)); /* Magic BOCHS debug: writes 'c' to port 0xe9 */
  if (c=='\n')
  {
    x = 0;
    check_scroll_need_and_apply();
  }
  else
  {
    Word ch = (Word) (c & 0x00FF) | 0x0200;
	screen[(y * NUM_COLUMNS + x)] = ch;
    if (++x >= NUM_COLUMNS)
    {
      x = 0;
      y=(y+1)%NUM_ROWS;
    }
  }
}

void printc_color(char c, char color)
/* The 'color' variable indicates the foreground and background color the character is
 * going to have. To be more specific, the 4 bits with less weight set the foreground
 * color and the 4 bits with the more weigh set the background color. i.e: the value
 * 0x41 will display a blue character with a red background. Some values can make the
 * character blink.
 */
{
  __asm__ __volatile__ ( "movb %0, %%al; outb $0xe9" ::"a"(c)); /* Magic BOCHS debug: writes 'c' to port 0xe9 */
  if (c=='\n')
  {
    x = 0;
    check_scroll_need_and_apply();
  }
  else
  {
    Word ch = (Word) (c & 0x00FF) | (Word) (color << 8); // The color is added just modifying the last part of this line
    screen[(y * NUM_COLUMNS + x)] = ch;
    if (++x >= NUM_COLUMNS)
    {
      x = 0;
      y=(y+1)%NUM_ROWS;
    }
  }
}

void printc_xy(Byte mx, Byte my, char c)
{
  Byte cx, cy;
  cx=x;
  cy=y;
  x=mx;
  y=my;
  printc(c);
  x=cx;
  y=cy;
}

void printk(char *string)
{
  int i;
  for (i = 0; string[i]; i++)
    printc_color(string[i], 0x41);
}
