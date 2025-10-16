/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModelManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:10:31 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/16 17:40:43 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class Engine{};

class	ModelManager
{
	public:
		ModelManager(Engine &engine);
		~ModelManager();

	private:
		Engine &_engine;
};