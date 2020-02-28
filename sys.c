/*
 * sys.c - Syscalls implementation
 */
#include <devices.h>

#include <utils.h>

#include <io.h>

#include <mm.h>

#include <mm_address.h>

#include <sched.h>

#define LECTURA 0
#define ESCRIPTURA 1

int check_fd(int fd, int permissions)
{
  if (fd!=1) return -9; /*EBADF*/
  if (permissions!=ESCRIPTURA) return -13; /*EACCES*/
  return 0;
}

int sys_ni_syscall()
{
	return -38; /*ENOSYS*/
}

int sys_getpid()
{
	return current()->PID;
}

int sys_fork()
{
  int PID=-1;

  // creates the child process
  
  return PID;
}

void sys_exit()
{  
}

#define K_BUFFER_SIZE 256
char kern_buffer [K_BUFFER_SIZE];

int sys_write(int fd, char * buffer, int size)
//fd: file descriptor. In this delivery it must always be 1.
//buffer: pointer to the bytes.
//size: number of bytes.
//return Negative number in case of error (specifying the kind of error) and the number of bytes written if OK.
{
  int is_fd_error=check_fd(fd, ESCRIPTURA);
  if (is_fd_error) return is_fd_error;
  if (buffer==NULL) return -14;  //This value is EFAULT. Will be replaced later
  if (size<0) return -22;        //This value is EINVAL. Will be replaced later

  int bytes_left=size;
  int ret;
  while (bytes_left>K_BUFFER_SIZE)
  {
    copy_from_user(buffer+(size-bytes_left), kern_buffer, K_BUFFER_SIZE);
    ret=sys_write_console(kern_buffer, K_BUFFER_SIZE);
    bytes_left-=ret;
  }
  copy_from_user(buffer+(size-bytes_left), kern_buffer, bytes_left);
  ret=sys_write_console(kern_buffer, bytes_left);
  bytes_left-=ret;
  return size-bytes_left;

}
