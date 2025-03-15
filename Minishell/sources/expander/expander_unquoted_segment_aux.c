/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_unquoted_segment_aux.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:55 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:56 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

// char	*preprocess_segment(const char *segment)
// {
// 	char	*new_segment;
// 	size_t	len;
// 	size_t	i;
// 	size_t	j;
// 	int		dollar_count;

// 	len = ft_strlen(segment);
// 	i = 0;
// 	j = 0;
// 	dollar_count = 0;
// 	new_segment = (char *)malloc(len + 1);
// 	if (!new_segment)
// 		return (NULL);
// 	while (segment[i])
// 	{
// 		if (segment[i] == '$')
// 		{
// 			dollar_count++;
// 			new_segment[j++] = segment[i++];
// 			if (dollar_count > 1 && ft_isdigit(segment[i]))
// 			{
// 				i++;
// 				continue ;
// 			}
// 		}
// 		new_segment[j++] = segment[i++];
// 	}
// 	new_segment[j] = '\0';
// 	return (new_segment);
// }

/// @brief Process a char from the source seg and copy it to the dest seg.
/// @param src Pointer to the current position in the source segment.
/// @param dest Pointer to the current position in the destination segment.
/// @param dollar_count Pointer to the count of dollar signs encountered.
void	process_char(const char **src, char **dest, int *dollar_count)
{
	if (**src == '$')
	{
		*dollar_count = *dollar_count + 1;
		**dest = **src;
		*dest = *dest + 1;
		*src = *src + 1;
		if (*dollar_count > 1 && ft_isdigit(**src))
			*src = *src + 1;
		else
		{
			**dest = **src;
			*dest = *dest + 1;
			*src = *src + 1;
		}
	}
	else
	{
		**dest = **src;
		*dest = *dest + 1;
		*src = *src + 1;
	}
}

/// @brief Preprocess a segment handling dollar signs and copying characters.
/// @param segment The input segment to preprocess.
/// @return A new string with the preprocessed segment, or NULL on failure.
/// For expansion cases where the dollar sign is not followed by a digit.
char	*preprocess_segment(const char *segment)
{
	const char	*src;
	char		*new_segment;
	char		*dest;
	int			dollar_count;

	new_segment = malloc(ft_strlen(segment) + 1);
	if (! new_segment)
		return (NULL);
	src = segment;
	dest = new_segment;
	dollar_count = 0;
	while (*src)
		process_char(&src, &dest, &dollar_count);
	*dest = '\0';
	return (new_segment);
}
