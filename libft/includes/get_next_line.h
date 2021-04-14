/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 17:55:22 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/26 15:56:56 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

int			get_next_line(int fd, char **line);
char		*gnl_strjoin(char const *s1, char const *s2);
size_t		gnl_strlcat(char *dst, const char *src, size_t size);
size_t		gnl_strlen(const char *s);
size_t		gnl_strlcpy(char *dst, const char *src, size_t size);
char		*gnl_strdup(const char *s1);
char		*gnl_strchr(char *s, char c);

#endif
