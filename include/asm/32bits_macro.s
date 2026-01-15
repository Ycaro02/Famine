BITS 32

; Macro to save and restore the registers
%macro save_registers 0
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	esi
	push	edi
%endmacro

%macro restore_registers 0
	pop		edi
	pop		esi
	pop		edx
	pop		ecx
	pop		ebx
	pop		eax
%endmacro
