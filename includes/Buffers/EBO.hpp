/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EBO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:15:01 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/09 07:32:44 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <includes.hpp>

class EBO
{
	public:
		EBO();
		EBO(GLuint *indices, GLsizeiptr size);
		~EBO();

		void	Bind();
		void	Unbind();
		void	Delete();

		GLuint	ID;
};