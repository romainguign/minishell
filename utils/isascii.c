/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isascii.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:16:24 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/06 16:06:27 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_space(char c)
{
	if ((c == ' ') || (c <= 13 && c >= 9))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (8);
	return (0);
}

int	no_space(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (is_space(value[i]))
			return (1);
		i++;
	}
	return (0);
}
