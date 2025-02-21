/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GrayCode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:01:02 by mbirou            #+#    #+#             */
/*   Updated: 2025/02/21 16:05:00 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>
#include <iostream>
#include <ctime>
#include <iomanip>

void	printTime(const timespec &time1, const timespec &time0);

std::string printBits(uint32_t bits)
{
	if (bits > 1)
		(void)printBits(bits >> 1);
	std::cout << (bits & 1);
	return ("");
}

uint32_t	gray_code(uint32_t num)
{
	uint32_t	code = 0;
	if (num > 1)
		code = gray_code(num >> 1) << 1;
	code = code ^ ((num ^ ((num >> 1) & 1)) & 1);
	return (code);
}

int	main(int ac, char **av) {
	std::string	a;
	timespec	start, end;
	uint32_t	code;

	if (ac == 1)
		return (0);
	for (int i = 1; i < ac; ++i)
	{
		a = av[i];
		if ( a.find_first_not_of("0123456789") != std::string::npos) {
			continue ;
		}
		uint32_t	ai = std::stoul(a);
		timespec_get(&start, TIME_UTC);
		code = gray_code(ai);
		timespec_get(&end, TIME_UTC);
		std::cout << printBits(ai) << " = " << printBits(code) << " ";
		printTime(end, start);
		std::cout << std::endl;
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
