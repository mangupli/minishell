; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strlen.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: mspyke <marvin@42.fr>                      +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2021/03/09 11:46:52 by mspyke            #+#    #+#              ;
;    Updated: 2021/03/09 11:46:54 by mspyke           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

global _ft_strlen

section .text
_ft_strlen:
			xor		rax, rax			; i = 0
			jmp	count

count:
			cmp		byte[rdi + rax], 0	; str[i] == 0 ?
			je		exit
			inc		rax					; i++;
			jmp		count

exit:
			ret							; return i
