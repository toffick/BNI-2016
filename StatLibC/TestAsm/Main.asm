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


.const
csname db 'BNI-2016', 0
Overflow db 'ERROR overflow', 0
DIV_NULL db 'ERROR DBN', 0
newline db ' ',0
L0 SDWORD  3
L1 SDWORD  5
.stack 4096


.code


main PROC 
 push offset csname
 call SetConsoleTitleA
  push L0
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
  push L1
 call ExitProcess


main ENDP


end main