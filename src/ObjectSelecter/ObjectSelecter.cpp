/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectSelecter.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:25:17 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/08 21:05:08 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ObjectSelecter/ObjectSelecter.hpp>

ObjectSelecter::ObjectSelecter() : shader(Shader("shaders/ObjectSelecter.vert", "shaders/ObjectSelecter.frag"))
{
	glGenFramebuffers(1, &_FBO);
	glGenTextures(1, &_ObjectSelecterMap);
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
	glBindTexture(GL_TEXTURE_2D, _ObjectSelecterMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _ObjectSelecterMap, 0);

	glGenRenderbuffers(1, &_RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, _RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::runtime_error("FrameBuffer could not finish");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ObjectSelecter::~ObjectSelecter()
{
	shader.Delete();
	glDeleteFramebuffers(1, &_FBO);
	glDeleteRenderbuffers(1, &_RBO);
	glDeleteTextures(1, &_ObjectSelecterMap);
}

int	ObjectSelecter::SelectObject(Object &lightEmitter, Object &object, v3 mousePos, v3 winSize)
{
	shader.Activate();

	glBindTexture(GL_TEXTURE_2D, _ObjectSelecterMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, winSize.x, winSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glBindRenderbuffer(GL_RENDERBUFFER, _RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, winSize.x, winSize.y);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
	glClearColor(0.0f, 0.0, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform3fv(glGetUniformLocation(shader.ID, "uColor"), 1, &_colors[0].x);
	lightEmitter.Render(shader);
	glUniform3fv(glGetUniformLocation(shader.ID, "uColor"), 1, &_colors[1].x);
	object.Render(shader);

	unsigned char data[3];
	glReadPixels(mousePos.x, winSize.y - mousePos.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, data);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT);

	v3 readcolor = {float(data[0] / 255), float(data[1] / 255), float(data[2] / 255)};
	for (int i = 0; i < 3; i++)
	{
		if (readcolor == _colors[i])
			return (i);
	}
	return (-1);
}
