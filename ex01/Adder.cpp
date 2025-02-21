/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Adder.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:00:33 by mbirou            #+#    #+#             */
/*   Updated: 2025/02/21 15:00:34 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>

uint32_t	carry(uint32_t result)
{
	if (result & 1)
		result = carry(result >> 1);
	else
		result = result ^ 1;
	return (result << 1);
}

uint32_t	adder(const uint32_t a, const uint32_t b)
{
	uint32_t	result = 0;
	if (a != 0 || b != 0)
		result = adder(a >> 1, b >> 1) << 1;
	if (a & 1 && b & 1)
		result = carry(result >> 1);
	return (result ^ ((a & 1) ^ (b & 1)));
}
