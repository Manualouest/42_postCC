/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Adder.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:00:41 by mbirou            #+#    #+#             */
/*   Updated: 2025/02/21 15:00:48 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>
#include <iostream>
#include <ctime>
#include <iomanip>

void	printTime(const timespec &time1, const timespec &time0);

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

int	main(int ac, char **av) {
	std::string	a, b;
	timespec	start, end;
	uint32_t	sum;
	uint32_t	sum2;

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
		sum = adder(ai, bi);
		timespec_get(&end, TIME_UTC);
		// std::cout << a << " + " << b << " = " << sum << " | ";
		printTime(end, start);
		std::cout << " versus: ";
		timespec_get(&start, TIME_UTC);
		sum2 = ai + bi;
		timespec_get(&end, TIME_UTC);
		printTime(end, start);

		if (sum == sum2)
			std::cout << "\t✅" << std::endl;
		else
		{
			std::cout << "\t❌: " << ai << " + " << bi << " != " << sum << " : " << ai + bi << std::endl;
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
