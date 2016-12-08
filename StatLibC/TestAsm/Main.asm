
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
mainl SDWORD  0 


.const
csname db 'BNI-2016', 0
L0 SDWORD  5
L1 SDWORD  2
.stack 4096


.code


main PROC 
 push offset csname
 call SetConsoleTitleA
  push L0
 push L1
 pop ebx
 pop eax
 cdq
 idiv ebx
 push eax
 pop mainl

  push mainl
 call writei
  push L0


  call ExitProcess

main ENDP


end main