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

sss1 PROTO :SDWORD,:SDWORD,:SDWORD
.stack 4096



.data
mainkk2 SDWORD  0 


.const
csname db 'BNI-2016', 0
L0 SDWORD  5
L1 SDWORD  1
L2 SDWORD  2
L3 SDWORD  44
L4 SDWORD  0
.stack 4096


.code


sss1 PROC sssf1:SDWORD, sssff1:SDWORD,  sssoo1:SDWORD

   push L0
 pop edx
 ret 

sss1 ENDP

main PROC 
 push offset csname
 call SetConsoleTitleA
  push L3
 push L2
 push L1
 call sss1
 push edx
 pop mainkk2

  push mainkk2
 call writei
  push L4


  call ExitProcess

main ENDP



end main