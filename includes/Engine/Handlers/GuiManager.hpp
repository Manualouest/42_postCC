/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GuiManager.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:10:28 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/16 17:40:45 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class Engine{};

class	GuiManager
{
	public:
		GuiManager(Engine &engine);
		~GuiManager();

	private:
		Engine &_engine;
};