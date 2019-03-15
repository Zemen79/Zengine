#pragma once

#include <GL/glew.h>

#include "vender/std_image/stb_image.h"

#include <string>

namespace Zen {

	class Texture2D
	{
	public:
		Texture2D();

		void LoadTexture(const std::string& texturePath);

		void Bind();

		void Unbind();

		GLuint GetID() { return m_id; }
	private:
		GLuint m_id;
		int m_width, m_height;
	};
}