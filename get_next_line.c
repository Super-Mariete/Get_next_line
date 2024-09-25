/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-ped <made-ped@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:57:38 by made-ped          #+#    #+#             */
/*   Updated: 2024/03/03 19:42:59 by made-ped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static size_t	find_next_line_break(char *str, size_t i)
{
	char	*ptr;

	ptr = str + i;
	while (*ptr && *ptr != '\n')
		ptr++;
	if (*ptr == '\n')
		ptr++;
	return (ptr - str);
}

static char	*create_substring(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*str)
		return (free(str), NULL);
	i = find_next_line_break(str, i);
	new_str = (char *)malloc((ft_strlen(str) - i) + 1);
	if (!new_str)
		return (free(new_str), NULL);
	while (*(str + i))
		*(new_str + j++) = *(str + i++);
	*(new_str + j) = '\0';
	if (!*new_str)
		return (free(str), free(new_str), NULL);
	free(str);
	return (new_str);
}

static char	*read_line(char *str)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!str || *str == '\0')
		return (NULL);
	i = find_next_line_break(str, i);
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (*(str + i) && *(str + i) != '\n')
	{
		*(line + i) = *(str + i);
		i++;
	}
	if (*(str + i) == '\n')
	{
		*(line + i) = *(str + i);
		i++;
	}
	*(line + i) = '\0';
	return (line);
}

static char	*free_and_null(char *buff1, char *buff2)
{
	free(buff1);
	free(buff2);
	buff2 = NULL;
	return (buff2);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			read_bytes;
	static char	*buffer;

	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	while (!(ft_strchr(buffer, '\n')) && read_bytes != 0)
	{
		read_bytes = read(fd, line, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			buffer = free_and_null(line, buffer);
			return (NULL);
		}
		*(line + read_bytes) = '\0';
		buffer = ft_strjoin(buffer, line);
	}
	free(line);
	line = read_line(buffer);
	buffer = create_substring(buffer);
	return (line);
}
/*
int	main (int	argc, char	**argv)
{
	int		fd;
	char	*result;
	int		i;

	if (argc < 2)
	{
		printf ("\033[34mError, envia argumentos a la función\n\033[0m");
		return (1);
	}
	fd = open (argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf ("\033[34mError al abrir el archivo\033[0m");
		return (1);
	}
	i = 0;
	while ((result = get_next_line(fd)) != NULL)
	{
		printf ("\033[32mLinea %d :\033[0m %s\n", i, result);
		free (result);
		i++;
	}
	close (fd);
	return (0);
}*/
/*Para ver los leaks de memoria usar la herramienta fsanitze
 * gcc -fsanitize=address -g get_next_line.c get_next_line_utils.c

También se usa leaks, se declara una funcion y se acota el tramo 
que se quiere depurar poniendo al final atexit

void	leaks(void)
{
	system("leaks -q a.out");
}

tramo a depurar.

atexit(leaks);
Al ejecutar solo enseña los leaks pero para ver el output se debe ejecutar
a.out | cat -e

*/
