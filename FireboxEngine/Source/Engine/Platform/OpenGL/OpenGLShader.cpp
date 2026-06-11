#include "OpenGLShader.h"
#include "Engine/Core/Log.h"
#include "Engine/Utils/OpenGLDebugger.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

Firebox::OpenGLShader::OpenGLShader()
{

}

Firebox::OpenGLShader::OpenGLShader(const char* vertexSrc, const char* fragmentSrc, bool fromSource)
{
	if (fromSource)
	{
		Compile(vertexSrc, fragmentSrc);
	}
	else
	{
		String vertexCode;
		String fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vShaderFile.open(vertexSrc);
			fShaderFile.open(fragmentSrc);
			std::stringstream vertexStream, fragmentStream;
			vertexStream << vShaderFile.rdbuf();
			fragmentStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();
			vertexCode = vertexStream.str();
			fragmentCode = fragmentStream.str();
		}
		catch (std::ifstream::failure e)
		{
			FIREBOX_CORE_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		Compile(vShaderCode, fShaderCode);
	}
}

void Firebox::OpenGLShader::Compile(const char* vertexShader, const char* fragmentShader)
{
	uint32_t vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShader, NULL);
	glCompileShader(vertex);
	glCheckError();

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		FIREBOX_CORE_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
		FIREBOX_CORE_ERROR(infoLog);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShader, NULL);
	glCompileShader(fragment);
	glCheckError();

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		FIREBOX_CORE_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
		FIREBOX_CORE_ERROR(infoLog);
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glCheckError();
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		FIREBOX_CORE_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED");
		FIREBOX_CORE_ERROR(infoLog);
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Firebox::OpenGLShader::~OpenGLShader()
{
	if (ID > -1)
	{
		glDeleteProgram(ID);
		glCheckError();
	}
}

void Firebox::OpenGLShader::UseShader()
{
	glUseProgram(ID);
}

void Firebox::OpenGLShader::SetFloat(const String& name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FIREBOX_CORE_ERROR(msg);
	}
}

void Firebox::OpenGLShader::SetInt(const String& name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FIREBOX_CORE_ERROR(msg);
	}
}

void Firebox::OpenGLShader::SetVector3(const String& name, Vector3 vector3)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), vector3.x, vector3.y, vector3.z);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FIREBOX_CORE_ERROR(msg);
	}
}

void Firebox::OpenGLShader::SetVector4(const String& name, Vector4 vector4)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), vector4.r, vector4.g, vector4.b, vector4.a);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FIREBOX_CORE_ERROR(msg);
	}
}

void Firebox::OpenGLShader::SetMat3(const String& name, const Mat3& matrix)
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FIREBOX_CORE_ERROR(msg);
	}
}

void Firebox::OpenGLShader::SetMat4(const String& name, const Mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FIREBOX_CORE_ERROR(msg);
	}
}
