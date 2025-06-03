/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:23:33 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/30 15:57:03 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <includes.hpp>
#include <spellBook.hpp>

class	Window
{
	public:
		Window();
		~Window();
	
		void	addVertices(std::vector<float> vertices, std::vector<int> indices);
};