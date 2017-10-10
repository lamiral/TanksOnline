#pragma once

#include <GL/glew.h>

#include <string>
#include <sstream>
#include <fstream>

#include "Log.h"

enum {SHADER_FILE = 1,SHADER_STRING = 2};

class Shader
{
private:

	GLuint vsShader, fsShader, program;

	void errorShader(GLuint shader);
	void errorProgram(GLuint program);

	void createProgram(const char *vsStr,const char *fsStr);

	void loadShadersFromFile(const char *vsPath,const char *fsPath);

public:

	Shader();
	~Shader();

	void loadShaders(const char *vsStr,const char *fsStr, int mode);

	void use();
	void stop();

	void deleteProgram();

	GLuint getProgram() const;
};