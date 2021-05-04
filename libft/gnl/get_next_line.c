/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:54:46 by mspyke            #+#    #+#             */
/*   Updated: 2020/12/07 20:22:52 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** The function find_line helps us to find a new line in STACK.
**
** PTR_N points at the '\n' in the string. And if there is no new line
** than PTR_N points to NULL and function returns (0).
**
** Otherwise if there is a '\n' in string we make PTR_N point to '\0'
** and put the content of STACK before the '\0' to the LINE.
**
** Then we create a new STACK with the remainder of the string
** after '\n'.
**
** The variable tmp_stack was used in order to avoid leaks.
*/

int	find_line(char **stack, char **line)
{
	char	*ptr_n;
	char	*tmp_stack;

	ptr_n = gnl_strchr(*stack, '\n');
	if (ptr_n)
	{
		*ptr_n = '\0';
		tmp_stack = *stack;
		*line = gnl_strdup(tmp_stack);
		*stack = gnl_strdup(++ptr_n);
		free(tmp_stack);
		return (1);
	}
	else
		return (0);
}

/*
** Read_file is the function which allows us to read a file and
** quits if there is a new line in bytes that were read.
**
** Return value. It returns (-1) if there was an error while reading.
** (0) if the function READ reached the end of the file.
** And if it has read some bytes, it returns 1.
**
** We enter the loop that will continue as long as the function READ
** returns the value more than 0 and the variable NEW_LINE
** is equal to 0 - it means the new line has not been found yet.
**
** After we read something from the file we put the content of buffer
** in STACK and check if it has a new line in it with function find_line.
**
** The variable tmp_stack was used in order to avoid leaks.
*/

int	read_file(int fd, char **stack, char *buf, char **line)
{
	char	*tmp_stack;
	int		ret;
	int		new_line;

	new_line = 0;
	ret = read(fd, buf, BUFFER_SIZE);
	while (!new_line && ret > 0)
	{
		buf[ret] = '\0';
		if (!*stack)
			*stack = gnl_strdup("");
		tmp_stack = *stack;
		*stack = gnl_strjoin(tmp_stack, buf);
		free(tmp_stack);
		if (find_line(stack, line))
			new_line = 1;
		if (!new_line)
			ret = read(fd, buf, BUFFER_SIZE);
	}
	if (ret < 0)
		return (ret);
	if (ret > 0)
		return (1);
	return (0);
}

static int	proccess_new_line(char **buf, char **stack, char **line)
{
	int	ret;

	ret = find_line(stack, line);
	if (ret)
	{
		free(*buf);
		return (1);
	}
	return (0);
}

/*
** Get_next_line is the function which reads the text
** available on a file descriptor(int fd) one line
** at a time(char **line) until the EOF.
**
** First, we check for errors. In case there is no line, or
** file despriptor is less than 0 or more than
** the maximum number of open file descriptors, or malloc returns NULL,
** or size of buffer is less or equal to zero we return (-1).
**
** Then, if there is something left in the static STACK,
** we check for new line in it. If STACK is empty or
** there is no line in it, we start reading a file.
**
** After that we free the memory in our buffer and check
** the return value RET of the function read_file.
** If RET equals to -1 or 1, return that. If RET = 0, but STACK is empty,
** before return we need to create an empty line for our LINE.
**
** If the read_file returned 0, but there is something left in the STACK,
** we put the content of STACK in our LINE, and point the STACK to NULL.
*/

int	get_next_line(int fd, char **line)
{
	int			ret;
	char		*buf;
	static char	*stack;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL || !line || (fd < 0 || fd > 999) || BUFFER_SIZE < 1)
		return (-1);
	if (stack)
	{
		ret = proccess_new_line(&buf, &stack, line);
		if (ret)
			return (1);
	}
	ret = read_file(fd, &stack, buf, line);
	free(buf);
	if (ret != 0 || stack == NULL || stack[0] == '\0')
	{
		if (!ret)
			*line = gnl_strdup("");
		return (ret);
	}
	*line = stack;
	stack = NULL;
	return (ret);
}
