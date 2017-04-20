/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:03:41 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/11 11:48:53 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*next_one;

	if ((*alst)->next == NULL)
		(*del)((*alst)->content, (*alst)->content_size);
	while (*alst)
	{
		next_one = (*alst)->next;
		(*del)((*alst)->content, (*alst)->content_size);
		(*alst)->next = NULL;
		*alst = next_one;
		free(next_one);
	}
}
