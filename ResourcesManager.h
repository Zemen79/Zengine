#pragma once

#include "Texture2D.h"
#include "Shader.h"

#include <unordered_map>

namespace Zen {
	class ResourcesManager
	{
	public:
		static Texture2D LoadTexture(const std::string& texturePath);
		static void LoadShader(const std::string& shaderPath, const std::string& shaderName);
		static Shader GetShader(const std::string& shaderName);
		static void Clear()
		{
			m_textureMap.clear();
			m_shaderMap.clear();
		}

	private:
		static std::unordered_map<std::string, Texture2D> m_textureMap;
		static std::unordered_map<std::string, Shader> m_shaderMap;
	};
}