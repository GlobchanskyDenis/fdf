/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:55:13 by bsabre-c          #+#    #+#             */
/*   Updated: 2018/11/29 18:23:23 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striter(char *s, void (*f)(char *))
{
	unsigned int	i;

	i = 0;
	if (s && f)
	{
		while (s[i])
		{
			f(&s[i]);
			i++;
		}
	}
}