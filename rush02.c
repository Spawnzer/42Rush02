/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubeau <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 10:41:50 by adubeau           #+#    #+#             */
/*   Updated: 2021/02/28 14:39:32 by adubeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char	*ft_getval(int, char *);
//t_list	ft_makeStruct(int);
char	*ft_getnb(int);
int	ft_atoi(char *);
char	*fstrdup( char *);


typedef struct t_list
{
	int nb;
	char *val;
}		t_list;

t_list *ft_makeStruct(int);
t_list *ft_makeStruct(int row)
{
	int i;
	int fd;
	char c[1];
	t_list *str;
	char *tmp;

	fd = open("numbers.dict.txt", O_RDONLY);
	str = (t_list *)malloc(sizeof(t_list) * row);
	i = 0;
	while (i < row)
	{
		str[i].nb = ft_atoi(ft_getnb(fd));
		read(fd, c, 1);
		while (c[0] == ' ')
			read(fd, c, 1);
		if (c[0] == ':')
			read(fd, c, 1);
		while (c[0] == ' ')
			read(fd, c, 1);
		tmp = ft_getval(fd, c);
		
		str[i].val = fstrdup(tmp);
		i++;
	}
	return(str);
}
int	main(int argc, char **argv)
{
	t_list	*str;
	int row;
	char c;
	int i;
	int fd;
	fd = open("numbers.dict.txt", O_RDONLY);
	i = 0;
	row = 0;
	while (read(fd, &c, 1))
			if (c == '\n')
				row++;
	str = ft_makeStruct(row);
	//printf("%d", str->nb);		
	
	while (i < row)
	{
		printf("%d", str[i].nb);
		write(1, " ", 1);
		printf("%s\n", str[i].val);
		i++;
	}
}

char	*ft_getval(int fd, char *c)
{
	int i;
	char *str;
	if(!(str = malloc(sizeof(char)*128)))
		exit(1);
	i = 0;

	while (c[0] != '\n')
	{
		str[i] = c[0];
		read(fd, c, 1);
		i++;
	}
	return (str);
}

char	*ft_getnb(int fd)
{
	int i;
	char c[1];
	char *str;

	if(!(str = malloc(sizeof(char)*128)))
		exit(1);

	i = 0;
	read(fd, c, 1);
	while (c[0] == '\n')
		read(fd, c, 1);
	while (c[0] >= '0' && c[0] <= '9')
	{
		str[i] = c[0];
		read(fd, c, 1);
		i++;
	}
	return (str);
}

int		ft_is_space(char c)
{
	if (c == '\f' || c == 32 || c == '\n' || c == '\r' ||
			c == '\t' || c == '\v')
		return (1);
	return (0);
}

int		ft_atoi(char *str)
{
	int i;
	int neg;
	int res;

	i = 0;
	res = 0;
	neg = 1;
	while (ft_is_space(str[i]))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = neg * -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res = res * 10 + (str[i] - '0');
			i++;
		}
		else
			return (res * neg);
	}
	return (res * neg);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*fstrdup(char *src)
{
	char *dest;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	dest = ft_strcpy(src, dest);
	return (!src ? NULL : dest);
}
