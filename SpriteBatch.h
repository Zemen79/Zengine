#pragma once

#include <string>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "ResourcesManager.h"

#define BATCH_MAX_SPRITES 60000
#define BATCH_VERTEX_SIZE sizeof(VertexData)
#define BATCH_SPRITE_SIZE BATCH_VERTEX_SIZE * 4
#define BATCH_BUFFER_SIZE BATCH_SPRITE_SIZE * BATCH_MAX_SPRITES
#define BATCH_INDICES_SIZE BATCH_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX     1
#define SHADER_TID_INDEX    2
#define SHADER_COLOR_INDEX  3
#define SHADER_MODEL_INDEX  4

namespace Zen {

	struct VertexData
	{
		glm::vec2 position;
		glm::vec2 uv;
		float tid; // texture id
		glm::vec4 color;
		glm::mat4 model;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void Init(Shader* shader);
		void Submit(Texture2D texture, const glm::vec2& position,
			const glm::vec2& size = glm::vec2(10.0f), float angle = 0.0f,
			const glm::vec4& uv = glm::vec4(0, 0, 1, 1),
			const glm::vec4& color = glm::vec4(1.0f));

		void Begin();
		void End(bool flush = true);

		void Flush();

		Shader*& GetShader() { return m_shader; }

	private:
		
		// shader
		Shader* m_shader;

		// buffers
		GLuint m_VAO, m_VBO, m_EBO;

		// vertices
		VertexData* m_verticesData;

		// indices
		std::shared_ptr<std::vector<unsigned int>> m_indices;
		unsigned int m_indexCount;

		// textures
		std::vector<unsigned int> m_textureSlots;
		int textureIDs[32] = {};
	};
}