SECTION .data

SECTION .bss

SECTION .text
global  main
extern printf
float_control_flow:
    push rbp
    mov  rbp, rsp
    sub  rsp, 160
    mov rax, 0x40091eb860000000
    movq xmm7, rax
    movsd QWORD [rbp - 8], xmm7
    mov rax, 0x4005ae1480000000
    movq xmm7, rax
    movsd QWORD [rbp - 16], xmm7
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 24], xmm7
    mov rax, 0
    cmp rax, 0
    jne .L0
    mov rax, 0x4017666680000000
    movq xmm0, rax
    movsd QWORD [rbp - 24], xmm0
    jmp .L1
    .L0:
    mov rax, 0xbfdb851f00000000
    movq xmm0, rax
    movsd QWORD [rbp - 24], xmm0
    .L1:
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 40], rax
    mov QWORD [rbp - 48], 0
    mov rax, 0x4014000000000000
    movq xmm0, rax
    movsd QWORD [rbp - 48], xmm0
    movsd xmm0, QWORD [rbp - 40]
    movsd xmm1, QWORD [rbp - 48]
    ucomisd xmm0,xmm1
    seta al
    movzx rax,al
    mov QWORD [rbp - 32], rax
    mov rax, QWORD [rbp - 32]
    cmp rax, 0
    jne .L2
    jmp .L3
    .L2:
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov rax, 0x4000000000000000
    movq xmm0, rax
    movsd QWORD [rbp - 72], xmm0
    movsd xmm0, QWORD [rbp - 64]
    movsd xmm1, QWORD [rbp - 72]
    mulsd xmm0,xmm1
    movsd QWORD [rbp - 56],xmm0
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 80], rax
    lea rax, [rbp - 120]
    mov QWORD [rbp - 128], rax
    mov byte [rbp - 120], 'F'
    mov byte [rbp - 119], 'r'
    mov byte [rbp - 118], 'o'
    mov byte [rbp - 117], 'm'
    mov byte [rbp - 116], ' '
    mov byte [rbp - 115], 'f'
    mov byte [rbp - 114], 'l'
    mov byte [rbp - 113], 'o'
    mov byte [rbp - 112], 'a'
    mov byte [rbp - 111], 't'
    mov byte [rbp - 110], '_'
    mov byte [rbp - 109], 'c'
    mov byte [rbp - 108], 'o'
    mov byte [rbp - 107], 'n'
    mov byte [rbp - 106], 't'
    mov byte [rbp - 105], 'r'
    mov byte [rbp - 104], 'o'
    mov byte [rbp - 103], 'l'
    mov byte [rbp - 102], '_'
    mov byte [rbp - 101], 'f'
    mov byte [rbp - 100], 'l'
    mov byte [rbp - 99], 'o'
    mov byte [rbp - 98], 'w'
    mov byte [rbp - 97], ','
    mov byte [rbp - 96], ' '
    mov byte [rbp - 95], 'V'
    mov byte [rbp - 94], 'a'
    mov byte [rbp - 93], 'l'
    mov byte [rbp - 92], 'u'
    mov byte [rbp - 91], 'e'
    mov byte [rbp - 90], ' '
    mov byte [rbp - 89], ':'
    mov byte [rbp - 88], ' '
    mov byte [rbp - 87], '%'
    mov byte [rbp - 86], '.'
    mov byte [rbp - 85], '2'
    mov byte [rbp - 84], 'f'
    mov byte [rbp - 83], 0x0A
    mov byte [rbp - 82], 0
    mov rdi, QWORD [rbp - 128]
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 136], rax
    movq xmm0, QWORD [rbp - 136]
    mov QWORD [rbp - 144], 0
    mov rax, 1
    call printf
    mov QWORD [rbp - 144],rax
    .L3:
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 48
    mov QWORD [rbp - 8], 0
    xor rax,rax
    call float_control_flow
    mov QWORD [rbp - 8],rax
    lea rax, [rbp - 16]
    mov QWORD [rbp - 24], rax
    mov byte [rbp - 16], 0x0A
    mov byte [rbp - 15], 0
    mov rdi, QWORD [rbp - 24]
    mov QWORD [rbp - 32], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 32],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack
