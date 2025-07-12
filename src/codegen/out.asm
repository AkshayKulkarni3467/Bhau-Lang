SECTION .data
global_x             dq 12
global_y             dq 2.3450000286102295
global_test_str      dq "hello this is a test string",0

SECTION .bss
global_test1 resq 1

SECTION .text
global  main
extern printf
extern scanf
main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    mov byte [rbp - 24], 'h'
    mov byte [rbp - 23], 'e'
    mov byte [rbp - 22], 'l'
    mov byte [rbp - 21], 'l'
    mov byte [rbp - 20], 'o'
    mov byte [rbp - 19], 0x0A
    mov byte [rbp - 18], 'n'
    mov byte [rbp - 17], 't'
    mov byte [rbp - 16], 'h'
    mov byte [rbp - 15], 'i'
    mov byte [rbp - 14], 's'
    mov byte [rbp - 13], 0

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack
