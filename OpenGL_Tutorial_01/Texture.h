#pragma once

class Texture
{
public:
	Texture();
	~Texture();
	bool loadTexture(const char* filepath);
	unsigned int getTextureID() const { return texID; }

private:
	unsigned int texID;
};


