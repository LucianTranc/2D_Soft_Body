#include "TextureManager.h"
#include "Game.h"

Texture * TextureManager::LoadTexture(const char* texturePath, float w, float h, float iw, float ih) {


    float positions[] {
        0.0f, h		, 0.0f, 0.0f, //bottomleft
        0.0f, 0.0f	, 0.0f, 1.0f, //topleft
        w	, 0.0f	, 1.0f, 1.0f, //topright
        w	, h		, 1.0f, 0.0f, //bottomright
    };


    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    }; 


	VertexArray * va = new VertexArray();

    VertexBuffer * vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));

	VertexBufferLayout * layout = new VertexBufferLayout();

    layout->Push<float>(2);
    layout->Push<float>(2);
    va->AddBuffer(*vb, *layout);

    IndexBuffer * ib = new IndexBuffer(indicies, 6);

    glm::mat4 proj = glm::ortho(0.0, static_cast<double>(iw), static_cast<double>(ih), 0.0);

    Shader * shader = new Shader("shaders/basic.shader");
    shader->Bind();
    shader->SetUniformMat4f("u_MVP", proj);
    
    Texture * texture = new Texture(texturePath);
    texture->Bind();
    shader->SetUniform1i("u_Texture", 0);

    va->Unbind();
    vb->Unbind();
    ib->Unbind();
    shader->Unbind();

	texture->va = va;
	texture->vb = vb;
	texture->layout = layout;
	texture->ib = ib;
	texture->shader = shader;

	return texture;


}
