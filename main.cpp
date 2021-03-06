#include "src/graphics/window.h"
#include <GL/glew.h>
#include "src/math/math.h"
#include "src/utils/timer.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/batchrenderer2d.h"
#include <time.h>
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"
#include "src/graphics/texture.h"
#include "src/graphics/label.h"
#include "src/graphics/font_manager.h"


#define TEST_50K_SPRITES 0




int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace math;

	Window window("Sparky", 1920, 1080);
	//glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0, 1.0);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.enable();
	shader.SetUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);

	Texture* textures[] =
	{
		new Texture("test.png"),
		new Texture("tb.png"),
		new Texture("tc.png"),
	};
	

	for (float y = -9.0f; y < 9.0f; y ++)
	{
		for (float x = -16.0; x < 16.0f; x ++)
		{
			int r = rand() % 256;

			int col = 0xffff00 << 8 | r;
			if(rand() % 4 == 0)
			layer.add(new Sprite(x, y, 0.9f, 0.9f, col));
			else
			layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3 ]));
		}
	}

	
	Group* g = new Group(math::mat4::translation(math::vec3(-15.0f, 7.0f, 0.0f)));
	Label* fps = new Label("", 0.4f, 0.4f, "arial", 50, 0xffffffff);
	g->add(new Sprite(0, 0, 5, 1.5f, 0x505050DD));
	g->add(fps);

	

	layer.add(g);



	GLint texIDs[] =
	{
		0,1,2,3,4,5,6,7,8,9
	};

	shader.enable();
	shader.SetUniform1iv("textures", texIDs, 10);
	shader.SetUniformMat4("pr_matrix", math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	float t = 0.0f;
	while (!window.closed())
	{
		t += 0.001f;
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.SetUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeigth())));
		layer.render();
	
		const std::vector<Renderable2D*>& rs = layer.getRenderables();
		for (int i = 0; i < rs.size(); i++)
		{
			float c = sin(t) / 2 + 0.5;
			rs[i]->setColor(math::vec4(c, 0, 1, 1));
		}

		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			fps->text = std::to_string(frames) + "fps";
			printf("%d fps\n", frames);
			frames = 0;
		}
		
	}
	for (int i = 0; i < 3; i++)
		delete textures[i];
	
}


