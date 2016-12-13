.586
.model flat, stdcall

includelib kernel32.lib
includelib libucrt.lib
includelib StatLibC.lib

ExitProcess      PROTO : DWORD

SetConsoleTitleA PROTO :DWORD
GetStdHandle     PROTO : DWORD
writei PROTO : SDWORD
writes PROTO : DWORD
strl   PROTO : DWORD
ipow   PROTO : DWORD, : DWORD
sum    PROTO : DWORD, : DWORD
.stack 4096



.data
maind3 SDWORD  0 


.const
csname db 'BNI-2016', 0
Overflow db 'ERROR on size of variable', 0
DIV_NULL db 'ERROR IN DIVISION(NULL)', 0
L0 SDWORD  2
L1 SDWORD  4
L2 SDWORD  0
L3 BYTE  'Hey, Kolya', 0
.stack 4096


.code


q1 PROC  qf1:SDWORD
 push qf1
 pop edx
  
 jmp EXIT
EXIT_div_on_NULL:
 push offset DIV_NULL
 call writes
 push - 1
 call ExitProcess

EXIT_overflow:
 push offset Overflow
 call writes
 push - 2
 call ExitProcess

EXIT: 
 ret 

q1 ENDP

w2 PROC wfhy2:SDWORD,  wt2y2:SDWORD
 push wfhy2
 pop edx
  
 jmp EXIT
EXIT_div_on_NULL:
 push offset DIV_NULL
 call writes
 push - 1
 call ExitProcess

EXIT_overflow:
 push offset Overflow
 call writes
 push - 2
 call ExitProcess

EXIT: 
 ret 

w2 ENDP

main PROC 
 push offset csname
 call SetConsoleTitleA
  push L0
 push L0
 call ipow
 push edx
 push L1
 push L2
 pop eax
 pop ebx
 add eax,ebx
 jo EXIT_overflow
 push eax
 push L0
 pop eax
 pop ebx
 add eax,ebx
 jo EXIT_overflow
 push eax
 pop eax
 pop ebx
 imul eax,ebx
 jo EXIT_overflow
 push eax
 pop maind3

 push maind3
 call writei
 jmp EXIT
EXIT_div_on_NULL:
 push offset DIV_NULL
 call writes
 push - 1
 call ExitProcess

EXIT_overflow:
 push offset Overflow
 call writes
 push - 2
 call ExitProcess

EXIT:
  push offset L3
 call ExitProcess


main ENDP




end main