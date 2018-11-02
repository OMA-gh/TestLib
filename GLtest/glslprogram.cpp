#include "glslprogram.h"

#include "glutils.h"

#include <fstream>
using std::ifstream;
using std::ios;

#include <sstream>
using std::ostringstream;

#include <sys/stat.h>

GLSLProgram::GLSLProgram() : mHandle(0), mIsLinked(false) { }

bool GLSLProgram::compileShaderFromFile(const char * fileName,
	GLSLShader::GLSLShaderType type)
{
	if (!fileExists(fileName))
	{
		mLogString = "File not found.";
		return false;
	}

	if (mHandle <= 0) {
		mHandle = glCreateProgram();
		if (mHandle == 0) {
			mLogString = "Unable to create shader program.";
			return false;
		}
	}

	ifstream inFile(fileName, ios::in);
	if (!inFile) {
		return false;
	}

	ostringstream code;
	while (inFile.good()) {
		int c = inFile.get();
		if (!inFile.eof())
			code << (char)c;
	}
	inFile.close();

	return compileShaderFromString(code.str(), type);
}

bool GLSLProgram::compileShaderFromString(const string & source, GLSLShader::GLSLShaderType type)
{
	if (mHandle <= 0) {
		mHandle = glCreateProgram();
		if (mHandle == 0) {
			mLogString = "Unable to create shader program.";
			return false;
		}
	}

	GLuint shaderHandle = 0;

	switch (type) {
	case GLSLShader::VERTEX:
		shaderHandle = glCreateShader(GL_VERTEX_SHADER);
		break;
	case GLSLShader::FRAGMENT:
		shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case GLSLShader::GEOMETRY:
		shaderHandle = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case GLSLShader::TESS_CONTROL:
		shaderHandle = glCreateShader(GL_TESS_CONTROL_SHADER);
		break;
	case GLSLShader::TESS_EVALUATION:
		shaderHandle = glCreateShader(GL_TESS_EVALUATION_SHADER);
		break;
	default:
		return false;
	}

	const char * c_code = source.c_str();
	glShaderSource(shaderHandle, 1, &c_code, NULL);

	// Compile the shader
	glCompileShader(shaderHandle);

	// Check for errors
	int result;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result) {
		// Compile failed, store log and return false
		int length = 0;
		mLogString = "";
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			char * c_log = new char[length];
			int written = 0;
			glGetShaderInfoLog(shaderHandle, length, &written, c_log);
			mLogString = c_log;
			delete[] c_log;
		}

		return false;
	}
	else {
		// Compile succeeded, attach shader and return true
		glAttachShader(mHandle, shaderHandle);
		return true;
	}
}

bool GLSLProgram::link()
{
	if (mIsLinked) return true;
	if (mHandle <= 0) return false;

	glLinkProgram(mHandle);

	int status = 0;
	glGetProgramiv(mHandle, GL_LINK_STATUS, &status);
	if (GL_FALSE == status) {
		// Store log and return false
		int length = 0;
		mLogString = "";

		glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &length);

		if (length > 0) {
			char * c_log = new char[length];
			int written = 0;
			glGetProgramInfoLog(mHandle, length, &written, c_log);
			mLogString = c_log;
			delete[] c_log;
		}

		return false;
	}
	else {
		mIsLinked = true;
		return mIsLinked;
	}
}

void GLSLProgram::use()
{
	if (mHandle <= 0 || (!mIsLinked)) return;
	glUseProgram(mHandle);
}

string GLSLProgram::log()
{
	return mLogString;
}

int GLSLProgram::getHandle()
{
	return mHandle;
}

bool GLSLProgram::isLinked()
{
	return mIsLinked;
}

void GLSLProgram::bindAttribLocation(GLuint location, const char * name)
{
	glBindAttribLocation(mHandle, location, name);
}

void GLSLProgram::bindFragDataLocation(GLuint location, const char * name)
{
	glBindFragDataLocation(mHandle, location, name);
}

void GLSLProgram::setUniform(const char *name, float x, float y, float z)
{
	int loc = getUniformLocation(name);
	if (loc >= 0) {
		glUniform3f(loc, x, y, z);
	}
	else {
		printf("Uniform: %s not found.\n", name);
	}
}
void GLSLProgram::setUniform(const char *name, float x, float y, float z,float w)
{
	int loc = getUniformLocation(name);
	if (loc >= 0) {
		glUniform4f(loc, x, y, z, w);
	}
	else {
		printf("Uniform: %s not found.\n", name);
	}
}

void GLSLProgram::setUniform(const char *name, const vec3 & v)
{
	this->setUniform(name, v.x, v.y, v.z);
}

void GLSLProgram::setUniform(const char *name, const vec4 & v)
{
	int loc = getUniformLocation(name);
	if (loc >= 0) {
		glUniform4f(loc, v.x, v.y, v.z, v.w);
	}
	else {
		printf("Uniform: %s not found.\n", name);
	}
}

void GLSLProgram::setUniform(const char *name, const mat4 & m)
{
	int loc = getUniformLocation(name);
	if (loc >= 0)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
	}
	else {
		printf("Uniform: %s not found.\n", name);
	}
}

void GLSLProgram::setUniform(const char *name, const mat3 & m)
{
	int loc = getUniformLocation(name);
	if (loc >= 0)
	{
		glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
	}
	else {
		printf("Uniform: %s not found.\n", name);
	}
}

void GLSLProgram::setUniform(const char *name, float val)
{
	int loc = getUniformLocation(name);
	if (loc >= 0)
	{
		glUniform1f(loc, val);
	}
	else {
		printf("Uniform: %s not found.\n", name);
	}
}

void GLSLProgram::setUniform(const char *name, int val)
{
	int loc = getUniformLocation(name);
	if (loc >= 0)
	{
		glUniform1i(loc, val);
	}
	else {
		printf("Uniform: %s not found.\n", name);
	}
}

void GLSLProgram::setUniform(const char *name, bool val)
{
	int loc = getUniformLocation(name);
	if (loc >= 0)
	{
		glUniform1i(loc, val);
	}
	else {
		printf("Uniform: %s not found.\n", name);
	}
}

void GLSLProgram::printActiveUniforms() {

	GLint nUniforms, size, location, maxLen;
	GLchar * name;
	GLsizei written;
	GLenum type;

	glGetProgramiv(mHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
	glGetProgramiv(mHandle, GL_ACTIVE_UNIFORMS, &nUniforms);

	name = (GLchar *)malloc(maxLen);

	printf(" Location | Name\n");
	printf("------------------------------------------------\n");
	for (int i = 0; i < nUniforms; ++i) {
		glGetActiveUniform(mHandle, i, maxLen, &written, &size, &type, name);
		location = glGetUniformLocation(mHandle, name);
		printf(" %-8d | %s\n", location, name);
	}

	free(name);
}

void GLSLProgram::printActiveAttribs() {

	GLint written, size, location, maxLength, nAttribs;
	GLenum type;
	GLchar * name;

	glGetProgramiv(mHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
	glGetProgramiv(mHandle, GL_ACTIVE_ATTRIBUTES, &nAttribs);

	name = (GLchar *)malloc(maxLength);

	printf(" Index | Name\n");
	printf("------------------------------------------------\n");
	for (int i = 0; i < nAttribs; i++) {
		glGetActiveAttrib(mHandle, i, maxLength, &written, &size, &type, name);
		location = glGetAttribLocation(mHandle, name);
		printf(" %-5d | %s\n", location, name);
	}

	free(name);
}

bool GLSLProgram::validate()
{
	if (!isLinked()) return false;

	GLint status;
	glValidateProgram(mHandle);
	glGetProgramiv(mHandle, GL_VALIDATE_STATUS, &status);

	if (GL_FALSE == status) {
		// Store log and return false
		int length = 0;
		mLogString = "";

		glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &length);

		if (length > 0) {
			char * c_log = new char[length];
			int written = 0;
			glGetProgramInfoLog(mHandle, length, &written, c_log);
			mLogString = c_log;
			delete[] c_log;
		}

		return false;
	}
	else {
		return true;
	}
}

int GLSLProgram::getUniformLocation(const char * name)
{
	return glGetUniformLocation(mHandle, name);
}

bool GLSLProgram::fileExists(const string & fileName)
{
	struct stat info;
	int ret = -1;

	ret = stat(fileName.c_str(), &info);
	return 0 == ret;
}
