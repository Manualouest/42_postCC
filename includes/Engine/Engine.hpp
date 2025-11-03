/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:46:51 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/02 18:11:32 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <Engine/Render/CameraManager.hpp>
# include <Engine/Render/ShaderManager.hpp>
# include <Engine/Render/TextureManager.hpp>
# include <Engine/Render/ModelManager.hpp>
# include <spellBook.hpp>

# include <glad/glad.h>
# include <glfw/glfw3.h>

# include <array>
# include <stdexcept>

extern int WWIDTH;
extern int WHEIGHT;
# define MAX_KEYS 512
# define MAX_MOUSE_KEYS 12
# define WNAME "VoxelRPG"

class Engine
{
	public:
		Engine();
		~Engine();

		// need them coded
		CameraManager	camera;
		// SceneManager	scenes;
		ShaderManager	ShaderManager;
		TextureManager	TextureManager;
		ModelManager	ModelManager;

		void	run();

		GLFWwindow	*getWindowData() const {return (_windowData);};

		static bool	getPressInput(const int &key) {bool value = _inputs[key]; _inputs[key] = false; return (value);}
		static bool	getRepeatInput(const int &key) {return (_inputs[key]);}
		static bool	getPressMouseInput(const int &key) {bool value = _inputsMouse[key]; _inputsMouse[key] = false; return (value);}
		static bool	getRepeatMouseInput(const int &key) {return (_inputsMouse[key]);}

		static bool	getlockMouse() {return (_lockMouse);}
		static void	setlockMous(const bool &value) {_lockMouse = value;}

		static float	getDeltaTime() {return (_deltaTime);}

		static glm::vec2	getMousePos() {return (_mousePos);}
		static float		getMousePosX() {return (_mousePos.x);}
		static float		getMousePosY() {return (_mousePos.y);}
		static void			setMousePos(const glm::vec2 &newMousePos) {_mousePos = newMousePos;}

	private:
		void	_init();
		void	_frameStart();
		void	_renderLoop();
		void	_frameEnd();

		void		_refreshMouse();
		static void	_resize(GLFWwindow *window, int width, int height);
		static void	_keyInput(GLFWwindow *window, int key, int, int action, int);
		static void	_mouseInput(GLFWwindow* window, int button, int action, int mods);

		static std::array<bool, MAX_KEYS>		_inputs;
		static std::array<bool, MAX_MOUSE_KEYS>	_inputsMouse;
		static glm::dvec2						_mousePos;
		static bool								_lockMouse;
		static float							_deltaTime;

		bool	_running;

		GLFWwindow	*_windowData;
		
		float	_frameTime = 0;
		float	_lastFrameTime = 0;
};

#endif