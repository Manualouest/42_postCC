/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TitleScreen.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:52:43 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/18 19:59:18 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TITLESCREEN_HPP
# define TITLESCREEN_HPP

# include <Engine/Scene/AScene.hpp>
# include <Engine/UI_UX/Guis/TestGui.hpp>
# include <Game/Chunk/Chunk.hpp>

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
};

#endif