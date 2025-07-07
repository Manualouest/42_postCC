/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:23:33 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/07 13:16:33 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <includes.hpp>
#include <spellBook.hpp>

class	Window
{
	public:
		Window();
		~Window();
	
		void	addVertices(std::vector<float> vertices, std::vector<int> indices);
	
	private:
		bool	torch;
		float	textureMix;
};