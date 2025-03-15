/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy </var/spool/mail/welepy>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:04:18 by welepy            #+#    #+#             */
/*   Updated: 2025/03/14 18:08:25 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char  *join_matrix(int n, char **strings, const char *separator)
{
    if (n <= 0 || !strings) return NULL;

    size_t total_length = 0;
    size_t sep_length = separator ? ft_strlen(separator) : 0;
    for (int i = 0; i < n; i++) {
        if (strings[i]) {
            total_length += ft_strlen(strings[i]);
            if (i < n - 1) total_length += sep_length;
        }
    }
    char *result = malloc(total_length + 1);
    if (!result) return NULL;
    result[0] = '\0';
    for (int i = 0; i < n; i++) {
        if (strings[i]) {
            ft_strcat(result, strings[i]);
            if (i < n - 1 && separator) ft_strcat(result, separator);
        }
    }
    return result;
}
