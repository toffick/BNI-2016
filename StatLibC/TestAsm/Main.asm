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
fid1 SDWORD  0 
mainz2 SDWORD  0 
mainsa2 DWORD  ?
mainsb2 DWORD  ?
mainsc2 DWORD  ?


.const
csname db 'BNI-2016', 0
L0 SDWORD  4
L1 SDWORD  5
L2 SDWORD  8
L3 SDWORD  100
L4 SDWORD  2
L5 BYTE  'Hello World', 0
L6 BYTE  '13.02.1998', 0
.stack 4096


.code


fi1 PROC fix1:SDWORD,  fiy1:SDWORD

   push fid1
 pop edx
 ret 

fi1 ENDP 

 
main PROC 
 push offset csname
 call SetConsoleTitleA
  push L1
 push L0
 call fi1
 push edx
 pop mainz2

 push L1
 push L2
 pop ebx
 pop eax
 sub eax,ebx
 push eax
 pop mainz2

  push mainz2
 call writei
 push mainz2
 push L1
 pop ebx
 pop eax
 sub eax,ebx
 push eax
 pop mainz2

  push mainz2
 call writei
 push mainz2
 push L3
 pop eax
 pop ebx
 add eax,ebx
 push eax
 pop mainz2

  push mainz2
 call writei
 push L4
 push mainz2
 call ipow
 push edx
 pop mainz2

  push mainz2
 call writei
 push offset L5
 pop mainsa2

  push mainsa2
 call writes
 push offset L6
 pop mainsb2






  push L0


 call ExitProcess

main ENDP


end main