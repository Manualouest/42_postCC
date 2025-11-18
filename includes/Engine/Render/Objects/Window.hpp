/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 07:58:45 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/18 22:14:03 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <array>
# include <stdexcept>
# include <iostream>
# include <spellBook.hpp>

# include <glad/glad.h>
# include <glfw/glfw3.h>
# include <glm/glm.hpp>

extern int WWIDTH;
extern int WHEIGHT;
# define MAX_KEYS 512
# define MAX_MOUSE_KEYS 12
# define WNAME "VoxelRPG"

class Window
{
	public:
		Window();
		~Window();

		static GLFWwindow	*getWindowData() {_checkInstance(); return (_instance->_windowData);};

		static bool	getPressInput(const int &key)		{_checkInstance(); bool value = _instance->_inputs[key]; _instance->_inputs[key] = false; return (value);}
		static bool	getRepeatInput(const int &key)		{_checkInstance(); return (_instance->_inputs[key]);}
		static bool	getPressMouseInput(const int &key)	{_checkInstance(); bool value = _instance->_inputsMouse[key]; _instance->_inputsMouse[key] = false; return (value);}
		static bool	getRepeatMouseInput(const int &key)	{_checkInstance(); return (_instance->_inputsMouse[key]);}

		static bool	getlockMouse()					{_checkInstance(); return (_instance->_lockMouse);}
		static void	setlockMouse(const bool &value)	{_checkInstance(); _instance->_lockMouse = value;}

		static bool	isRunning()							{_checkInstance(); return (_instance->_running);}
		static void	setRunning(const bool &newState)	{_checkInstance(); _instance->_running = newState;}

		static float	getDeltaTime()	{_checkInstance(); return (_instance->_deltaTime);}

		static glm::vec2	getMousePos()								{_checkInstance(); return (_instance->_mousePos);}
		static float		getMousePosX()								{_checkInstance(); return (_instance->_mousePos.x);}
		static float		getMousePosY()								{_checkInstance(); return (_instance->_mousePos.y);}
		static void			setMousePos(const glm::vec2 &newMousePos)	{_checkInstance(); _instance->_mousePos = newMousePos;}

		static void	startFrame();
		static void	endFrame();

	private:
		static void	_checkInstance();
		void		_refreshMouse();

		static void	_resize(GLFWwindow *window, int width, int height);
		static void	_keyInput(GLFWwindow *window, int key, int, int action, int);
		static void	_mouseInput(GLFWwindow* window, int button, int action, int mods);

		static Window	*_instance;
		GLFWwindow		*_windowData;
		bool			_running;

		std::array<bool, MAX_KEYS>			_inputs = {false};
		std::array<bool, MAX_MOUSE_KEYS>	_inputsMouse = {false};
		glm::dvec2							_mousePos = {0, 0};
		bool								_lockMouse = false;

		float	_deltaTime = 0;
		float	_frameTime = 0;
		float	_lastFrameTime = 0;
};

#endif