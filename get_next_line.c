/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctechy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:39:35 by ctechy            #+#    #+#             */
/*   Updated: 2022/06/06 12:39:45 by ctechy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_clean(char *stock)
{
	int		i;
	int		j;
	char	*final_stock;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	final_stock = malloc((ft_strlen(stock) - i + 1) * sizeof(char));
	if (!final_stock)
		return (NULL);
	i++;
	j = 0;
	while (stock[i])
		final_stock[j++] = stock[i++];
	final_stock[j] = '\0';
	free(stock);
	return (final_stock);
}

char	*ft_check_read(char *stock, int fd, char *temp)
{
	int		read_char;

	read_char = 1;
	while (!ft_strchr(stock, '\n') && read_char != 0)
	{
		read_char = read(fd, temp, BUFFER_SIZE);
		if (read_char == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[read_char] = '\0';
		stock = ft_strjoin(stock, temp);
	}
	free(temp);
	return (stock);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	stock = ft_check_read(stock, fd, temp);
	if (!stock)
		return (NULL);
	line = ft_make_line(stock);
	stock = ft_clean(stock);
	return (line);
}
/*
int main()
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	char *str;
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	close(fd);
	return (0);
}
*/