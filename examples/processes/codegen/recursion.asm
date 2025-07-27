SECTION .data

SECTION .bss

SECTION .text
global  main
extern printf
factorial:
    push rbp
    mov  rbp, rsp
    sub  rsp, 128
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 1
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L0
    jmp .L1
    .L0:
    mov QWORD [rbp - 112], 1
    mov rax, QWORD [rbp - 112]
    leave
    ret
    .L1:
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 1
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    sub rax,rbx
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 64], rax
    mov rdi, QWORD [rbp - 64]
    mov QWORD [rbp - 72], 0
    xor rax,rax
    call factorial
    mov QWORD [rbp - 72],rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    imul rax,rbx
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    leave
    ret
fibonacci:
    push rbp
    mov  rbp, rsp
    sub  rsp, 160
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 1
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L2
    jmp .L3
    .L2:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 152], rax
    mov rax, QWORD [rbp - 152]
    leave
    ret
    .L3:
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 1
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    sub rax,rbx
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 64], rax
    mov rdi, QWORD [rbp - 64]
    mov QWORD [rbp - 72], 0
    xor rax,rax
    call fibonacci
    mov QWORD [rbp - 72],rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 96], 2
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    sub rax,rbx
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 104], rax
    mov rdi, QWORD [rbp - 104]
    mov QWORD [rbp - 112], 0
    xor rax,rax
    call fibonacci
    mov QWORD [rbp - 112],rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 136], rax
    mov rax, QWORD [rbp - 128]
    mov rbx, QWORD [rbp - 136]
    add rax,rbx
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 144]
    leave
    ret
print_recursion_tests:
    push rbp
    mov  rbp, rsp
    sub  rsp, 160
    mov QWORD [rbp - 8], 5
    mov rdi, QWORD [rbp - 8]
    mov QWORD [rbp - 16], 0
    xor rax,rax
    call factorial
    mov QWORD [rbp - 16],rax
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 24], rax
    lea rax, [rbp - 48]
    mov QWORD [rbp - 56], rax
    mov byte [rbp - 48], 'F'
    mov byte [rbp - 47], 'a'
    mov byte [rbp - 46], 'c'
    mov byte [rbp - 45], 't'
    mov byte [rbp - 44], 'o'
    mov byte [rbp - 43], 'r'
    mov byte [rbp - 42], 'i'
    mov byte [rbp - 41], 'a'
    mov byte [rbp - 40], 'l'
    mov byte [rbp - 39], ' '
    mov byte [rbp - 38], ':'
    mov byte [rbp - 37], ' '
    mov byte [rbp - 36], '%'
    mov byte [rbp - 35], 'd'
    mov byte [rbp - 34], 0x0A
    mov byte [rbp - 33], 0
    mov rdi, QWORD [rbp - 56]
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 64], rax
    mov rsi, QWORD [rbp - 64]
    mov QWORD [rbp - 72], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 72],rax
    mov QWORD [rbp - 80], 5
    mov rdi, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 0
    xor rax,rax
    call fibonacci
    mov QWORD [rbp - 88],rax
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 96], rax
    lea rax, [rbp - 120]
    mov QWORD [rbp - 128], rax
    mov byte [rbp - 120], 'F'
    mov byte [rbp - 119], 'i'
    mov byte [rbp - 118], 'b'
    mov byte [rbp - 117], 'o'
    mov byte [rbp - 116], 'n'
    mov byte [rbp - 115], 'a'
    mov byte [rbp - 114], 'c'
    mov byte [rbp - 113], 'c'
    mov byte [rbp - 112], 'i'
    mov byte [rbp - 111], ' '
    mov byte [rbp - 110], ':'
    mov byte [rbp - 109], ' '
    mov byte [rbp - 108], '%'
    mov byte [rbp - 107], 'd'
    mov byte [rbp - 106], 0x0A
    mov byte [rbp - 105], 0
    mov rdi, QWORD [rbp - 128]
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 136], rax
    mov rsi, QWORD [rbp - 136]
    mov QWORD [rbp - 144], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 144],rax
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 16
    mov QWORD [rbp - 8], 0
    xor rax,rax
    call print_recursion_tests
    mov QWORD [rbp - 8],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack
