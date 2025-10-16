/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:10:37 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/16 17:40:39 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class Engine{};

class	TextureManager
{
	public:
		TextureManager(Engine &engine);
		~TextureManager();

	private:
		Engine &_engine;
};