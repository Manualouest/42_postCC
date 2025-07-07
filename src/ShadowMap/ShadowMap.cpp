/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShadowMap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:31:02 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/07 20:37:47 by mbirou           ###   ########.fr       */
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
}

ShadowMap::~ShadowMap()
{

}

void	ShadowMap::sendToShader(Shader shader)
{
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, _shadowMap);
	glUniform1i(glGetUniformLocation(shader.ID, "uShadow"), 1);
}

void	ShadowMap::getShadows(glm::mat4 lightProj, Object &object)
{
	
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "uLightProjection"), 1, GL_FALSE, glm::value_ptr(lightProj));

	glViewport(0, 0, _width, _height);
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	object.Render(shader);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_DEPTH_BUFFER_BIT);
}
