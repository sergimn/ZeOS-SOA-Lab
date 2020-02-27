#include <asm.h>

ENTRY(write)
    pushl %ebp
    mov %esp, %ebp
    pushl %ecx # Needed so 'sysexit' runs with success
    pushl %edx # Same as above
    mov 0x08(%ebp), %ebx # fd
    mov 0x0c(%ebp), %ecx # buffer
    mov 0x10(%ebp), %edx # size

    mov $0x04, %eax # Tells that we will access the 4th position in the sys_call_table

    pushl $write_return # Fake dyn. link for the handler
    pushl %ebp # Same as above
    mov %esp, %ebp # Same as above
    sysenter

write_return:
    popl %ebp
    add $0x4, %esp # Handles the return addres in the stack. We could use a 'pop' instruction too
    popl %edx
    popl %ecx
    popl %ebp
    ret