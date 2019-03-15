#include "SpriteBatch.h"

namespace Zen {

	SpriteBatch::SpriteBatch() :
		m_VAO(0),
		m_VBO(0),
		m_EBO(0)
	{
	}

	SpriteBatch::~SpriteBatch()
	{
		if (m_VAO != 0)
			glDeleteVertexArrays(1, &m_VAO);
		if (m_VBO != 0)
			glDeleteBuffers(1, &m_VBO);
		if (m_EBO != 0)
			glDeleteBuffers(1, &m_EBO);
	}

	void SpriteBatch::Init(Shader* shader)
	{
		m_shader = shader;

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, BATCH_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		/// Attributes
		// position attribute 
		glVertexAttribPointer(SHADER_VERTEX_INDEX, 2, GL_FLOAT, GL_FALSE, BATCH_VERTEX_SIZE, (const void*)offsetof(VertexData, position));
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);

		// uv attribute 
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, BATCH_VERTEX_SIZE, (const void*)offsetof(VertexData, uv));
		glEnableVertexAttribArray(SHADER_UV_INDEX);

		// texture id attribute 
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, BATCH_VERTEX_SIZE, (const void*)offsetof(VertexData, tid));
		glEnableVertexAttribArray(SHADER_TID_INDEX);

		// color attribute
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, BATCH_VERTEX_SIZE, (const void*)offsetof(VertexData, color));
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		// model attribute
		for (int i = 0; i < 4; i++)
		{
			glVertexAttribPointer(SHADER_MODEL_INDEX + i, 4, GL_FLOAT, GL_FALSE, BATCH_VERTEX_SIZE, (const void*)(9 * sizeof(float) + (4 * i * sizeof(float))));
			glEnableVertexAttribArray(SHADER_MODEL_INDEX + i);
			glVertexAttribDivisor(SHADER_MODEL_INDEX + i, 0);
		}

		// indices
		m_indices = std::make_shared<std::vector<unsigned int>>(BATCH_INDICES_SIZE);
		int offset = 0;
		for (unsigned int i = 0; i < m_indices->size(); i += 6)
		{
			m_indices->at(i) = offset + 0;
			m_indices->at(i + 1) = offset + 1;
			m_indices->at(i + 2) = offset + 2;

			m_indices->at(i + 3) = offset + 1;
			m_indices->at(i + 4) = offset + 2;
			m_indices->at(i + 5) = offset + 3;

			offset += 4;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * BATCH_INDICES_SIZE, nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * BATCH_INDICES_SIZE, &m_indices->at(0));

		// unbind buffer		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// textures
		for (int i = 0; i < 32; i++)
		{
			textureIDs[i] = i;
		}

		m_shader->Bind();
		m_shader->SetIntegers("u_Textures", 32, textureIDs);
		m_shader->Unbind();
	}

	void SpriteBatch::Begin()
	{
		m_shader->Bind();

		m_indexCount = 0;

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_verticesData = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void SpriteBatch::Submit(Texture2D texture, const glm::vec2& position,
		const glm::vec2& size, float angle, const glm::vec4& uv, const glm::vec4& color)
	{
		// Model
		glm::mat4* model = new glm::mat4(1.0f);// = std::make_shared<glm::mat4>(glm::mat4(1.0f));
		*model = glm::translate(*model, glm::vec3(position, 0.0f));

		*model = glm::translate(*model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		*model = glm::rotate(*model, angle, glm::vec3(0.0f, 0.0f, 1.0f));

		*model = glm::translate(*model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
		*model = glm::scale(*model, glm::vec3(size, 1.0f));

		// texture
		float ts = 0.0f;
		if (texture.GetID() > 0.0f)
		{
			bool found = false;
			for (unsigned int i = 0; i < m_textureSlots.size(); i++)
			{
				if (m_textureSlots[i] == texture.GetID())
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (m_textureSlots.size() >= 32)
				{
					End();
					Begin();
				}
				m_textureSlots.push_back(texture.GetID());
				ts = (float)(m_textureSlots.back());
			}
		}

		// data for each sprite
		m_verticesData->position = glm::vec2(0, 0);
		m_verticesData->uv = glm::vec2(uv.x, uv.y);
		m_verticesData->tid = ts;
		m_verticesData->color = color;
		m_verticesData->model = *model;
		m_verticesData++;

		m_verticesData->position = glm::vec2(1, 0);
		m_verticesData->uv = glm::vec2(uv.x + uv.z, uv.y);
		m_verticesData->tid = ts;
		m_verticesData->color = color;
		m_verticesData->model = *model;
		m_verticesData++;

		m_verticesData->position = glm::vec2(0, 1);
		m_verticesData->uv = glm::vec2(uv.x, uv.y + uv.w);
		m_verticesData->tid = ts;
		m_verticesData->color = color;
		m_verticesData->model = *model;
		m_verticesData++;

		m_verticesData->position = glm::vec2(1, 1);
		m_verticesData->uv = glm::vec2(uv.x + uv.z, uv.y + uv.w);
		m_verticesData->tid = ts;
		m_verticesData->color = color;
		m_verticesData->model = *model;
		m_verticesData++;

		m_indexCount += 6;

		delete model;
	}

	void SpriteBatch::End(bool flush)
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if(flush)
			Flush();

		m_shader->Unbind();
	}

	void SpriteBatch::Flush()
	{
		for (unsigned int i = 0; i < m_textureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
		}

		// bind the vao, it also binds the vbo
		glBindVertexArray(m_VAO);

		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, &m_indices->at(0));

		glBindVertexArray(0);
	}
}