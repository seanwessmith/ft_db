/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 10:09:06 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/11 11:28:17 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *root;

	root = (t_list *)malloc(sizeof(t_list));
	if (root == NULL)
		return (NULL);
	if (content == NULL)
	{
		root->content = NULL;
		root->content_size = 0;
	}
	else
	{
		root->content = malloc(sizeof(content));
		if (root->content == NULL)
			return (NULL);
		ft_memcpy(root->content, content, content_size);
		root->content_size = content_size;
	}
	root->next = NULL;
	return (root);
}
