#pragma once
#include <GL/glew.h>
#include "../math/math.h"
#include <vector>
#include "font.h"



namespace sparky {	namespace graphics {
	
class Renderable2D;
	class Renderer2D
	{
	protected:
		std::vector<math::mat4> m_TransformationStack;
		const math::mat4* m_TransformationStackBack;
	protected:
		Renderer2D()
		{
			m_TransformationStack.push_back(math::mat4::identity());
			m_TransformationStackBack = &m_TransformationStack.back();
		}
	public:

		void push(const math::mat4& matrix, bool override = false)
		{
			if (override)
				m_TransformationStack.push_back(matrix);
			else
			m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

			m_TransformationStackBack = &m_TransformationStack.back();
		}
		void pop()
		{
			if (m_TransformationStack.size() > 1)
			m_TransformationStack.pop_back();

			m_TransformationStackBack = &m_TransformationStack.back();
		}
		virtual void begin() {}
		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void drawString(const std::string& text, const math::vec3& position, const Font& font, unsigned int color) { }
		virtual void end(){}
		virtual void flush() = 0;

	};

}}