/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:10:59 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/16 17:41:21 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine.hpp>

Engine::Engine() : gui(*this), models(*this), scene(*this), shaders(*this), textures(*this)
{
}

Engine::~Engine()
{

}

void	Engine::run()
{
	_init();
	
	_renderLoop();
}

void	Engine::_init()
{

}

void	Engine::_renderLoop()
{

}
