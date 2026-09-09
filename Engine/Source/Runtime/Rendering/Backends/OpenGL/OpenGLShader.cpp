#include "OpenGLShader.h"
#include "Core/Log.h"
#include "OpenGLDebugger.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

Firebox::OpenGLShader::OpenGLShader()
{

}

Firebox::OpenGLShader::OpenGLShader(const char* vertexSrc, const char* fragmentSrc, const char* geometrySrc = nullptr, bool fromSource = false)
{
	if (fromSource)
	{
		Compile(vertexSrc, fragmentSrc, geometrySrc);
	}
	else
	{
		String vertexCode;
		String fragmentCode;
		String geometryCode;
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
		catch (const std::ifstream::failure& e)
		{
			FB_CORE_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
		}

		bool hasGeometry = geometrySrc && geometrySrc[0] != '\0';
		if (hasGeometry)
		{
			std::ifstream gShaderFile;
			gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				gShaderFile.open(geometrySrc);
				std::stringstream geometryStream;
				geometryStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = geometryStream.str();
			}
			catch (const std::ifstream::failure& e)
			{
				FB_CORE_ERROR("ERROR::SHADER::GEOMETRY_FILE_NOT_SUCCESFULLY_READ");
				hasGeometry = false;
			}
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		const char* gShaderCode = hasGeometry ? geometryCode.c_str() : nullptr;

		Compile(vShaderCode, fShaderCode, gShaderCode);
	}
}

void Firebox::OpenGLShader::Compile(const char* vertexShader, const char* fragmentShader, const char* geometryShader = nullptr)
{
	FB_CORE_TRACE("Compile() called - vertex len: {0}, fragment len: {1}", strlen(vertexShader), strlen(fragmentShader));

	uint32_t vertex, fragment, geometry;
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
		FB_CORE_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED : {0}", vertexShader);
		FB_CORE_ERROR(infoLog);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShader, NULL);
	glCompileShader(fragment);
	glCheckError();

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		FB_CORE_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED : {0}", fragmentShader);
		FB_CORE_ERROR(infoLog);
	}

	bool hasGeometry = geometryShader && geometryShader[0] != '\0';

	if (hasGeometry)
	{
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &geometryShader, NULL);
		glCompileShader(geometry);
		glCheckError();

		glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(geometry, 512, NULL, infoLog);
			FB_CORE_ERROR("ERROR::SHADER::GEOMETRY::COMPILATION_FAILED : {0}", geometryShader);
			FB_CORE_ERROR(infoLog);
		}
	}
	
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);

	if(hasGeometry)
		glAttachShader(ID, geometry);

	glLinkProgram(ID);
	glCheckError();
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		FB_CORE_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED");
		FB_CORE_ERROR(infoLog);
	}

	GLuint blockIndex = glGetUniformBlockIndex(ID, "LightSpaceMatrices");
	if (blockIndex == GL_INVALID_INDEX)
	{
		FB_CORE_ERROR("LightSpaceMatrices block not found/active in program {0}", ID);
	}
	else
	{
		GLint binding = -1;
		glGetActiveUniformBlockiv(ID, blockIndex, GL_UNIFORM_BLOCK_BINDING, &binding);
		FB_CORE_TRACE("Program {0}: LightSpaceMatrices block index {1}, binding {2}", ID, blockIndex, binding);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	if(hasGeometry)
		glDeleteShader(geometry);
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

void Firebox::OpenGLShader::SetBool(const String& name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FB_CORE_WARN(msg);
	}
}

void Firebox::OpenGLShader::SetFloat(const String& name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FB_CORE_WARN(msg);
	}
}

void Firebox::OpenGLShader::SetInt(const String& name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FB_CORE_WARN(msg);
	}
}
void Firebox::OpenGLShader::SetVector2(const String& name, Vector2 vector2)
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), vector2.x, vector2.y);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FB_CORE_WARN(msg);
	}
}


void Firebox::OpenGLShader::SetVector3(const String& name, Vector3 vector3)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), vector3.x, vector3.y, vector3.z);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FB_CORE_WARN(msg);
	}
}

void Firebox::OpenGLShader::SetVector4(const String& name, Vector4 vector4)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), vector4.r, vector4.g, vector4.b, vector4.a);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FB_CORE_WARN(msg);
	}
}

void Firebox::OpenGLShader::SetMat3(const String& name, const Mat3x3& matrix)
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FB_CORE_WARN(msg);
	}
}

void Firebox::OpenGLShader::SetMat4(const String& name, const Mat4x4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		String msg = "[Shader] Warning: uniform '" + name + "' not found";
		FB_CORE_WARN(msg);
	}
}
