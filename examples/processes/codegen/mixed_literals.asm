SECTION .data

SECTION .bss

SECTION .text
global  main
extern printf
mixed_conds:
    push rbp
    mov  rbp, rsp
    sub  rsp, 288
    mov QWORD [rbp - 8], 10
    mov rax, 0x4004000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 16], xmm7
    mov QWORD [rbp - 24], 'A'
    mov QWORD [rbp - 32], 1
    lea rax, [rbp - 40]
    mov QWORD [rbp - 48], rax
    mov byte [rbp - 40], 'h'
    mov byte [rbp - 39], 'e'
    mov byte [rbp - 38], 'l'
    mov byte [rbp - 37], 'l'
    mov byte [rbp - 36], 'o'
    mov byte [rbp - 35], 0
    lea rax, [rbp - 56]
    mov QWORD [rbp - 64], rax
    mov byte [rbp - 56], 'h'
    mov byte [rbp - 55], 'e'
    mov byte [rbp - 54], 'l'
    mov byte [rbp - 53], 'l'
    mov byte [rbp - 52], 'o'
    mov byte [rbp - 51], 0
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 80], 1
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 88], 1
    mov rax, QWORD [rbp - 80]
    mov rbx, QWORD [rbp - 88]
    test rax,rax
    setz al
    movzx rax,al
    test rbx,rbx
    setz bl
    movzx rbx,bl
    or rax,rbx
    xor rax,1
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 104], 1
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 112], 1
    mov rax, QWORD [rbp - 104]
    mov rbx, QWORD [rbp - 112]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 136], rax
    mov rax, QWORD [rbp - 128]
    mov rbx, QWORD [rbp - 136]
    test rax,rax
    setz al
    movzx rax,al
    test rbx,rbx
    setz bl
    movzx rbx,bl
    or rax,rbx
    xor rax,1
    mov QWORD [rbp - 120], rax
    mov QWORD [rbp - 144], 0
    mov QWORD [rbp - 152], 0
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 152], rax
    mov QWORD [rbp - 160], 0
    mov QWORD [rbp - 160], 1
    mov rax, QWORD [rbp - 152]
    mov rbx, QWORD [rbp - 160]
    test rax,rax
    setz al
    movzx rax,al
    test rbx,rbx
    setz bl
    movzx rbx,bl
    or rax,rbx
    xor rax,1
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 144]
    cmp rax, 0
    jne .L0
    lea rax, [rbp - 192]
    mov QWORD [rbp - 200], rax
    mov byte [rbp - 192], 'F'
    mov byte [rbp - 191], 'r'
    mov byte [rbp - 190], 'o'
    mov byte [rbp - 189], 'm'
    mov byte [rbp - 188], ' '
    mov byte [rbp - 187], 'm'
    mov byte [rbp - 186], 'i'
    mov byte [rbp - 185], 'x'
    mov byte [rbp - 184], 'e'
    mov byte [rbp - 183], 'd'
    mov byte [rbp - 182], '_'
    mov byte [rbp - 181], 'c'
    mov byte [rbp - 180], 'o'
    mov byte [rbp - 179], 'n'
    mov byte [rbp - 178], 'd'
    mov byte [rbp - 177], 's'
    mov byte [rbp - 176], ' '
    mov byte [rbp - 175], ','
    mov byte [rbp - 174], ' '
    mov byte [rbp - 173], 'V'
    mov byte [rbp - 172], 'a'
    mov byte [rbp - 171], 'l'
    mov byte [rbp - 170], 'u'
    mov byte [rbp - 169], 'e'
    mov byte [rbp - 168], ' '
    mov byte [rbp - 167], ':'
    mov byte [rbp - 166], ' '
    mov byte [rbp - 165], '%'
    mov byte [rbp - 164], 'd'
    mov byte [rbp - 163], 0x0A
    mov byte [rbp - 162], 0
    mov rdi, QWORD [rbp - 200]
    mov QWORD [rbp - 208], 0
    mov rsi, QWORD [rbp - 208]
    mov QWORD [rbp - 216], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 216],rax
    jmp .L1
    .L0:
    lea rax, [rbp - 248]
    mov QWORD [rbp - 256], rax
    mov byte [rbp - 248], 'F'
    mov byte [rbp - 247], 'r'
    mov byte [rbp - 246], 'o'
    mov byte [rbp - 245], 'm'
    mov byte [rbp - 244], ' '
    mov byte [rbp - 243], 'm'
    mov byte [rbp - 242], 'i'
    mov byte [rbp - 241], 'x'
    mov byte [rbp - 240], 'e'
    mov byte [rbp - 239], 'd'
    mov byte [rbp - 238], '_'
    mov byte [rbp - 237], 'c'
    mov byte [rbp - 236], 'o'
    mov byte [rbp - 235], 'n'
    mov byte [rbp - 234], 'd'
    mov byte [rbp - 233], 's'
    mov byte [rbp - 232], ' '
    mov byte [rbp - 231], ','
    mov byte [rbp - 230], ' '
    mov byte [rbp - 229], 'v'
    mov byte [rbp - 228], 'a'
    mov byte [rbp - 227], 'l'
    mov byte [rbp - 226], 'u'
    mov byte [rbp - 225], 'e'
    mov byte [rbp - 224], ' '
    mov byte [rbp - 223], ':'
    mov byte [rbp - 222], ' '
    mov byte [rbp - 221], '%'
    mov byte [rbp - 220], 'd'
    mov byte [rbp - 219], 0x0A
    mov byte [rbp - 218], 0
    mov rdi, QWORD [rbp - 256]
    mov QWORD [rbp - 264], 1
    mov rsi, QWORD [rbp - 264]
    mov QWORD [rbp - 272], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 272],rax
    .L1:
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 48
    mov QWORD [rbp - 8], 0
    xor rax,rax
    call mixed_conds
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
