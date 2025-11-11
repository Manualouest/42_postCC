/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TitleScreen.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:52:43 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/08 12:41:30 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TITLESCREEN_HPP
# define TITLESCREEN_HPP

#include <Engine/Scene/AScene.hpp>
#include <Engine/UI_UX/Guis/TestGui.hpp>

class TitleScreen : public AScene
{
	public:
		TitleScreen() {;}
		~TitleScreen() {;}
	
		void	init();
		void	unload();
		void	processInputs();
		void	update();
		void	draw();

	private:
		bool	menuOpen = false;
};

#endif