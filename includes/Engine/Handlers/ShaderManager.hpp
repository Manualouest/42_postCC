/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:10:35 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/16 17:53:52 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class Engine{};

class	Shader
{

};

class	ShaderManager
{
	public:
		ShaderManager(Engine &engine);
		~ShaderManager();

	private:
		Engine &_engine;
};