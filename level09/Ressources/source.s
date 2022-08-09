;  -------------------------------------------------
; | secret_backdor() function at 0x000055555555488c |
;  -------------------------------------------------

; prologue
0x000055555555088c <+0>:     push   %rbp
0x000055555555088d <+1>:     mov    %rsp,%rbp
0x0000555555550890 <+4>:     add    $0xffffffffffffff80,%rsp

; fgets()
0x0000555555550894 <+8>:     mov    0x20171d(%rip),%rax        # 0x201fb8
0x000055555555089b <+15>:    mov    (%rax),%rax
0x000055555555089e <+18>:    mov    %rax,%rdx
0x00005555555508a1 <+21>:    lea    -0x80(%rbp),%rax
0x00005555555508a5 <+25>:    mov    $0x80,%esi
0x00005555555508aa <+30>:    mov    %rax,%rdi
0x00005555555508ad <+33>:    callq  0x770 <fgets@plt>

; system();
0x00005555555508b2 <+38>:    lea    -0x80(%rbp),%rax
0x00005555555508b6 <+42>:    mov    %rax,%rdi
0x00005555555508b9 <+45>:    callq  0x740 <system@plt>

; epilogue
0x00005555555508be <+50>:    leaveq 
0x00005555555508bf <+51>:    retq

;  -----------------------------------------------
; | set_username() function at 0x00005555555549cd |
;  -----------------------------------------------

; prologue
0x00005555555509cd <+0>:     push   %rbp
0x00005555555509ce <+1>:     mov    %rsp,%rbp
0x00005555555509d1 <+4>:     sub    $0xa0,%rsp
0x00005555555509d8 <+11>:    mov    %rdi,-0x98(%rbp)

; bzero()
0x00005555555509df <+18>:    lea    -0x90(%rbp),%rax
0x00005555555509e6 <+25>:    mov    %rax,%rsi
0x00005555555509e9 <+28>:    mov    $0x0,%eax
0x00005555555509ee <+33>:    mov    $0x10,%edx
0x00005555555509f3 <+38>:    mov    %rsi,%rdi
0x00005555555509f6 <+41>:    mov    %rdx,%rcx
0x00005555555509f9 <+44>:    rep stos %rax,%es:(%rdi)

; puts()
0x00005555555509fc <+47>:    lea    0x1e1(%rip),%rdi        # 0xbe4
0x0000555555550a03 <+54>:    callq  0x730 <puts@plt>

; printf()
0x0000555555550a08 <+59>:    lea    0x1d0(%rip),%rax        # 0xbdf
0x0000555555550a0f <+66>:    mov    %rax,%rdi
0x0000555555550a12 <+69>:    mov    $0x0,%eax
0x0000555555550a17 <+74>:    callq  0x750 <printf@plt>

; fgets()
0x0000555555550a1c <+79>:    mov    0x201595(%rip),%rax        # 0x201fb8
0x0000555555550a23 <+86>:    mov    (%rax),%rax
0x0000555555550a26 <+89>:    mov    %rax,%rdx
0x0000555555550a29 <+92>:    lea    -0x90(%rbp),%rax
0x0000555555550a30 <+99>:    mov    $0x80,%esi
0x0000555555550a35 <+104>:   mov    %rax,%rdi
0x0000555555550a38 <+107>:   callq  0x770 <fgets@plt>

; for loop => copy buf in message->username
0x0000555555550a3d <+112>:   movl   $0x0,-0x4(%rbp)
0x0000555555550a44 <+119>:   jmp    0xa6a <set_username+157>
0x0000555555550a46 <+121>:   mov    -0x4(%rbp),%eax
0x0000555555550a49 <+124>:   cltq   
0x0000555555550a4b <+126>:   movzbl -0x90(%rbp,%rax,1),%ecx
0x0000555555550a53 <+134>:   mov    -0x98(%rbp),%rdx
0x0000555555550a5a <+141>:   mov    -0x4(%rbp),%eax
0x0000555555550a5d <+144>:   cltq   
0x0000555555550a5f <+146>:   mov    %cl,0x8c(%rdx,%rax,1)
0x0000555555550a66 <+153>:   addl   $0x1,-0x4(%rbp)
0x0000555555550a6a <+157>:   cmpl   $0x28,-0x4(%rbp)
0x0000555555550a6e <+161>:   jg     0xa81 <set_username+180>
0x0000555555550a70 <+163>:   mov    -0x4(%rbp),%eax
0x0000555555550a73 <+166>:   cltq   
0x0000555555550a75 <+168>:   movzbl -0x90(%rbp,%rax,1),%eax
0x0000555555550a7d <+176>:   test   %al,%al
0x0000555555550a7f <+178>:   jne    0xa46 <set_username+121>

; printf()
0x0000555555550a81 <+180>:   mov    -0x98(%rbp),%rax
0x0000555555550a88 <+187>:   lea    0x8c(%rax),%rdx
0x0000555555550a8f <+194>:   lea    0x165(%rip),%rax        # 0xbfb
0x0000555555550a96 <+201>:   mov    %rdx,%rsi
0x0000555555550a99 <+204>:   mov    %rax,%rdi
0x0000555555550a9c <+207>:   mov    $0x0,%eax
0x0000555555550aa1 <+212>:   callq  0x750 <printf@plt>

; epilogue
0x0000555555550aa6 <+217>:   leaveq 
0x0000555555550aa7 <+218>:   retq

;  ------------------------------------------
; | set_msg() function at 0x0000555555554932 |
;  ------------------------------------------

; prologue
0x0000555555550932 <+0>:     push   %rbp
0x0000555555550933 <+1>:     mov    %rsp,%rbp
0x0000555555550936 <+4>:     sub    $0x410,%rsp
0x000055555555093d <+11>:    mov    %rdi,-0x408(%rbp)

; bzero()
0x0000555555550944 <+18>:    lea    -0x400(%rbp),%rax
0x000055555555094b <+25>:    mov    %rax,%rsi
0x000055555555094e <+28>:    mov    $0x0,%eax
0x0000555555550953 <+33>:    mov    $0x80,%edx
0x0000555555550958 <+38>:    mov    %rsi,%rdi
0x000055555555095b <+41>:    mov    %rdx,%rcx
0x000055555555095e <+44>:    rep stos %rax,%es:(%rdi)

; puts()
0x0000555555550961 <+47>:    lea    0x265(%rip),%rdi        # 0xbcd
0x0000555555550968 <+54>:    callq  0x730 <puts@plt>

; printf()
0x000055555555096d <+59>:    lea    0x26b(%rip),%rax        # 0xbdf
0x0000555555550974 <+66>:    mov    %rax,%rdi
0x0000555555550977 <+69>:    mov    $0x0,%eax
0x000055555555097c <+74>:    callq  0x750 <printf@plt>

; fgets()
0x0000555555550981 <+79>:    mov    0x201630(%rip),%rax        # 0x201fb8
0x0000555555550988 <+86>:    mov    (%rax),%rax
0x000055555555098b <+89>:    mov    %rax,%rdx
0x000055555555098e <+92>:    lea    -0x400(%rbp),%rax                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ,%rax
0x0000555555550995 <+99>:    mov    $0x400,%esi
0x000055555555099a <+104>:   mov    %rax,%rdi
0x000055555555099d <+107>:   callq  0x770 <fgets@plt>

; strncpy()
0x00005555555509a2 <+112>:   mov    -0x408(%rbp),%rax
0x00005555555509a9 <+119>:   mov    0xb4(%rax),%eax
0x00005555555509af <+125>:   movslq %eax,%rdx
0x00005555555509b2 <+128>:   lea    -0x400(%rbp),%rcx
0x00005555555509b9 <+135>:   mov    -0x408(%rbp),%rax
0x00005555555509c0 <+142>:   mov    %rcx,%rsi
0x00005555555509c3 <+145>:   mov    %rax,%rdi
0x00005555555509c6 <+148>:   callq  0x720 <strncpy@plt>

; epilogue
0x00005555555509cb <+153>:   leaveq 
0x00005555555509cc <+154>:   retq

;  ---------------------------------------------
; | handle_msg() function at 0x0000555555554aa8 |
;  ---------------------------------------------

; prologue
0x00005555555508c0 <+0>:     push   %rbp
0x00005555555508c1 <+1>:     mov    %rsp,%rbp
0x00005555555508c4 <+4>:     sub    $0xc0,%rsp
0x00005555555508cb <+11>:    lea    -0xc0(%rbp),%rax
0x00005555555508d2 <+18>:    add    $0x8c,%rax
0x00005555555508d8 <+24>:    movq   $0x0,(%rax)
0x00005555555508df <+31>:    movq   $0x0,0x8(%rax)
0x00005555555508e7 <+39>:    movq   $0x0,0x10(%rax)
0x00005555555508ef <+47>:    movq   $0x0,0x18(%rax)
0x00005555555508f7 <+55>:    movq   $0x0,0x20(%rax)

; set message->size
0x00005555555508ff <+63>:    movl   $0x8c,-0xc(%rbp)

; set_username()
0x0000555555550906 <+70>:    lea    -0xc0(%rbp),%rax
0x000055555555090d <+77>:    mov    %rax,%rdi
0x0000555555550910 <+80>:    callq  0x9cd <set_username>

; set_msg()
0x0000555555550915 <+85>:    lea    -0xc0(%rbp),%rax
0x000055555555091c <+92>:    mov    %rax,%rdi
0x000055555555091f <+95>:    callq  0x932 <set_msg>

; puts()
0x0000555555550924 <+100>:   lea    0x295(%rip),%rdi        # 0xbc0
0x000055555555092b <+107>:   callq  0x730 <puts@plt>

; epilogue
0x0000555555550930 <+112>:   leaveq 
0x0000555555550931 <+113>:   retq

;  ---------------------------------------
; | main() function at 0x0000555555550aa8 |
;  ---------------------------------------

; prologue
0x0000555555550aa8 <+0>:     push   %rbp
0x0000555555550aa9 <+1>:     mov    %rsp,%rbp

; puts()
0x0000555555550aac <+4>:     lea    0x15d(%rip),%rdi        # 0xc10
0x0000555555550ab3 <+11>:    callq  0x730 <puts@plt>

; handle_msg()
0x0000555555550ab8 <+16>:    callq  0x8c0 <handle_msg>

; epilogue
0x0000555555550abd <+21>:    mov    $0x0,%eax
0x0000555555550ac2 <+26>:    pop    %rbp
0x0000555555550ac3 <+27>:    retq