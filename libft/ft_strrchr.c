/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taemkim <taemkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:37:22 by taemkim           #+#    #+#             */
/*   Updated: 2021/05/19 20:13:46 by taemkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *source, int c)
{
	int	i;

	i = (int)ft_strlen(source) + 1;
	while (i--)
	{
		if (*(source + i) == (char)c)
			return ((char *)source + i);
	}
	return (0);
}
