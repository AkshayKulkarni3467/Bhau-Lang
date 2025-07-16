SECTION .data

SECTION .bss

SECTION .text
global  main
extern printf
mixed_conds:
    push rbp
    mov  rbp, rsp
    sub  rsp, 352
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
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 88], rax
    mov rax, QWORD [rbp - 80]
    cvtsi2sd xmm0, rax
    movsd xmm1, QWORD [rbp - 88]
    addsd xmm0,xmm1
    movsd QWORD [rbp - 72],xmm0
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 0
    mov rax, 0x4029000000000000
    movq xmm0, rax
    movsd QWORD [rbp - 112], xmm0
    movsd xmm0, QWORD [rbp - 104]
    movsd xmm1, QWORD [rbp - 112]
    ucomisd xmm0,xmm1
    sete al
    setnp dl
    and al,dl
    movzx rax,al
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 136], 'A'
    mov rax, QWORD [rbp - 128]
    mov rbx, QWORD [rbp - 136]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 120], rax
    mov QWORD [rbp - 144], 0
    mov QWORD [rbp - 152], 0
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 152], rax
    mov QWORD [rbp - 160], 0
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 160], rax
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
    mov QWORD [rbp - 168], 0
    mov QWORD [rbp - 176], 0
    mov QWORD [rbp - 176], 1
    mov QWORD [rbp - 184], 0
    mov QWORD [rbp - 184], 1
    mov rax, QWORD [rbp - 176]
    mov rbx, QWORD [rbp - 184]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 168], rax
    mov QWORD [rbp - 192], 0
    mov QWORD [rbp - 200], 0
    mov rax, QWORD [rbp - 144]
    mov QWORD [rbp - 200], rax
    mov QWORD [rbp - 208], 0
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 208], rax
    mov rax, QWORD [rbp - 200]
    mov rbx, QWORD [rbp - 208]
    test rax,rax
    setz al
    movzx rax,al
    test rbx,rbx
    setz bl
    movzx rbx,bl
    or rax,rbx
    xor rax,1
    mov QWORD [rbp - 192], rax
    mov QWORD [rbp - 216], 0
    mov QWORD [rbp - 224], 0
    mov rax, QWORD [rbp - 192]
    mov QWORD [rbp - 224], rax
    mov QWORD [rbp - 232], 0
    mov QWORD [rbp - 232], 1
    mov rax, QWORD [rbp - 224]
    mov rbx, QWORD [rbp - 232]
    test rax,rax
    setz al
    movzx rax,al
    test rbx,rbx
    setz bl
    movzx rbx,bl
    or rax,rbx
    xor rax,1
    mov QWORD [rbp - 216], rax
    mov rax, QWORD [rbp - 216]
    cmp rax, 0
    jne .L0
    lea rax, [rbp - 264]
    mov QWORD [rbp - 272], rax
    mov byte [rbp - 264], 'F'
    mov byte [rbp - 263], 'r'
    mov byte [rbp - 262], 'o'
    mov byte [rbp - 261], 'm'
    mov byte [rbp - 260], ' '
    mov byte [rbp - 259], 'm'
    mov byte [rbp - 258], 'i'
    mov byte [rbp - 257], 'x'
    mov byte [rbp - 256], 'e'
    mov byte [rbp - 255], 'd'
    mov byte [rbp - 254], '_'
    mov byte [rbp - 253], 'c'
    mov byte [rbp - 252], 'o'
    mov byte [rbp - 251], 'n'
    mov byte [rbp - 250], 'd'
    mov byte [rbp - 249], 's'
    mov byte [rbp - 248], ' '
    mov byte [rbp - 247], ','
    mov byte [rbp - 246], ' '
    mov byte [rbp - 245], 'V'
    mov byte [rbp - 244], 'a'
    mov byte [rbp - 243], 'l'
    mov byte [rbp - 242], 'u'
    mov byte [rbp - 241], 'e'
    mov byte [rbp - 240], ' '
    mov byte [rbp - 239], ':'
    mov byte [rbp - 238], ' '
    mov byte [rbp - 237], '%'
    mov byte [rbp - 236], 'd'
    mov byte [rbp - 235], 0x0A
    mov byte [rbp - 234], 0
    mov rdi, QWORD [rbp - 272]
    mov QWORD [rbp - 280], 0
    mov rsi, QWORD [rbp - 280]
    mov QWORD [rbp - 288], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 288],rax
    jmp .L1
    .L0:
    lea rax, [rbp - 320]
    mov QWORD [rbp - 328], rax
    mov byte [rbp - 320], 'F'
    mov byte [rbp - 319], 'r'
    mov byte [rbp - 318], 'o'
    mov byte [rbp - 317], 'm'
    mov byte [rbp - 316], ' '
    mov byte [rbp - 315], 'm'
    mov byte [rbp - 314], 'i'
    mov byte [rbp - 313], 'x'
    mov byte [rbp - 312], 'e'
    mov byte [rbp - 311], 'd'
    mov byte [rbp - 310], '_'
    mov byte [rbp - 309], 'c'
    mov byte [rbp - 308], 'o'
    mov byte [rbp - 307], 'n'
    mov byte [rbp - 306], 'd'
    mov byte [rbp - 305], 's'
    mov byte [rbp - 304], ' '
    mov byte [rbp - 303], ','
    mov byte [rbp - 302], ' '
    mov byte [rbp - 301], 'v'
    mov byte [rbp - 300], 'a'
    mov byte [rbp - 299], 'l'
    mov byte [rbp - 298], 'u'
    mov byte [rbp - 297], 'e'
    mov byte [rbp - 296], ' '
    mov byte [rbp - 295], ':'
    mov byte [rbp - 294], ' '
    mov byte [rbp - 293], '%'
    mov byte [rbp - 292], 'd'
    mov byte [rbp - 291], 0x0A
    mov byte [rbp - 290], 0
    mov rdi, QWORD [rbp - 328]
    mov QWORD [rbp - 336], 1
    mov rsi, QWORD [rbp - 336]
    mov QWORD [rbp - 344], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 344],rax
    .L1:
    leave
    ret

float_and_int:
    push rbp
    mov  rbp, rsp
    sub  rsp, 112
    mov QWORD [rbp - 8], rdi
    movsd QWORD [rbp - 16], xmm0
    lea rax, [rbp - 56]
    mov QWORD [rbp - 64], rax
    mov byte [rbp - 56], 'F'
    mov byte [rbp - 55], 'r'
    mov byte [rbp - 54], 'o'
    mov byte [rbp - 53], 'm'
    mov byte [rbp - 52], ' '
    mov byte [rbp - 51], 'f'
    mov byte [rbp - 50], 'l'
    mov byte [rbp - 49], 'o'
    mov byte [rbp - 48], 'a'
    mov byte [rbp - 47], 't'
    mov byte [rbp - 46], '_'
    mov byte [rbp - 45], 'a'
    mov byte [rbp - 44], 'n'
    mov byte [rbp - 43], 'd'
    mov byte [rbp - 42], '_'
    mov byte [rbp - 41], 'i'
    mov byte [rbp - 40], 'n'
    mov byte [rbp - 39], 't'
    mov byte [rbp - 38], ' '
    mov byte [rbp - 37], ','
    mov byte [rbp - 36], ' '
    mov byte [rbp - 35], 'v'
    mov byte [rbp - 34], 'a'
    mov byte [rbp - 33], 'l'
    mov byte [rbp - 32], 'u'
    mov byte [rbp - 31], 'e'
    mov byte [rbp - 30], ' '
    mov byte [rbp - 29], ':'
    mov byte [rbp - 28], ' '
    mov byte [rbp - 27], '%'
    mov byte [rbp - 26], '.'
    mov byte [rbp - 25], '2'
    mov byte [rbp - 24], 'f'
    mov byte [rbp - 23], 0x0A
    mov byte [rbp - 22], 0
    mov rdi, QWORD [rbp - 64]
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 88], rax
    mov rax, QWORD [rbp - 80]
    cvtsi2sd xmm0, rax
    movsd xmm1, QWORD [rbp - 88]
    addsd xmm0,xmm1
    movsd QWORD [rbp - 72],xmm0
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 96], rax
    movq xmm0, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    mov rax, 1
    call printf
    mov QWORD [rbp - 104],rax
    leave
    ret

int_char_bool:
    push rbp
    mov  rbp, rsp
    sub  rsp, 144
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], rsi
    mov QWORD [rbp - 24], rdx
    lea rax, [rbp - 64]
    mov QWORD [rbp - 72], rax
    mov byte [rbp - 64], 'F'
    mov byte [rbp - 63], 'r'
    mov byte [rbp - 62], 'o'
    mov byte [rbp - 61], 'm'
    mov byte [rbp - 60], ' '
    mov byte [rbp - 59], 'i'
    mov byte [rbp - 58], 'n'
    mov byte [rbp - 57], 't'
    mov byte [rbp - 56], '_'
    mov byte [rbp - 55], 'c'
    mov byte [rbp - 54], 'h'
    mov byte [rbp - 53], 'a'
    mov byte [rbp - 52], 'r'
    mov byte [rbp - 51], '_'
    mov byte [rbp - 50], 'b'
    mov byte [rbp - 49], 'o'
    mov byte [rbp - 48], 'o'
    mov byte [rbp - 47], 'l'
    mov byte [rbp - 46], ' '
    mov byte [rbp - 45], ','
    mov byte [rbp - 44], ' '
    mov byte [rbp - 43], 'v'
    mov byte [rbp - 42], 'a'
    mov byte [rbp - 41], 'l'
    mov byte [rbp - 40], 'u'
    mov byte [rbp - 39], 'e'
    mov byte [rbp - 38], ' '
    mov byte [rbp - 37], ':'
    mov byte [rbp - 36], ' '
    mov byte [rbp - 35], '%'
    mov byte [rbp - 34], 'd'
    mov byte [rbp - 33], 0x0A
    mov byte [rbp - 32], 0
    mov rdi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    add rax,rbx
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 112]
    mov rbx, QWORD [rbp - 120]
    add rax,rbx
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 128], rax
    mov rsi, QWORD [rbp - 128]
    mov QWORD [rbp - 136], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 136],rax
    leave
    ret

char_float:
    push rbp
    mov  rbp, rsp
    sub  rsp, 112
    mov QWORD [rbp - 8], rdi
    movsd QWORD [rbp - 16], xmm0
    lea rax, [rbp - 56]
    mov QWORD [rbp - 64], rax
    mov byte [rbp - 56], 'F'
    mov byte [rbp - 55], 'r'
    mov byte [rbp - 54], 'o'
    mov byte [rbp - 53], 'm'
    mov byte [rbp - 52], ' '
    mov byte [rbp - 51], 'c'
    mov byte [rbp - 50], 'h'
    mov byte [rbp - 49], 'a'
    mov byte [rbp - 48], 'r'
    mov byte [rbp - 47], '_'
    mov byte [rbp - 46], 'f'
    mov byte [rbp - 45], 'l'
    mov byte [rbp - 44], 'o'
    mov byte [rbp - 43], 'a'
    mov byte [rbp - 42], 't'
    mov byte [rbp - 41], ' '
    mov byte [rbp - 40], ','
    mov byte [rbp - 39], ' '
    mov byte [rbp - 38], 'v'
    mov byte [rbp - 37], 'a'
    mov byte [rbp - 36], 'l'
    mov byte [rbp - 35], 'u'
    mov byte [rbp - 34], 'e'
    mov byte [rbp - 33], ' '
    mov byte [rbp - 32], ':'
    mov byte [rbp - 31], ' '
    mov byte [rbp - 30], '%'
    mov byte [rbp - 29], '.'
    mov byte [rbp - 28], '2'
    mov byte [rbp - 27], 'f'
    mov byte [rbp - 26], 0x0A
    mov byte [rbp - 25], 0
    mov rdi, QWORD [rbp - 64]
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 88], rax
    mov rax, QWORD [rbp - 80]
    cvtsi2sd xmm0, rax
    movsd xmm1, QWORD [rbp - 88]
    addsd xmm0,xmm1
    movsd QWORD [rbp - 72],xmm0
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 96], rax
    movq xmm0, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    mov rax, 1
    call printf
    mov QWORD [rbp - 104],rax
    leave
    ret

bool_float:
    push rbp
    mov  rbp, rsp
    sub  rsp, 192
    mov QWORD [rbp - 8], rdi
    movsd QWORD [rbp - 16], xmm0
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov rax, 0x40139999a0000000
    movq xmm0, rax
    movsd QWORD [rbp - 40], xmm0
    movsd xmm0, QWORD [rbp - 32]
    movsd xmm1, QWORD [rbp - 40]
    ucomisd xmm0,xmm1
    seta al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 48], 0
    mov QWORD [rbp - 56], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 56], rax
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 56]
    mov rbx, QWORD [rbp - 64]
    test rax,rax
    setz al
    movzx rax,al
    test rbx,rbx
    setz bl
    movzx rbx,bl
    or rax,rbx
    xor rax,1
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    cmp rax, 0
    jne .L2
    lea rax, [rbp - 96]
    mov QWORD [rbp - 104], rax
    mov byte [rbp - 96], 'F'
    mov byte [rbp - 95], 'r'
    mov byte [rbp - 94], 'o'
    mov byte [rbp - 93], 'm'
    mov byte [rbp - 92], ' '
    mov byte [rbp - 91], 'b'
    mov byte [rbp - 90], 'o'
    mov byte [rbp - 89], 'o'
    mov byte [rbp - 88], 'l'
    mov byte [rbp - 87], '_'
    mov byte [rbp - 86], 'f'
    mov byte [rbp - 85], 'l'
    mov byte [rbp - 84], 'o'
    mov byte [rbp - 83], 'a'
    mov byte [rbp - 82], 't'
    mov byte [rbp - 81], ' '
    mov byte [rbp - 80], ','
    mov byte [rbp - 79], ' '
    mov byte [rbp - 78], 'v'
    mov byte [rbp - 77], 'a'
    mov byte [rbp - 76], 'l'
    mov byte [rbp - 75], 'u'
    mov byte [rbp - 74], 'e'
    mov byte [rbp - 73], ' '
    mov byte [rbp - 72], ':'
    mov byte [rbp - 71], ' '
    mov byte [rbp - 70], '%'
    mov byte [rbp - 69], 'd'
    mov byte [rbp - 68], 0x0A
    mov byte [rbp - 67], 0
    mov rdi, QWORD [rbp - 104]
    mov QWORD [rbp - 112], 0
    mov rsi, QWORD [rbp - 112]
    mov QWORD [rbp - 120], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 120],rax
    jmp .L3
    .L2:
    lea rax, [rbp - 152]
    mov QWORD [rbp - 160], rax
    mov byte [rbp - 152], 'F'
    mov byte [rbp - 151], 'r'
    mov byte [rbp - 150], 'o'
    mov byte [rbp - 149], 'm'
    mov byte [rbp - 148], ' '
    mov byte [rbp - 147], 'b'
    mov byte [rbp - 146], 'o'
    mov byte [rbp - 145], 'o'
    mov byte [rbp - 144], 'l'
    mov byte [rbp - 143], '_'
    mov byte [rbp - 142], 'f'
    mov byte [rbp - 141], 'l'
    mov byte [rbp - 140], 'o'
    mov byte [rbp - 139], 'a'
    mov byte [rbp - 138], 't'
    mov byte [rbp - 137], ' '
    mov byte [rbp - 136], ','
    mov byte [rbp - 135], ' '
    mov byte [rbp - 134], 'v'
    mov byte [rbp - 133], 'a'
    mov byte [rbp - 132], 'l'
    mov byte [rbp - 131], 'u'
    mov byte [rbp - 130], 'e'
    mov byte [rbp - 129], ' '
    mov byte [rbp - 128], ':'
    mov byte [rbp - 127], ' '
    mov byte [rbp - 126], '%'
    mov byte [rbp - 125], 'd'
    mov byte [rbp - 124], 0x0A
    mov byte [rbp - 123], 0
    mov rdi, QWORD [rbp - 160]
    mov QWORD [rbp - 168], 1
    mov rsi, QWORD [rbp - 168]
    mov QWORD [rbp - 176], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 176],rax
    .L3:
    leave
    ret

char_comp_int:
    push rbp
    mov  rbp, rsp
    sub  rsp, 176
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
    cmp rax, 0
    jne .L4
    lea rax, [rbp - 80]
    mov QWORD [rbp - 88], rax
    mov byte [rbp - 80], 'F'
    mov byte [rbp - 79], 'r'
    mov byte [rbp - 78], 'o'
    mov byte [rbp - 77], 'm'
    mov byte [rbp - 76], ' '
    mov byte [rbp - 75], 'c'
    mov byte [rbp - 74], 'h'
    mov byte [rbp - 73], 'a'
    mov byte [rbp - 72], 'r'
    mov byte [rbp - 71], '_'
    mov byte [rbp - 70], 'c'
    mov byte [rbp - 69], 'o'
    mov byte [rbp - 68], 'm'
    mov byte [rbp - 67], 'p'
    mov byte [rbp - 66], '_'
    mov byte [rbp - 65], 'i'
    mov byte [rbp - 64], 'n'
    mov byte [rbp - 63], 't'
    mov byte [rbp - 62], ' '
    mov byte [rbp - 61], ','
    mov byte [rbp - 60], ' '
    mov byte [rbp - 59], 'v'
    mov byte [rbp - 58], 'a'
    mov byte [rbp - 57], 'l'
    mov byte [rbp - 56], 'u'
    mov byte [rbp - 55], 'e'
    mov byte [rbp - 54], ' '
    mov byte [rbp - 53], ':'
    mov byte [rbp - 52], ' '
    mov byte [rbp - 51], '%'
    mov byte [rbp - 50], 'd'
    mov byte [rbp - 49], 0x0A
    mov byte [rbp - 48], 0
    mov rdi, QWORD [rbp - 88]
    mov QWORD [rbp - 96], 0
    mov rsi, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 104],rax
    jmp .L5
    .L4:
    lea rax, [rbp - 144]
    mov QWORD [rbp - 152], rax
    mov byte [rbp - 144], 'F'
    mov byte [rbp - 143], 'r'
    mov byte [rbp - 142], 'o'
    mov byte [rbp - 141], 'm'
    mov byte [rbp - 140], ' '
    mov byte [rbp - 139], 'c'
    mov byte [rbp - 138], 'h'
    mov byte [rbp - 137], 'a'
    mov byte [rbp - 136], 'r'
    mov byte [rbp - 135], '_'
    mov byte [rbp - 134], 'c'
    mov byte [rbp - 133], 'o'
    mov byte [rbp - 132], 'm'
    mov byte [rbp - 131], 'p'
    mov byte [rbp - 130], '_'
    mov byte [rbp - 129], 'i'
    mov byte [rbp - 128], 'n'
    mov byte [rbp - 127], 't'
    mov byte [rbp - 126], ' '
    mov byte [rbp - 125], ','
    mov byte [rbp - 124], ' '
    mov byte [rbp - 123], 'v'
    mov byte [rbp - 122], 'a'
    mov byte [rbp - 121], 'l'
    mov byte [rbp - 120], 'u'
    mov byte [rbp - 119], 'e'
    mov byte [rbp - 118], ' '
    mov byte [rbp - 117], ':'
    mov byte [rbp - 116], ' '
    mov byte [rbp - 115], '%'
    mov byte [rbp - 114], 'd'
    mov byte [rbp - 113], 0x0A
    mov byte [rbp - 112], 0
    mov rdi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 1
    mov rsi, QWORD [rbp - 160]
    mov QWORD [rbp - 168], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 168],rax
    .L5:
    leave
    ret

float_comp_int:
    push rbp
    mov  rbp, rsp
    sub  rsp, 176
    mov QWORD [rbp - 8], rdi
    movsd QWORD [rbp - 16], xmm0
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 32]
    cvtsi2sd xmm0, rax
    movsd xmm1, QWORD [rbp - 40]
    ucomisd xmm0,xmm1
    sete al
    setnp dl
    and al,dl
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L6
    lea rax, [rbp - 80]
    mov QWORD [rbp - 88], rax
    mov byte [rbp - 80], 'F'
    mov byte [rbp - 79], 'r'
    mov byte [rbp - 78], 'o'
    mov byte [rbp - 77], 'm'
    mov byte [rbp - 76], ' '
    mov byte [rbp - 75], 'f'
    mov byte [rbp - 74], 'l'
    mov byte [rbp - 73], 'o'
    mov byte [rbp - 72], 'a'
    mov byte [rbp - 71], 't'
    mov byte [rbp - 70], '_'
    mov byte [rbp - 69], 'c'
    mov byte [rbp - 68], 'o'
    mov byte [rbp - 67], 'm'
    mov byte [rbp - 66], 'p'
    mov byte [rbp - 65], '_'
    mov byte [rbp - 64], 'i'
    mov byte [rbp - 63], 'n'
    mov byte [rbp - 62], 't'
    mov byte [rbp - 61], ' '
    mov byte [rbp - 60], ','
    mov byte [rbp - 59], ' '
    mov byte [rbp - 58], 'v'
    mov byte [rbp - 57], 'a'
    mov byte [rbp - 56], 'l'
    mov byte [rbp - 55], 'u'
    mov byte [rbp - 54], 'e'
    mov byte [rbp - 53], ' '
    mov byte [rbp - 52], ':'
    mov byte [rbp - 51], ' '
    mov byte [rbp - 50], '%'
    mov byte [rbp - 49], 'd'
    mov byte [rbp - 48], 0x0A
    mov byte [rbp - 47], 0
    mov rdi, QWORD [rbp - 88]
    mov QWORD [rbp - 96], 0
    mov rsi, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 104],rax
    jmp .L7
    .L6:
    lea rax, [rbp - 144]
    mov QWORD [rbp - 152], rax
    mov byte [rbp - 144], 'F'
    mov byte [rbp - 143], 'r'
    mov byte [rbp - 142], 'o'
    mov byte [rbp - 141], 'm'
    mov byte [rbp - 140], ' '
    mov byte [rbp - 139], 'f'
    mov byte [rbp - 138], 'l'
    mov byte [rbp - 137], 'o'
    mov byte [rbp - 136], 'a'
    mov byte [rbp - 135], 't'
    mov byte [rbp - 134], '_'
    mov byte [rbp - 133], 'c'
    mov byte [rbp - 132], 'o'
    mov byte [rbp - 131], 'm'
    mov byte [rbp - 130], 'p'
    mov byte [rbp - 129], '_'
    mov byte [rbp - 128], 'i'
    mov byte [rbp - 127], 'n'
    mov byte [rbp - 126], 't'
    mov byte [rbp - 125], ' '
    mov byte [rbp - 124], ','
    mov byte [rbp - 123], ' '
    mov byte [rbp - 122], 'v'
    mov byte [rbp - 121], 'a'
    mov byte [rbp - 120], 'l'
    mov byte [rbp - 119], 'u'
    mov byte [rbp - 118], 'e'
    mov byte [rbp - 117], ' '
    mov byte [rbp - 116], ':'
    mov byte [rbp - 115], ' '
    mov byte [rbp - 114], '%'
    mov byte [rbp - 113], 'd'
    mov byte [rbp - 112], 0x0A
    mov byte [rbp - 111], 0
    mov rdi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 1
    mov rsi, QWORD [rbp - 160]
    mov QWORD [rbp - 168], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 168],rax
    .L7:
    leave
    ret

mixed_sum:
    push rbp
    mov  rbp, rsp
    sub  rsp, 176
    mov QWORD [rbp - 8], rdi
    movsd QWORD [rbp - 16], xmm0
    mov QWORD [rbp - 24], rsi
    mov QWORD [rbp - 32], rdx
    lea rax, [rbp - 64]
    mov QWORD [rbp - 72], rax
    mov byte [rbp - 64], 'F'
    mov byte [rbp - 63], 'r'
    mov byte [rbp - 62], 'o'
    mov byte [rbp - 61], 'm'
    mov byte [rbp - 60], ' '
    mov byte [rbp - 59], 'm'
    mov byte [rbp - 58], 'i'
    mov byte [rbp - 57], 'x'
    mov byte [rbp - 56], 'e'
    mov byte [rbp - 55], 'd'
    mov byte [rbp - 54], '_'
    mov byte [rbp - 53], 's'
    mov byte [rbp - 52], 'u'
    mov byte [rbp - 51], 'm'
    mov byte [rbp - 50], ' '
    mov byte [rbp - 49], ','
    mov byte [rbp - 48], ' '
    mov byte [rbp - 47], 'v'
    mov byte [rbp - 46], 'a'
    mov byte [rbp - 45], 'l'
    mov byte [rbp - 44], 'u'
    mov byte [rbp - 43], 'e'
    mov byte [rbp - 42], ' '
    mov byte [rbp - 41], ':'
    mov byte [rbp - 40], ' '
    mov byte [rbp - 39], '%'
    mov byte [rbp - 38], '.'
    mov byte [rbp - 37], '2'
    mov byte [rbp - 36], 'f'
    mov byte [rbp - 35], 0x0A
    mov byte [rbp - 34], 0
    mov rdi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 88]
    cvtsi2sd xmm0, rax
    movsd xmm1, QWORD [rbp - 96]
    addsd xmm0,xmm1
    movsd QWORD [rbp - 80],xmm0
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 120], rax
    movsd xmm0, QWORD [rbp - 112]
    mov rax, QWORD [rbp - 120]
    cvtsi2sd xmm1, rax
    addsd xmm0,xmm1
    movsd QWORD [rbp - 104],xmm0
    mov QWORD [rbp - 128], 0
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 136], rax
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 144], rax
    movsd xmm0, QWORD [rbp - 136]
    mov rax, QWORD [rbp - 144]
    cvtsi2sd xmm1, rax
    addsd xmm0,xmm1
    movsd QWORD [rbp - 128],xmm0
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 152], rax
    movq xmm0, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 0
    mov rax, 1
    call printf
    mov QWORD [rbp - 160],rax
    leave
    ret

mixed_control_flow:
    push rbp
    mov  rbp, rsp
    sub  rsp, 304
    mov rax, 0x400a666660000000
    movq xmm7, rax
    movsd QWORD [rbp - 8], xmm7
    mov QWORD [rbp - 16], 3
    mov QWORD [rbp - 24], 'c'
    mov QWORD [rbp - 32], 1
    lea rax, [rbp - 40]
    mov QWORD [rbp - 48], rax
    mov byte [rbp - 40], 't'
    mov byte [rbp - 39], 'e'
    mov byte [rbp - 38], 's'
    mov byte [rbp - 37], 't'
    mov byte [rbp - 36], 0
    lea rax, [rbp - 56]
    mov QWORD [rbp - 64], rax
    mov byte [rbp - 56], 't'
    mov byte [rbp - 55], 'e'
    mov byte [rbp - 54], 's'
    mov byte [rbp - 53], 't'
    mov byte [rbp - 52], 0
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 88], 'a'
    mov rax, QWORD [rbp - 80]
    mov rbx, QWORD [rbp - 88]
    cmp rax,rbx
    setne al
    movzx rax,al
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 104], 1
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 112], rax
    mov rax, QWORD [rbp - 104]
    mov rbx, QWORD [rbp - 112]
    test rax,rax
    setz al
    movzx rax,al
    test rbx,rbx
    setz bl
    movzx rbx,bl
    or rax,rbx
    xor rax,1
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 32]
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
    jne .L8
    lea rax, [rbp - 200]
    mov QWORD [rbp - 208], rax
    mov byte [rbp - 200], 'F'
    mov byte [rbp - 199], 'r'
    mov byte [rbp - 198], 'o'
    mov byte [rbp - 197], 'm'
    mov byte [rbp - 196], ' '
    mov byte [rbp - 195], 'm'
    mov byte [rbp - 194], 'i'
    mov byte [rbp - 193], 'x'
    mov byte [rbp - 192], 'e'
    mov byte [rbp - 191], 'd'
    mov byte [rbp - 190], '_'
    mov byte [rbp - 189], 'c'
    mov byte [rbp - 188], 'o'
    mov byte [rbp - 187], 'n'
    mov byte [rbp - 186], 't'
    mov byte [rbp - 185], 'r'
    mov byte [rbp - 184], 'o'
    mov byte [rbp - 183], 'l'
    mov byte [rbp - 182], '_'
    mov byte [rbp - 181], 'f'
    mov byte [rbp - 180], 'l'
    mov byte [rbp - 179], 'o'
    mov byte [rbp - 178], 'w'
    mov byte [rbp - 177], ' '
    mov byte [rbp - 176], ','
    mov byte [rbp - 175], ' '
    mov byte [rbp - 174], 'v'
    mov byte [rbp - 173], 'a'
    mov byte [rbp - 172], 'l'
    mov byte [rbp - 171], 'u'
    mov byte [rbp - 170], 'e'
    mov byte [rbp - 169], ' '
    mov byte [rbp - 168], ':'
    mov byte [rbp - 167], ' '
    mov byte [rbp - 166], '%'
    mov byte [rbp - 165], 'd'
    mov byte [rbp - 164], 0x0A
    mov byte [rbp - 163], 0
    mov rdi, QWORD [rbp - 208]
    mov QWORD [rbp - 216], 0
    mov rsi, QWORD [rbp - 216]
    mov QWORD [rbp - 224], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 224],rax
    jmp .L9
    .L8:
    lea rax, [rbp - 264]
    mov QWORD [rbp - 272], rax
    mov byte [rbp - 264], 'F'
    mov byte [rbp - 263], 'r'
    mov byte [rbp - 262], 'o'
    mov byte [rbp - 261], 'm'
    mov byte [rbp - 260], ' '
    mov byte [rbp - 259], 'm'
    mov byte [rbp - 258], 'i'
    mov byte [rbp - 257], 'x'
    mov byte [rbp - 256], 'e'
    mov byte [rbp - 255], 'd'
    mov byte [rbp - 254], '_'
    mov byte [rbp - 253], 'c'
    mov byte [rbp - 252], 'o'
    mov byte [rbp - 251], 'n'
    mov byte [rbp - 250], 't'
    mov byte [rbp - 249], 'r'
    mov byte [rbp - 248], 'o'
    mov byte [rbp - 247], 'l'
    mov byte [rbp - 246], '_'
    mov byte [rbp - 245], 'f'
    mov byte [rbp - 244], 'l'
    mov byte [rbp - 243], 'o'
    mov byte [rbp - 242], 'w'
    mov byte [rbp - 241], ' '
    mov byte [rbp - 240], ','
    mov byte [rbp - 239], ' '
    mov byte [rbp - 238], 'v'
    mov byte [rbp - 237], 'a'
    mov byte [rbp - 236], 'l'
    mov byte [rbp - 235], 'u'
    mov byte [rbp - 234], 'e'
    mov byte [rbp - 233], ' '
    mov byte [rbp - 232], ':'
    mov byte [rbp - 231], ' '
    mov byte [rbp - 230], '%'
    mov byte [rbp - 229], 'd'
    mov byte [rbp - 228], 0x0A
    mov byte [rbp - 227], 0
    mov rdi, QWORD [rbp - 272]
    mov QWORD [rbp - 280], 1
    mov rsi, QWORD [rbp - 280]
    mov QWORD [rbp - 288], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 288],rax
    .L9:
    leave
    ret

to_fail_str_comp_char:
    push rbp
    mov  rbp, rsp
    sub  rsp, 128
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], rsi
    lea rax, [rbp - 64]
    mov QWORD [rbp - 72], rax
    mov byte [rbp - 64], 'F'
    mov byte [rbp - 63], 'r'
    mov byte [rbp - 62], 'o'
    mov byte [rbp - 61], 'm'
    mov byte [rbp - 60], ' '
    mov byte [rbp - 59], 't'
    mov byte [rbp - 58], 'o'
    mov byte [rbp - 57], '_'
    mov byte [rbp - 56], 'f'
    mov byte [rbp - 55], 'a'
    mov byte [rbp - 54], 'i'
    mov byte [rbp - 53], 'l'
    mov byte [rbp - 52], '_'
    mov byte [rbp - 51], 's'
    mov byte [rbp - 50], 't'
    mov byte [rbp - 49], 'r'
    mov byte [rbp - 48], '_'
    mov byte [rbp - 47], 'c'
    mov byte [rbp - 46], 'o'
    mov byte [rbp - 45], 'm'
    mov byte [rbp - 44], 'p'
    mov byte [rbp - 43], '_'
    mov byte [rbp - 42], 'c'
    mov byte [rbp - 41], 'h'
    mov byte [rbp - 40], 'a'
    mov byte [rbp - 39], 'r'
    mov byte [rbp - 38], ' '
    mov byte [rbp - 37], ','
    mov byte [rbp - 36], ' '
    mov byte [rbp - 35], 'v'
    mov byte [rbp - 34], 'a'
    mov byte [rbp - 33], 'l'
    mov byte [rbp - 32], 'u'
    mov byte [rbp - 31], 'e'
    mov byte [rbp - 30], ' '
    mov byte [rbp - 29], ':'
    mov byte [rbp - 28], ' '
    mov byte [rbp - 27], '%'
    mov byte [rbp - 26], 'd'
    mov byte [rbp - 25], 0x0A
    mov byte [rbp - 24], 0
    mov rdi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 104], rax
    mov rsi, QWORD [rbp - 104]
    mov QWORD [rbp - 112], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 112],rax
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 496
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
    mov QWORD [rbp - 40], 2
    mov rdi, QWORD [rbp - 40]
    mov rax, 0x400c000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 48], xmm7
    movq xmm0, QWORD [rbp - 48]
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 56], xmm7
    mov rax, 1
    call float_and_int
    mov QWORD [rbp - 56],rax
    lea rax, [rbp - 64]
    mov QWORD [rbp - 72], rax
    mov byte [rbp - 64], 0x0A
    mov byte [rbp - 63], 0
    mov rdi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 80],rax
    mov QWORD [rbp - 88], 'a'
    mov rdi, QWORD [rbp - 88]
    mov QWORD [rbp - 96], 1
    mov rsi, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 11
    mov rdx, QWORD [rbp - 104]
    mov QWORD [rbp - 112], 0
    xor rax,rax
    call int_char_bool
    mov QWORD [rbp - 112],rax
    lea rax, [rbp - 120]
    mov QWORD [rbp - 128], rax
    mov byte [rbp - 120], 0x0A
    mov byte [rbp - 119], 0
    mov rdi, QWORD [rbp - 128]
    mov QWORD [rbp - 136], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 136],rax
    mov QWORD [rbp - 144], 'C'
    mov rdi, QWORD [rbp - 144]
    mov rax, 0x3fd1eb8520000000
    movq xmm7, rax
    movsd QWORD [rbp - 152], xmm7
    movq xmm0, QWORD [rbp - 152]
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 160], xmm7
    mov rax, 1
    call char_float
    mov QWORD [rbp - 160],rax
    lea rax, [rbp - 168]
    mov QWORD [rbp - 176], rax
    mov byte [rbp - 168], 0x0A
    mov byte [rbp - 167], 0
    mov rdi, QWORD [rbp - 176]
    mov QWORD [rbp - 184], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 184],rax
    mov QWORD [rbp - 192], 1
    mov rdi, QWORD [rbp - 192]
    mov rax, 0x4014000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 200], xmm7
    movq xmm0, QWORD [rbp - 200]
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 208], xmm7
    mov rax, 1
    call bool_float
    mov QWORD [rbp - 208],rax
    lea rax, [rbp - 216]
    mov QWORD [rbp - 224], rax
    mov byte [rbp - 216], 0x0A
    mov byte [rbp - 215], 0
    mov rdi, QWORD [rbp - 224]
    mov QWORD [rbp - 232], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 232],rax
    mov QWORD [rbp - 240], 'B'
    mov rdi, QWORD [rbp - 240]
    mov QWORD [rbp - 248], 66
    mov rsi, QWORD [rbp - 248]
    mov QWORD [rbp - 256], 0
    xor rax,rax
    call char_comp_int
    mov QWORD [rbp - 256],rax
    lea rax, [rbp - 264]
    mov QWORD [rbp - 272], rax
    mov byte [rbp - 264], 0x0A
    mov byte [rbp - 263], 0
    mov rdi, QWORD [rbp - 272]
    mov QWORD [rbp - 280], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 280],rax
    mov QWORD [rbp - 288], 10
    mov rdi, QWORD [rbp - 288]
    mov rax, 0x4024000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 296], xmm7
    movq xmm0, QWORD [rbp - 296]
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 304], xmm7
    mov rax, 1
    call float_comp_int
    mov QWORD [rbp - 304],rax
    lea rax, [rbp - 312]
    mov QWORD [rbp - 320], rax
    mov byte [rbp - 312], 0x0A
    mov byte [rbp - 311], 0
    mov rdi, QWORD [rbp - 320]
    mov QWORD [rbp - 328], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 328],rax
    mov QWORD [rbp - 336], 'a'
    mov rdi, QWORD [rbp - 336]
    mov rax, 0x4002a3d700000000
    movq xmm7, rax
    movsd QWORD [rbp - 344], xmm7
    movq xmm0, QWORD [rbp - 344]
    mov QWORD [rbp - 352], 1
    mov rsi, QWORD [rbp - 352]
    mov QWORD [rbp - 360], 7
    mov rdx, QWORD [rbp - 360]
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 368], xmm7
    mov rax, 1
    call mixed_sum
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
    mov QWORD [rbp - 400], 0
    xor rax,rax
    call mixed_control_flow
    mov QWORD [rbp - 400],rax
    lea rax, [rbp - 408]
    mov QWORD [rbp - 416], rax
    mov byte [rbp - 408], 0x0A
    mov byte [rbp - 407], 0
    mov rdi, QWORD [rbp - 416]
    mov QWORD [rbp - 424], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 424],rax
    mov QWORD [rbp - 432], 'h'
    mov rdi, QWORD [rbp - 432]
    lea rax, [rbp - 440]
    mov QWORD [rbp - 448], rax
    mov byte [rbp - 440], 'h'
    mov byte [rbp - 439], 0
    mov rsi, QWORD [rbp - 448]
    mov QWORD [rbp - 456], 0
    xor rax,rax
    call to_fail_str_comp_char
    mov QWORD [rbp - 456],rax
    lea rax, [rbp - 464]
    mov QWORD [rbp - 472], rax
    mov byte [rbp - 464], 0x0A
    mov byte [rbp - 463], 0
    mov rdi, QWORD [rbp - 472]
    mov QWORD [rbp - 480], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 480],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack
