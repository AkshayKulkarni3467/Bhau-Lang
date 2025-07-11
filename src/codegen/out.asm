SECTION .data
global_x             dq 12
global_y             dq 2.3450000286102295
global_z             dq 'A'
global_w             dq "hello this is a string example",0
global_q             dq 1
global_point         dq -2.3450000286102295

SECTION .bss
global_akshay resq 1
global_jkkk resq 1

SECTION .text
global  main
extern printf
extern scanf
main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 0
    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack
