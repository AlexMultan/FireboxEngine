#include "OpenGLShader.h"
#include "Engine/Core/Log.h"
#include "Engine/Utils/OpenGLDebugger.h"

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

Firebox::OpenGLShader::OpenGLShader()
{

}

Firebox::OpenGLShader::OpenGLShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	String vertexCode;
	String fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexShaderPath);
		fShaderFile.open(fragmentShaderPath);
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

	uint32_t vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
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
	glShaderSource(fragment, 1, &fShaderCode, NULL);
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

void Firebox::OpenGLShader::SetFloat4(const String& name, float r, float g, float b, float a)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), r, g, b, a);
}
