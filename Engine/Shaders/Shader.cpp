#include "Shader.h"

Shader::Shader()
{
	vsShader = fsShader = program = 0;
}

Shader::~Shader()
{
	deleteProgram();
}

void Shader::errorProgram(GLuint program)
{
	int link_status = 0;

	glGetProgramiv(program, GL_LINK_STATUS,&link_status);

	if (!link_status)
	{
		char buffer[512];

		glGetProgramInfoLog(program,512,0,buffer);

		LogOut::log(buffer);
	}
}

void Shader::errorShader(GLuint shader)
{
	int compile_status = 0;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

	if (!compile_status)
	{
		char buffer[512];

		glGetShaderInfoLog(shader, 512, 0, buffer);

		LogOut::log(buffer);
	}
}

void Shader::createProgram(const char *vsStr, const char *fsStr)
{
	vsShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsShader, 1, &fsStr, NULL);
	glCompileShader(vsShader);

	errorShader(vsShader);

	fsShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsShader, 1, &fsStr, NULL);
	glCompileShader(fsShader);

	program = glCreateProgram();

	glAttachShader(program, vsShader);
	glAttachShader(program, fsShader);

	errorProgram(program);
}

void Shader::loadShadersFromFile(const char *vsPath, const char *fsPath) 
{
	std::fstream vsFile, fsFile;

	vsFile.open(vsPath);
	fsFile.open(fsPath);

	if (!vsFile.is_open())
	{
		LogOut::log("\n Error : bad filepath vertex shader)");

		return;
	}
	else if (!fsFile.is_open())
	{
		LogOut::log("\n Error : bad filepath fragment shader");

		return;
	}

	std::stringstream v_ss, f_ss;
	std::string vsStr, fsStr;

	v_ss << vsFile.rdbuf();
	f_ss << fsFile.rdbuf();

	vsFile.close();
	fsFile.close();

	vsStr = v_ss.str();
	fsStr = f_ss.str();

	createProgram(vsStr.c_str(), fsStr.c_str());
}

void Shader::loadShaders(const char *vsStr, const char *fsStr, int mode)
{
	if (mode == SHADER_FILE)
	{
		loadShadersFromFile(vsStr, fsStr);
	}
	else if (mode == SHADER_STRING)
	{
		createProgram(vsStr, fsStr);
	}
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::stop()
{
	glUseProgram(0);
}

void Shader::deleteProgram()
{
	glUseProgram(0);

	glDeleteShader(vsShader);
	glDeleteShader(fsShader);

	glDeleteProgram(program);
}