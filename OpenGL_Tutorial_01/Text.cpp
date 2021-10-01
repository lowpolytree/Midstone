#include "Text.h"
#include <iostream>
#include "glew.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <array>
#include "ResourceLoader.h"
#include <glm/gtc/matrix_transform.hpp>

Text::Text() {}

Text::~Text() {
    glDeleteTextures(1, &texID);
}

bool Text::Load(const std::string& filepath, int textSize, const std::string& textMessage, SDL_Color color)
{
    TTF_Font* font = TTF_OpenFont(filepath.c_str(), textSize);
    if (!font) return false;

    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, textMessage.c_str(), color);
    if (!surfaceMessage) {
        TTF_CloseFont(font);
        return false;
    }

    //MAKING OPENGL TEX
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    int mode = (surfaceMessage->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, mode, surfaceMessage->w, surfaceMessage->h, 0, mode, GL_UNSIGNED_BYTE, surfaceMessage->pixels);
    glBindTexture(GL_TEXTURE_2D, 0); //Unbinds the texture

   /* float w = (float)surfaceMessage->w / 1280;
    float h = (float)surfaceMessage->h / 720;*/

    float w = (float)surfaceMessage->w;
    float h = (float)surfaceMessage->h;

    SDL_FreeSurface(surfaceMessage);
    TTF_CloseFont(font);

    std::array<GLfloat, 20> vertices{
         0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // Vertex 0, bottom left
         w,    0.0f, 0.0f, 1.0f, 1.0f,  // Vertex 1, bottom right
         0.0f, h,    0.0f, 0.0f, 0.0f,  // Vertex 2, top left
         w,    h,    0.0f, 1.0f, 0.0f,  // Vertex 3, top right
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

    //SCALE AND TRANSLATE
    //Position around text's center
    auto newPosX = -w / 2.0f;
    auto newPosY = -h / 2.0f;

    model = glm::translate(glm::mat4{ 1.0f }, glm::vec3{ newPosX, newPosY, 0.0f });
    projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);

    ResourceLoader::shaders[SHADER::TEXT]->sendMatrixToShader("projection", projection);

	return true;
}

void Text::Render()
{
    //Alpha blending ON
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ResourceLoader::shaders[SHADER::TEXT]->useProgram();
    ResourceLoader::shaders[SHADER::TEXT]->sendMatrixToShader("model", model);

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, texID);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

    glDisable(GL_BLEND);
}

void Text::UpdateModel(const PositionText pos, const float scale, const glm::mat4& parent)
{
    model = parent * glm::translate(glm::mat4{ model }, glm::vec3{ pos.x, pos.y, 0.0f }) *
            glm::scale(glm::mat4{ 1.0f }, glm::vec3{ scale });
}
