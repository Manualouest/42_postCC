/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:10:33 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/16 17:40:42 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GuiManager.hpp>
#include <ModelManager.hpp>

class Engine{};

class	SceneManager
{
	public:
		SceneManager(Engine &engine);
		~SceneManager();

	private:
		Engine &_engine;

};