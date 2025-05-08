/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:07:30 by dmalasek          #+#    #+#             */
/*   Updated: 2024/10/07 16:25:46 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_lstmap
** Creates a new linked list by applying a function
** to each element of an existing list
*/

#include "libft.h"

t_list	*create_and_add(t_list **list, t_list **current, void *content,
		void (*del)(void *))
{
	t_list	*new_node;

	new_node = ft_lstnew(content);
	if (!new_node)
	{
		del(content);
		ft_lstclear(list, del);
		return (NULL);
	}
	if (!*list)
		*list = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current_node;
	void	*new_content;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (!create_and_add(&new_list, &current_node, new_content, del))
			return (NULL);
		lst = lst->next;
	}
	return (new_list);
}
