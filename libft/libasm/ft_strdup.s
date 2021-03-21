; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strdup.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: mspyke <marvin@42.fr>                      +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2021/03/09 11:46:52 by mspyke            #+#    #+#              ;
;    Updated: 2021/03/09 11:46:54 by mspyke           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

global	_ft_strdup
extern	_ft_strlen
extern	_malloc	
extern	_ft_strcpy

segment	.text
_ft_strdup:
	push	rdi
	call _ft_strlen
	inc rax
	mov rdi, rax
	call _malloc
	pop rdi
	cmp rax, 0
	jz error
	mov rsi, rdi
	mov	rdi, rax
	call _ft_strcpy
	ret

error:
	xor rax, rax
