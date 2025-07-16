SECTION .data

SECTION .bss

SECTION .text
global  main
extern printf
char_decl:
    push rbp
    mov  rbp, rsp
    sub  rsp, 80
    mov QWORD [rbp - 8], 'A'
    lea rax, [rbp - 48]
    mov QWORD [rbp - 56], rax
    mov byte [rbp - 48], 'F'
    mov byte [rbp - 47], 'r'
    mov byte [rbp - 46], 'o'
    mov byte [rbp - 45], 'm'
    mov byte [rbp - 44], ' '
    mov byte [rbp - 43], 'c'
    mov byte [rbp - 42], 'h'
    mov byte [rbp - 41], 'a'
    mov byte [rbp - 40], 'r'
    mov byte [rbp - 39], '_'
    mov byte [rbp - 38], 'd'
    mov byte [rbp - 37], 'e'
    mov byte [rbp - 36], 'c'
    mov byte [rbp - 35], 'l'
    mov byte [rbp - 34], ','
    mov byte [rbp - 33], ' '
    mov byte [rbp - 32], 'c'
    mov byte [rbp - 31], 'h'
    mov byte [rbp - 30], 'a'
    mov byte [rbp - 29], 'r'
    mov byte [rbp - 28], 'a'
    mov byte [rbp - 27], 'c'
    mov byte [rbp - 26], 't'
    mov byte [rbp - 25], 'e'
    mov byte [rbp - 24], 'r'
    mov byte [rbp - 23], ' '
    mov byte [rbp - 22], ':'
    mov byte [rbp - 21], ' '
    mov byte [rbp - 20], '%'
    mov byte [rbp - 19], 'c'
    mov byte [rbp - 18], 0x0A
    mov byte [rbp - 17], 0
    mov rdi, QWORD [rbp - 56]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 64], rax
    mov rsi, QWORD [rbp - 64]
    mov QWORD [rbp - 72], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 72],rax
    leave
    ret

char_reassign:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 8], 'B'
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    leave
    ret
char_arithmetic:
    push rbp
    mov  rbp, rsp
    sub  rsp, 64
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 1
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    add rax,rbx
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    leave
    ret
compare_char:
    push rbp
    mov  rbp, rsp
    sub  rsp, 64
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], rsi
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    leave
    ret
switch_char:
    push rbp
    mov  rbp, rsp
    sub  rsp, 208
    mov QWORD [rbp - 8], rdi
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 'A'
    je .L1
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 'B'
    je .L2
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov rax, QWORD [rbp - 32]
    cmp rax, 'C'
    je .L3
    jmp .L4
    .L1:
    lea rax, [rbp - 64]
    mov QWORD [rbp - 72], rax
    mov byte [rbp - 64], 'F'
    mov byte [rbp - 63], 'r'
    mov byte [rbp - 62], 'o'
    mov byte [rbp - 61], 'm'
    mov byte [rbp - 60], ' '
    mov byte [rbp - 59], 's'
    mov byte [rbp - 58], 'w'
    mov byte [rbp - 57], 'i'
    mov byte [rbp - 56], 't'
    mov byte [rbp - 55], 'c'
    mov byte [rbp - 54], 'h'
    mov byte [rbp - 53], '_'
    mov byte [rbp - 52], 'c'
    mov byte [rbp - 51], 'h'
    mov byte [rbp - 50], 'a'
    mov byte [rbp - 49], 'r'
    mov byte [rbp - 48], ','
    mov byte [rbp - 47], ' '
    mov byte [rbp - 46], 'V'
    mov byte [rbp - 45], 'a'
    mov byte [rbp - 44], 'l'
    mov byte [rbp - 43], 'u'
    mov byte [rbp - 42], 'e'
    mov byte [rbp - 41], ' '
    mov byte [rbp - 40], '='
    mov byte [rbp - 39], ' '
    mov byte [rbp - 38], '%'
    mov byte [rbp - 37], 'c'
    mov byte [rbp - 36], 0x0A
    mov byte [rbp - 35], 0
    mov rdi, QWORD [rbp - 72]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 80], rax
    mov rsi, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 88],rax
    jmp .L0
    .L2:
    lea rax, [rbp - 120]
    mov QWORD [rbp - 128], rax
    mov byte [rbp - 120], 'F'
    mov byte [rbp - 119], 'r'
    mov byte [rbp - 118], 'o'
    mov byte [rbp - 117], 'm'
    mov byte [rbp - 116], ' '
    mov byte [rbp - 115], 's'
    mov byte [rbp - 114], 'w'
    mov byte [rbp - 113], 'i'
    mov byte [rbp - 112], 't'
    mov byte [rbp - 111], 'c'
    mov byte [rbp - 110], 'h'
    mov byte [rbp - 109], '_'
    mov byte [rbp - 108], 'c'
    mov byte [rbp - 107], 'h'
    mov byte [rbp - 106], 'a'
    mov byte [rbp - 105], 'r'
    mov byte [rbp - 104], ','
    mov byte [rbp - 103], ' '
    mov byte [rbp - 102], 'V'
    mov byte [rbp - 101], 'a'
    mov byte [rbp - 100], 'l'
    mov byte [rbp - 99], 'u'
    mov byte [rbp - 98], 'e'
    mov byte [rbp - 97], ' '
    mov byte [rbp - 96], '='
    mov byte [rbp - 95], ' '
    mov byte [rbp - 94], '%'
    mov byte [rbp - 93], 'c'
    mov byte [rbp - 92], 0x0A
    mov byte [rbp - 91], 0
    mov rdi, QWORD [rbp - 128]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 136], rax
    mov rsi, QWORD [rbp - 136]
    mov QWORD [rbp - 144], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 144],rax
    jmp .L0
    .L3:
    lea rax, [rbp - 176]
    mov QWORD [rbp - 184], rax
    mov byte [rbp - 176], 'F'
    mov byte [rbp - 175], 'r'
    mov byte [rbp - 174], 'o'
    mov byte [rbp - 173], 'm'
    mov byte [rbp - 172], ' '
    mov byte [rbp - 171], 's'
    mov byte [rbp - 170], 'w'
    mov byte [rbp - 169], 'i'
    mov byte [rbp - 168], 't'
    mov byte [rbp - 167], 'c'
    mov byte [rbp - 166], 'h'
    mov byte [rbp - 165], '_'
    mov byte [rbp - 164], 'c'
    mov byte [rbp - 163], 'h'
    mov byte [rbp - 162], 'a'
    mov byte [rbp - 161], 'r'
    mov byte [rbp - 160], ','
    mov byte [rbp - 159], ' '
    mov byte [rbp - 158], 'V'
    mov byte [rbp - 157], 'a'
    mov byte [rbp - 156], 'l'
    mov byte [rbp - 155], 'u'
    mov byte [rbp - 154], 'e'
    mov byte [rbp - 153], ' '
    mov byte [rbp - 152], '='
    mov byte [rbp - 151], ' '
    mov byte [rbp - 150], '%'
    mov byte [rbp - 149], 'c'
    mov byte [rbp - 148], 0x0A
    mov byte [rbp - 147], 0
    mov rdi, QWORD [rbp - 184]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 192], rax
    mov rsi, QWORD [rbp - 192]
    mov QWORD [rbp - 200], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 200],rax
    jmp .L0
    .L4:
    .L0:
    leave
    ret

loop_char:
    push rbp
    mov  rbp, rsp
    sub  rsp, 112
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 'A'
    .L5:
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L6
    jmp .L7
    .L6:
    lea rax, [rbp - 72]
    mov QWORD [rbp - 80], rax
    mov byte [rbp - 72], '%'
    mov byte [rbp - 71], 'c'
    mov byte [rbp - 70], ' '
    mov byte [rbp - 69], 0
    mov rdi, QWORD [rbp - 80]
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 88], rax
    mov rsi, QWORD [rbp - 88]
    mov QWORD [rbp - 96], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 96],rax
    mov QWORD [rbp - 104], 0
    mov rax, [rbp - 16]
    inc rax
    mov [rbp - 104],rax
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 16], rax
    jmp .L5
    .L7:
    lea rax, [rbp - 48]
    mov QWORD [rbp - 56], rax
    mov byte [rbp - 48], 0x0A
    mov byte [rbp - 47], 0
    mov rdi, QWORD [rbp - 56]
    mov QWORD [rbp - 64], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 64],rax
    leave
    ret

char_offset:
    push rbp
    mov  rbp, rsp
    sub  rsp, 64
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], rsi
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    add rax,rbx
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    leave
    ret
capital_vowels:
    push rbp
    mov  rbp, rsp
    sub  rsp, 384
    mov QWORD [rbp - 8], 'A'
    .L8:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 'Z'
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L9
    jmp .L10
    .L9:
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 80], 'A'
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 104], 'E'
    mov rax, QWORD [rbp - 96]
    mov rbx, QWORD [rbp - 104]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 120], rax
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 128], rax
    mov rax, QWORD [rbp - 120]
    mov rbx, QWORD [rbp - 128]
    or rax,rbx
    test rax,rax
    setnz al
    movzx rax,al
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 144], rax
    mov QWORD [rbp - 152], 0
    mov QWORD [rbp - 152], 'I'
    mov rax, QWORD [rbp - 144]
    mov rbx, QWORD [rbp - 152]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 136], rax
    mov QWORD [rbp - 160], 0
    mov QWORD [rbp - 168], 0
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 168], rax
    mov QWORD [rbp - 176], 0
    mov rax, QWORD [rbp - 136]
    mov QWORD [rbp - 176], rax
    mov rax, QWORD [rbp - 168]
    mov rbx, QWORD [rbp - 176]
    or rax,rbx
    test rax,rax
    setnz al
    movzx rax,al
    mov QWORD [rbp - 160], rax
    mov QWORD [rbp - 184], 0
    mov QWORD [rbp - 192], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 192], rax
    mov QWORD [rbp - 200], 0
    mov QWORD [rbp - 200], 'O'
    mov rax, QWORD [rbp - 192]
    mov rbx, QWORD [rbp - 200]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 184], rax
    mov QWORD [rbp - 208], 0
    mov QWORD [rbp - 216], 0
    mov rax, QWORD [rbp - 160]
    mov QWORD [rbp - 216], rax
    mov QWORD [rbp - 224], 0
    mov rax, QWORD [rbp - 184]
    mov QWORD [rbp - 224], rax
    mov rax, QWORD [rbp - 216]
    mov rbx, QWORD [rbp - 224]
    or rax,rbx
    test rax,rax
    setnz al
    movzx rax,al
    mov QWORD [rbp - 208], rax
    mov QWORD [rbp - 232], 0
    mov QWORD [rbp - 240], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 240], rax
    mov QWORD [rbp - 248], 0
    mov QWORD [rbp - 248], 'U'
    mov rax, QWORD [rbp - 240]
    mov rbx, QWORD [rbp - 248]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 232], rax
    mov QWORD [rbp - 256], 0
    mov QWORD [rbp - 264], 0
    mov rax, QWORD [rbp - 208]
    mov QWORD [rbp - 264], rax
    mov QWORD [rbp - 272], 0
    mov rax, QWORD [rbp - 232]
    mov QWORD [rbp - 272], rax
    mov rax, QWORD [rbp - 264]
    mov rbx, QWORD [rbp - 272]
    or rax,rbx
    test rax,rax
    setnz al
    movzx rax,al
    mov QWORD [rbp - 256], rax
    mov rax, QWORD [rbp - 256]
    cmp rax, 0
    jne .L11
    lea rax, [rbp - 288]
    mov QWORD [rbp - 296], rax
    mov byte [rbp - 288], '%'
    mov byte [rbp - 287], 'c'
    mov byte [rbp - 286], ' '
    mov byte [rbp - 285], 0
    mov rdi, QWORD [rbp - 296]
    mov QWORD [rbp - 304], 0
    mov QWORD [rbp - 312], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 312], rax
    mov QWORD [rbp - 320], 0
    mov QWORD [rbp - 320], 32
    mov rax, QWORD [rbp - 312]
    mov rbx, QWORD [rbp - 320]
    add rax,rbx
    mov QWORD [rbp - 304], rax
    mov rax, QWORD [rbp - 304]
    mov QWORD [rbp - 328], rax
    mov rsi, QWORD [rbp - 328]
    mov QWORD [rbp - 336], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 336],rax
    jmp .L12
    .L11:
    lea rax, [rbp - 344]
    mov QWORD [rbp - 352], rax
    mov byte [rbp - 344], '%'
    mov byte [rbp - 343], 'c'
    mov byte [rbp - 342], ' '
    mov byte [rbp - 341], 0
    mov rdi, QWORD [rbp - 352]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 360], rax
    mov rsi, QWORD [rbp - 360]
    mov QWORD [rbp - 368], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 368],rax
    .L12:
    mov QWORD [rbp - 280], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 280],rax
    mov rax, QWORD [rbp - 280]
    mov QWORD [rbp - 8], rax
    jmp .L8
    .L10:
    lea rax, [rbp - 40]
    mov QWORD [rbp - 48], rax
    mov byte [rbp - 40], 0x0A
    mov byte [rbp - 39], 0
    mov rdi, QWORD [rbp - 48]
    mov QWORD [rbp - 56], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 56],rax
    leave
    ret

print_characters:
    push rbp
    mov  rbp, rsp
    sub  rsp, 576
    mov QWORD [rbp - 8], 0
    xor rax,rax
    call char_decl
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
    mov QWORD [rbp - 40], 'A'
    mov rdi, QWORD [rbp - 40]
    mov QWORD [rbp - 48], 0
    xor rax,rax
    call char_reassign
    mov QWORD [rbp - 48],rax
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 56], rax
    lea rax, [rbp - 80]
    mov QWORD [rbp - 88], rax
    mov byte [rbp - 80], 'R'
    mov byte [rbp - 79], 'e'
    mov byte [rbp - 78], 'a'
    mov byte [rbp - 77], 's'
    mov byte [rbp - 76], 's'
    mov byte [rbp - 75], 'i'
    mov byte [rbp - 74], 'g'
    mov byte [rbp - 73], 'n'
    mov byte [rbp - 72], 'e'
    mov byte [rbp - 71], 'd'
    mov byte [rbp - 70], ' '
    mov byte [rbp - 69], 'c'
    mov byte [rbp - 68], 'h'
    mov byte [rbp - 67], 'a'
    mov byte [rbp - 66], 'r'
    mov byte [rbp - 65], ' '
    mov byte [rbp - 64], ':'
    mov byte [rbp - 63], ' '
    mov byte [rbp - 62], '%'
    mov byte [rbp - 61], 'c'
    mov byte [rbp - 60], 0x0A
    mov byte [rbp - 59], 0
    mov rdi, QWORD [rbp - 88]
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 96], rax
    mov rsi, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 104],rax
    lea rax, [rbp - 112]
    mov QWORD [rbp - 120], rax
    mov byte [rbp - 112], 0x0A
    mov byte [rbp - 111], 0
    mov rdi, QWORD [rbp - 120]
    mov QWORD [rbp - 128], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 128],rax
    mov QWORD [rbp - 136], 'A'
    mov rdi, QWORD [rbp - 136]
    mov QWORD [rbp - 144], 0
    xor rax,rax
    call char_arithmetic
    mov QWORD [rbp - 144],rax
    mov rax, QWORD [rbp - 144]
    mov QWORD [rbp - 152], rax
    lea rax, [rbp - 192]
    mov QWORD [rbp - 200], rax
    mov byte [rbp - 192], 'C'
    mov byte [rbp - 191], 'h'
    mov byte [rbp - 190], 'a'
    mov byte [rbp - 189], 'r'
    mov byte [rbp - 188], 'a'
    mov byte [rbp - 187], 'c'
    mov byte [rbp - 186], 't'
    mov byte [rbp - 185], 'e'
    mov byte [rbp - 184], 'r'
    mov byte [rbp - 183], ' '
    mov byte [rbp - 182], 'a'
    mov byte [rbp - 181], 'r'
    mov byte [rbp - 180], 'i'
    mov byte [rbp - 179], 't'
    mov byte [rbp - 178], 'h'
    mov byte [rbp - 177], 'm'
    mov byte [rbp - 176], 'e'
    mov byte [rbp - 175], 't'
    mov byte [rbp - 174], 'i'
    mov byte [rbp - 173], 'c'
    mov byte [rbp - 172], ' '
    mov byte [rbp - 171], ':'
    mov byte [rbp - 170], ' '
    mov byte [rbp - 169], 'A'
    mov byte [rbp - 168], ' '
    mov byte [rbp - 167], '+'
    mov byte [rbp - 166], ' '
    mov byte [rbp - 165], '1'
    mov byte [rbp - 164], ' '
    mov byte [rbp - 163], ':'
    mov byte [rbp - 162], ' '
    mov byte [rbp - 161], '%'
    mov byte [rbp - 160], 'c'
    mov byte [rbp - 159], 0x0A
    mov byte [rbp - 158], 0
    mov rdi, QWORD [rbp - 200]
    mov rax, QWORD [rbp - 152]
    mov QWORD [rbp - 208], rax
    mov rsi, QWORD [rbp - 208]
    mov QWORD [rbp - 216], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 216],rax
    lea rax, [rbp - 224]
    mov QWORD [rbp - 232], rax
    mov byte [rbp - 224], 0x0A
    mov byte [rbp - 223], 0
    mov rdi, QWORD [rbp - 232]
    mov QWORD [rbp - 240], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 240],rax
    mov QWORD [rbp - 248], 'A'
    mov rdi, QWORD [rbp - 248]
    mov QWORD [rbp - 256], 'A'
    mov rsi, QWORD [rbp - 256]
    mov QWORD [rbp - 264], 0
    xor rax,rax
    call compare_char
    mov QWORD [rbp - 264],rax
    mov rax, QWORD [rbp - 264]
    mov QWORD [rbp - 272], rax
    lea rax, [rbp - 304]
    mov QWORD [rbp - 312], rax
    mov byte [rbp - 304], 'C'
    mov byte [rbp - 303], 'o'
    mov byte [rbp - 302], 'm'
    mov byte [rbp - 301], 'p'
    mov byte [rbp - 300], 'a'
    mov byte [rbp - 299], 'r'
    mov byte [rbp - 298], 'i'
    mov byte [rbp - 297], 's'
    mov byte [rbp - 296], 'o'
    mov byte [rbp - 295], 'n'
    mov byte [rbp - 294], ' '
    mov byte [rbp - 293], 'b'
    mov byte [rbp - 292], 'e'
    mov byte [rbp - 291], 't'
    mov byte [rbp - 290], 'w'
    mov byte [rbp - 289], 'e'
    mov byte [rbp - 288], 'e'
    mov byte [rbp - 287], 'n'
    mov byte [rbp - 286], ' '
    mov byte [rbp - 285], 'A'
    mov byte [rbp - 284], ','
    mov byte [rbp - 283], 'A'
    mov byte [rbp - 282], ' '
    mov byte [rbp - 281], ':'
    mov byte [rbp - 280], ' '
    mov byte [rbp - 279], '%'
    mov byte [rbp - 278], 'd'
    mov byte [rbp - 277], 0x0A
    mov byte [rbp - 276], 0
    mov rdi, QWORD [rbp - 312]
    mov rax, QWORD [rbp - 272]
    mov QWORD [rbp - 320], rax
    mov rsi, QWORD [rbp - 320]
    mov QWORD [rbp - 328], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 328],rax
    lea rax, [rbp - 336]
    mov QWORD [rbp - 344], rax
    mov byte [rbp - 336], 0x0A
    mov byte [rbp - 335], 0
    mov rdi, QWORD [rbp - 344]
    mov QWORD [rbp - 352], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 352],rax
    mov QWORD [rbp - 360], 'A'
    mov rdi, QWORD [rbp - 360]
    mov QWORD [rbp - 368], 0
    xor rax,rax
    call switch_char
    mov QWORD [rbp - 368],rax
    lea rax, [rbp - 376]
    mov QWORD [rbp - 384], rax
    mov byte [rbp - 376], 0x0A
    mov byte [rbp - 375], 0
    mov rdi, QWORD [rbp - 384]
    mov QWORD [rbp - 392], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 392],rax
    mov QWORD [rbp - 400], 'G'
    mov rdi, QWORD [rbp - 400]
    mov QWORD [rbp - 408], 0
    xor rax,rax
    call loop_char
    mov QWORD [rbp - 408],rax
    lea rax, [rbp - 416]
    mov QWORD [rbp - 424], rax
    mov byte [rbp - 416], 0x0A
    mov byte [rbp - 415], 0
    mov rdi, QWORD [rbp - 424]
    mov QWORD [rbp - 432], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 432],rax
    mov QWORD [rbp - 440], 'D'
    mov rdi, QWORD [rbp - 440]
    mov QWORD [rbp - 448], 3
    mov rsi, QWORD [rbp - 448]
    mov QWORD [rbp - 456], 0
    xor rax,rax
    call char_offset
    mov QWORD [rbp - 456],rax
    mov rax, QWORD [rbp - 456]
    mov QWORD [rbp - 464], rax
    lea rax, [rbp - 488]
    mov QWORD [rbp - 496], rax
    mov byte [rbp - 488], 'O'
    mov byte [rbp - 487], 'f'
    mov byte [rbp - 486], 'f'
    mov byte [rbp - 485], 's'
    mov byte [rbp - 484], 'e'
    mov byte [rbp - 483], 't'
    mov byte [rbp - 482], ' '
    mov byte [rbp - 481], 'D'
    mov byte [rbp - 480], ' '
    mov byte [rbp - 479], 'b'
    mov byte [rbp - 478], 'y'
    mov byte [rbp - 477], ' '
    mov byte [rbp - 476], '3'
    mov byte [rbp - 475], ' '
    mov byte [rbp - 474], ':'
    mov byte [rbp - 473], ' '
    mov byte [rbp - 472], '%'
    mov byte [rbp - 471], 'c'
    mov byte [rbp - 470], 0x0A
    mov byte [rbp - 469], 0
    mov rdi, QWORD [rbp - 496]
    mov rax, QWORD [rbp - 464]
    mov QWORD [rbp - 504], rax
    mov rsi, QWORD [rbp - 504]
    mov QWORD [rbp - 512], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 512],rax
    lea rax, [rbp - 520]
    mov QWORD [rbp - 528], rax
    mov byte [rbp - 520], 0x0A
    mov byte [rbp - 519], 0
    mov rdi, QWORD [rbp - 528]
    mov QWORD [rbp - 536], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 536],rax
    mov QWORD [rbp - 544], 0
    xor rax,rax
    call capital_vowels
    mov QWORD [rbp - 544],rax
    lea rax, [rbp - 552]
    mov QWORD [rbp - 560], rax
    mov byte [rbp - 552], 0x0A
    mov byte [rbp - 551], 0
    mov rdi, QWORD [rbp - 560]
    mov QWORD [rbp - 568], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 568],rax
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 16
    mov QWORD [rbp - 8], 0
    xor rax,rax
    call print_characters
    mov QWORD [rbp - 8],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack
