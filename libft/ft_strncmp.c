/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:55:45 by malja-fa          #+#    #+#             */
/*   Updated: 2024/06/13 07:16:17 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s;
	unsigned char	*ss;
	size_t			i;

	s = (unsigned char *)s1;
	ss = (unsigned char *)s2;
	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while ((s[i] || ss[i]) && i < n - 1)
	{
		if (s[i] - ss[i] != 0)
		{
			return (s[i] - ss[i]);
		}
		i++;
	}
	return (s[i] - ss[i]);
}
/*
int	main(void)
{
	char *str1 = "moh";
	char *str2 = "mt";
	int v =ft_strncmp(str1, str2,0);
	printf("%i",v);
}*/
