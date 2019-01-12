#pragma once
#include "../utils/fileutils.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "../math/math.h"

namespace sparky {	namespace graphics {

	class Shader
	{
	private:
		const char* m_VertPath;
		const char* m_FragPath;
	public:
		GLuint m_ShaderID;
		Shader(const char* vertPath, const char* fragPath);
		~Shader();


		void SetUniform1f(const GLchar* name, float value);
		void SetUniform1fv(const GLchar* name, float* value, int count);
		void SetUniform1i(const GLchar* name, int value);
		void SetUniform1iv(const GLchar* name, int* value, int count);
		void SetUniform2f(const GLchar* name, const math::vec2& vector);
		void SetUniform3f(const GLchar* name, const math::vec3& vector);
		void SetUniform4f(const GLchar* name, const math::vec4& vector);
		void SetUniformMat4(const GLchar* name, const math::mat4& matrix);

		void enable() const;
		void disable() const;
	private:
		GLint getUniformLocation(const GLchar* name);
		GLuint load();
	};

} }