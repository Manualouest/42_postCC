/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:36:29 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/23 13:41:18 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include <iostream>
# include <vector>

struct	Texture
{
	uint						ID;
	std::vector<unsigned char>	data;
	int							width;
	int							height;
	std::string					path;

	Texture(){};
	Texture(const char *path);

	void	loadImage(const char *path);
};

#endif