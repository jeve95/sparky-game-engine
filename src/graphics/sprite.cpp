#include "sprite.h"

namespace sparky {	namespace graphics {
	
	Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
		: Renderable2D(math::vec3(x, y, 0), math::vec2(width, height), color)
	{

	}
	
	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Renderable2D(math::vec3(x, y, 0), math::vec2(width, height), 0xffffffff)
	{
		m_Texture = texture;
	}

}}