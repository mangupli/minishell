; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_read.s                                          :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: mspyke <marvin@42.fr>                      +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2021/03/09 11:46:52 by mspyke            #+#    #+#              ;
;    Updated: 2021/03/09 11:46:54 by mspyke           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

global _ft_read
extern ___error

section .text
; ft_read(rdi, rsi, rdx)
_ft_read:
	mov rax, 0x2000003  ;call write
	syscall
	jc error            ;if flag CF==1, go to error
	ret

error:
	mov r11, rax        ;keep error in temporary register
	push -1             ;push return value (-1) onto the stack
	call ___error       ;puts the address of the global variable errno into the rax
	mov qword[rax], r11 ;we put the number of error byt the rax address
	pop rax             ;now rax == -1
	ret
