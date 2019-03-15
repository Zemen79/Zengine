#include "Texture2D.h"

namespace Zen {

	Texture2D::Texture2D()
		: m_id(0), m_width(0), m_height(0)
	{
	}

	void Texture2D::LoadTexture(const std::string& texturePath)
	{
		// generate and bind the texture
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		// flip texture
		stbi_set_flip_vertically_on_load(true);

		// load image with soil
		unsigned char* image = stbi_load(texturePath.c_str(), &m_width, &m_height, 0, 4);
		// specify the image, this allows the shaders to read the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		// generate mipmap
		glGenerateMipmap(GL_TEXTURE_2D);

		// wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// filtering parameters   
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// free the image from memory
		if (image)
			stbi_image_free(image);

		// unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}