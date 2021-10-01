#include "Texture.h"
#include <iostream>
#include "glew.h"
#include "SDL.h"
#include "SDL_image.h"

Texture::Texture(): texID(0){}

Texture::~Texture() {
	glDeleteTextures(1, &texID);
}

bool Texture::loadTexture(const char* filepath)
{
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	SDL_Surface *texSurface = IMG_Load(filepath);
	if (!texSurface)
		return false;
		
	int mode = (texSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, mode, texSurface->w, texSurface->h, 0, mode, GL_UNSIGNED_BYTE, texSurface->pixels);
	glBindTexture(GL_TEXTURE_2D, 0); //Unbinds the texture
	SDL_FreeSurface(texSurface);
	return true;
}
