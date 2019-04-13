/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 07:17:23 by araout            #+#    #+#             */
/*   Updated: 2019/04/13 07:31:26 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			catch_sigint(int fake)
{
	(void)fake;
	ft_printf("\n%%>");
}

void			catch_sigint2(int fake)
{
	(void)fake;
	ft_printf("\nINTERRUPTED\n");
}
