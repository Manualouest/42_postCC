/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplier.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:00:37 by mbirou            #+#    #+#             */
/*   Updated: 2025/02/21 15:00:39 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>
#include <iostream>
#include <ctime>
#include <iomanip>

uint32_t	adder(const uint32_t a, const uint32_t b);
void		printTime(const timespec &time1, const timespec &time0);

uint32_t	domult(const uint32_t a, const uint32_t b)
{
	uint32_t	result = 0;

	if (b > 1)
		result = (domult(a << 1, b >> 1));
	if (b & 1)
		return (adder(result, a));
	return (result);
}

uint32_t	multiplier(const uint32_t a, const uint32_t b)
{
	if (a > b)
		return (domult(a, b));
	return (domult(b, a));
}

int	main(int ac, char **av) {
	std::string	a, b;
	timespec	start, end;
	uint32_t	sum;

	if ((ac - 1) % 2 != 0)
		return (0);
	for (int i = 1; i < (ac - 1); i += 2)
	{
		a = av[i];
		b = av[i + 1];
		if ( a.find_first_not_of("0123456789") != std::string::npos
			|| b.find_first_not_of("0123456789") != std::string::npos ) {
			continue ;
		}
		uint32_t	ai = std::stoul(a);
		uint32_t	bi = std::stoul(b);
		timespec_get(&start, TIME_UTC);
		sum = multiplier(ai, bi);
		timespec_get(&end, TIME_UTC);
		// std::cout << a << " * " << b << " = " << sum << " | ";
		printTime(end, start);

		if (sum == ai * bi)
			std::cout << "\t✅" << std::endl;
		else
		{
			std::cout << "\t❌: " << ai << " + " << bi << " != " << sum << " : " << ai * bi << std::endl;
			break ;
		}
	}
}

void	printTime(const timespec &time1, const timespec &time0)
{
	double	time = (time1.tv_sec - time0.tv_sec) + (time1.tv_nsec - time0.tv_nsec) / 1000000000.;
	if (time > 1)
		std::cout << "Took " << std::fixed << std::setprecision(9) << time << " seconds.";
	else if (time * 1000 > 1)
		std::cout << "Took " << std::fixed << std::setprecision(6) << time * 1000 << " miliseconds.";
	else if (time * 1000000 > 1)
		std::cout << "Took " << std::fixed << std::setprecision(3) << time * 1000000 << " microseconds.";
	else if (time * 1000000000 > 1)
		std::cout << "Took " << time * 1000000000 << " nanoseconds.";
}
