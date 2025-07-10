/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShadowMap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:31:02 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/09 17:53:50 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ShadowMap/ShadowMap.hpp>

ShadowMap::ShadowMap() : shader(Shader("shaders/shadowMap.vert", "shaders/shadowMap.frag"))
{
	glGenFramebuffers(1, &_FBO);
	glGenTextures(1, &_shadowMap);
	glBindTexture(GL_TEXTURE_2D, _shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float clamColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clamColor);

	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _shadowMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::runtime_error("FrameBuffer could not finish");
}

ShadowMap::~ShadowMap()
{
	glDeleteFramebuffers(1, &_FBO);
	glDeleteTextures(1, &_shadowMap);
}

void	ShadowMap::sendToShader(Shader &shader)
{
	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, _shadowMap);
	glUniform1i(glGetUniformLocation(shader.ID, "uShadow"), 2);
}

void	ShadowMap::startShadowGen(math::mat4 &lightProj)
{
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "uLightProjection"), 1, GL_FALSE, &lightProj.data[0]);

	glViewport(0, 0, _width, _height);
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void	ShadowMap::renderShadows(Object &object)
{
	object.Render(shader);
}

void	ShadowMap::endShadowGen()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT);
}
