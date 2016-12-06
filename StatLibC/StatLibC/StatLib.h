//;
//;.586
//;.model flat, stdcall
//;
//;includelib kernel32.lib
//;includelib StatLibC.lib
//;
//;ExitProcess      PROTO : DWORD
//;
//;writei PROTO : SDWORD
//;writes PROTO : DWORD
//;strl   PROTO : DWORD
//;ipow   PROTO : DWORD, : DWORD
//;sum    PROTO : DWORD, : DWORD
//;
//;.stack 4096
//;
//;
//;
//;.data
//;mainx SDWORD  0
//;
//;
//;.const
//;L0 SDWORD  5
//;L1 SDWORD  6
//;L2 SDWORD  0
//;.stack 4096
//;
//;
//;.code
//;
//;main PROC uses eax ebx ecx edi esi
//;push L0
//;push L1
//;pop eax
//;pop ebx
//;add eax, ebx
//;push eax
//;pop mainx
//;push L2
//;
//;
//;call ExitProcess
//;main ENDP
//;
//;
//;end main
#pragma once

extern "C"
{
	//int _stdcall  strl(char*);
	//int _stdcall  ipow(int, int);
	void   writes(char*);
	void _stdcall  writei(int);
	int _stdcall  sum(int, int);

};