.586
.model flat, stdcall

includelib kernel32.lib
includelib libucrt.lib
includelib StatLibC.lib

ExitProcess      PROTO : DWORD

writei PROTO : SDWORD
writes PROTO : DWORD
strl   PROTO : DWORD
ipow   PROTO : DWORD, : DWORD
sum    PROTO : DWORD, : DWORD

.stack 4096



.data
maink SDWORD  0 


.const
L0 SDWORD  4
L1 SDWORD  0
.stack 4096


.code


main PROC 
 push L0
 pop maink

 push maink
 call writei
 push L1


  call ExitProcess

main ENDP


end main