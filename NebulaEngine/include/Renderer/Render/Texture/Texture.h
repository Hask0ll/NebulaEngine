#pragma once

#include <string>
#include <glm/fwd.hpp>

#include "Core.h"

/**
 * \brief OpenGl Texture implementation
 */
class NEBULA_API Texture
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