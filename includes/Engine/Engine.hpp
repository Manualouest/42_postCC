/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:10:40 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/16 17:35:10 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CameraManager.hpp>
#include <SceneManager.hpp>
#include <ShaderManager.hpp>
#include <TextureManager.hpp>

class	Engine
{
	public:
		Engine();
		~Engine();

		void	run();

		CameraManager	camera;
		GuiManager		gui;
		ModelManager	models;
		SceneManager	scene;
		ShaderManager	shaders;
		TextureManager	textures;
	
	private:
		void	_init();
		void	_renderLoop();
};