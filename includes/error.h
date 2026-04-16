/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:15:22 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/16 16:33:51 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"


typedef enum e_error_type
{
	ERR_NO_INPUT,
	ERR_INVALID_FILE,
	ERR_INVALID_RATIO,
	ERR_INVALID_RGB,
	ERR_INVALID_CORDS,
	ERR_INVALID_FOV,
	ERR_INVALID_DIA,
	ERR_INVALID_HEIGHT,
	ERR_INVALID_VECTOR
}			t_error_type;

typedef struct s_error
{
	t_error_type	type;
	char			*err_line;
	struct t_error	*next;
}				t_error;

