#pragma once
#include <memory>
#include <glm/glm.hpp>

#include "Renderer/Render/Shader/Shader.h"
#include "Renderer/Buffer/VertexBuffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer/IndexBuffer.h"
#include "Renderer/VertexArray/VertexArray.h"

/**
 * \brief Triangle shape implementation in OpenGL
 */
class TriangleShape
{
public:
	TriangleShape();
	/**
	 * \brief Render shape with specified transform
	 * \param transform transform of shape
	 */
	void Render(glm::mat4 transform) const;
	/**
	 * \brief Set color of current triangle
	 * \param r Red
	 * \param g Green
	 * \param b Blue
	 * \param a Alpha
	 */
	void SetColor(const float& r, const float& g, const float& b, const float& a) const;
private:
	uint32_t m_triangleI[3] = { 0, 1, 2 };
	float m_vertices[3 * 3] = {
			0.0f,  0.5f, 0.0f,
		   -0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f
	};
	std::shared_ptr<Nebula::Shader> m_shader;
	std::shared_ptr<Nebula::VertexArray> m_triangleVA;
	std::shared_ptr<Nebula::VertexBuffer> m_triangleVB;
	std::shared_ptr<Nebula::IndexBuffer> m_triangleIB;
};