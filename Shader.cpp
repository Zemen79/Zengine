#include "Shader.h"

namespace Zen {

	Shader::Shader()
		: m_filePath(""), m_renderID(0)
	{

	}

	Shader::~Shader()
	{
		glDeleteProgram(m_renderID);
	}

	void Shader::Init(const std::string & filePath)
	{
		ShaderProgramSource source = ParseShader(filePath);
		m_renderID = CreateShader(source.VertexSource, source.FragmentSource);
	}

	ShaderProgramSource Shader::ParseShader(const std::string& filePath)
	{
		std::ifstream stream(filePath);

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else
			{
				ss[(int)type] << line << '\n';
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		// Error Handling
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::string typeString = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			Error(("Failed to compile " + typeString + " Shader" + "\n" + message));
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	unsigned int Shader::CreateShader(const std::string & vertexShader, const std::string & fragmentShader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	void Shader::Bind() const
	{
		glUseProgram(m_renderID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (_uniformLocationCache.find(name) != _uniformLocationCache.end())
			return _uniformLocationCache[name];

		int location = glGetUniformLocation(m_renderID, name.c_str());

		if (location == -1)
			Error("uniform " + name + " does not exist!");

		_uniformLocationCache[name] = location;

		return location;
	}

	void Shader::SetBool(const std::string& uniformName, bool value)
	{
		glUniform1i(GetUniformLocation(uniformName), value);
	}

	void Shader::SetFloat(const std::string& uniformName, float value)
	{
		glUniform1f(GetUniformLocation(uniformName), value);
	}

	void Shader::SetIntegers(const std::string& uniformName, int count, int* value)
	{
		glUniform1iv(GetUniformLocation(uniformName), count, value);
	}

	void Shader::SetInteger(const std::string& uniformName, int value)
	{
		glUniform1i(GetUniformLocation(uniformName), value);
	}
	void Shader::SetVector2f(const std::string& uniformName, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(uniformName), value.x, value.y);
	}

	void Shader::SetVector3f(const std::string& uniformName, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(uniformName), value.x, value.y, value.z);
	}

	void Shader::SetVector4f(const std::string& uniformName, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(uniformName), value.x, value.y, value.z, value.w);
	}

	void Shader::SetMatrix4(const std::string& uniformName, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
	}
}