; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strcmp.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: mspyke <marvin@42.fr>                      +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2021/03/09 11:46:52 by mspyke            #+#    #+#              ;
;    Updated: 2021/03/09 11:46:54 by mspyke           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

global	_ft_strcmp

segment	.text
_ft_strcmp:
	jmp		compare

compare:
	mov al,	byte[rdi]	; *str1
	mov	bl, byte[rsi]	; *str2
	cmp	al,	0			; *str1 == 0 ?
	je	exit
	cmp	bl, 0			; *str2 == 0 ?
	je	exit
	cmp	al, bl			; *str1 == *str2 ?
	jne	exit			; if not
	inc	rdi				; str1++
	inc rsi				; str2++
	jmp	compare
	
exit:
	sub rax, rbx; rax = *str1 - *str2
	ret