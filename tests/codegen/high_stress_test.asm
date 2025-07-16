SECTION .data
global_global_1      dq 100
global_global_2      dq 200
global_app_name      dq "Stress Tester",0

SECTION .bss

SECTION .text
global  main
extern printf
extern scanf
extern strlen
math_ops:
    push rbp
    mov  rbp, rsp
    sub  rsp, 1232
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], rsi
    mov QWORD [rbp - 24], rdx
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 40], rax
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 40]
    mov rbx, QWORD [rbp - 48]
    imul rax,rbx
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 64]
    mov rbx, QWORD [rbp - 72]
    add rax,rbx
    mov QWORD [rbp - 56], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 96], 1
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    add rax,rbx
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 112]
    mov rbx, QWORD [rbp - 120]
    cqo
    idiv rbx
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 128], 0
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 136], rax
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 136]
    mov rbx, QWORD [rbp - 144]
    sub rax,rbx
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 152], 0
    mov QWORD [rbp - 160], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 160], rax
    mov QWORD [rbp - 168], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 168], rax
    mov rax, QWORD [rbp - 160]
    mov rbx, QWORD [rbp - 168]
    add rax,rbx
    mov QWORD [rbp - 152], rax
    mov QWORD [rbp - 176], 0
    mov QWORD [rbp - 184], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 184], rax
    mov QWORD [rbp - 192], 0
    mov QWORD [rbp - 192], 2
    mov rax, QWORD [rbp - 184]
    mov rbx, QWORD [rbp - 192]
    sub rax,rbx
    mov QWORD [rbp - 176], rax
    mov QWORD [rbp - 200], 0
    mov QWORD [rbp - 208], 0
    mov rax, QWORD [rbp - 152]
    mov QWORD [rbp - 208], rax
    mov QWORD [rbp - 216], 0
    mov rax, QWORD [rbp - 176]
    mov QWORD [rbp - 216], rax
    mov rax, QWORD [rbp - 208]
    mov rbx, QWORD [rbp - 216]
    imul rax,rbx
    mov QWORD [rbp - 200], rax
    mov QWORD [rbp - 224], 0
    mov QWORD [rbp - 232], 0
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 232], rax
    mov QWORD [rbp - 240], 0
    mov rax, QWORD [rbp - 200]
    mov QWORD [rbp - 240], rax
    mov rax, QWORD [rbp - 232]
    mov rbx, QWORD [rbp - 240]
    add rax,rbx
    mov QWORD [rbp - 224], rax
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 248], rax
    mov QWORD [rbp - 256], 0
    mov QWORD [rbp - 264], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 264], rax
    mov QWORD [rbp - 272], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 272], rax
    mov rax, QWORD [rbp - 264]
    mov rbx, QWORD [rbp - 272]
    imul rax,rbx
    mov QWORD [rbp - 256], rax
    mov QWORD [rbp - 280], 0
    mov QWORD [rbp - 288], 0
    mov rax, QWORD [rbp - 256]
    mov QWORD [rbp - 288], rax
    mov QWORD [rbp - 296], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 296], rax
    mov rax, QWORD [rbp - 288]
    mov rbx, QWORD [rbp - 296]
    add rax,rbx
    mov QWORD [rbp - 280], rax
    mov QWORD [rbp - 304], 0
    mov QWORD [rbp - 312], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 312], rax
    mov QWORD [rbp - 320], 0
    mov QWORD [rbp - 320], 1
    mov rax, QWORD [rbp - 312]
    mov rbx, QWORD [rbp - 320]
    add rax,rbx
    mov QWORD [rbp - 304], rax
    mov QWORD [rbp - 328], 0
    mov QWORD [rbp - 336], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 336], rax
    mov QWORD [rbp - 344], 0
    mov rax, QWORD [rbp - 304]
    mov QWORD [rbp - 344], rax
    mov rax, QWORD [rbp - 336]
    mov rbx, QWORD [rbp - 344]
    cqo
    idiv rbx
    mov QWORD [rbp - 328], rax
    mov QWORD [rbp - 352], 0
    mov QWORD [rbp - 360], 0
    mov rax, QWORD [rbp - 280]
    mov QWORD [rbp - 360], rax
    mov QWORD [rbp - 368], 0
    mov rax, QWORD [rbp - 328]
    mov QWORD [rbp - 368], rax
    mov rax, QWORD [rbp - 360]
    mov rbx, QWORD [rbp - 368]
    sub rax,rbx
    mov QWORD [rbp - 352], rax
    mov QWORD [rbp - 376], 0
    mov QWORD [rbp - 384], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 384], rax
    mov QWORD [rbp - 392], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 392], rax
    mov rax, QWORD [rbp - 384]
    mov rbx, QWORD [rbp - 392]
    add rax,rbx
    mov QWORD [rbp - 376], rax
    mov QWORD [rbp - 400], 0
    mov QWORD [rbp - 408], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 408], rax
    mov QWORD [rbp - 416], 0
    mov QWORD [rbp - 416], 2
    mov rax, QWORD [rbp - 408]
    mov rbx, QWORD [rbp - 416]
    sub rax,rbx
    mov QWORD [rbp - 400], rax
    mov QWORD [rbp - 424], 0
    mov QWORD [rbp - 432], 0
    mov rax, QWORD [rbp - 376]
    mov QWORD [rbp - 432], rax
    mov QWORD [rbp - 440], 0
    mov rax, QWORD [rbp - 400]
    mov QWORD [rbp - 440], rax
    mov rax, QWORD [rbp - 432]
    mov rbx, QWORD [rbp - 440]
    imul rax,rbx
    mov QWORD [rbp - 424], rax
    mov QWORD [rbp - 448], 0
    mov QWORD [rbp - 456], 0
    mov rax, QWORD [rbp - 352]
    mov QWORD [rbp - 456], rax
    mov QWORD [rbp - 464], 0
    mov rax, QWORD [rbp - 424]
    mov QWORD [rbp - 464], rax
    mov rax, QWORD [rbp - 456]
    mov rbx, QWORD [rbp - 464]
    add rax,rbx
    mov QWORD [rbp - 448], rax
    mov QWORD [rbp - 472], 0
    mov QWORD [rbp - 480], 0
    mov rax, QWORD [rbp - 448]
    mov QWORD [rbp - 480], rax
    mov QWORD [rbp - 488], 0
    mov QWORD [rbp - 488], 2
    mov rax, QWORD [rbp - 480]
    mov rbx, QWORD [rbp - 488]
    imul rax,rbx
    mov QWORD [rbp - 472], rax
    mov QWORD [rbp - 496], 0
    mov QWORD [rbp - 504], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 504], rax
    mov QWORD [rbp - 512], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 512], rax
    mov rax, QWORD [rbp - 504]
    mov rbx, QWORD [rbp - 512]
    sub rax,rbx
    mov QWORD [rbp - 496], rax
    mov QWORD [rbp - 520], 0
    mov QWORD [rbp - 528], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 528], rax
    mov QWORD [rbp - 536], 0
    mov QWORD [rbp - 536], 10
    mov rax, QWORD [rbp - 528]
    mov rbx, QWORD [rbp - 536]
    imul rax,rbx
    mov QWORD [rbp - 520], rax
    mov QWORD [rbp - 544], 0
    mov QWORD [rbp - 552], 0
    mov rax, QWORD [rbp - 496]
    mov QWORD [rbp - 552], rax
    mov QWORD [rbp - 560], 0
    mov rax, QWORD [rbp - 520]
    mov QWORD [rbp - 560], rax
    mov rax, QWORD [rbp - 552]
    mov rbx, QWORD [rbp - 560]
    add rax,rbx
    mov QWORD [rbp - 544], rax
    mov QWORD [rbp - 568], 0
    mov QWORD [rbp - 576], 0
    mov rax, QWORD [rbp - 544]
    mov QWORD [rbp - 576], rax
    mov QWORD [rbp - 584], 0
    mov QWORD [rbp - 584], 7
    mov rax, QWORD [rbp - 576]
    mov rbx, QWORD [rbp - 584]
    cqo
    idiv rbx
    mov QWORD [rbp - 568],rdx
    mov QWORD [rbp - 592], 0
    mov QWORD [rbp - 600], 0
    mov rax, QWORD [rbp - 472]
    mov QWORD [rbp - 600], rax
    mov QWORD [rbp - 608], 0
    mov rax, QWORD [rbp - 568]
    mov QWORD [rbp - 608], rax
    mov rax, QWORD [rbp - 600]
    mov rbx, QWORD [rbp - 608]
    add rax,rbx
    mov QWORD [rbp - 592], rax
    mov rax, QWORD [rbp - 592]
    mov QWORD [rbp - 616], rax
    mov QWORD [rbp - 624], 0
    mov QWORD [rbp - 632], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 632], rax
    mov QWORD [rbp - 640], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 640], rax
    mov rax, QWORD [rbp - 632]
    mov rbx, QWORD [rbp - 640]
    imul rax,rbx
    mov QWORD [rbp - 624], rax
    mov QWORD [rbp - 648], 0
    mov QWORD [rbp - 656], 0
    mov rax, QWORD [rbp - 624]
    mov QWORD [rbp - 656], rax
    mov QWORD [rbp - 664], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 664], rax
    mov rax, QWORD [rbp - 656]
    mov rbx, QWORD [rbp - 664]
    add rax,rbx
    mov QWORD [rbp - 648], rax
    mov QWORD [rbp - 672], 0
    mov QWORD [rbp - 680], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 680], rax
    mov QWORD [rbp - 688], 0
    mov QWORD [rbp - 688], 1
    mov rax, QWORD [rbp - 680]
    mov rbx, QWORD [rbp - 688]
    add rax,rbx
    mov QWORD [rbp - 672], rax
    mov QWORD [rbp - 696], 0
    mov QWORD [rbp - 704], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 704], rax
    mov QWORD [rbp - 712], 0
    mov rax, QWORD [rbp - 672]
    mov QWORD [rbp - 712], rax
    mov rax, QWORD [rbp - 704]
    mov rbx, QWORD [rbp - 712]
    cqo
    idiv rbx
    mov QWORD [rbp - 696], rax
    mov QWORD [rbp - 720], 0
    mov QWORD [rbp - 728], 0
    mov rax, QWORD [rbp - 648]
    mov QWORD [rbp - 728], rax
    mov QWORD [rbp - 736], 0
    mov rax, QWORD [rbp - 696]
    mov QWORD [rbp - 736], rax
    mov rax, QWORD [rbp - 728]
    mov rbx, QWORD [rbp - 736]
    sub rax,rbx
    mov QWORD [rbp - 720], rax
    mov QWORD [rbp - 744], 0
    mov QWORD [rbp - 752], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 752], rax
    mov QWORD [rbp - 760], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 760], rax
    mov rax, QWORD [rbp - 752]
    mov rbx, QWORD [rbp - 760]
    add rax,rbx
    mov QWORD [rbp - 744], rax
    mov QWORD [rbp - 768], 0
    mov QWORD [rbp - 776], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 776], rax
    mov QWORD [rbp - 784], 0
    mov QWORD [rbp - 784], 2
    mov rax, QWORD [rbp - 776]
    mov rbx, QWORD [rbp - 784]
    sub rax,rbx
    mov QWORD [rbp - 768], rax
    mov QWORD [rbp - 792], 0
    mov QWORD [rbp - 800], 0
    mov rax, QWORD [rbp - 744]
    mov QWORD [rbp - 800], rax
    mov QWORD [rbp - 808], 0
    mov rax, QWORD [rbp - 768]
    mov QWORD [rbp - 808], rax
    mov rax, QWORD [rbp - 800]
    mov rbx, QWORD [rbp - 808]
    imul rax,rbx
    mov QWORD [rbp - 792], rax
    mov QWORD [rbp - 816], 0
    mov QWORD [rbp - 824], 0
    mov rax, QWORD [rbp - 720]
    mov QWORD [rbp - 824], rax
    mov QWORD [rbp - 832], 0
    mov rax, QWORD [rbp - 792]
    mov QWORD [rbp - 832], rax
    mov rax, QWORD [rbp - 824]
    mov rbx, QWORD [rbp - 832]
    add rax,rbx
    mov QWORD [rbp - 816], rax
    mov QWORD [rbp - 840], 0
    mov QWORD [rbp - 848], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 848], rax
    mov QWORD [rbp - 856], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 856], rax
    mov rax, QWORD [rbp - 848]
    mov rbx, QWORD [rbp - 856]
    imul rax,rbx
    mov QWORD [rbp - 840], rax
    mov QWORD [rbp - 864], 0
    mov QWORD [rbp - 872], 0
    mov rax, QWORD [rbp - 840]
    mov QWORD [rbp - 872], rax
    mov QWORD [rbp - 880], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 880], rax
    mov rax, QWORD [rbp - 872]
    mov rbx, QWORD [rbp - 880]
    add rax,rbx
    mov QWORD [rbp - 864], rax
    mov QWORD [rbp - 888], 0
    mov QWORD [rbp - 896], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 896], rax
    mov QWORD [rbp - 904], 0
    mov QWORD [rbp - 904], 1
    mov rax, QWORD [rbp - 896]
    mov rbx, QWORD [rbp - 904]
    add rax,rbx
    mov QWORD [rbp - 888], rax
    mov QWORD [rbp - 912], 0
    mov QWORD [rbp - 920], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 920], rax
    mov QWORD [rbp - 928], 0
    mov rax, QWORD [rbp - 888]
    mov QWORD [rbp - 928], rax
    mov rax, QWORD [rbp - 920]
    mov rbx, QWORD [rbp - 928]
    cqo
    idiv rbx
    mov QWORD [rbp - 912], rax
    mov QWORD [rbp - 936], 0
    mov QWORD [rbp - 944], 0
    mov rax, QWORD [rbp - 864]
    mov QWORD [rbp - 944], rax
    mov QWORD [rbp - 952], 0
    mov rax, QWORD [rbp - 912]
    mov QWORD [rbp - 952], rax
    mov rax, QWORD [rbp - 944]
    mov rbx, QWORD [rbp - 952]
    sub rax,rbx
    mov QWORD [rbp - 936], rax
    mov QWORD [rbp - 960], 0
    mov QWORD [rbp - 968], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 968], rax
    mov QWORD [rbp - 976], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 976], rax
    mov rax, QWORD [rbp - 968]
    mov rbx, QWORD [rbp - 976]
    add rax,rbx
    mov QWORD [rbp - 960], rax
    mov QWORD [rbp - 984], 0
    mov QWORD [rbp - 992], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 992], rax
    mov QWORD [rbp - 1000], 0
    mov QWORD [rbp - 1000], 2
    mov rax, QWORD [rbp - 992]
    mov rbx, QWORD [rbp - 1000]
    sub rax,rbx
    mov QWORD [rbp - 984], rax
    mov QWORD [rbp - 1008], 0
    mov QWORD [rbp - 1016], 0
    mov rax, QWORD [rbp - 960]
    mov QWORD [rbp - 1016], rax
    mov QWORD [rbp - 1024], 0
    mov rax, QWORD [rbp - 984]
    mov QWORD [rbp - 1024], rax
    mov rax, QWORD [rbp - 1016]
    mov rbx, QWORD [rbp - 1024]
    imul rax,rbx
    mov QWORD [rbp - 1008], rax
    mov QWORD [rbp - 1032], 0
    mov QWORD [rbp - 1040], 0
    mov rax, QWORD [rbp - 936]
    mov QWORD [rbp - 1040], rax
    mov QWORD [rbp - 1048], 0
    mov rax, QWORD [rbp - 1008]
    mov QWORD [rbp - 1048], rax
    mov rax, QWORD [rbp - 1040]
    mov rbx, QWORD [rbp - 1048]
    add rax,rbx
    mov QWORD [rbp - 1032], rax
    mov QWORD [rbp - 1056], 0
    mov QWORD [rbp - 1064], 0
    mov rax, QWORD [rbp - 1032]
    mov QWORD [rbp - 1064], rax
    mov QWORD [rbp - 1072], 0
    mov QWORD [rbp - 1072], 2
    mov rax, QWORD [rbp - 1064]
    mov rbx, QWORD [rbp - 1072]
    imul rax,rbx
    mov QWORD [rbp - 1056], rax
    mov QWORD [rbp - 1080], 0
    mov QWORD [rbp - 1088], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 1088], rax
    mov QWORD [rbp - 1096], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 1096], rax
    mov rax, QWORD [rbp - 1088]
    mov rbx, QWORD [rbp - 1096]
    sub rax,rbx
    mov QWORD [rbp - 1080], rax
    mov QWORD [rbp - 1104], 0
    mov QWORD [rbp - 1112], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 1112], rax
    mov QWORD [rbp - 1120], 0
    mov QWORD [rbp - 1120], 10
    mov rax, QWORD [rbp - 1112]
    mov rbx, QWORD [rbp - 1120]
    imul rax,rbx
    mov QWORD [rbp - 1104], rax
    mov QWORD [rbp - 1128], 0
    mov QWORD [rbp - 1136], 0
    mov rax, QWORD [rbp - 1080]
    mov QWORD [rbp - 1136], rax
    mov QWORD [rbp - 1144], 0
    mov rax, QWORD [rbp - 1104]
    mov QWORD [rbp - 1144], rax
    mov rax, QWORD [rbp - 1136]
    mov rbx, QWORD [rbp - 1144]
    add rax,rbx
    mov QWORD [rbp - 1128], rax
    mov QWORD [rbp - 1152], 0
    mov QWORD [rbp - 1160], 0
    mov rax, QWORD [rbp - 1128]
    mov QWORD [rbp - 1160], rax
    mov QWORD [rbp - 1168], 0
    mov QWORD [rbp - 1168], 7
    mov rax, QWORD [rbp - 1160]
    mov rbx, QWORD [rbp - 1168]
    cqo
    idiv rbx
    mov QWORD [rbp - 1152],rdx
    mov QWORD [rbp - 1176], 0
    mov QWORD [rbp - 1184], 0
    mov rax, QWORD [rbp - 1056]
    mov QWORD [rbp - 1184], rax
    mov QWORD [rbp - 1192], 0
    mov rax, QWORD [rbp - 1152]
    mov QWORD [rbp - 1192], rax
    mov rax, QWORD [rbp - 1184]
    mov rbx, QWORD [rbp - 1192]
    add rax,rbx
    mov QWORD [rbp - 1176], rax
    mov QWORD [rbp - 1200], 0
    mov QWORD [rbp - 1208], 0
    mov rax, QWORD [rbp - 816]
    mov QWORD [rbp - 1208], rax
    mov QWORD [rbp - 1216], 0
    mov rax, QWORD [rbp - 1176]
    mov QWORD [rbp - 1216], rax
    mov rax, QWORD [rbp - 1208]
    mov rbx, QWORD [rbp - 1216]
    add rax,rbx
    mov QWORD [rbp - 1200], rax
    mov rax, QWORD [rbp - 1200]
    mov QWORD [rbp - 1224], rax
    mov rax, QWORD [rbp - 1224]
    leave
    ret
level2:
    push rbp
    mov  rbp, rsp
    sub  rsp, 144
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
    imul rax,rbx
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    .L0:
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 64]
    cmp rax, 0
    jne .L1
    jmp .L2
    .L1:
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 112], rax
    mov rax, QWORD [rbp - 104]
    mov rbx, QWORD [rbp - 112]
    add rax,rbx
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 56], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 136], 1
    mov rax, QWORD [rbp - 128]
    mov rbx, QWORD [rbp - 136]
    sub rax,rbx
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 48], rax
    jmp .L0
    .L2:
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 88], rax
    mov rax, QWORD [rbp - 88]
    leave
    ret
level1:
    push rbp
    mov  rbp, rsp
    sub  rsp, 112
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
    mov QWORD [rbp - 48], 0
    mov QWORD [rbp - 56], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 56], rax
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 64], 1
    mov rax, QWORD [rbp - 56]
    mov rbx, QWORD [rbp - 64]
    add rax,rbx
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 80], rax
    mov rdi, QWORD [rbp - 80]
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 88], rax
    mov rsi, QWORD [rbp - 88]
    mov QWORD [rbp - 96], 0
    xor rax,rax
    call level2
    mov QWORD [rbp - 96],rax
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    leave
    ret
decision_tree:
    push rbp
    mov  rbp, rsp
    sub  rsp, 336
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
    setl al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L3
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 0
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    cmp rax, 0
    jne .L5
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 104], 10
    mov rax, QWORD [rbp - 96]
    mov rbx, QWORD [rbp - 104]
    cmp rax,rbx
    setl al
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
    test rax,rax
    setz al
    movzx rax,al
    test rbx,rbx
    setz bl
    movzx rbx,bl
    or rax,rbx
    xor rax,1
    mov QWORD [rbp - 112], rax
    mov rax, QWORD [rbp - 112]
    cmp rax, 0
    jne .L7
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 144], rax
    mov QWORD [rbp - 152], 0
    mov QWORD [rbp - 152], 10
    mov rax, QWORD [rbp - 144]
    mov rbx, QWORD [rbp - 152]
    cmp rax,rbx
    setge al
    movzx rax,al
    mov QWORD [rbp - 136], rax
    mov QWORD [rbp - 160], 0
    mov QWORD [rbp - 168], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 168], rax
    mov QWORD [rbp - 176], 0
    mov QWORD [rbp - 176], 100
    mov rax, QWORD [rbp - 168]
    mov rbx, QWORD [rbp - 176]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 160], rax
    mov QWORD [rbp - 184], 0
    mov QWORD [rbp - 192], 0
    mov rax, QWORD [rbp - 136]
    mov QWORD [rbp - 192], rax
    mov QWORD [rbp - 200], 0
    mov rax, QWORD [rbp - 160]
    mov QWORD [rbp - 200], rax
    mov rax, QWORD [rbp - 192]
    mov rbx, QWORD [rbp - 200]
    test rax,rax
    setz al
    movzx rax,al
    test rbx,rbx
    setz bl
    movzx rbx,bl
    or rax,rbx
    xor rax,1
    mov QWORD [rbp - 184], rax
    mov rax, QWORD [rbp - 184]
    cmp rax, 0
    jne .L9
    lea rax, [rbp - 208]
    mov QWORD [rbp - 216], rax
    mov byte [rbp - 208], 'B'
    mov byte [rbp - 207], 'i'
    mov byte [rbp - 206], 'g'
    mov byte [rbp - 205], 0x0A
    mov byte [rbp - 204], 0
    mov rdi, QWORD [rbp - 216]
    mov QWORD [rbp - 224], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 224],rax
    jmp .L10
    .L9:
    lea rax, [rbp - 232]
    mov QWORD [rbp - 240], rax
    mov byte [rbp - 232], 'M'
    mov byte [rbp - 231], 'e'
    mov byte [rbp - 230], 'd'
    mov byte [rbp - 229], 0x0A
    mov byte [rbp - 228], 0
    mov rdi, QWORD [rbp - 240]
    mov QWORD [rbp - 248], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 248],rax
    .L10:
    jmp .L8
    .L7:
    lea rax, [rbp - 256]
    mov QWORD [rbp - 264], rax
    mov byte [rbp - 256], 'S'
    mov byte [rbp - 255], 'm'
    mov byte [rbp - 254], 'a'
    mov byte [rbp - 253], 'l'
    mov byte [rbp - 252], 'l'
    mov byte [rbp - 251], 0x0A
    mov byte [rbp - 250], 0
    mov rdi, QWORD [rbp - 264]
    mov QWORD [rbp - 272], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 272],rax
    .L8:
    jmp .L6
    .L5:
    lea rax, [rbp - 280]
    mov QWORD [rbp - 288], rax
    mov byte [rbp - 280], 'Z'
    mov byte [rbp - 279], 'e'
    mov byte [rbp - 278], 'r'
    mov byte [rbp - 277], 'o'
    mov byte [rbp - 276], 0x0A
    mov byte [rbp - 275], 0
    mov rdi, QWORD [rbp - 288]
    mov QWORD [rbp - 296], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 296],rax
    .L6:
    jmp .L4
    .L3:
    lea rax, [rbp - 304]
    mov QWORD [rbp - 312], rax
    mov byte [rbp - 304], 'N'
    mov byte [rbp - 303], 'e'
    mov byte [rbp - 302], 'g'
    mov byte [rbp - 301], 0x0A
    mov byte [rbp - 300], 0
    mov rdi, QWORD [rbp - 312]
    mov QWORD [rbp - 320], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 320],rax
    .L4:
    leave
    ret

multiple_assigns:
    push rbp
    mov  rbp, rsp
    sub  rsp, 160
    mov QWORD [rbp - 8], 5
    mov QWORD [rbp - 16], 5
    mov QWORD [rbp - 24], 5
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 40], rax
    mov QWORD [rbp - 48], 0
    mov QWORD [rbp - 48], 1
    mov rax, QWORD [rbp - 40]
    mov rbx, QWORD [rbp - 48]
    add rax,rbx
    mov QWORD [rbp - 32], rax
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 72], 2
    mov rax, QWORD [rbp - 64]
    mov rbx, QWORD [rbp - 72]
    imul rax,rbx
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 16], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 96], 3
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    sub rax,rbx
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 8], rax
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 112]
    mov rbx, QWORD [rbp - 120]
    add rax,rbx
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 128], 0
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 136], rax
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 136]
    mov rbx, QWORD [rbp - 144]
    add rax,rbx
    mov QWORD [rbp - 128], rax
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 152], rax
    mov rax, QWORD [rbp - 152]
    leave
    ret
scope_depth_test:
    push rbp
    mov  rbp, rsp
    sub  rsp, 176
    mov QWORD [rbp - 8], 10
    .L11:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L12
    jmp .L13
    .L12:
    mov QWORD [rbp - 64], 10
    .L14:
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 88], 5
    mov rax, QWORD [rbp - 80]
    mov rbx, QWORD [rbp - 88]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 72]
    cmp rax, 0
    jne .L15
    jmp .L16
    .L15:
    lea rax, [rbp - 144]
    mov QWORD [rbp - 152], rax
    mov byte [rbp - 144], '*'
    mov byte [rbp - 143], ' '
    mov byte [rbp - 142], 0
    mov rdi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 160],rax
    mov QWORD [rbp - 168], 0
    mov rax, [rbp - 64]
    dec rax
    mov [rbp - 168],rax
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 64], rax
    jmp .L14
    .L16:
    lea rax, [rbp - 96]
    mov QWORD [rbp - 104], rax
    mov byte [rbp - 96], 0x0A
    mov byte [rbp - 95], 0
    mov rdi, QWORD [rbp - 104]
    mov QWORD [rbp - 112], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 112],rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 136], 1
    mov rax, QWORD [rbp - 128]
    mov rbx, QWORD [rbp - 136]
    sub rax,rbx
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 8], rax
    jmp .L11
    .L13:
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

call_chain:
    push rbp
    mov  rbp, rsp
    sub  rsp, 224
    mov QWORD [rbp - 8], rdi
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov rdi, QWORD [rbp - 16]
    mov QWORD [rbp - 24], 0
    xor rax,rax
    call level1
    mov QWORD [rbp - 24],rax
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov rdi, QWORD [rbp - 32]
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 1
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    add rax,rbx
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 64], rax
    mov rsi, QWORD [rbp - 64]
    mov QWORD [rbp - 72], 0
    xor rax,rax
    call level2
    mov QWORD [rbp - 72],rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    add rax,rbx
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 104], rax
    mov rdi, QWORD [rbp - 104]
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 120], rax
    mov QWORD [rbp - 128], 0
    mov QWORD [rbp - 128], 1
    mov rax, QWORD [rbp - 120]
    mov rbx, QWORD [rbp - 128]
    add rax,rbx
    mov QWORD [rbp - 112], rax
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 136], rax
    mov rsi, QWORD [rbp - 136]
    mov QWORD [rbp - 144], 0
    mov QWORD [rbp - 152], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 152], rax
    mov QWORD [rbp - 160], 0
    mov QWORD [rbp - 160], 2
    mov rax, QWORD [rbp - 152]
    mov rbx, QWORD [rbp - 160]
    add rax,rbx
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 144]
    mov QWORD [rbp - 168], rax
    mov rdx, QWORD [rbp - 168]
    mov QWORD [rbp - 176], 0
    xor rax,rax
    call math_ops
    mov QWORD [rbp - 176],rax
    mov QWORD [rbp - 184], 0
    mov QWORD [rbp - 192], 0
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 192], rax
    mov QWORD [rbp - 200], 0
    mov rax, QWORD [rbp - 176]
    mov QWORD [rbp - 200], rax
    mov rax, QWORD [rbp - 192]
    mov rbx, QWORD [rbp - 200]
    add rax,rbx
    mov QWORD [rbp - 184], rax
    mov rax, QWORD [rbp - 184]
    mov QWORD [rbp - 208], rax
    mov rax, QWORD [rbp - 208]
    leave
    ret
giant_exprs:
    push rbp
    mov  rbp, rsp
    sub  rsp, 912
    mov QWORD [rbp - 8], 1400
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 2
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    imul rax,rbx
    mov QWORD [rbp - 16], rax
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 3
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    cqo
    idiv rbx
    mov QWORD [rbp - 40], rax
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    add rax,rbx
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 104], 4
    mov rax, QWORD [rbp - 96]
    mov rbx, QWORD [rbp - 104]
    cqo
    idiv rbx
    mov QWORD [rbp - 88],rdx
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 120], rax
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 128], rax
    mov rax, QWORD [rbp - 120]
    mov rbx, QWORD [rbp - 128]
    sub rax,rbx
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 8]
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
    mov QWORD [rbp - 168], 0
    mov QWORD [rbp - 176], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 176], rax
    mov QWORD [rbp - 184], 0
    mov QWORD [rbp - 184], 2
    mov rax, QWORD [rbp - 176]
    mov rbx, QWORD [rbp - 184]
    imul rax,rbx
    mov QWORD [rbp - 168], rax
    mov QWORD [rbp - 192], 0
    mov QWORD [rbp - 200], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 200], rax
    mov QWORD [rbp - 208], 0
    mov QWORD [rbp - 208], 3
    mov rax, QWORD [rbp - 200]
    mov rbx, QWORD [rbp - 208]
    cqo
    idiv rbx
    mov QWORD [rbp - 192], rax
    mov QWORD [rbp - 216], 0
    mov QWORD [rbp - 224], 0
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 224], rax
    mov QWORD [rbp - 232], 0
    mov rax, QWORD [rbp - 192]
    mov QWORD [rbp - 232], rax
    mov rax, QWORD [rbp - 224]
    mov rbx, QWORD [rbp - 232]
    add rax,rbx
    mov QWORD [rbp - 216], rax
    mov QWORD [rbp - 240], 0
    mov QWORD [rbp - 248], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 248], rax
    mov QWORD [rbp - 256], 0
    mov QWORD [rbp - 256], 4
    mov rax, QWORD [rbp - 248]
    mov rbx, QWORD [rbp - 256]
    cqo
    idiv rbx
    mov QWORD [rbp - 240],rdx
    mov QWORD [rbp - 264], 0
    mov QWORD [rbp - 272], 0
    mov rax, QWORD [rbp - 216]
    mov QWORD [rbp - 272], rax
    mov QWORD [rbp - 280], 0
    mov rax, QWORD [rbp - 240]
    mov QWORD [rbp - 280], rax
    mov rax, QWORD [rbp - 272]
    mov rbx, QWORD [rbp - 280]
    sub rax,rbx
    mov QWORD [rbp - 264], rax
    mov QWORD [rbp - 288], 0
    mov QWORD [rbp - 296], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 296], rax
    mov QWORD [rbp - 304], 0
    mov rax, QWORD [rbp - 264]
    mov QWORD [rbp - 304], rax
    mov rax, QWORD [rbp - 296]
    mov rbx, QWORD [rbp - 304]
    add rax,rbx
    mov QWORD [rbp - 288], rax
    mov QWORD [rbp - 312], 0
    mov QWORD [rbp - 320], 0
    mov rax, QWORD [rbp - 288]
    mov QWORD [rbp - 320], rax
    mov QWORD [rbp - 328], 0
    mov QWORD [rbp - 328], 3
    mov rax, QWORD [rbp - 320]
    mov rbx, QWORD [rbp - 328]
    cqo
    idiv rbx
    mov QWORD [rbp - 312], rax
    mov QWORD [rbp - 336], 0
    mov QWORD [rbp - 344], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 344], rax
    mov QWORD [rbp - 352], 0
    mov QWORD [rbp - 352], 2
    mov rax, QWORD [rbp - 344]
    mov rbx, QWORD [rbp - 352]
    imul rax,rbx
    mov QWORD [rbp - 336], rax
    mov QWORD [rbp - 360], 0
    mov QWORD [rbp - 368], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 368], rax
    mov QWORD [rbp - 376], 0
    mov QWORD [rbp - 376], 3
    mov rax, QWORD [rbp - 368]
    mov rbx, QWORD [rbp - 376]
    cqo
    idiv rbx
    mov QWORD [rbp - 360], rax
    mov QWORD [rbp - 384], 0
    mov QWORD [rbp - 392], 0
    mov rax, QWORD [rbp - 336]
    mov QWORD [rbp - 392], rax
    mov QWORD [rbp - 400], 0
    mov rax, QWORD [rbp - 360]
    mov QWORD [rbp - 400], rax
    mov rax, QWORD [rbp - 392]
    mov rbx, QWORD [rbp - 400]
    add rax,rbx
    mov QWORD [rbp - 384], rax
    mov QWORD [rbp - 408], 0
    mov QWORD [rbp - 416], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 416], rax
    mov QWORD [rbp - 424], 0
    mov QWORD [rbp - 424], 4
    mov rax, QWORD [rbp - 416]
    mov rbx, QWORD [rbp - 424]
    cqo
    idiv rbx
    mov QWORD [rbp - 408],rdx
    mov QWORD [rbp - 432], 0
    mov QWORD [rbp - 440], 0
    mov rax, QWORD [rbp - 384]
    mov QWORD [rbp - 440], rax
    mov QWORD [rbp - 448], 0
    mov rax, QWORD [rbp - 408]
    mov QWORD [rbp - 448], rax
    mov rax, QWORD [rbp - 440]
    mov rbx, QWORD [rbp - 448]
    sub rax,rbx
    mov QWORD [rbp - 432], rax
    mov QWORD [rbp - 456], 0
    mov QWORD [rbp - 464], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 464], rax
    mov QWORD [rbp - 472], 0
    mov rax, QWORD [rbp - 432]
    mov QWORD [rbp - 472], rax
    mov rax, QWORD [rbp - 464]
    mov rbx, QWORD [rbp - 472]
    add rax,rbx
    mov QWORD [rbp - 456], rax
    mov QWORD [rbp - 480], 0
    mov QWORD [rbp - 488], 0
    mov rax, QWORD [rbp - 456]
    mov QWORD [rbp - 488], rax
    mov QWORD [rbp - 496], 0
    mov QWORD [rbp - 496], 7
    mov rax, QWORD [rbp - 488]
    mov rbx, QWORD [rbp - 496]
    cqo
    idiv rbx
    mov QWORD [rbp - 480],rdx
    mov QWORD [rbp - 504], 0
    mov QWORD [rbp - 512], 0
    mov rax, QWORD [rbp - 312]
    mov QWORD [rbp - 512], rax
    mov QWORD [rbp - 520], 0
    mov rax, QWORD [rbp - 480]
    mov QWORD [rbp - 520], rax
    mov rax, QWORD [rbp - 512]
    mov rbx, QWORD [rbp - 520]
    add rax,rbx
    mov QWORD [rbp - 504], rax
    mov rax, QWORD [rbp - 504]
    mov QWORD [rbp - 528], rax
    mov QWORD [rbp - 536], 0
    mov QWORD [rbp - 544], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 544], rax
    mov QWORD [rbp - 552], 0
    mov QWORD [rbp - 552], 2
    mov rax, QWORD [rbp - 544]
    mov rbx, QWORD [rbp - 552]
    imul rax,rbx
    mov QWORD [rbp - 536], rax
    mov QWORD [rbp - 560], 0
    mov QWORD [rbp - 568], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 568], rax
    mov QWORD [rbp - 576], 0
    mov QWORD [rbp - 576], 3
    mov rax, QWORD [rbp - 568]
    mov rbx, QWORD [rbp - 576]
    cqo
    idiv rbx
    mov QWORD [rbp - 560], rax
    mov QWORD [rbp - 584], 0
    mov QWORD [rbp - 592], 0
    mov rax, QWORD [rbp - 536]
    mov QWORD [rbp - 592], rax
    mov QWORD [rbp - 600], 0
    mov rax, QWORD [rbp - 560]
    mov QWORD [rbp - 600], rax
    mov rax, QWORD [rbp - 592]
    mov rbx, QWORD [rbp - 600]
    add rax,rbx
    mov QWORD [rbp - 584], rax
    mov QWORD [rbp - 608], 0
    mov QWORD [rbp - 616], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 616], rax
    mov QWORD [rbp - 624], 0
    mov QWORD [rbp - 624], 4
    mov rax, QWORD [rbp - 616]
    mov rbx, QWORD [rbp - 624]
    cqo
    idiv rbx
    mov QWORD [rbp - 608],rdx
    mov QWORD [rbp - 632], 0
    mov QWORD [rbp - 640], 0
    mov rax, QWORD [rbp - 584]
    mov QWORD [rbp - 640], rax
    mov QWORD [rbp - 648], 0
    mov rax, QWORD [rbp - 608]
    mov QWORD [rbp - 648], rax
    mov rax, QWORD [rbp - 640]
    mov rbx, QWORD [rbp - 648]
    sub rax,rbx
    mov QWORD [rbp - 632], rax
    mov QWORD [rbp - 656], 0
    mov QWORD [rbp - 664], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 664], rax
    mov QWORD [rbp - 672], 0
    mov rax, QWORD [rbp - 632]
    mov QWORD [rbp - 672], rax
    mov rax, QWORD [rbp - 664]
    mov rbx, QWORD [rbp - 672]
    add rax,rbx
    mov QWORD [rbp - 656], rax
    mov QWORD [rbp - 680], 0
    mov QWORD [rbp - 688], 0
    mov rax, QWORD [rbp - 656]
    mov QWORD [rbp - 688], rax
    mov QWORD [rbp - 696], 0
    mov QWORD [rbp - 696], 3
    mov rax, QWORD [rbp - 688]
    mov rbx, QWORD [rbp - 696]
    cqo
    idiv rbx
    mov QWORD [rbp - 680], rax
    mov QWORD [rbp - 704], 0
    mov QWORD [rbp - 712], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 712], rax
    mov QWORD [rbp - 720], 0
    mov QWORD [rbp - 720], 2
    mov rax, QWORD [rbp - 712]
    mov rbx, QWORD [rbp - 720]
    imul rax,rbx
    mov QWORD [rbp - 704], rax
    mov QWORD [rbp - 728], 0
    mov QWORD [rbp - 736], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 736], rax
    mov QWORD [rbp - 744], 0
    mov QWORD [rbp - 744], 3
    mov rax, QWORD [rbp - 736]
    mov rbx, QWORD [rbp - 744]
    cqo
    idiv rbx
    mov QWORD [rbp - 728], rax
    mov QWORD [rbp - 752], 0
    mov QWORD [rbp - 760], 0
    mov rax, QWORD [rbp - 704]
    mov QWORD [rbp - 760], rax
    mov QWORD [rbp - 768], 0
    mov rax, QWORD [rbp - 728]
    mov QWORD [rbp - 768], rax
    mov rax, QWORD [rbp - 760]
    mov rbx, QWORD [rbp - 768]
    add rax,rbx
    mov QWORD [rbp - 752], rax
    mov QWORD [rbp - 776], 0
    mov QWORD [rbp - 784], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 784], rax
    mov QWORD [rbp - 792], 0
    mov QWORD [rbp - 792], 4
    mov rax, QWORD [rbp - 784]
    mov rbx, QWORD [rbp - 792]
    cqo
    idiv rbx
    mov QWORD [rbp - 776],rdx
    mov QWORD [rbp - 800], 0
    mov QWORD [rbp - 808], 0
    mov rax, QWORD [rbp - 752]
    mov QWORD [rbp - 808], rax
    mov QWORD [rbp - 816], 0
    mov rax, QWORD [rbp - 776]
    mov QWORD [rbp - 816], rax
    mov rax, QWORD [rbp - 808]
    mov rbx, QWORD [rbp - 816]
    sub rax,rbx
    mov QWORD [rbp - 800], rax
    mov QWORD [rbp - 824], 0
    mov QWORD [rbp - 832], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 832], rax
    mov QWORD [rbp - 840], 0
    mov rax, QWORD [rbp - 800]
    mov QWORD [rbp - 840], rax
    mov rax, QWORD [rbp - 832]
    mov rbx, QWORD [rbp - 840]
    add rax,rbx
    mov QWORD [rbp - 824], rax
    mov QWORD [rbp - 848], 0
    mov QWORD [rbp - 856], 0
    mov rax, QWORD [rbp - 824]
    mov QWORD [rbp - 856], rax
    mov QWORD [rbp - 864], 0
    mov QWORD [rbp - 864], 7
    mov rax, QWORD [rbp - 856]
    mov rbx, QWORD [rbp - 864]
    cqo
    idiv rbx
    mov QWORD [rbp - 848],rdx
    mov QWORD [rbp - 872], 0
    mov QWORD [rbp - 880], 0
    mov rax, QWORD [rbp - 680]
    mov QWORD [rbp - 880], rax
    mov QWORD [rbp - 888], 0
    mov rax, QWORD [rbp - 848]
    mov QWORD [rbp - 888], rax
    mov rax, QWORD [rbp - 880]
    mov rbx, QWORD [rbp - 888]
    add rax,rbx
    mov QWORD [rbp - 872], rax
    mov rax, QWORD [rbp - 872]
    mov QWORD [rbp - 896], rax
    mov rax, QWORD [rbp - 896]
    leave
    ret
recursive_deep:
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
    setle al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L17
    jmp .L18
    .L17:
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 112]
    leave
    ret
    .L18:
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
    call recursive_deep
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
long_loop_chain:
    push rbp
    mov  rbp, rsp
    sub  rsp, 240
    mov QWORD [rbp - 8], 0
    mov QWORD [rbp - 16], 0
    .L19:
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 40], 100
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L20
    jmp .L21
    .L20:
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 96], 10
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    cqo
    idiv rbx
    mov QWORD [rbp - 80],rdx
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 112]
    mov rbx, QWORD [rbp - 120]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    cmp rax, 0
    jne .L22
    jmp .L23
    .L22:
    lea rax, [rbp - 176]
    mov QWORD [rbp - 184], rax
    mov byte [rbp - 176], 'T'
    mov byte [rbp - 175], 'e'
    mov byte [rbp - 174], 'n'
    mov byte [rbp - 173], 's'
    mov byte [rbp - 172], ':'
    mov byte [rbp - 171], ' '
    mov byte [rbp - 170], 0
    mov rdi, QWORD [rbp - 184]
    mov QWORD [rbp - 192], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 192],rax
    lea rax, [rbp - 200]
    mov QWORD [rbp - 208], rax
    mov byte [rbp - 200], '%'
    mov byte [rbp - 199], 'd'
    mov byte [rbp - 198], ' '
    mov byte [rbp - 197], 0
    mov rdi, QWORD [rbp - 208]
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 216], rax
    mov rsi, QWORD [rbp - 216]
    mov QWORD [rbp - 224], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 224],rax
    .L23:
    mov QWORD [rbp - 128], 0
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 136], rax
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 136]
    mov rbx, QWORD [rbp - 144]
    add rax,rbx
    mov QWORD [rbp - 128], rax
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 8], rax
    mov QWORD [rbp - 152], 0
    mov QWORD [rbp - 160], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 160], rax
    mov QWORD [rbp - 168], 0
    mov QWORD [rbp - 168], 1
    mov rax, QWORD [rbp - 160]
    mov rbx, QWORD [rbp - 168]
    add rax,rbx
    mov QWORD [rbp - 152], rax
    mov rax, QWORD [rbp - 152]
    mov QWORD [rbp - 16], rax
    jmp .L19
    .L21:
    lea rax, [rbp - 48]
    mov QWORD [rbp - 56], rax
    mov byte [rbp - 48], 0x0A
    mov byte [rbp - 47], 0
    mov rdi, QWORD [rbp - 56]
    mov QWORD [rbp - 64], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 64],rax
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 72]
    leave
    ret
string_block:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    lea rax, [rbp - 16]
    mov QWORD [rbp - 24], rax
    mov byte [rbp - 16], 'B'
    mov byte [rbp - 15], 'h'
    mov byte [rbp - 14], 'a'
    mov byte [rbp - 13], 'u'
    mov byte [rbp - 12], 'L'
    mov byte [rbp - 11], 'a'
    mov byte [rbp - 10], 'n'
    mov byte [rbp - 9], 'g'
    mov byte [rbp - 8], 0
    leave
    ret

everything:
    push rbp
    mov  rbp, rsp
    sub  rsp, 624
    mov QWORD [rbp - 8], rdi
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 24], rax
    mov rdi, QWORD [rbp - 24]
    mov QWORD [rbp - 32], 0
    xor rax,rax
    call recursive_deep
    mov QWORD [rbp - 32],rax
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 48], rax
    mov rdi, QWORD [rbp - 48]
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 56], rax
    mov rsi, QWORD [rbp - 56]
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 80], 1
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    add rax,rbx
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 88], rax
    mov rdx, QWORD [rbp - 88]
    mov QWORD [rbp - 96], 0
    xor rax,rax
    call math_ops
    mov QWORD [rbp - 96],rax
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 0
    xor rax,rax
    call long_loop_chain
    mov QWORD [rbp - 112],rax
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 120], rax
    mov QWORD [rbp - 128], 0
    xor rax,rax
    call giant_exprs
    mov QWORD [rbp - 128],rax
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 136], rax
    lea rax, [rbp - 144]
    mov QWORD [rbp - 152], rax
    mov byte [rbp - 144], 't'
    mov byte [rbp - 143], 'e'
    mov byte [rbp - 142], 'm'
    mov byte [rbp - 141], 'p'
    mov byte [rbp - 140], ':'
    mov byte [rbp - 139], ' '
    mov byte [rbp - 138], 0
    mov rdi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 160],rax
    lea rax, [rbp - 168]
    mov QWORD [rbp - 176], rax
    mov byte [rbp - 168], '%'
    mov byte [rbp - 167], 'd'
    mov byte [rbp - 166], 0x0A
    mov byte [rbp - 165], 0
    mov rdi, QWORD [rbp - 176]
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 184], rax
    mov rsi, QWORD [rbp - 184]
    mov QWORD [rbp - 192], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 192],rax
    lea rax, [rbp - 200]
    mov QWORD [rbp - 208], rax
    mov byte [rbp - 200], 'm'
    mov byte [rbp - 199], 'i'
    mov byte [rbp - 198], 'd'
    mov byte [rbp - 197], ':'
    mov byte [rbp - 196], ' '
    mov byte [rbp - 195], 0
    mov rdi, QWORD [rbp - 208]
    mov QWORD [rbp - 216], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 216],rax
    lea rax, [rbp - 224]
    mov QWORD [rbp - 232], rax
    mov byte [rbp - 224], '%'
    mov byte [rbp - 223], 'd'
    mov byte [rbp - 222], 0x0A
    mov byte [rbp - 221], 0
    mov rdi, QWORD [rbp - 232]
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 240], rax
    mov rsi, QWORD [rbp - 240]
    mov QWORD [rbp - 248], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 248],rax
    lea rax, [rbp - 256]
    mov QWORD [rbp - 264], rax
    mov byte [rbp - 256], 'o'
    mov byte [rbp - 255], 'p'
    mov byte [rbp - 254], 's'
    mov byte [rbp - 253], ':'
    mov byte [rbp - 252], ' '
    mov byte [rbp - 251], 0
    mov rdi, QWORD [rbp - 264]
    mov QWORD [rbp - 272], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 272],rax
    lea rax, [rbp - 280]
    mov QWORD [rbp - 288], rax
    mov byte [rbp - 280], '%'
    mov byte [rbp - 279], 'd'
    mov byte [rbp - 278], 0x0A
    mov byte [rbp - 277], 0
    mov rdi, QWORD [rbp - 288]
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 296], rax
    mov rsi, QWORD [rbp - 296]
    mov QWORD [rbp - 304], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 304],rax
    lea rax, [rbp - 320]
    mov QWORD [rbp - 328], rax
    mov byte [rbp - 320], 'l'
    mov byte [rbp - 319], 'o'
    mov byte [rbp - 318], 'n'
    mov byte [rbp - 317], 'g'
    mov byte [rbp - 316], 'r'
    mov byte [rbp - 315], 'e'
    mov byte [rbp - 314], 's'
    mov byte [rbp - 313], ':'
    mov byte [rbp - 312], ' '
    mov byte [rbp - 311], 0
    mov rdi, QWORD [rbp - 328]
    mov QWORD [rbp - 336], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 336],rax
    lea rax, [rbp - 344]
    mov QWORD [rbp - 352], rax
    mov byte [rbp - 344], '%'
    mov byte [rbp - 343], 'd'
    mov byte [rbp - 342], 0x0A
    mov byte [rbp - 341], 0
    mov rdi, QWORD [rbp - 352]
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 360], rax
    mov rsi, QWORD [rbp - 360]
    mov QWORD [rbp - 368], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 368],rax
    lea rax, [rbp - 376]
    mov QWORD [rbp - 384], rax
    mov byte [rbp - 376], 'g'
    mov byte [rbp - 375], 'i'
    mov byte [rbp - 374], 'a'
    mov byte [rbp - 373], 'n'
    mov byte [rbp - 372], 't'
    mov byte [rbp - 371], ':'
    mov byte [rbp - 370], ' '
    mov byte [rbp - 369], 0
    mov rdi, QWORD [rbp - 384]
    mov QWORD [rbp - 392], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 392],rax
    lea rax, [rbp - 400]
    mov QWORD [rbp - 408], rax
    mov byte [rbp - 400], '%'
    mov byte [rbp - 399], 'd'
    mov byte [rbp - 398], 0x0A
    mov byte [rbp - 397], 0
    mov rdi, QWORD [rbp - 408]
    mov rax, QWORD [rbp - 136]
    mov QWORD [rbp - 416], rax
    mov rsi, QWORD [rbp - 416]
    mov QWORD [rbp - 424], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 424],rax
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 432], rax
    mov rdi, QWORD [rbp - 432]
    mov QWORD [rbp - 440], 0
    xor rax,rax
    call recursive_deep
    mov QWORD [rbp - 440],rax
    mov QWORD [rbp - 448], 0
    mov QWORD [rbp - 456], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 456], rax
    mov QWORD [rbp - 464], 0
    mov rax, QWORD [rbp - 440]
    mov QWORD [rbp - 464], rax
    mov rax, QWORD [rbp - 456]
    mov rbx, QWORD [rbp - 464]
    add rax,rbx
    mov QWORD [rbp - 448], rax
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 472], rax
    mov rdi, QWORD [rbp - 472]
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 480], rax
    mov rsi, QWORD [rbp - 480]
    mov QWORD [rbp - 488], 0
    mov QWORD [rbp - 496], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 496], rax
    mov QWORD [rbp - 504], 0
    mov QWORD [rbp - 504], 1
    mov rax, QWORD [rbp - 496]
    mov rbx, QWORD [rbp - 504]
    add rax,rbx
    mov QWORD [rbp - 488], rax
    mov rax, QWORD [rbp - 488]
    mov QWORD [rbp - 512], rax
    mov rdx, QWORD [rbp - 512]
    mov QWORD [rbp - 520], 0
    xor rax,rax
    call math_ops
    mov QWORD [rbp - 520],rax
    mov QWORD [rbp - 528], 0
    mov QWORD [rbp - 536], 0
    mov rax, QWORD [rbp - 448]
    mov QWORD [rbp - 536], rax
    mov QWORD [rbp - 544], 0
    mov rax, QWORD [rbp - 520]
    mov QWORD [rbp - 544], rax
    mov rax, QWORD [rbp - 536]
    mov rbx, QWORD [rbp - 544]
    add rax,rbx
    mov QWORD [rbp - 528], rax
    mov QWORD [rbp - 552], 0
    xor rax,rax
    call long_loop_chain
    mov QWORD [rbp - 552],rax
    mov QWORD [rbp - 560], 0
    mov QWORD [rbp - 568], 0
    mov rax, QWORD [rbp - 528]
    mov QWORD [rbp - 568], rax
    mov QWORD [rbp - 576], 0
    mov rax, QWORD [rbp - 552]
    mov QWORD [rbp - 576], rax
    mov rax, QWORD [rbp - 568]
    mov rbx, QWORD [rbp - 576]
    add rax,rbx
    mov QWORD [rbp - 560], rax
    mov QWORD [rbp - 584], 0
    xor rax,rax
    call giant_exprs
    mov QWORD [rbp - 584],rax
    mov QWORD [rbp - 592], 0
    mov QWORD [rbp - 600], 0
    mov rax, QWORD [rbp - 560]
    mov QWORD [rbp - 600], rax
    mov QWORD [rbp - 608], 0
    mov rax, QWORD [rbp - 584]
    mov QWORD [rbp - 608], rax
    mov rax, QWORD [rbp - 600]
    mov rbx, QWORD [rbp - 608]
    add rax,rbx
    mov QWORD [rbp - 592], rax
    mov rax, QWORD [rbp - 592]
    mov QWORD [rbp - 616], rax
    mov rax, QWORD [rbp - 616]
    leave
    ret
branch_test:
    push rbp
    mov  rbp, rsp
    sub  rsp, 208
    mov QWORD [rbp - 8], 5
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L24
    lea rax, [rbp - 56]
    mov QWORD [rbp - 64], rax
    mov byte [rbp - 56], 'N'
    mov byte [rbp - 55], 'e'
    mov byte [rbp - 54], 'g'
    mov byte [rbp - 53], 'a'
    mov byte [rbp - 52], 't'
    mov byte [rbp - 51], 'i'
    mov byte [rbp - 50], 'v'
    mov byte [rbp - 49], 'e'
    mov byte [rbp - 48], ' '
    mov byte [rbp - 47], 'o'
    mov byte [rbp - 46], 'r'
    mov byte [rbp - 45], ' '
    mov byte [rbp - 44], 'Z'
    mov byte [rbp - 43], 'e'
    mov byte [rbp - 42], 'r'
    mov byte [rbp - 41], 'o'
    mov byte [rbp - 40], 0x0A
    mov byte [rbp - 39], 0
    mov rdi, QWORD [rbp - 64]
    mov QWORD [rbp - 72], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 72],rax
    jmp .L25
    .L24:
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 96], 3
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 80]
    cmp rax, 0
    jne .L26
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 120], 6
    mov rax, QWORD [rbp - 112]
    mov rbx, QWORD [rbp - 120]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    cmp rax, 0
    jne .L28
    lea rax, [rbp - 128]
    mov QWORD [rbp - 136], rax
    mov byte [rbp - 128], '?'
    mov byte [rbp - 127], '?'
    mov byte [rbp - 126], '?'
    mov byte [rbp - 125], 0x0A
    mov byte [rbp - 124], 0
    mov rdi, QWORD [rbp - 136]
    mov QWORD [rbp - 144], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 144],rax
    jmp .L29
    .L28:
    lea rax, [rbp - 160]
    mov QWORD [rbp - 168], rax
    mov byte [rbp - 160], 'S'
    mov byte [rbp - 159], 'm'
    mov byte [rbp - 158], 'a'
    mov byte [rbp - 157], 'l'
    mov byte [rbp - 156], 'l'
    mov byte [rbp - 155], 'i'
    mov byte [rbp - 154], 's'
    mov byte [rbp - 153], 'h'
    mov byte [rbp - 152], 0x0A
    mov byte [rbp - 151], 0
    mov rdi, QWORD [rbp - 168]
    mov QWORD [rbp - 176], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 176],rax
    .L29:
    jmp .L27
    .L26:
    lea rax, [rbp - 184]
    mov QWORD [rbp - 192], rax
    mov byte [rbp - 184], 'T'
    mov byte [rbp - 183], 'i'
    mov byte [rbp - 182], 'n'
    mov byte [rbp - 181], 'y'
    mov byte [rbp - 180], 0x0A
    mov byte [rbp - 179], 0
    mov rdi, QWORD [rbp - 192]
    mov QWORD [rbp - 200], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 200],rax
    .L27:
    .L25:
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 624
    mov rax, global_app_name
    mov QWORD [rbp - 8], rax
    mov rdi, QWORD [rbp - 8]
    mov QWORD [rbp - 16], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 16],rax
    lea rax, [rbp - 48]
    mov QWORD [rbp - 56], rax
    mov byte [rbp - 48], '='
    mov byte [rbp - 47], '='
    mov byte [rbp - 46], '='
    mov byte [rbp - 45], '='
    mov byte [rbp - 44], ' '
    mov byte [rbp - 43], 'S'
    mov byte [rbp - 42], 't'
    mov byte [rbp - 41], 'a'
    mov byte [rbp - 40], 'r'
    mov byte [rbp - 39], 't'
    mov byte [rbp - 38], ' '
    mov byte [rbp - 37], 'S'
    mov byte [rbp - 36], 't'
    mov byte [rbp - 35], 'r'
    mov byte [rbp - 34], 'e'
    mov byte [rbp - 33], 's'
    mov byte [rbp - 32], 's'
    mov byte [rbp - 31], ' '
    mov byte [rbp - 30], 'T'
    mov byte [rbp - 29], 'e'
    mov byte [rbp - 28], 's'
    mov byte [rbp - 27], 't'
    mov byte [rbp - 26], ' '
    mov byte [rbp - 25], '='
    mov byte [rbp - 24], '='
    mov byte [rbp - 23], '='
    mov byte [rbp - 22], '='
    mov byte [rbp - 21], 0x0A
    mov byte [rbp - 20], 0
    mov rdi, QWORD [rbp - 56]
    mov QWORD [rbp - 64], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 64],rax
    mov QWORD [rbp - 72], 2
    mov rdi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 3
    mov rsi, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 4
    mov rdx, QWORD [rbp - 88]
    mov QWORD [rbp - 96], 0
    xor rax,rax
    call math_ops
    mov QWORD [rbp - 96],rax
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 5
    mov rdi, QWORD [rbp - 112]
    mov QWORD [rbp - 120], 0
    xor rax,rax
    call level1
    mov QWORD [rbp - 120],rax
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 3
    mov rdi, QWORD [rbp - 136]
    mov QWORD [rbp - 144], 0
    xor rax,rax
    call call_chain
    mov QWORD [rbp - 144],rax
    mov rax, QWORD [rbp - 144]
    mov QWORD [rbp - 152], rax
    mov QWORD [rbp - 160], 4
    mov rdi, QWORD [rbp - 160]
    mov QWORD [rbp - 168], 0
    xor rax,rax
    call everything
    mov QWORD [rbp - 168],rax
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 176], rax
    lea rax, [rbp - 192]
    mov QWORD [rbp - 200], rax
    mov byte [rbp - 192], 'M'
    mov byte [rbp - 191], 'a'
    mov byte [rbp - 190], 't'
    mov byte [rbp - 189], 'h'
    mov byte [rbp - 188], 'O'
    mov byte [rbp - 187], 'p'
    mov byte [rbp - 186], 's'
    mov byte [rbp - 185], ':'
    mov byte [rbp - 184], ' '
    mov byte [rbp - 183], 0
    mov rdi, QWORD [rbp - 200]
    mov QWORD [rbp - 208], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 208],rax
    lea rax, [rbp - 216]
    mov QWORD [rbp - 224], rax
    mov byte [rbp - 216], '%'
    mov byte [rbp - 215], 'd'
    mov byte [rbp - 214], 0x0A
    mov byte [rbp - 213], 0
    mov rdi, QWORD [rbp - 224]
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 232], rax
    mov rsi, QWORD [rbp - 232]
    mov QWORD [rbp - 240], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 240],rax
    lea rax, [rbp - 256]
    mov QWORD [rbp - 264], rax
    mov byte [rbp - 256], 'L'
    mov byte [rbp - 255], 'e'
    mov byte [rbp - 254], 'v'
    mov byte [rbp - 253], 'e'
    mov byte [rbp - 252], 'l'
    mov byte [rbp - 251], '1'
    mov byte [rbp - 250], ':'
    mov byte [rbp - 249], ' '
    mov byte [rbp - 248], 0
    mov rdi, QWORD [rbp - 264]
    mov QWORD [rbp - 272], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 272],rax
    lea rax, [rbp - 280]
    mov QWORD [rbp - 288], rax
    mov byte [rbp - 280], '%'
    mov byte [rbp - 279], 'd'
    mov byte [rbp - 278], 0x0A
    mov byte [rbp - 277], 0
    mov rdi, QWORD [rbp - 288]
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 296], rax
    mov rsi, QWORD [rbp - 296]
    mov QWORD [rbp - 304], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 304],rax
    lea rax, [rbp - 320]
    mov QWORD [rbp - 328], rax
    mov byte [rbp - 320], 'C'
    mov byte [rbp - 319], 'a'
    mov byte [rbp - 318], 'l'
    mov byte [rbp - 317], 'l'
    mov byte [rbp - 316], 'C'
    mov byte [rbp - 315], 'h'
    mov byte [rbp - 314], 'a'
    mov byte [rbp - 313], 'i'
    mov byte [rbp - 312], 'n'
    mov byte [rbp - 311], ':'
    mov byte [rbp - 310], ' '
    mov byte [rbp - 309], 0
    mov rdi, QWORD [rbp - 328]
    mov QWORD [rbp - 336], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 336],rax
    lea rax, [rbp - 344]
    mov QWORD [rbp - 352], rax
    mov byte [rbp - 344], '%'
    mov byte [rbp - 343], 'd'
    mov byte [rbp - 342], 0x0A
    mov byte [rbp - 341], 0
    mov rdi, QWORD [rbp - 352]
    mov rax, QWORD [rbp - 152]
    mov QWORD [rbp - 360], rax
    mov rsi, QWORD [rbp - 360]
    mov QWORD [rbp - 368], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 368],rax
    lea rax, [rbp - 392]
    mov QWORD [rbp - 400], rax
    mov byte [rbp - 392], 'E'
    mov byte [rbp - 391], 'v'
    mov byte [rbp - 390], 'e'
    mov byte [rbp - 389], 'r'
    mov byte [rbp - 388], 'y'
    mov byte [rbp - 387], 't'
    mov byte [rbp - 386], 'h'
    mov byte [rbp - 385], 'i'
    mov byte [rbp - 384], 'n'
    mov byte [rbp - 383], 'g'
    mov byte [rbp - 382], ' '
    mov byte [rbp - 381], 'C'
    mov byte [rbp - 380], 'o'
    mov byte [rbp - 379], 'm'
    mov byte [rbp - 378], 'b'
    mov byte [rbp - 377], 'o'
    mov byte [rbp - 376], ':'
    mov byte [rbp - 375], ' '
    mov byte [rbp - 374], 0
    mov rdi, QWORD [rbp - 400]
    mov QWORD [rbp - 408], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 408],rax
    lea rax, [rbp - 416]
    mov QWORD [rbp - 424], rax
    mov byte [rbp - 416], '%'
    mov byte [rbp - 415], 'd'
    mov byte [rbp - 414], 0x0A
    mov byte [rbp - 413], 0
    mov rdi, QWORD [rbp - 424]
    mov rax, QWORD [rbp - 176]
    mov QWORD [rbp - 432], rax
    mov rsi, QWORD [rbp - 432]
    mov QWORD [rbp - 440], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 440],rax
    mov QWORD [rbp - 448], -10
    mov rdi, QWORD [rbp - 448]
    mov QWORD [rbp - 456], 0
    xor rax,rax
    call decision_tree
    mov QWORD [rbp - 456],rax
    mov QWORD [rbp - 464], 0
    mov rdi, QWORD [rbp - 464]
    mov QWORD [rbp - 472], 0
    xor rax,rax
    call decision_tree
    mov QWORD [rbp - 472],rax
    mov QWORD [rbp - 480], 5
    mov rdi, QWORD [rbp - 480]
    mov QWORD [rbp - 488], 0
    xor rax,rax
    call decision_tree
    mov QWORD [rbp - 488],rax
    mov QWORD [rbp - 496], 50
    mov rdi, QWORD [rbp - 496]
    mov QWORD [rbp - 504], 0
    xor rax,rax
    call decision_tree
    mov QWORD [rbp - 504],rax
    mov QWORD [rbp - 512], 500
    mov rdi, QWORD [rbp - 512]
    mov QWORD [rbp - 520], 0
    xor rax,rax
    call decision_tree
    mov QWORD [rbp - 520],rax
    mov QWORD [rbp - 528], 0
    xor rax,rax
    call multiple_assigns
    mov QWORD [rbp - 528],rax
    mov QWORD [rbp - 536], 0
    xor rax,rax
    call scope_depth_test
    mov QWORD [rbp - 536],rax
    mov QWORD [rbp - 544], 0
    xor rax,rax
    call giant_exprs
    mov QWORD [rbp - 544],rax
    mov QWORD [rbp - 552], 0
    xor rax,rax
    call long_loop_chain
    mov QWORD [rbp - 552],rax
    mov QWORD [rbp - 560], 0
    xor rax,rax
    call string_block
    mov QWORD [rbp - 560],rax
    mov QWORD [rbp - 568], 0
    xor rax,rax
    call branch_test
    mov QWORD [rbp - 568],rax
    lea rax, [rbp - 600]
    mov QWORD [rbp - 608], rax
    mov byte [rbp - 600], '='
    mov byte [rbp - 599], '='
    mov byte [rbp - 598], '='
    mov byte [rbp - 597], '='
    mov byte [rbp - 596], ' '
    mov byte [rbp - 595], 'E'
    mov byte [rbp - 594], 'n'
    mov byte [rbp - 593], 'd'
    mov byte [rbp - 592], ' '
    mov byte [rbp - 591], 'S'
    mov byte [rbp - 590], 't'
    mov byte [rbp - 589], 'r'
    mov byte [rbp - 588], 'e'
    mov byte [rbp - 587], 's'
    mov byte [rbp - 586], 's'
    mov byte [rbp - 585], ' '
    mov byte [rbp - 584], 'T'
    mov byte [rbp - 583], 'e'
    mov byte [rbp - 582], 's'
    mov byte [rbp - 581], 't'
    mov byte [rbp - 580], ' '
    mov byte [rbp - 579], '='
    mov byte [rbp - 578], '='
    mov byte [rbp - 577], '='
    mov byte [rbp - 576], '='
    mov byte [rbp - 575], 0
    mov rdi, QWORD [rbp - 608]
    mov QWORD [rbp - 616], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 616],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack
