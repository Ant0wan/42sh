/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:07:48 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/10 14:12:13 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vctlib.h"

t_vector	*vct_new(void)
{
	t_vector	*vct;

	vct = (t_vector*)malloc(sizeof(t_vector));
	if (vct != NULL)
	{
		vct->len = 0;
		vct->size = DFL_SIZE;
		vct->scale = DFL_SCALE;
		vct->str = (char*)malloc(sizeof(char) * vct->size);
		if (vct->str != NULL)
			ft_bzero(vct->str, vct->size);
	}
	return (vct);
}
