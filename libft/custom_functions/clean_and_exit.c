/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:05:06 by welepy            #+#    #+#             */
/*   Updated: 2025/03/07 10:03:00 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	clean_and_exit(t_generic *data)
{
	if (data->input)
		free(data->input);
	if (data->env)
		ft_lstclear((t_list **)&data->env, free);
	exit(0);
}
/*	shell->input
	shell->matrix (also each word)
	temp string at extract_quote
	tab at search_env
*/