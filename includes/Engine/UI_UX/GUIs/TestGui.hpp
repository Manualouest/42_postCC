/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestGui.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:55:10 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/07 20:24:38 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTGUI_HPP
# define TESTGUI_HPP

#include <Engine/UI_UX/AGui.hpp>

class TestGui : public AGui
{
	public:
		TestGui() {;}
		~TestGui() {;}
	
		void	init() {;}
		void	unload() {;}
		void	processInputs() {;}
		void	update() {;}
		void	draw() {;}
};

#endif