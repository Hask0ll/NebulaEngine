#include <memory>
#include <glm/glm.hpp>

#include "Renderer/Render/Shader/Shader.h"
#include "Renderer/VertexArray/VertexArray.h"

namespace Nebula
{
	/**
	 * \brief Rectangle shape implementation in OpenGL
	 */
	class RectangleShape
	{
	public:
		RectangleShape();

		/**
		 * \brief Render Shape with specified transform
		 * \param transform transform of shape
		 */
		void Render(const glm::mat4 transform) const;

		/**
		 * \brief Set color of current rectangle
		 * \param r Red
		 * \param g Green
		 * \param b Blue
		 * \param a Alpha
		 */
		void SetColor(const float& r, const float& g, const float& b, const float& a) const;
	private:
		uint32_t m_squareI[6] = { 0, 1, 2, 2, 3, 0 };
		float m_vertices[3 * 4] = {
				-0.5f,  0.5f, 0.0f, // Top left
		 0.5f,  0.5f, 0.0f, // Top right
		 0.5f, -0.5f, 0.0f, // Bottom right
		-0.5f, -0.5f, 0.0f
		};
		std::shared_ptr<Nebula::Shader> m_shader;
		std::shared_ptr<Nebula::VertexArray> m_squareVA;
		std::shared_ptr<Nebula::VertexBuffer> m_squareVB;
		std::shared_ptr<Nebula::IndexBuffer> m_squareIB;
	};
}
