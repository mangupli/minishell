; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strcpy.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: mspyke <marvin@42.fr>                      +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2021/03/09 11:46:52 by mspyke            #+#    #+#              ;
;    Updated: 2021/03/09 11:46:54 by mspyke           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

global _ft_strcpy

section .text
_ft_strcpy:
	push rdx		; for char c
	push rcx		; i
	xor	rcx, rcx    ; i == 0
	jmp	copy

copy:
	mov dl, byte[rsi + rcx] ; c = src[i]
	mov byte [rdi + rcx], dl; dst[i] = c
	cmp byte [rsi + rcx], 0	; src[i] == ?
	je exit
	inc	rcx					; i++
	jmp	copy

exit:
	mov	rax, rdi
	pop	rdx
	pop rcx
	ret
