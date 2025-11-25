/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:46:51 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/08 15:19:17 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <Engine/Render/Objects/Window.hpp>
# include <Engine/Render/CameraManager.hpp>
# include <Engine/Render/ShaderManager.hpp>
# include <Engine/Render/TextureManager.hpp>
# include <Engine/Render/ModelManager.hpp>
# include <Engine/Scene/SceneManager.hpp>
# include <Engine/Scene/Scenes/TitleScreen.hpp>
# include <Engine/UI_UX/GuiManager.hpp>

class Engine
{
	public:
		Engine();
		~Engine();

		// need them coded
		Window			window;
		CameraManager	camera;
		SceneManager	sceneManager;
		ShaderManager	shaderManager;
		TextureManager	textureManager;
		ModelManager	modelManager;
		GuiManager		guiManager;

		void	run();

	private:
		void	_init();
		void	_renderLoop();
};

#endif