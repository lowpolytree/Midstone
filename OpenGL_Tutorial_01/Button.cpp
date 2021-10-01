#include "Button.h"
#include "ResourceLoader.h"
#include <array>
#include <glm/gtc/matrix_transform.hpp>
#include "SDL.h"

Button::Button(Position p, Size s, const std::string& buttonText_, std::unique_ptr<Command>&& cmd): 
        position(p), size(s), buttonText(buttonText_), buttonCommand(std::move(cmd)) {
    OnCreate();
    isActive = true;
    state = STATE::DEFAULT;
}

void Button::OnCreate()
{
    //BUTTON RECTANGLE
    std::array<GLfloat, 20> vertices{
         0.0f,        0.0f, 0.0f,    0.0f, 1.0f,  // Vertex 0, bottom left
         size.width,  0.0f, 0.0f,    1.0f, 1.0f,  // Vertex 1, bottom right
         0.0f,        size.height,   0.0f, 0.0f, 0.0f,  // Vertex 2, top left
         size.width,  size.height,   0.0f, 1.0f, 0.0f,  // Vertex 3, top right
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

    //Position around button's center
    minX = position.x - size.width / 2.0f;
    minY = position.y - size.height / 2.0f;
    maxX = minX + size.width;
    maxY = minY + size.height;
    model = glm::translate(glm::mat4{ 1.0f }, glm::vec3{ minX, minY, 0.0f });
    projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);

    ResourceLoader::shaders[SHADER::UI]->sendMatrixToShader("projection", projection);

    //TEXT
    text = std::make_unique<Text>();
    text->Load("Resources\\Fonts\\Bubbleboddy_EL.ttf", 60, buttonText, SDL_Color{ 0, 0, 0, 0 });
    text->UpdateModel(PositionText{ size.width / 2.0f, 30.0f }, 1.0f, model);
}

void Button::HandleEvents(const SDL_Event& ev) {
    SDL_GetMouseState(&mouseX, &mouseY);
    //Remapping y coordinate to increment from the bottom.
    mouseY = -mouseY + 720;

    //If mouse is hovering over the button
    if (mouseX > minX && mouseX < maxX && mouseY > minY && mouseY < maxY) {
        //std::cout << "HOVER: " << mouseX << "," << mouseY << "\n";
        state = STATE::HOVER;

        //Check for mouse pressed
        if (ev.type == SDL_MOUSEBUTTONDOWN) {
            state = STATE::PRESSED;
            ExecuteCommand();
            this->setIsActive(false);
        }
    }
    else {
        state = STATE::DEFAULT;
    }
}

void Button::Render()
{
    //Alpha blending ON
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ResourceLoader::shaders[SHADER::UI]->useProgram();
    ResourceLoader::shaders[SHADER::UI]->sendMatrixToShader("model", model);

    //Changing button state color
    switch (state) {
    case STATE::DEFAULT:
        ResourceLoader::shaders[SHADER::UI]->sendVector3ToShader("color", glm::vec3(1.0f, 1.0f, 1.0f));
        break;
    case STATE::HOVER:
        ResourceLoader::shaders[SHADER::UI]->sendVector3ToShader("color", glm::vec3(0.8f, 0.0f, 0.0f));
        break;
    case STATE::PRESSED:
        ResourceLoader::shaders[SHADER::UI]->sendVector3ToShader("color", glm::vec3(0.3f, 0.0f, 0.0f));
        break;
    }

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, ResourceLoader::textures[TEXTURE::UI_BUTTON]->getTextureID());

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

    text->Render();
}
