#pragma once

#include "Shader.h"
#include "Camera2D.h"
#include "ResourcesManager.h"

// Std.Includes
#include <iostream>
#include <map>
#include <string>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// FreeType
#include <ft2build.h>
#include <freetype/freetype.h>
#include FT_FREETYPE_H

namespace Zen {
	/// Holds all state information relevant to a character as loaded using FreeType
	struct Character {
		GLuint TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};

	class Font
	{
	public:
		void Init(const std::string& font, Shader* shader, int screenWidth, int screenHeight);

		void RenderText(const std::string& text, glm::vec2 position, float size, const glm::vec4& color);

	private:
		std::map<char, Character> Characters;
		GLuint VAO, VBO;

		Shader m_shader;
	};
}
