/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModelManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:27:05 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/05 09:03:51 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODELMANAGER_HPP
# define MODELMANAGER_HPP

# include <Engine/Render/Objects/Model.hpp>
# include <spellBook.hpp>

# include <map>

class ModelManager
{
	public:
		ModelManager();
		~ModelManager();

		static void		addModel(const std::string &modelID, const std::string &path);
		static Model	&getModel(const std::string &modelID);
		static void		delModel(const std::string &modelID);

	private:
		static void _checkInstance();

		static ModelManager	*_instance;

		std::map<std::string, Model>	_models;
};

#endif