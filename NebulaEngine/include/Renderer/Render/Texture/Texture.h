#pragma once

#include <string>

#include "Core/Core.h"

/**
 * \brief OpenGl Texture implementation
 */
class NEBULA Texture
{
public:
	Texture(const std::string& path);
	~Texture();
	void Bind();
	const std::string& GetPath();
private:
	uint32_t m_rendererID;
	const std::string m_path;
};