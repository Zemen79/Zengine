#pragma once
#include <GL\glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Error.h"

namespace Zen {

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	private:
		std::string m_filePath;
		unsigned int m_renderID;
		std::unordered_map<std::string, int> _uniformLocationCache;

	public:
		Shader();
		~Shader();

		void Init(const std::string& filePath);

		void Bind() const;
		void Unbind() const;
		             
		// Set uniforms
		//void SetUniformMat4(std::mat)
		void SetBool(const std::string& uniformName, bool value);
		void SetFloat(const std::string& uniformName, float value); 
		void SetIntegers(const std::string& uniformName, int count, int* value);
		void SetInteger(const std::string& uniformName, int value);
		void SetVector2f(const std::string& uniformName, const glm::vec2& value);
		void SetVector3f(const std::string& uniformName, const glm::vec3& value);
		void SetVector4f(const std::string& uniformName, const glm::vec4& value);
		void SetMatrix4(const std::string& uniformName, const glm::mat4& matrix);


	private:
		ShaderProgramSource ParseShader(const std::string& filePath);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		unsigned int CompileShader(unsigned int type, const std::string& source);

		int GetUniformLocation(const std::string& name);
	};
}