#include "Image.h"
#include "ResourceLoader.h"
#include <array>
#include <glm/gtc/matrix_transform.hpp>
#include "SDL.h"
#include "Texture.h"

Image::Image(const float x, const float y, const float w, const float h, std::shared_ptr<Texture> tex):
        width(w), height(h), posx(x), posy(y), texture(tex)
{
    OnCreate();
}

void Image::OnCreate()
{
    //IMAGE RECTANGLE
    std::array<GLfloat, 20> vertices{
         0.0f,   0.0f,   0.0f, 0.0f, 1.0f,  // Vertex 0, bottom left
         width,  0.0f,   0.0f, 1.0f, 1.0f,  // Vertex 1, bottom right
         0.0f,   height, 0.0f, 0.0f, 0.0f,  // Vertex 2, top left
         width,  height, 0.0f, 1.0f, 0.0f,  // Vertex 3, top right
    };

    std::array<GLuint, 6> indices{
        0, 1, 3,
        3, 2, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);             // <<-VAO BOUND
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // <<-VBO BOUND
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    //Position attribute
    glEnableVertexAttribArray(0);
    //Stride - how many floats separates each vertex
    //Offset - between each attribute within a vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    //UV attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);  // <<-EBO BOUND
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);                     // <<-VAO UNBOUND
    glBindBuffer(GL_ARRAY_BUFFER, 0);         // <<-VBO UNBOUND
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // <<-EBO UNBOUND

    model = glm::translate(glm::mat4{ 1.0f }, glm::vec3{ posx, posy, 0.0f });
    projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);

    ResourceLoader::shaders[SHADER::UI_IMAGE]->sendMatrixToShader("projection", projection);
}

void Image::Render()
{
    //Alpha blending ON
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ResourceLoader::shaders[SHADER::UI_IMAGE]->useProgram();
    ResourceLoader::shaders[SHADER::UI_IMAGE]->sendMatrixToShader("model", model);

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, texture->getTextureID());

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
