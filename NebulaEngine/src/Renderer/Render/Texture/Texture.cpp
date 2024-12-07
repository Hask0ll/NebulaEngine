#include "Renderer/Render/Texture/Texture.h"

#include <iostream>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION

Texture::Texture(const std::string& path) : m_path(path)
{

}

Texture::~Texture()
{
	glDeleteProgram(m_rendererID);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_rendererID);
}

std::string& Texture::GetPath()
{
	return m_path;
}