/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GuiManager.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:26:42 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/07 20:12:02 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUIMANAGER_HPP
# define GUIMANAGER_HPP

# include <Engine/UI_UX/AGui.hpp>

class GuiManager
{
	public:
		GuiManager();
		~GuiManager();

		static void	setCurrent(const std::string &guiID);
		static void	unloadCurrent(const std::string &guiID);

		static AGui	*getCurrent();
		static AGui	*getGui(const std::string &guiID);
		static void	useGui(const std::string &guiID);
		static void	addGui(const std::string &guiID, AGui *newGui);
		
	private:
		static void	_checkInstance();

		static GuiManager	*_instance;

		std::string						_current = "";
		std::map<std::string, AGui*>	_guis;
};

#endif