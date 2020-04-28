.686
.model flat

public _BigIntSmallDivision	;Digit BigIntSmallDivision(Digit* start, Int NDigits, Digit divider)

.code
;This function is made assuming Digit is 32bit unsigned integer.
;It BigInt by divider and returns remainder
_BigIntSmallDivision PROC
	push ebp
	mov ebp, esp
	push esi		
	push ebx

	mov esi, [ebp + 8]	; esi is pointer to begin of array of digits
	mov ecx, [ebp + 12]	; ecx = N
	mov ebx, [ebp + 16]	; ebx = divider

	mov edx, 0			; edx is current remainder
	divide:
		mov eax, [esi + 4 * ecx - 4]	; eax is current digit from end to begin
		div ebx				; Dividing [edx : eax] = [remainder : digit] by divider
							; Remainder of division is edx, as should be
		mov [esi + 4 * ecx - 4], eax	; saving result of division
		loop divide

	mov eax, edx	; eax keeps returned value, so we place remainder there

	pop ebx
	pop esi
	pop ebp
	ret
_BigIntSmallDivision ENDP
END