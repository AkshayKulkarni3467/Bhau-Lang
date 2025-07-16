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
recurse_sum:
    push rbp
    mov  rbp, rsp
    sub  rsp, 128
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L4
    jmp .L5
    .L4:
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 112]
    leave
    ret
    .L5:
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
    call recurse_sum
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
    add rax,rbx
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    leave
    ret
inv_digits:
    push rbp
    mov  rbp, rsp
    sub  rsp, 160
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L6
    jmp .L7
    .L6:
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 144]
    leave
    ret
    .L7:
    lea rax, [rbp - 40]
    mov QWORD [rbp - 48], rax
    mov byte [rbp - 40], '%'
    mov byte [rbp - 39], 'd'
    mov byte [rbp - 38], ' '
    mov byte [rbp - 37], 0
    mov rdi, QWORD [rbp - 48]
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 72], 10
    mov rax, QWORD [rbp - 64]
    mov rbx, QWORD [rbp - 72]
    cqo
    idiv rbx
    mov QWORD [rbp - 56],rdx
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 80], rax
    mov rsi, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 88],rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 112], 10
    mov rax, QWORD [rbp - 104]
    mov rbx, QWORD [rbp - 112]
    cqo
    idiv rbx
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 120], rax
    mov rdi, QWORD [rbp - 120]
    mov QWORD [rbp - 128], 0
    xor rax,rax
    call inv_digits
    mov QWORD [rbp - 128],rax
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 136], rax
    mov rax, QWORD [rbp - 136]
    leave
    ret
power:
    push rbp
    mov  rbp, rsp
    sub  rsp, 144
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], rsi
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L8
    jmp .L9
    .L8:
    mov QWORD [rbp - 128], 1
    mov rax, QWORD [rbp - 128]
    leave
    ret
    .L9:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov rdi, QWORD [rbp - 48]
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 72], 1
    mov rax, QWORD [rbp - 64]
    mov rbx, QWORD [rbp - 72]
    sub rax,rbx
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 80], rax
    mov rsi, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 0
    xor rax,rax
    call power
    mov QWORD [rbp - 88],rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 112], rax
    mov rax, QWORD [rbp - 104]
    mov rbx, QWORD [rbp - 112]
    imul rax,rbx
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 120]
    leave
    ret
reverse:
    push rbp
    mov  rbp, rsp
    sub  rsp, 192
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], rsi
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L10
    jmp .L11
    .L10:
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 176], rax
    mov rax, QWORD [rbp - 176]
    leave
    ret
    .L11:
    mov QWORD [rbp - 48], 0
    mov QWORD [rbp - 56], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 56], rax
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 64], 10
    mov rax, QWORD [rbp - 56]
    mov rbx, QWORD [rbp - 64]
    cqo
    idiv rbx
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 72], rax
    mov rdi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 96], 10
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    imul rax,rbx
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 120], 10
    mov rax, QWORD [rbp - 112]
    mov rbx, QWORD [rbp - 120]
    cqo
    idiv rbx
    mov QWORD [rbp - 104],rdx
    mov QWORD [rbp - 128], 0
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 136], rax
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 136]
    mov rbx, QWORD [rbp - 144]
    add rax,rbx
    mov QWORD [rbp - 128], rax
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 152], rax
    mov rsi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 0
    xor rax,rax
    call reverse
    mov QWORD [rbp - 160],rax
    mov rax, QWORD [rbp - 160]
    mov QWORD [rbp - 168], rax
    mov rax, QWORD [rbp - 168]
    leave
    ret
is_palindrome:
    push rbp
    mov  rbp, rsp
    sub  rsp, 224
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], rsi
    mov QWORD [rbp - 24], rdx
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 40], rax
    mov QWORD [rbp - 48], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 40]
    mov rbx, QWORD [rbp - 48]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 32], rax
    mov rax, QWORD [rbp - 32]
    cmp rax, 0
    jne .L12
    jmp .L13
    .L12:
    mov QWORD [rbp - 192], 0
    mov QWORD [rbp - 200], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 200], rax
    mov QWORD [rbp - 208], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 208], rax
    mov rax, QWORD [rbp - 200]
    mov rbx, QWORD [rbp - 208]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 192], rax
    mov rax, QWORD [rbp - 192]
    mov QWORD [rbp - 216], rax
    mov rax, QWORD [rbp - 216]
    leave
    ret
    .L13:
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 72], 10
    mov rax, QWORD [rbp - 64]
    mov rbx, QWORD [rbp - 72]
    cqo
    idiv rbx
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 80], rax
    mov rdi, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 104], 10
    mov rax, QWORD [rbp - 96]
    mov rbx, QWORD [rbp - 104]
    imul rax,rbx
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 120], rax
    mov QWORD [rbp - 128], 0
    mov QWORD [rbp - 128], 10
    mov rax, QWORD [rbp - 120]
    mov rbx, QWORD [rbp - 128]
    cqo
    idiv rbx
    mov QWORD [rbp - 112],rdx
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 144], rax
    mov QWORD [rbp - 152], 0
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 152], rax
    mov rax, QWORD [rbp - 144]
    mov rbx, QWORD [rbp - 152]
    add rax,rbx
    mov QWORD [rbp - 136], rax
    mov rax, QWORD [rbp - 136]
    mov QWORD [rbp - 160], rax
    mov rsi, QWORD [rbp - 160]
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 168], rax
    mov rdx, QWORD [rbp - 168]
    mov QWORD [rbp - 176], 0
    xor rax,rax
    call is_palindrome
    mov QWORD [rbp - 176],rax
    mov rax, QWORD [rbp - 176]
    mov QWORD [rbp - 184], rax
    mov rax, QWORD [rbp - 184]
    leave
    ret
gcd:
    push rbp
    mov  rbp, rsp
    sub  rsp, 112
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], rsi
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L14
    jmp .L15
    .L14:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    leave
    ret
    .L15:
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 48], rax
    mov rdi, QWORD [rbp - 48]
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 64]
    mov rbx, QWORD [rbp - 72]
    cqo
    idiv rbx
    mov QWORD [rbp - 56],rdx
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 80], rax
    mov rsi, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 0
    xor rax,rax
    call gcd
    mov QWORD [rbp - 88],rax
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 96]
    leave
    ret
print_stars:
    push rbp
    mov  rbp, rsp
    sub  rsp, 208
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L16
    jmp .L17
    .L16:
    lea rax, [rbp - 144]
    mov QWORD [rbp - 152], rax
    mov byte [rbp - 144], 0x0A
    mov byte [rbp - 143], 0
    mov rdi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 160],rax
    mov QWORD [rbp - 168], 0
    mov rax, QWORD [rbp - 168]
    leave
    ret
    .L17:
    mov QWORD [rbp - 40], 0
    .L18:
    mov QWORD [rbp - 48], 0
    mov QWORD [rbp - 56], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 56], rax
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 56]
    mov rbx, QWORD [rbp - 64]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    cmp rax, 0
    jne .L19
    jmp .L20
    .L19:
    lea rax, [rbp - 176]
    mov QWORD [rbp - 184], rax
    mov byte [rbp - 176], '*'
    mov byte [rbp - 175], ' '
    mov byte [rbp - 174], 0
    mov rdi, QWORD [rbp - 184]
    mov QWORD [rbp - 192], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 192],rax
    mov QWORD [rbp - 200], 0
    mov rax, [rbp - 40]
    inc rax
    mov [rbp - 200],rax
    mov rax, QWORD [rbp - 200]
    mov QWORD [rbp - 40], rax
    jmp .L18
    .L20:
    lea rax, [rbp - 72]
    mov QWORD [rbp - 80], rax
    mov byte [rbp - 72], 0x0A
    mov byte [rbp - 71], 0
    mov rdi, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 88],rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 112], 1
    mov rax, QWORD [rbp - 104]
    mov rbx, QWORD [rbp - 112]
    sub rax,rbx
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 120], rax
    mov rdi, QWORD [rbp - 120]
    mov QWORD [rbp - 128], 0
    xor rax,rax
    call print_stars
    mov QWORD [rbp - 128],rax
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 136], rax
    mov rax, QWORD [rbp - 136]
    leave
    ret
digit_sum:
    push rbp
    mov  rbp, rsp
    sub  rsp, 144
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L21
    jmp .L22
    .L21:
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 136]
    leave
    ret
    .L22:
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 10
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    cqo
    idiv rbx
    mov QWORD [rbp - 40],rdx
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 80], 10
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    cqo
    idiv rbx
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 88], rax
    mov rdi, QWORD [rbp - 88]
    mov QWORD [rbp - 96], 0
    xor rax,rax
    call digit_sum
    mov QWORD [rbp - 96],rax
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 112]
    mov rbx, QWORD [rbp - 120]
    add rax,rbx
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 128], rax
    mov rax, QWORD [rbp - 128]
    leave
    ret
print_recursion_tests:
    push rbp
    mov  rbp, rsp
    sub  rsp, 672
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
    mov QWORD [rbp - 152], 5
    mov rdi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 0
    xor rax,rax
    call recurse_sum
    mov QWORD [rbp - 160],rax
    mov rax, QWORD [rbp - 160]
    mov QWORD [rbp - 168], rax
    lea rax, [rbp - 192]
    mov QWORD [rbp - 200], rax
    mov byte [rbp - 192], 'R'
    mov byte [rbp - 191], 'e'
    mov byte [rbp - 190], 'c'
    mov byte [rbp - 189], 'u'
    mov byte [rbp - 188], 'r'
    mov byte [rbp - 187], 's'
    mov byte [rbp - 186], 'e'
    mov byte [rbp - 185], ' '
    mov byte [rbp - 184], 's'
    mov byte [rbp - 183], 'u'
    mov byte [rbp - 182], 'm'
    mov byte [rbp - 181], ' '
    mov byte [rbp - 180], ':'
    mov byte [rbp - 179], ' '
    mov byte [rbp - 178], '%'
    mov byte [rbp - 177], 'd'
    mov byte [rbp - 176], 0x0A
    mov byte [rbp - 175], 0
    mov rdi, QWORD [rbp - 200]
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 208], rax
    mov rsi, QWORD [rbp - 208]
    mov QWORD [rbp - 216], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 216],rax
    mov QWORD [rbp - 224], 5324
    mov rdi, QWORD [rbp - 224]
    mov QWORD [rbp - 232], 0
    xor rax,rax
    call inv_digits
    mov QWORD [rbp - 232],rax
    lea rax, [rbp - 240]
    mov QWORD [rbp - 248], rax
    mov byte [rbp - 240], 0x0A
    mov byte [rbp - 239], 0
    mov rdi, QWORD [rbp - 248]
    mov QWORD [rbp - 256], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 256],rax
    mov QWORD [rbp - 264], 5
    mov rdi, QWORD [rbp - 264]
    mov QWORD [rbp - 272], 2
    mov rsi, QWORD [rbp - 272]
    mov QWORD [rbp - 280], 0
    xor rax,rax
    call power
    mov QWORD [rbp - 280],rax
    mov rax, QWORD [rbp - 280]
    mov QWORD [rbp - 288], rax
    lea rax, [rbp - 304]
    mov QWORD [rbp - 312], rax
    mov byte [rbp - 304], 'P'
    mov byte [rbp - 303], 'o'
    mov byte [rbp - 302], 'w'
    mov byte [rbp - 301], 'e'
    mov byte [rbp - 300], 'r'
    mov byte [rbp - 299], ' '
    mov byte [rbp - 298], ':'
    mov byte [rbp - 297], ' '
    mov byte [rbp - 296], '%'
    mov byte [rbp - 295], 'd'
    mov byte [rbp - 294], 0x0A
    mov byte [rbp - 293], 0
    mov rdi, QWORD [rbp - 312]
    mov rax, QWORD [rbp - 288]
    mov QWORD [rbp - 320], rax
    mov rsi, QWORD [rbp - 320]
    mov QWORD [rbp - 328], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 328],rax
    mov QWORD [rbp - 336], 1234
    mov rdi, QWORD [rbp - 336]
    mov QWORD [rbp - 344], 0
    mov rsi, QWORD [rbp - 344]
    mov QWORD [rbp - 352], 0
    xor rax,rax
    call reverse
    mov QWORD [rbp - 352],rax
    mov rax, QWORD [rbp - 352]
    mov QWORD [rbp - 360], rax
    lea rax, [rbp - 376]
    mov QWORD [rbp - 384], rax
    mov byte [rbp - 376], 'R'
    mov byte [rbp - 375], 'e'
    mov byte [rbp - 374], 'v'
    mov byte [rbp - 373], 'e'
    mov byte [rbp - 372], 'r'
    mov byte [rbp - 371], 's'
    mov byte [rbp - 370], 'e'
    mov byte [rbp - 369], ' '
    mov byte [rbp - 368], ':'
    mov byte [rbp - 367], ' '
    mov byte [rbp - 366], '%'
    mov byte [rbp - 365], 'd'
    mov byte [rbp - 364], 0x0A
    mov byte [rbp - 363], 0
    mov rdi, QWORD [rbp - 384]
    mov rax, QWORD [rbp - 360]
    mov QWORD [rbp - 392], rax
    mov rsi, QWORD [rbp - 392]
    mov QWORD [rbp - 400], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 400],rax
    mov QWORD [rbp - 408], 1221
    mov rdi, QWORD [rbp - 408]
    mov QWORD [rbp - 416], 0
    mov rsi, QWORD [rbp - 416]
    mov QWORD [rbp - 424], 1221
    mov rdx, QWORD [rbp - 424]
    mov QWORD [rbp - 432], 0
    xor rax,rax
    call is_palindrome
    mov QWORD [rbp - 432],rax
    mov rax, QWORD [rbp - 432]
    mov QWORD [rbp - 440], rax
    lea rax, [rbp - 464]
    mov QWORD [rbp - 472], rax
    mov byte [rbp - 464], 'I'
    mov byte [rbp - 463], 's'
    mov byte [rbp - 462], ' '
    mov byte [rbp - 461], 'p'
    mov byte [rbp - 460], 'a'
    mov byte [rbp - 459], 'l'
    mov byte [rbp - 458], 'i'
    mov byte [rbp - 457], 'n'
    mov byte [rbp - 456], 'd'
    mov byte [rbp - 455], 'r'
    mov byte [rbp - 454], 'o'
    mov byte [rbp - 453], 'm'
    mov byte [rbp - 452], 'e'
    mov byte [rbp - 451], ' '
    mov byte [rbp - 450], ':'
    mov byte [rbp - 449], ' '
    mov byte [rbp - 448], '%'
    mov byte [rbp - 447], 'd'
    mov byte [rbp - 446], 0x0A
    mov byte [rbp - 445], 0
    mov rdi, QWORD [rbp - 472]
    mov rax, QWORD [rbp - 440]
    mov QWORD [rbp - 480], rax
    mov rsi, QWORD [rbp - 480]
    mov QWORD [rbp - 488], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 488],rax
    mov QWORD [rbp - 496], 39
    mov rdi, QWORD [rbp - 496]
    mov QWORD [rbp - 504], 26
    mov rsi, QWORD [rbp - 504]
    mov QWORD [rbp - 512], 0
    xor rax,rax
    call gcd
    mov QWORD [rbp - 512],rax
    mov rax, QWORD [rbp - 512]
    mov QWORD [rbp - 520], rax
    lea rax, [rbp - 544]
    mov QWORD [rbp - 552], rax
    mov byte [rbp - 544], 'G'
    mov byte [rbp - 543], 'C'
    mov byte [rbp - 542], 'D'
    mov byte [rbp - 541], ' '
    mov byte [rbp - 540], 'o'
    mov byte [rbp - 539], 'f'
    mov byte [rbp - 538], ' '
    mov byte [rbp - 537], '2'
    mov byte [rbp - 536], '6'
    mov byte [rbp - 535], ' '
    mov byte [rbp - 534], '&'
    mov byte [rbp - 533], ' '
    mov byte [rbp - 532], '3'
    mov byte [rbp - 531], '9'
    mov byte [rbp - 530], ' '
    mov byte [rbp - 529], ':'
    mov byte [rbp - 528], ' '
    mov byte [rbp - 527], '%'
    mov byte [rbp - 526], 'd'
    mov byte [rbp - 525], 0x0A
    mov byte [rbp - 524], 0
    mov rdi, QWORD [rbp - 552]
    mov rax, QWORD [rbp - 520]
    mov QWORD [rbp - 560], rax
    mov rsi, QWORD [rbp - 560]
    mov QWORD [rbp - 568], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 568],rax
    mov QWORD [rbp - 576], 10
    mov rdi, QWORD [rbp - 576]
    mov QWORD [rbp - 584], 0
    xor rax,rax
    call print_stars
    mov QWORD [rbp - 584],rax
    mov QWORD [rbp - 592], 1234
    mov rdi, QWORD [rbp - 592]
    mov QWORD [rbp - 600], 0
    xor rax,rax
    call digit_sum
    mov QWORD [rbp - 600],rax
    mov rax, QWORD [rbp - 600]
    mov QWORD [rbp - 608], rax
    lea rax, [rbp - 632]
    mov QWORD [rbp - 640], rax
    mov byte [rbp - 632], 'S'
    mov byte [rbp - 631], 'u'
    mov byte [rbp - 630], 'm'
    mov byte [rbp - 629], ' '
    mov byte [rbp - 628], 'o'
    mov byte [rbp - 627], 'f'
    mov byte [rbp - 626], ' '
    mov byte [rbp - 625], 'd'
    mov byte [rbp - 624], 'i'
    mov byte [rbp - 623], 'g'
    mov byte [rbp - 622], 'i'
    mov byte [rbp - 621], 't'
    mov byte [rbp - 620], 's'
    mov byte [rbp - 619], ' '
    mov byte [rbp - 618], ':'
    mov byte [rbp - 617], ' '
    mov byte [rbp - 616], '%'
    mov byte [rbp - 615], 'd'
    mov byte [rbp - 614], 0x0A
    mov byte [rbp - 613], 0
    mov rdi, QWORD [rbp - 640]
    mov rax, QWORD [rbp - 608]
    mov QWORD [rbp - 648], rax
    mov rsi, QWORD [rbp - 648]
    mov QWORD [rbp - 656], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 656],rax
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
