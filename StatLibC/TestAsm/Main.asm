;.586                           
;.model flat, stdcall     
;      
;includelib kernel32.lib      
;includelib StatLibC.lib  
;						       
;ExitProcess      PROTO :DWORD  
;    
;writei PROTO :SDWORD
;writes PROTO :DWORD
;strl   PROTO :DWORD
;ipow   PROTO :DWORD, :DWORD
;sum    PROTO :DWORD, :DWORD
;						       
;.stack 4096                    
;						       
;.const             
;;	consoletitle db 'LP_asm01', 0  
;;	result_str   db 'getmax - getmin = ', 0
;						       
;.data                
;	consolehandle dd 0h          
;	arr	       DWORD 4, 5, 25, 9, 7, 52, 12, 8, 2, 638   
;	min        SDWORD ?
;	max        DWORD ?
;	result_int DWORD 'kokoko', 0
;	result_sym BYTE 10 dup(?)
;	funst DB ?
;
;.code                          
;						       
;main PROC    
; 
;
;	push offset result_int
;	;push 1
;call writes
;
;
;	push 0              
;	call ExitProcess    
;main ENDP    
;
;
;       
;end main 

.586
.model flat, stdcall

includelib kernel32.lib
includelib StatLibC.lib

ExitProcess      PROTO : DWORD

writei PROTO : SDWORD
writes PROTO : DWORD
strl   PROTO : DWORD
ipow   PROTO : DWORD, : DWORD
sum    PROTO : DWORD, : DWORD

.stack 4096



.data
mainx SDWORD  0 


.const
L0 SDWORD  7
L1 SDWORD  11
L2 SDWORD  3
L3 SDWORD  0
.stack 4096


.code

main PROC 
  push L0
 push L1
 pop eax
 pop ebx
 add eax,ebx
 push eax
 push L2
 pop eax
 pop ebx
 imul eax,ebx
 push eax
 pop mainx
  push L3


  call ExitProcess
 main ENDP


end main