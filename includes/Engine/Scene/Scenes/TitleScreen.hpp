/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TitleScreen.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:52:43 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/06 09:39:16 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TITLESCREEN_HPP
# define TITLESCREEN_HPP

#include <Engine/Scene/AScene.hpp>

class TitleScreen : public AScene
{
	public:
		TitleScreen();
		~TitleScreen();
	
		void	init();
		void	unload();
		void	processInputs();
		void	update();
		void	draw();
};

#endif