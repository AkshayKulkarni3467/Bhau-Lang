SECTION .data
global_rule          dq 137
global_width         dq 65
global_steps         dq 32

SECTION .bss

SECTION .text
global  main
extern putchar
extern printf
print_state:
    push rbp
    mov  rbp, rsp
    sub  rsp, 192
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, [global_width]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 1
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    sub rax,rbx
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 40], rax
    .L0:
    mov QWORD [rbp - 48], 0
    mov QWORD [rbp - 56], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 56], rax
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 56]
    mov rbx, QWORD [rbp - 64]
    cmp rax,rbx
    setge al
    movzx rax,al
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    cmp rax, 0
    jne .L1
    jmp .L2
    .L1:
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 112], rax
    mov rax, QWORD [rbp - 104]
    mov rbx, QWORD [rbp - 112]
    and rbx, 63
    mov rcx, rbx
    shr rax,cl
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 136], 1
    mov rax, QWORD [rbp - 128]
    mov rbx, QWORD [rbp - 136]
    and rax,rbx
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 120]
    cmp rax, 0
    jne .L3
    mov QWORD [rbp - 152], ' '
    mov rdi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 0
    xor rax,rax
    call putchar
    mov QWORD [rbp - 160],rax
    jmp .L4
    .L3:
    mov QWORD [rbp - 168], '*'
    mov rdi, QWORD [rbp - 168]
    mov QWORD [rbp - 176], 0
    xor rax,rax
    call putchar
    mov QWORD [rbp - 176],rax
    .L4:
    mov QWORD [rbp - 144], 0
    mov rax, [rbp - 40]
    dec rax
    mov [rbp - 144],rax
    mov rax, QWORD [rbp - 144]
    mov QWORD [rbp - 40], rax
    jmp .L0
    .L2:
    lea rax, [rbp - 72]
    mov QWORD [rbp - 80], rax
    mov byte [rbp - 72], 0x0A
    mov byte [rbp - 71], 0
    mov rdi, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 88],rax
    leave
    ret

update_state:
    push rbp
    mov  rbp, rsp
    sub  rsp, 928
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], rsi
    mov QWORD [rbp - 24], rdx
    mov QWORD [rbp - 32], rcx
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov QWORD [rbp - 56], 0
    mov rax, [global_width]
    mov QWORD [rbp - 56], rax
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 64], 1
    mov rax, QWORD [rbp - 56]
    mov rbx, QWORD [rbp - 64]
    sub rax,rbx
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 88], rax
    mov rax, QWORD [rbp - 80]
    mov rbx, QWORD [rbp - 88]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 72]
    cmp rax, 0
    jne .L5
    mov QWORD [rbp - 736], 0
    mov QWORD [rbp - 744], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 744], rax
    mov QWORD [rbp - 752], 0
    mov QWORD [rbp - 752], 1
    mov rax, QWORD [rbp - 744]
    mov rbx, QWORD [rbp - 752]
    add rax,rbx
    mov QWORD [rbp - 736], rax
    mov QWORD [rbp - 760], 0
    mov QWORD [rbp - 768], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 768], rax
    mov QWORD [rbp - 776], 0
    mov rax, QWORD [rbp - 736]
    mov QWORD [rbp - 776], rax
    mov rax, QWORD [rbp - 768]
    mov rbx, QWORD [rbp - 776]
    and rbx, 63
    mov rcx, rbx
    shr rax,cl
    mov QWORD [rbp - 760], rax
    mov QWORD [rbp - 784], 0
    mov QWORD [rbp - 792], 0
    mov rax, QWORD [rbp - 760]
    mov QWORD [rbp - 792], rax
    mov QWORD [rbp - 800], 0
    mov QWORD [rbp - 800], 1
    mov rax, QWORD [rbp - 792]
    mov rbx, QWORD [rbp - 800]
    and rax,rbx
    mov QWORD [rbp - 784], rax
    mov rax, QWORD [rbp - 784]
    mov QWORD [rbp - 40], rax
    jmp .L6
    .L5:
    mov QWORD [rbp - 40], 0
    .L6:
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 112], rax
    mov rax, QWORD [rbp - 104]
    mov rbx, QWORD [rbp - 112]
    and rbx, 63
    mov rcx, rbx
    shr rax,cl
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 136], 1
    mov rax, QWORD [rbp - 128]
    mov rbx, QWORD [rbp - 136]
    and rax,rbx
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 144], rax
    mov QWORD [rbp - 152], 0
    mov QWORD [rbp - 160], 0
    mov QWORD [rbp - 168], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 168], rax
    mov QWORD [rbp - 176], 0
    mov QWORD [rbp - 176], 0
    mov rax, QWORD [rbp - 168]
    mov rbx, QWORD [rbp - 176]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 160], rax
    mov rax, QWORD [rbp - 160]
    cmp rax, 0
    jne .L7
    mov QWORD [rbp - 808], 0
    mov QWORD [rbp - 816], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 816], rax
    mov QWORD [rbp - 824], 0
    mov QWORD [rbp - 824], 1
    mov rax, QWORD [rbp - 816]
    mov rbx, QWORD [rbp - 824]
    sub rax,rbx
    mov QWORD [rbp - 808], rax
    mov QWORD [rbp - 832], 0
    mov QWORD [rbp - 840], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 840], rax
    mov QWORD [rbp - 848], 0
    mov rax, QWORD [rbp - 808]
    mov QWORD [rbp - 848], rax
    mov rax, QWORD [rbp - 840]
    mov rbx, QWORD [rbp - 848]
    and rbx, 63
    mov rcx, rbx
    shr rax,cl
    mov QWORD [rbp - 832], rax
    mov QWORD [rbp - 856], 0
    mov QWORD [rbp - 864], 0
    mov rax, QWORD [rbp - 832]
    mov QWORD [rbp - 864], rax
    mov QWORD [rbp - 872], 0
    mov QWORD [rbp - 872], 1
    mov rax, QWORD [rbp - 864]
    mov rbx, QWORD [rbp - 872]
    and rax,rbx
    mov QWORD [rbp - 856], rax
    mov rax, QWORD [rbp - 856]
    mov QWORD [rbp - 152], rax
    jmp .L8
    .L7:
    mov QWORD [rbp - 152], 0
    .L8:
    mov QWORD [rbp - 184], 0
    mov QWORD [rbp - 192], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 192], rax
    mov QWORD [rbp - 200], 0
    mov QWORD [rbp - 200], 2
    mov rax, QWORD [rbp - 192]
    mov rbx, QWORD [rbp - 200]
    and rbx, 63
    mov rcx, rbx
    shl rax, cl
    mov QWORD [rbp - 184], rax
    mov QWORD [rbp - 208], 0
    mov QWORD [rbp - 216], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 216], rax
    mov QWORD [rbp - 224], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 224], rax
    mov rax, QWORD [rbp - 216]
    mov rbx, QWORD [rbp - 224]
    and rbx, 63
    mov rcx, rbx
    shr rax,cl
    mov QWORD [rbp - 208], rax
    mov QWORD [rbp - 232], 0
    mov QWORD [rbp - 240], 0
    mov rax, QWORD [rbp - 208]
    mov QWORD [rbp - 240], rax
    mov QWORD [rbp - 248], 0
    mov QWORD [rbp - 248], 1
    mov rax, QWORD [rbp - 240]
    mov rbx, QWORD [rbp - 248]
    and rax,rbx
    mov QWORD [rbp - 232], rax
    mov QWORD [rbp - 256], 0
    mov QWORD [rbp - 264], 0
    mov rax, QWORD [rbp - 232]
    mov QWORD [rbp - 264], rax
    mov QWORD [rbp - 272], 0
    mov QWORD [rbp - 272], 1
    mov rax, QWORD [rbp - 264]
    mov rbx, QWORD [rbp - 272]
    and rbx, 63
    mov rcx, rbx
    shl rax, cl
    mov QWORD [rbp - 256], rax
    mov QWORD [rbp - 280], 0
    mov QWORD [rbp - 288], 0
    mov rax, QWORD [rbp - 184]
    mov QWORD [rbp - 288], rax
    mov QWORD [rbp - 296], 0
    mov rax, QWORD [rbp - 256]
    mov QWORD [rbp - 296], rax
    mov rax, QWORD [rbp - 288]
    mov rbx, QWORD [rbp - 296]
    or rax,rbx
    mov QWORD [rbp - 280], rax
    mov QWORD [rbp - 304], 0
    mov QWORD [rbp - 312], 0
    mov rax, QWORD [rbp - 280]
    mov QWORD [rbp - 312], rax
    mov QWORD [rbp - 320], 0
    mov rax, QWORD [rbp - 152]
    mov QWORD [rbp - 320], rax
    mov rax, QWORD [rbp - 312]
    mov rbx, QWORD [rbp - 320]
    or rax,rbx
    mov QWORD [rbp - 304], rax
    mov rax, QWORD [rbp - 304]
    mov QWORD [rbp - 328], rax
    mov QWORD [rbp - 336], 0
    mov QWORD [rbp - 344], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 344], rax
    mov QWORD [rbp - 352], 0
    mov QWORD [rbp - 352], 2
    mov rax, QWORD [rbp - 344]
    mov rbx, QWORD [rbp - 352]
    and rbx, 63
    mov rcx, rbx
    shl rax, cl
    mov QWORD [rbp - 336], rax
    mov QWORD [rbp - 360], 0
    mov QWORD [rbp - 368], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 368], rax
    mov QWORD [rbp - 376], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 376], rax
    mov rax, QWORD [rbp - 368]
    mov rbx, QWORD [rbp - 376]
    and rbx, 63
    mov rcx, rbx
    shr rax,cl
    mov QWORD [rbp - 360], rax
    mov QWORD [rbp - 384], 0
    mov QWORD [rbp - 392], 0
    mov rax, QWORD [rbp - 360]
    mov QWORD [rbp - 392], rax
    mov QWORD [rbp - 400], 0
    mov QWORD [rbp - 400], 1
    mov rax, QWORD [rbp - 392]
    mov rbx, QWORD [rbp - 400]
    and rax,rbx
    mov QWORD [rbp - 384], rax
    mov QWORD [rbp - 408], 0
    mov QWORD [rbp - 416], 0
    mov rax, QWORD [rbp - 384]
    mov QWORD [rbp - 416], rax
    mov QWORD [rbp - 424], 0
    mov QWORD [rbp - 424], 1
    mov rax, QWORD [rbp - 416]
    mov rbx, QWORD [rbp - 424]
    and rbx, 63
    mov rcx, rbx
    shl rax, cl
    mov QWORD [rbp - 408], rax
    mov QWORD [rbp - 432], 0
    mov QWORD [rbp - 440], 0
    mov rax, QWORD [rbp - 336]
    mov QWORD [rbp - 440], rax
    mov QWORD [rbp - 448], 0
    mov rax, QWORD [rbp - 408]
    mov QWORD [rbp - 448], rax
    mov rax, QWORD [rbp - 440]
    mov rbx, QWORD [rbp - 448]
    or rax,rbx
    mov QWORD [rbp - 432], rax
    mov QWORD [rbp - 456], 0
    mov QWORD [rbp - 464], 0
    mov rax, QWORD [rbp - 432]
    mov QWORD [rbp - 464], rax
    mov QWORD [rbp - 472], 0
    mov rax, QWORD [rbp - 152]
    mov QWORD [rbp - 472], rax
    mov rax, QWORD [rbp - 464]
    mov rbx, QWORD [rbp - 472]
    or rax,rbx
    mov QWORD [rbp - 456], rax
    mov QWORD [rbp - 480], 0
    mov QWORD [rbp - 488], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 488], rax
    mov QWORD [rbp - 496], 0
    mov rax, QWORD [rbp - 456]
    mov QWORD [rbp - 496], rax
    mov rax, QWORD [rbp - 488]
    mov rbx, QWORD [rbp - 496]
    and rbx, 63
    mov rcx, rbx
    shr rax,cl
    mov QWORD [rbp - 480], rax
    mov QWORD [rbp - 504], 0
    mov QWORD [rbp - 512], 0
    mov rax, QWORD [rbp - 480]
    mov QWORD [rbp - 512], rax
    mov QWORD [rbp - 520], 0
    mov QWORD [rbp - 520], 1
    mov rax, QWORD [rbp - 512]
    mov rbx, QWORD [rbp - 520]
    and rax,rbx
    mov QWORD [rbp - 504], rax
    mov rax, QWORD [rbp - 504]
    mov QWORD [rbp - 528], rax
    mov QWORD [rbp - 536], 0
    mov QWORD [rbp - 544], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 544], rax
    mov QWORD [rbp - 552], 0
    mov QWORD [rbp - 552], 2
    mov rax, QWORD [rbp - 544]
    mov rbx, QWORD [rbp - 552]
    and rbx, 63
    mov rcx, rbx
    shl rax, cl
    mov QWORD [rbp - 536], rax
    mov QWORD [rbp - 560], 0
    mov QWORD [rbp - 568], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 568], rax
    mov QWORD [rbp - 576], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 576], rax
    mov rax, QWORD [rbp - 568]
    mov rbx, QWORD [rbp - 576]
    and rbx, 63
    mov rcx, rbx
    shr rax,cl
    mov QWORD [rbp - 560], rax
    mov QWORD [rbp - 584], 0
    mov QWORD [rbp - 592], 0
    mov rax, QWORD [rbp - 560]
    mov QWORD [rbp - 592], rax
    mov QWORD [rbp - 600], 0
    mov QWORD [rbp - 600], 1
    mov rax, QWORD [rbp - 592]
    mov rbx, QWORD [rbp - 600]
    and rax,rbx
    mov QWORD [rbp - 584], rax
    mov QWORD [rbp - 608], 0
    mov QWORD [rbp - 616], 0
    mov rax, QWORD [rbp - 584]
    mov QWORD [rbp - 616], rax
    mov QWORD [rbp - 624], 0
    mov QWORD [rbp - 624], 1
    mov rax, QWORD [rbp - 616]
    mov rbx, QWORD [rbp - 624]
    and rbx, 63
    mov rcx, rbx
    shl rax, cl
    mov QWORD [rbp - 608], rax
    mov QWORD [rbp - 632], 0
    mov QWORD [rbp - 640], 0
    mov rax, QWORD [rbp - 536]
    mov QWORD [rbp - 640], rax
    mov QWORD [rbp - 648], 0
    mov rax, QWORD [rbp - 608]
    mov QWORD [rbp - 648], rax
    mov rax, QWORD [rbp - 640]
    mov rbx, QWORD [rbp - 648]
    or rax,rbx
    mov QWORD [rbp - 632], rax
    mov QWORD [rbp - 656], 0
    mov QWORD [rbp - 664], 0
    mov rax, QWORD [rbp - 632]
    mov QWORD [rbp - 664], rax
    mov QWORD [rbp - 672], 0
    mov rax, QWORD [rbp - 152]
    mov QWORD [rbp - 672], rax
    mov rax, QWORD [rbp - 664]
    mov rbx, QWORD [rbp - 672]
    or rax,rbx
    mov QWORD [rbp - 656], rax
    mov QWORD [rbp - 680], 0
    mov QWORD [rbp - 688], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 688], rax
    mov QWORD [rbp - 696], 0
    mov rax, QWORD [rbp - 656]
    mov QWORD [rbp - 696], rax
    mov rax, QWORD [rbp - 688]
    mov rbx, QWORD [rbp - 696]
    and rbx, 63
    mov rcx, rbx
    shr rax,cl
    mov QWORD [rbp - 680], rax
    mov QWORD [rbp - 704], 0
    mov QWORD [rbp - 712], 0
    mov rax, QWORD [rbp - 680]
    mov QWORD [rbp - 712], rax
    mov QWORD [rbp - 720], 0
    mov QWORD [rbp - 720], 1
    mov rax, QWORD [rbp - 712]
    mov rbx, QWORD [rbp - 720]
    and rax,rbx
    mov QWORD [rbp - 704], rax
    mov rax, QWORD [rbp - 704]
    cmp rax, 0
    jne .L9
    jmp .L10
    .L9:
    mov QWORD [rbp - 880], 0
    mov QWORD [rbp - 888], 0
    mov QWORD [rbp - 888], 1
    mov QWORD [rbp - 896], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 896], rax
    mov rax, QWORD [rbp - 888]
    mov rbx, QWORD [rbp - 896]
    and rbx, 63
    mov rcx, rbx
    shl rax, cl
    mov QWORD [rbp - 880], rax
    mov QWORD [rbp - 904], 0
    mov QWORD [rbp - 912], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 912], rax
    mov QWORD [rbp - 920], 0
    mov rax, QWORD [rbp - 880]
    mov QWORD [rbp - 920], rax
    mov rax, QWORD [rbp - 912]
    mov rbx, QWORD [rbp - 920]
    or rax,rbx
    mov QWORD [rbp - 904], rax
    mov rax, QWORD [rbp - 904]
    mov QWORD [rbp - 24], rax
    .L10:
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 728], rax
    mov rax, QWORD [rbp - 728]
    leave
    ret
generate_automata:
    push rbp
    mov  rbp, rsp
    sub  rsp, 240
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], rsi
    mov QWORD [rbp - 24], rdx
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 40], rax
    mov QWORD [rbp - 48], 0
    mov QWORD [rbp - 48], 2
    mov rax, QWORD [rbp - 40]
    mov rbx, QWORD [rbp - 48]
    cqo
    idiv rbx
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 64], 1
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 64]
    mov rbx, QWORD [rbp - 72]
    and rbx, 63
    mov rcx, rbx
    shl rax, cl
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 88], 0
    .L11:
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 112], rax
    mov rax, QWORD [rbp - 104]
    mov rbx, QWORD [rbp - 112]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 96]
    cmp rax, 0
    jne .L12
    jmp .L13
    .L12:
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 128], rax
    mov rdi, QWORD [rbp - 128]
    mov QWORD [rbp - 136], 0
    xor rax,rax
    call print_state
    mov QWORD [rbp - 136],rax
    mov QWORD [rbp - 144], 0
    .L14:
    mov QWORD [rbp - 152], 0
    mov QWORD [rbp - 160], 0
    mov rax, QWORD [rbp - 144]
    mov QWORD [rbp - 160], rax
    mov QWORD [rbp - 168], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 168], rax
    mov rax, QWORD [rbp - 160]
    mov rbx, QWORD [rbp - 168]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 152], rax
    mov rax, QWORD [rbp - 152]
    cmp rax, 0
    jne .L15
    jmp .L16
    .L15:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 184], rax
    mov rdi, QWORD [rbp - 184]
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 192], rax
    mov rsi, QWORD [rbp - 192]
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 200], rax
    mov rdx, QWORD [rbp - 200]
    mov rax, QWORD [rbp - 144]
    mov QWORD [rbp - 208], rax
    mov rcx, QWORD [rbp - 208]
    mov QWORD [rbp - 216], 0
    xor rax,rax
    call update_state
    mov QWORD [rbp - 216],rax
    mov rax, QWORD [rbp - 216]
    mov QWORD [rbp - 120], rax
    mov QWORD [rbp - 224], 0
    mov rax, [rbp - 144]
    inc rax
    mov [rbp - 224],rax
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 144], rax
    jmp .L14
    .L16:
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 176], 0
    mov rax, [rbp - 88]
    inc rax
    mov [rbp - 176],rax
    mov rax, QWORD [rbp - 176]
    mov QWORD [rbp - 88], rax
    jmp .L11
    .L13:
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 48
    mov rax, [global_rule]
    mov QWORD [rbp - 8], rax
    mov rdi, QWORD [rbp - 8]
    mov rax, [global_width]
    mov QWORD [rbp - 16], rax
    mov rsi, QWORD [rbp - 16]
    mov rax, [global_steps]
    mov QWORD [rbp - 24], rax
    mov rdx, QWORD [rbp - 24]
    mov QWORD [rbp - 32], 0
    xor rax,rax
    call generate_automata
    mov QWORD [rbp - 32],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack
