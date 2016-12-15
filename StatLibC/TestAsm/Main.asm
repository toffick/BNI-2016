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
retpow0v SDWORD  0 
retlen0x SDWORD  0 
main0x SDWORD  0 
main0y SDWORD  0 
main0z SDWORD  0 
main0sa DWORD  ?
main0sb SDWORD  0 


.const
csname db 'BNI-2016', 0
Overflow db 'ERROR overflow', 0
DIV_NULL db 'ERROR DBN', 0
newline db '0',0
L0 SDWORD  4
L1 BYTE  'string for return', 0
L2 SDWORD  8
L3 BYTE  'dd', 0
L4 SDWORD  3
L5 SDWORD  2
L6 BYTE  'the value of function = ', 0
L7 SDWORD  88
L8 BYTE  'qwerty', 0
L9 BYTE  'the length of string = ', 0
.stack 4096


.code


retpow0 PROC retpow0x:SDWORD,  retpow0y:SDWORD
 push retpow0y
 push retpow0x
 call ipow
 push edx
 push L0
 pop eax
 pop ebx
 add eax,ebx
 jo EXIT_overflow
 push eax
 pop retpow0v
 push retpow0v
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

retpow0 ENDP 

 
retlen0 PROC  retlen0st:DWORD
 push retlen0st
 call strl
 push edx
 pop retlen0x
 push retlen0x
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

retlen0 ENDP 

 
retstr0 PROC  retstr0i:DWORD
 push offset L1
 pop retstr0i
 push retstr0i
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

retstr0 ENDP 

 
main PROC 
 push offset csname
 call SetConsoleTitleA
  push L2
 push offset L3
 call strl
 push edx
 push L4
 pop eax
 pop ebx
 add eax,ebx
 jo EXIT_overflow
 push eax
 pop ebx
 pop eax
 test ebx, ebx
 jz EXIT_div_on_NULL
 cdq
 idiv ebx
 push eax
 pop main0x

 push L4
 pop main0x

 push L5
 pop main0y

 push offset L6
 call writes
 push main0y
 push main0x
 call retpow0
 push edx
 push L5
 pop eax
 pop ebx
 imul eax,ebx
 jo EXIT_overflow
 push eax
 push L7
 pop ebx
 pop eax
 sub eax,ebx
 jo EXIT_overflow
 push eax
 push L2
 push L0
 pop ebx
 pop eax
 test ebx, ebx
 jz EXIT_div_on_NULL
 cdq
 idiv ebx
 push eax
 pop ebx
 pop eax
 sub eax,ebx
 jo EXIT_overflow
 push eax
 pop main0z

 push main0z
 call writei
 push offset newline
 call writes
 push main0sa
 call retstr0
 push edx
 pop main0sa

 push main0sa
 call writes
 push offset newline
 call writes
 push offset L8
 call retlen0
 push edx
 pop main0sb

 push offset L9
 call writes
 push main0sb
 call writei
 push offset newline
 call writes





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
  push offset L1
 call ExitProcess


main ENDP


end main