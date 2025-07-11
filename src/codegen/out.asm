SECTION .data
global_x             dq 12
global_y             dq 2.3450000286102295
global_z             dq 'A'
global_w             dq "hello this is a string example",0
global_q             dq 1
global_test_test     dq "akshay",0

SECTION .text
   global  main
   main:
       push rbp
       mov  rbp, rsp
       sub  rsp, 0
       xor rax, rax
       leave
       ret

SECTION .bss
SECTION .note.GNU-stack
