#pragma once

#include <string>
#include "Core/Core.h"
#include <glm/glm.hpp>

namespace Nebula
{
	class NEBULA Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void UnBind() ;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;
		void UploadUniformFloat4(const std::string& name, const float& x, const float& y, const float& z, const float& w) const;
	private:
		uint32_t m_RendererID;
	};
}
