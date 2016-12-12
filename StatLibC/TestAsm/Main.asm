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
mainz1 SDWORD  0 


.const
csname db 'BNI-2016', 0
Overflow db 'ERROR on size of variable', 0
DIV_NULL db 'ERROR IN DIVISION(NULL)', 0
L0 SDWORD  4
.stack 4096


.code


main PROC 
 push offset csname
 call SetConsoleTitleA
  push mainz1
 push mainz1
 pop eax
 pop ebx
 add eax,ebx
 jo EXIT_overflow
 push eax
 push mainz1
 pop eax
 pop ebx
 add eax,ebx
 jo EXIT_overflow
 push eax
 push mainz1
 pop eax
 pop ebx
 add eax,ebx
 jo EXIT_overflow
 push eax
 pop mainz1

 push mainz1
 call writei
 push L0
 call ExitProcess


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


main ENDP


end main