/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BoolEval.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:05:54 by mbirou            #+#    #+#             */
/*   Updated: 2025/02/21 17:06:19 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <iomanip>

void		printTime(const timespec &time1, const timespec &time0);
std::string	printBits(uint32_t bits);

bool	eval_formula(std::string str)
{
	if (str.length() < 2 || (str[0] != '1' && str[0] != '0')
		|| (str[1] != '1' && str[1] != '0' && str[1] != '!' ) || str.find_first_not_of("01") == std::string::npos)
		throw(std::exception());
	int					op = str[str.find_first_not_of("01")];
	std::pair<int, int>	values(str[0] - '0', str[1] - '0');
	str.erase(str.find_first_not_of("01"), 1);
	str.erase(1, 1);
	str.erase(0, 1);

	switch (op)
	{
		case '!':
		{
			if (values.second == 0 || values.second == 1)
				str.insert(0, 1, (char)(values.second + '0'));
			str.insert(0, 1, (char)(!values.first + '0'));
			break ;
		}
		case '&':
		{
			str.insert(0, 1, (char)((values.first & values.second) + '0'));
			break ;
		}
		case '|':
		{
			str.insert(0, 1, (char)((values.first | values.second) + '0'));
			break ;
		}
		case '^':
		{
			str.insert(0, 1, (char)((values.first ^ values.second) + '0'));
			break ;
		}
		case '>':
		{
			str.insert(0, 1, (char)((values.first <= values.second) + '0'));
			break ;
		}
		case '=':
		{
			str.insert(0, 1, (char)((values.first == values.second) + '0'));
			break ;
		}
		default:
			break ;
	}
	if (str.length() < 2)
		return (str[0] - '0');
	else
		return (eval_formula(str));
}

int	main(int ac, char **av) {
	std::string	a;
	timespec	start, end;
	bool		code;

	if (ac == 1)
		return (0);
	for (int i = 1; i < ac; ++i)
	{
		a = av[i];
		timespec_get(&start, TIME_UTC);
		code = eval_formula(a);
		timespec_get(&end, TIME_UTC);
		std::cout << a << " = ";
		if (code)
			std::cout << "true; ";
		else
			std::cout << "false; ";
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

std::string printBits(uint32_t bits)
{
	if (bits > 1)
		(void)printBits(bits >> 1);
	std::cout << (bits & 1);
	return ("");
}
// c++ -Wall -Werror -Wextra BoolEval.cpp
