#include "ResourcesManager.h"

namespace Zen {

	std::unordered_map<std::string, Texture2D> ResourcesManager::m_textureMap;
	std::unordered_map<std::string, Shader> ResourcesManager::m_shaderMap;

	Texture2D ResourcesManager::LoadTexture(const std::string& texturePath)
	{
		// search for the texture
		auto mit = m_textureMap.find(texturePath);

		// if texture is not found
		if (mit == m_textureMap.end())
		{
			// load the texture
			Texture2D newTexture;
			newTexture.LoadTexture(texturePath);

			// insert it in the texture map
			m_textureMap.emplace(texturePath, newTexture);

			return newTexture;
		}

		// else return the found texture
		return mit->second;
	}

	void ResourcesManager::LoadShader(const std::string& shaderPath, const std::string& shaderName)
	{
		auto mit = m_shaderMap.find(shaderName);

		if (mit == m_shaderMap.end())
		{
			// load, compile and link the shader
			Shader newShader;

			// insert to map
			m_shaderMap.emplace(shaderName, newShader);
			m_shaderMap[shaderName].Init(shaderPath);
		}
		else {
			// if we try to load the same shader
			std::cout << shaderName << " is aleardy loaded." << std::endl;
		}
	}

	Shader ResourcesManager::GetShader(const std::string& shaderName)
	{
		return m_shaderMap[shaderName];
	}
}