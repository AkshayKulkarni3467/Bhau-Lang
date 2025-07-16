SECTION .data

SECTION .bss

SECTION .text
global  main
extern printf
ret_float:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    movsd QWORD [rbp - 8], xmm0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    leave
    ret
operator_add_float:
    push rbp
    mov  rbp, rsp
    sub  rsp, 64
    movsd QWORD [rbp - 8], xmm0
    movsd QWORD [rbp - 16], xmm1
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 40], rax
    movsd xmm0, QWORD [rbp - 32]
    movsd xmm1, QWORD [rbp - 40]
    addsd xmm0,xmm1
    movsd QWORD [rbp - 24],xmm0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    leave
    ret
op_mult_div_float:
    push rbp
    mov  rbp, rsp
    sub  rsp, 176
    movsd QWORD [rbp - 8], xmm0
    movsd QWORD [rbp - 16], xmm1
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 40], rax
    movsd xmm0, QWORD [rbp - 32]
    movsd xmm1, QWORD [rbp - 40]
    mulsd xmm0,xmm1
    movsd QWORD [rbp - 24],xmm0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 72], rax
    movsd xmm0, QWORD [rbp - 64]
    movsd xmm1, QWORD [rbp - 72]
    divsd xmm0,xmm1
    movsd QWORD [rbp - 56],xmm0
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 104], rax
    movsd xmm0, QWORD [rbp - 96]
    movsd xmm1, QWORD [rbp - 104]
    mulsd xmm0,xmm1
    movsd QWORD [rbp - 88],xmm0
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 120], rax
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 128], rax
    movsd xmm0, QWORD [rbp - 120]
    movsd xmm1, QWORD [rbp - 128]
    divsd xmm0,xmm1
    movsd QWORD [rbp - 112],xmm0
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 144], rax
    mov QWORD [rbp - 152], 0
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 152], rax
    movsd xmm0, QWORD [rbp - 144]
    movsd xmm1, QWORD [rbp - 152]
    mulsd xmm0,xmm1
    movsd QWORD [rbp - 136],xmm0
    mov rax, QWORD [rbp - 136]
    mov QWORD [rbp - 160], rax
    mov rax, QWORD [rbp - 160]
    leave
    ret
comparison_float:
    push rbp
    mov  rbp, rsp
    sub  rsp, 224
    movsd QWORD [rbp - 8], xmm0
    movsd QWORD [rbp - 16], xmm1
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 40], rax
    movsd xmm0, QWORD [rbp - 32]
    movsd xmm1, QWORD [rbp - 40]
    ucomisd xmm0,xmm1
    setb al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L0
    lea rax, [rbp - 96]
    mov QWORD [rbp - 104], rax
    mov byte [rbp - 96], 'F'
    mov byte [rbp - 95], 'r'
    mov byte [rbp - 94], 'o'
    mov byte [rbp - 93], 'm'
    mov byte [rbp - 92], ' '
    mov byte [rbp - 91], 'c'
    mov byte [rbp - 90], 'o'
    mov byte [rbp - 89], 'm'
    mov byte [rbp - 88], 'p'
    mov byte [rbp - 87], 'a'
    mov byte [rbp - 86], 'r'
    mov byte [rbp - 85], 'i'
    mov byte [rbp - 84], 's'
    mov byte [rbp - 83], 'o'
    mov byte [rbp - 82], 'n'
    mov byte [rbp - 81], '_'
    mov byte [rbp - 80], 'f'
    mov byte [rbp - 79], 'l'
    mov byte [rbp - 78], 'o'
    mov byte [rbp - 77], 'a'
    mov byte [rbp - 76], 't'
    mov byte [rbp - 75], ','
    mov byte [rbp - 74], ' '
    mov byte [rbp - 73], '%'
    mov byte [rbp - 72], '.'
    mov byte [rbp - 71], '2'
    mov byte [rbp - 70], 'f'
    mov byte [rbp - 69], ' '
    mov byte [rbp - 68], 'i'
    mov byte [rbp - 67], 's'
    mov byte [rbp - 66], ' '
    mov byte [rbp - 65], 'g'
    mov byte [rbp - 64], 'r'
    mov byte [rbp - 63], 'e'
    mov byte [rbp - 62], 'a'
    mov byte [rbp - 61], 't'
    mov byte [rbp - 60], 'e'
    mov byte [rbp - 59], 'r'
    mov byte [rbp - 58], ' '
    mov byte [rbp - 57], 't'
    mov byte [rbp - 56], 'h'
    mov byte [rbp - 55], 'a'
    mov byte [rbp - 54], 'n'
    mov byte [rbp - 53], ' '
    mov byte [rbp - 52], '%'
    mov byte [rbp - 51], '.'
    mov byte [rbp - 50], '2'
    mov byte [rbp - 49], 'f'
    mov byte [rbp - 48], 0x0A
    mov byte [rbp - 47], 0
    mov rdi, QWORD [rbp - 104]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 112], rax
    movq xmm0, QWORD [rbp - 112]
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 120], rax
    movq xmm1, QWORD [rbp - 120]
    mov QWORD [rbp - 128], 0
    mov rax, 2
    call printf
    mov QWORD [rbp - 128],rax
    jmp .L1
    .L0:
    lea rax, [rbp - 176]
    mov QWORD [rbp - 184], rax
    mov byte [rbp - 176], 'F'
    mov byte [rbp - 175], 'r'
    mov byte [rbp - 174], 'o'
    mov byte [rbp - 173], 'm'
    mov byte [rbp - 172], ' '
    mov byte [rbp - 171], 'c'
    mov byte [rbp - 170], 'o'
    mov byte [rbp - 169], 'm'
    mov byte [rbp - 168], 'p'
    mov byte [rbp - 167], 'a'
    mov byte [rbp - 166], 'r'
    mov byte [rbp - 165], 'i'
    mov byte [rbp - 164], 's'
    mov byte [rbp - 163], 'o'
    mov byte [rbp - 162], 'n'
    mov byte [rbp - 161], '_'
    mov byte [rbp - 160], 'f'
    mov byte [rbp - 159], 'l'
    mov byte [rbp - 158], 'o'
    mov byte [rbp - 157], 'a'
    mov byte [rbp - 156], 't'
    mov byte [rbp - 155], ','
    mov byte [rbp - 154], ' '
    mov byte [rbp - 153], '%'
    mov byte [rbp - 152], '.'
    mov byte [rbp - 151], '2'
    mov byte [rbp - 150], 'f'
    mov byte [rbp - 149], ' '
    mov byte [rbp - 148], 'i'
    mov byte [rbp - 147], 's'
    mov byte [rbp - 146], ' '
    mov byte [rbp - 145], 'l'
    mov byte [rbp - 144], 'e'
    mov byte [rbp - 143], 's'
    mov byte [rbp - 142], 's'
    mov byte [rbp - 141], ' '
    mov byte [rbp - 140], 't'
    mov byte [rbp - 139], 'h'
    mov byte [rbp - 138], 'a'
    mov byte [rbp - 137], 'n'
    mov byte [rbp - 136], ' '
    mov byte [rbp - 135], '%'
    mov byte [rbp - 134], '.'
    mov byte [rbp - 133], '2'
    mov byte [rbp - 132], 'f'
    mov byte [rbp - 131], 0x0A
    mov byte [rbp - 130], 0
    mov rdi, QWORD [rbp - 184]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 192], rax
    movq xmm0, QWORD [rbp - 192]
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 200], rax
    movq xmm1, QWORD [rbp - 200]
    mov QWORD [rbp - 208], 0
    mov rax, 2
    call printf
    mov QWORD [rbp - 208],rax
    .L1:
    leave
    ret

type_mixing:
    push rbp
    mov  rbp, rsp
    sub  rsp, 64
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
    mulsd xmm0,xmm1
    movsd QWORD [rbp - 24],xmm0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    leave
    ret
pre_inc_float:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    movsd QWORD [rbp - 8], xmm0
    mov QWORD [rbp - 16], 0
    movsd xmm0, QWORD [rbp-8]
    mov    rax, 0x3ff0000000000000
    movq   xmm1, rax
    addsd  xmm0, xmm1
    movsd  QWORD [rbp-16], xmm0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 8], rax
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    leave
    ret
loop_float:
    push rbp
    mov  rbp, rsp
    sub  rsp, 160
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 8], xmm7
    .L2:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov rax, 0x4014000000000000
    movq xmm0, rax
    movsd QWORD [rbp - 32], xmm0
    movsd xmm0, QWORD [rbp - 24]
    movsd xmm1, QWORD [rbp - 32]
    ucomisd xmm0,xmm1
    setb al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L3
    jmp .L4
    .L3:
    lea rax, [rbp - 96]
    mov QWORD [rbp - 104], rax
    mov byte [rbp - 96], 'F'
    mov byte [rbp - 95], 'r'
    mov byte [rbp - 94], 'o'
    mov byte [rbp - 93], 'm'
    mov byte [rbp - 92], ' '
    mov byte [rbp - 91], 'l'
    mov byte [rbp - 90], 'o'
    mov byte [rbp - 89], 'o'
    mov byte [rbp - 88], 'p'
    mov byte [rbp - 87], '_'
    mov byte [rbp - 86], 'f'
    mov byte [rbp - 85], 'l'
    mov byte [rbp - 84], 'o'
    mov byte [rbp - 83], 'a'
    mov byte [rbp - 82], 't'
    mov byte [rbp - 81], ','
    mov byte [rbp - 80], ' '
    mov byte [rbp - 79], 'V'
    mov byte [rbp - 78], 'a'
    mov byte [rbp - 77], 'l'
    mov byte [rbp - 76], 'u'
    mov byte [rbp - 75], 'e'
    mov byte [rbp - 74], ' '
    mov byte [rbp - 73], 'a'
    mov byte [rbp - 72], ' '
    mov byte [rbp - 71], ':'
    mov byte [rbp - 70], ' '
    mov byte [rbp - 69], '%'
    mov byte [rbp - 68], '.'
    mov byte [rbp - 67], '2'
    mov byte [rbp - 66], 'f'
    mov byte [rbp - 65], 0x0A
    mov byte [rbp - 64], 0
    mov rdi, QWORD [rbp - 104]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 112], rax
    movq xmm0, QWORD [rbp - 112]
    mov QWORD [rbp - 120], 0
    mov rax, 1
    call printf
    mov QWORD [rbp - 120],rax
    mov QWORD [rbp - 128], 0
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 136], rax
    mov QWORD [rbp - 144], 0
    mov rax, 0x3ff8000000000000
    movq xmm0, rax
    movsd QWORD [rbp - 144], xmm0
    movsd xmm0, QWORD [rbp - 136]
    movsd xmm1, QWORD [rbp - 144]
    addsd xmm0,xmm1
    movsd QWORD [rbp - 128],xmm0
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 8], rax
    jmp .L2
    .L4:
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
    jne .L5
    mov rax, 0x4017666680000000
    movq xmm0, rax
    movsd QWORD [rbp - 24], xmm0
    jmp .L6
    .L5:
    mov rax, 0xbfdb851f00000000
    movq xmm0, rax
    movsd QWORD [rbp - 24], xmm0
    .L6:
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
    jne .L7
    jmp .L8
    .L7:
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
    .L8:
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 688
    mov rax, 0x40091eb860000000
    movq xmm7, rax
    movsd QWORD [rbp - 8], xmm7
    movq xmm0, QWORD [rbp - 8]
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 16], xmm7
    mov rax, 1
    call ret_float
    mov QWORD [rbp - 16],rax
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 24], rax
    lea rax, [rbp - 64]
    mov QWORD [rbp - 72], rax
    mov byte [rbp - 64], 'F'
    mov byte [rbp - 63], 'r'
    mov byte [rbp - 62], 'o'
    mov byte [rbp - 61], 'm'
    mov byte [rbp - 60], ' '
    mov byte [rbp - 59], 'r'
    mov byte [rbp - 58], 'e'
    mov byte [rbp - 57], 't'
    mov byte [rbp - 56], '_'
    mov byte [rbp - 55], 'f'
    mov byte [rbp - 54], 'l'
    mov byte [rbp - 53], 'o'
    mov byte [rbp - 52], 'a'
    mov byte [rbp - 51], 't'
    mov byte [rbp - 50], '_'
    mov byte [rbp - 49], 'v'
    mov byte [rbp - 48], 'a'
    mov byte [rbp - 47], 'r'
    mov byte [rbp - 46], ','
    mov byte [rbp - 45], ' '
    mov byte [rbp - 44], 'V'
    mov byte [rbp - 43], 'a'
    mov byte [rbp - 42], 'l'
    mov byte [rbp - 41], 'u'
    mov byte [rbp - 40], 'e'
    mov byte [rbp - 39], ' '
    mov byte [rbp - 38], ':'
    mov byte [rbp - 37], ' '
    mov byte [rbp - 36], '%'
    mov byte [rbp - 35], '.'
    mov byte [rbp - 34], '2'
    mov byte [rbp - 33], 'f'
    mov byte [rbp - 32], 0x0A
    mov byte [rbp - 31], 0
    mov rdi, QWORD [rbp - 72]
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 80], rax
    movq xmm0, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 0
    mov rax, 1
    call printf
    mov QWORD [rbp - 88],rax
    lea rax, [rbp - 96]
    mov QWORD [rbp - 104], rax
    mov byte [rbp - 96], 0x0A
    mov byte [rbp - 95], 0
    mov rdi, QWORD [rbp - 104]
    mov QWORD [rbp - 112], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 112],rax
    mov rax, 0x401b9999a0000000
    movq xmm7, rax
    movsd QWORD [rbp - 120], xmm7
    movq xmm0, QWORD [rbp - 120]
    mov rax, 0x401b9999a0000000
    movq xmm7, rax
    movsd QWORD [rbp - 128], xmm7
    movq xmm1, QWORD [rbp - 128]
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 136], xmm7
    mov rax, 2
    call operator_add_float
    mov QWORD [rbp - 136],rax
    mov rax, QWORD [rbp - 136]
    mov QWORD [rbp - 144], rax
    lea rax, [rbp - 184]
    mov QWORD [rbp - 192], rax
    mov byte [rbp - 184], 'F'
    mov byte [rbp - 183], 'r'
    mov byte [rbp - 182], 'o'
    mov byte [rbp - 181], 'm'
    mov byte [rbp - 180], ' '
    mov byte [rbp - 179], 'o'
    mov byte [rbp - 178], 'p'
    mov byte [rbp - 177], 'e'
    mov byte [rbp - 176], 'r'
    mov byte [rbp - 175], 'a'
    mov byte [rbp - 174], 't'
    mov byte [rbp - 173], 'o'
    mov byte [rbp - 172], 'r'
    mov byte [rbp - 171], '_'
    mov byte [rbp - 170], 'a'
    mov byte [rbp - 169], 'd'
    mov byte [rbp - 168], 'd'
    mov byte [rbp - 167], '_'
    mov byte [rbp - 166], 'f'
    mov byte [rbp - 165], 'l'
    mov byte [rbp - 164], 'o'
    mov byte [rbp - 163], 'a'
    mov byte [rbp - 162], 't'
    mov byte [rbp - 161], ','
    mov byte [rbp - 160], ' '
    mov byte [rbp - 159], 'V'
    mov byte [rbp - 158], 'a'
    mov byte [rbp - 157], 'l'
    mov byte [rbp - 156], 'u'
    mov byte [rbp - 155], 'e'
    mov byte [rbp - 154], ' '
    mov byte [rbp - 153], ':'
    mov byte [rbp - 152], ' '
    mov byte [rbp - 151], '%'
    mov byte [rbp - 150], '.'
    mov byte [rbp - 149], '2'
    mov byte [rbp - 148], 'f'
    mov byte [rbp - 147], 0x0A
    mov byte [rbp - 146], 0
    mov rdi, QWORD [rbp - 192]
    mov rax, QWORD [rbp - 144]
    mov QWORD [rbp - 200], rax
    movq xmm0, QWORD [rbp - 200]
    mov QWORD [rbp - 208], 0
    mov rax, 1
    call printf
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
    mov rax, 0x4024000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 240], xmm7
    movq xmm0, QWORD [rbp - 240]
    mov rax, 0x4004000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 248], xmm7
    movq xmm1, QWORD [rbp - 248]
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 256], xmm7
    mov rax, 2
    call op_mult_div_float
    mov QWORD [rbp - 256],rax
    mov rax, QWORD [rbp - 256]
    mov QWORD [rbp - 264], rax
    lea rax, [rbp - 304]
    mov QWORD [rbp - 312], rax
    mov byte [rbp - 304], 'F'
    mov byte [rbp - 303], 'r'
    mov byte [rbp - 302], 'o'
    mov byte [rbp - 301], 'm'
    mov byte [rbp - 300], ' '
    mov byte [rbp - 299], 'o'
    mov byte [rbp - 298], 'p'
    mov byte [rbp - 297], '_'
    mov byte [rbp - 296], 'm'
    mov byte [rbp - 295], 'u'
    mov byte [rbp - 294], 'l'
    mov byte [rbp - 293], 't'
    mov byte [rbp - 292], '_'
    mov byte [rbp - 291], 'd'
    mov byte [rbp - 290], 'i'
    mov byte [rbp - 289], 'v'
    mov byte [rbp - 288], '_'
    mov byte [rbp - 287], 'f'
    mov byte [rbp - 286], 'l'
    mov byte [rbp - 285], 'o'
    mov byte [rbp - 284], 'a'
    mov byte [rbp - 283], 't'
    mov byte [rbp - 282], ','
    mov byte [rbp - 281], ' '
    mov byte [rbp - 280], 'V'
    mov byte [rbp - 279], 'a'
    mov byte [rbp - 278], 'l'
    mov byte [rbp - 277], 'u'
    mov byte [rbp - 276], 'e'
    mov byte [rbp - 275], ' '
    mov byte [rbp - 274], ':'
    mov byte [rbp - 273], ' '
    mov byte [rbp - 272], '%'
    mov byte [rbp - 271], '.'
    mov byte [rbp - 270], '2'
    mov byte [rbp - 269], 'f'
    mov byte [rbp - 268], 0x0A
    mov byte [rbp - 267], 0
    mov rdi, QWORD [rbp - 312]
    mov rax, QWORD [rbp - 264]
    mov QWORD [rbp - 320], rax
    movq xmm0, QWORD [rbp - 320]
    mov QWORD [rbp - 328], 0
    mov rax, 1
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
    mov rax, 0x4024000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 360], xmm7
    movq xmm0, QWORD [rbp - 360]
    mov rax, 0x4004000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 368], xmm7
    movq xmm1, QWORD [rbp - 368]
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 376], xmm7
    mov rax, 2
    call comparison_float
    mov QWORD [rbp - 376],rax
    lea rax, [rbp - 384]
    mov QWORD [rbp - 392], rax
    mov byte [rbp - 384], 0x0A
    mov byte [rbp - 383], 0
    mov rdi, QWORD [rbp - 392]
    mov QWORD [rbp - 400], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 400],rax
    mov QWORD [rbp - 408], 10
    mov rdi, QWORD [rbp - 408]
    mov rax, 0x4004000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 416], xmm7
    movq xmm0, QWORD [rbp - 416]
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 424], xmm7
    mov rax, 1
    call type_mixing
    mov QWORD [rbp - 424],rax
    mov rax, QWORD [rbp - 424]
    mov QWORD [rbp - 432], rax
    lea rax, [rbp - 472]
    mov QWORD [rbp - 480], rax
    mov byte [rbp - 472], 'F'
    mov byte [rbp - 471], 'r'
    mov byte [rbp - 470], 'o'
    mov byte [rbp - 469], 'm'
    mov byte [rbp - 468], ' '
    mov byte [rbp - 467], 't'
    mov byte [rbp - 466], 'y'
    mov byte [rbp - 465], 'p'
    mov byte [rbp - 464], 'e'
    mov byte [rbp - 463], '_'
    mov byte [rbp - 462], 'm'
    mov byte [rbp - 461], 'i'
    mov byte [rbp - 460], 'x'
    mov byte [rbp - 459], 'i'
    mov byte [rbp - 458], 'n'
    mov byte [rbp - 457], 'g'
    mov byte [rbp - 456], ','
    mov byte [rbp - 455], ' '
    mov byte [rbp - 454], 'V'
    mov byte [rbp - 453], 'a'
    mov byte [rbp - 452], 'l'
    mov byte [rbp - 451], 'u'
    mov byte [rbp - 450], 'e'
    mov byte [rbp - 449], ' '
    mov byte [rbp - 448], ':'
    mov byte [rbp - 447], ' '
    mov byte [rbp - 446], '%'
    mov byte [rbp - 445], '.'
    mov byte [rbp - 444], '2'
    mov byte [rbp - 443], 'f'
    mov byte [rbp - 442], 0x0A
    mov byte [rbp - 441], 0
    mov rdi, QWORD [rbp - 480]
    mov rax, QWORD [rbp - 432]
    mov QWORD [rbp - 488], rax
    movq xmm0, QWORD [rbp - 488]
    mov QWORD [rbp - 496], 0
    mov rax, 1
    call printf
    mov QWORD [rbp - 496],rax
    lea rax, [rbp - 504]
    mov QWORD [rbp - 512], rax
    mov byte [rbp - 504], 0x0A
    mov byte [rbp - 503], 0
    mov rdi, QWORD [rbp - 512]
    mov QWORD [rbp - 520], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 520],rax
    mov rax, 0x4009d70a40000000
    movq xmm7, rax
    movsd QWORD [rbp - 528], xmm7
    movq xmm0, QWORD [rbp - 528]
    mov rax, 0x0000000000000000
    movq xmm7, rax
    movsd QWORD [rbp - 536], xmm7
    mov rax, 1
    call pre_inc_float
    mov QWORD [rbp - 536],rax
    mov rax, QWORD [rbp - 536]
    mov QWORD [rbp - 544], rax
    lea rax, [rbp - 584]
    mov QWORD [rbp - 592], rax
    mov byte [rbp - 584], 'F'
    mov byte [rbp - 583], 'r'
    mov byte [rbp - 582], 'o'
    mov byte [rbp - 581], 'm'
    mov byte [rbp - 580], ' '
    mov byte [rbp - 579], 'p'
    mov byte [rbp - 578], 'r'
    mov byte [rbp - 577], 'e'
    mov byte [rbp - 576], '_'
    mov byte [rbp - 575], 'i'
    mov byte [rbp - 574], 'n'
    mov byte [rbp - 573], 'c'
    mov byte [rbp - 572], '_'
    mov byte [rbp - 571], 'f'
    mov byte [rbp - 570], 'l'
    mov byte [rbp - 569], 'o'
    mov byte [rbp - 568], 'a'
    mov byte [rbp - 567], 't'
    mov byte [rbp - 566], ','
    mov byte [rbp - 565], ' '
    mov byte [rbp - 564], 'V'
    mov byte [rbp - 563], 'a'
    mov byte [rbp - 562], 'l'
    mov byte [rbp - 561], 'u'
    mov byte [rbp - 560], 'e'
    mov byte [rbp - 559], ' '
    mov byte [rbp - 558], ':'
    mov byte [rbp - 557], ' '
    mov byte [rbp - 556], '%'
    mov byte [rbp - 555], '.'
    mov byte [rbp - 554], '2'
    mov byte [rbp - 553], 'f'
    mov byte [rbp - 552], 0x0A
    mov byte [rbp - 551], 0
    mov rdi, QWORD [rbp - 592]
    mov rax, QWORD [rbp - 544]
    mov QWORD [rbp - 600], rax
    movq xmm0, QWORD [rbp - 600]
    mov QWORD [rbp - 608], 0
    mov rax, 1
    call printf
    mov QWORD [rbp - 608],rax
    lea rax, [rbp - 616]
    mov QWORD [rbp - 624], rax
    mov byte [rbp - 616], 0x0A
    mov byte [rbp - 615], 0
    mov rdi, QWORD [rbp - 624]
    mov QWORD [rbp - 632], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 632],rax
    mov QWORD [rbp - 640], 0
    xor rax,rax
    call loop_float
    mov QWORD [rbp - 640],rax
    mov QWORD [rbp - 648], 0
    xor rax,rax
    call float_control_flow
    mov QWORD [rbp - 648],rax
    lea rax, [rbp - 656]
    mov QWORD [rbp - 664], rax
    mov byte [rbp - 656], 0x0A
    mov byte [rbp - 655], 0
    mov rdi, QWORD [rbp - 664]
    mov QWORD [rbp - 672], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 672],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack
