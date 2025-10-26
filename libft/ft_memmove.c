/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:42:08 by epresa-c          #+#    #+#             */
/*   Updated: 2021/11/10 14:57:28 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;
	size_t			index;

	index = 0;
	ptr_dst = (unsigned char *) dst;
	ptr_src = (unsigned char *) src;
	if ((src == NULL) && (dst == NULL))
		return (NULL);
	else if (ptr_dst > ptr_src)
	{
		while (len > 0)
		{
			ptr_dst [len - 1] = ptr_src [len - 1];
			len--;
		}
	}
	while (index < len)
	{
		ptr_dst[index] = ptr_src[index];
		index++;
	}
	return (dst);
}
/*
int	main()
{
	char one[15] = "123456789";
	char two[15] = "000000000000";
	
	ft_memmove(one + 1, one, 8);
	printf("%s\n", one);
	return (0);
}*/