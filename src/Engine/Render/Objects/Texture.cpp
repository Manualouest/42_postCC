/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:04:16 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/03 16:39:08 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Render/TextureManager.hpp>


typedef struct s_bmp_header
{
	uint16_t	identifier;
	uint32_t	size;
	uint32_t	reserved;
	uint32_t	data_offset;
	uint32_t	dib_size;
	uint16_t	dib_width;
	uint16_t	dib_height;
	uint16_t	dib_cp;
	uint16_t	dib_bpp;

	uint32_t	data_size;
} __attribute__((packed))	bmp_header;

# define BMP_ID			0x4D42
# define HEADER_SIZE	26
# define MAX_SIZE		0x5F5E11A

void	check_header(bmp_header *header)
{
	uint64_t	expected_size;

	if (header->identifier != BMP_ID)
		throw std::runtime_error(std::string("Invalid texture identifier"));
	if (header->size <= HEADER_SIZE || header->size > MAX_SIZE)
		throw std::runtime_error(std::string("Invalid texture size"));
	std::cout << header->data_offset << std::endl;
	if (header->data_offset != HEADER_SIZE)
		throw std::runtime_error(std::string("Invalid texture data_offset"));
	if (header->dib_size != 12)
		throw std::runtime_error(std::string("Invalid texture dib_size"));
	header->data_size = header->size - HEADER_SIZE;
	if (header->dib_width < 5 || header->dib_height < 5)
		throw std::runtime_error(std::string("Invalid texture dib_width"));
	expected_size = 3 * (header->dib_height
			* (header->dib_width + header->dib_width % 4));
	if (header->data_size != expected_size)
		throw std::runtime_error(std::string("Invalid texture data_size"));
	if (header->dib_bpp != 24)
		throw std::runtime_error(std::string("Invalid texture dib_bpp"));
	if (header->dib_cp != 1)
		throw std::runtime_error(std::string("Invalid texture dib_cp"));
}

void	Texture::loadImage(const char *path)
{
	std::ifstream	file;
	bmp_header informationHeader;

	file.open(path);
	if (!file.is_open())
		throw std::runtime_error(std::string("Failed to open ") + path);

	file.read((char*)&informationHeader, 26);
	check_header(&informationHeader);
	
	width = informationHeader.dib_width;
	height = informationHeader.dib_height;
	
	data.resize((width * height) * 4);
	
	for (int y = 0; y < height * 4; y += 4)
	{
		for (int x = 0; x < width * 4; x += 4)
		{
			char	color[3];
			file.read(color, 3);

			data[(y * width + x)] = color[2];
			data[(y * width + x) + 1] = color[1];
			data[(y * width + x) + 2] = color[0];
			data[(y * width + x) + 3] = 255;
		}
	}
	file.close();
}

Texture::Texture(const char *path)
{
	loadImage(path);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}
