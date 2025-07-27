SECTION .data
global_x             dq "declared in global",0

SECTION .bss

SECTION .text
global  main
extern printf
print_global:
    push rbp
    mov  rbp, rsp
    sub  rsp, 64
    lea rax, [rbp - 24]
    mov QWORD [rbp - 32], rax
    mov byte [rbp - 24], 'F'
    mov byte [rbp - 23], 'r'
    mov byte [rbp - 22], 'o'
    mov byte [rbp - 21], 'm'
    mov byte [rbp - 20], ' '
    mov byte [rbp - 19], 'p'
    mov byte [rbp - 18], 'r'
    mov byte [rbp - 17], 'i'
    mov byte [rbp - 16], 'n'
    mov byte [rbp - 15], 't'
    mov byte [rbp - 14], '_'
    mov byte [rbp - 13], 'g'
    mov byte [rbp - 12], 'l'
    mov byte [rbp - 11], 'o'
    mov byte [rbp - 10], 'b'
    mov byte [rbp - 9], 'a'
    mov byte [rbp - 8], 'l'
    mov byte [rbp - 7], ':'
    mov byte [rbp - 6], ' '
    mov byte [rbp - 5], '%'
    mov byte [rbp - 4], 's'
    mov byte [rbp - 3], 0x0A
    mov byte [rbp - 2], 0
    mov rdi, QWORD [rbp - 32]
    mov rax, global_x
    mov QWORD [rbp - 40], rax
    mov rsi, QWORD [rbp - 40]
    mov QWORD [rbp - 48], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 48],rax
    leave
    ret

print_infunc:
    push rbp
    mov  rbp, rsp
    sub  rsp, 96
    lea rax, [rbp - 24]
    mov QWORD [rbp - 32], rax
    mov byte [rbp - 24], 'd'
    mov byte [rbp - 23], 'e'
    mov byte [rbp - 22], 'c'
    mov byte [rbp - 21], 'l'
    mov byte [rbp - 20], 'a'
    mov byte [rbp - 19], 'r'
    mov byte [rbp - 18], 'e'
    mov byte [rbp - 17], 'd'
    mov byte [rbp - 16], ' '
    mov byte [rbp - 15], 'i'
    mov byte [rbp - 14], 'n'
    mov byte [rbp - 13], ' '
    mov byte [rbp - 12], 'f'
    mov byte [rbp - 11], 'u'
    mov byte [rbp - 10], 'n'
    mov byte [rbp - 9], 'c'
    mov byte [rbp - 8], 't'
    mov byte [rbp - 7], 'i'
    mov byte [rbp - 6], 'o'
    mov byte [rbp - 5], 'n'
    mov byte [rbp - 4], 0
    lea rax, [rbp - 56]
    mov QWORD [rbp - 64], rax
    mov byte [rbp - 56], 'F'
    mov byte [rbp - 55], 'r'
    mov byte [rbp - 54], 'o'
    mov byte [rbp - 53], 'm'
    mov byte [rbp - 52], ' '
    mov byte [rbp - 51], 'p'
    mov byte [rbp - 50], 'r'
    mov byte [rbp - 49], 'i'
    mov byte [rbp - 48], 'n'
    mov byte [rbp - 47], 't'
    mov byte [rbp - 46], '_'
    mov byte [rbp - 45], 'i'
    mov byte [rbp - 44], 'n'
    mov byte [rbp - 43], 'f'
    mov byte [rbp - 42], 'u'
    mov byte [rbp - 41], 'n'
    mov byte [rbp - 40], 'c'
    mov byte [rbp - 39], ':'
    mov byte [rbp - 38], ' '
    mov byte [rbp - 37], '%'
    mov byte [rbp - 36], 's'
    mov byte [rbp - 35], 0x0A
    mov byte [rbp - 34], 0
    mov rdi, QWORD [rbp - 64]
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 72], rax
    mov rsi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 80],rax
    leave
    ret

print_inblock:
    push rbp
    mov  rbp, rsp
    sub  rsp, 128
    lea rax, [rbp - 24]
    mov QWORD [rbp - 32], rax
    mov byte [rbp - 24], 'd'
    mov byte [rbp - 23], 'e'
    mov byte [rbp - 22], 'c'
    mov byte [rbp - 21], 'l'
    mov byte [rbp - 20], 'a'
    mov byte [rbp - 19], 'r'
    mov byte [rbp - 18], 'e'
    mov byte [rbp - 17], 'd'
    mov byte [rbp - 16], ' '
    mov byte [rbp - 15], 'i'
    mov byte [rbp - 14], 'n'
    mov byte [rbp - 13], ' '
    mov byte [rbp - 12], 'f'
    mov byte [rbp - 11], 'u'
    mov byte [rbp - 10], 'n'
    mov byte [rbp - 9], 'c'
    mov byte [rbp - 8], ' '
    mov byte [rbp - 7], 's'
    mov byte [rbp - 6], 'c'
    mov byte [rbp - 5], 'o'
    mov byte [rbp - 4], 'p'
    mov byte [rbp - 3], 'e'
    mov byte [rbp - 2], 0
    mov rax, 1
    cmp rax, 0
    jne .L0
    jmp .L1
    .L0:
    lea rax, [rbp - 56]
    mov QWORD [rbp - 64], rax
    mov byte [rbp - 56], 'd'
    mov byte [rbp - 55], 'e'
    mov byte [rbp - 54], 'c'
    mov byte [rbp - 53], 'l'
    mov byte [rbp - 52], 'a'
    mov byte [rbp - 51], 'r'
    mov byte [rbp - 50], 'e'
    mov byte [rbp - 49], 'd'
    mov byte [rbp - 48], ' '
    mov byte [rbp - 47], 'i'
    mov byte [rbp - 46], 'n'
    mov byte [rbp - 45], ' '
    mov byte [rbp - 44], 'b'
    mov byte [rbp - 43], 'l'
    mov byte [rbp - 42], 'o'
    mov byte [rbp - 41], 'c'
    mov byte [rbp - 40], 'k'
    mov byte [rbp - 39], ' '
    mov byte [rbp - 38], 's'
    mov byte [rbp - 37], 'c'
    mov byte [rbp - 36], 'o'
    mov byte [rbp - 35], 'p'
    mov byte [rbp - 34], 'e'
    mov byte [rbp - 33], 0
    lea rax, [rbp - 96]
    mov QWORD [rbp - 104], rax
    mov byte [rbp - 96], 'F'
    mov byte [rbp - 95], 'r'
    mov byte [rbp - 94], 'o'
    mov byte [rbp - 93], 'm'
    mov byte [rbp - 92], ' '
    mov byte [rbp - 91], 'p'
    mov byte [rbp - 90], 'r'
    mov byte [rbp - 89], 'i'
    mov byte [rbp - 88], 'n'
    mov byte [rbp - 87], 't'
    mov byte [rbp - 86], '_'
    mov byte [rbp - 85], 'i'
    mov byte [rbp - 84], 'n'
    mov byte [rbp - 83], 'b'
    mov byte [rbp - 82], 'l'
    mov byte [rbp - 81], 'o'
    mov byte [rbp - 80], 'c'
    mov byte [rbp - 79], 'k'
    mov byte [rbp - 78], ':'
    mov byte [rbp - 77], ' '
    mov byte [rbp - 76], '%'
    mov byte [rbp - 75], 's'
    mov byte [rbp - 74], 0x0A
    mov byte [rbp - 73], 0
    mov rdi, QWORD [rbp - 104]
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 112], rax
    mov rsi, QWORD [rbp - 112]
    mov QWORD [rbp - 120], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 120],rax
    .L1:
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    mov QWORD [rbp - 8], 0
    xor rax,rax
    call print_global
    mov QWORD [rbp - 8],rax
    mov QWORD [rbp - 16], 0
    xor rax,rax
    call print_infunc
    mov QWORD [rbp - 16],rax
    mov QWORD [rbp - 24], 0
    xor rax,rax
    call print_inblock
    mov QWORD [rbp - 24],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack
