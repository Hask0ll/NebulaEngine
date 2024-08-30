/*#include "Renderer/Shape/Rectangle/RectangleShape.h"

#include "Renderer/Manager/RendererManager.h"

RectangleShape::RectangleShape()
{
	m_squareVA.reset(NEBULA::VertexArray::Create());
	m_squareVB.reset(NEBULA::VertexBuffer::Create(m_vertices, sizeof(m_vertices)));
	m_squareVB->SetLayout({
			{NEBULA::ShaderDataType::Float3,  "aPosition" }
		});
	m_squareVA->AddVertexBuffer(m_squareVB);
	m_squareIB.reset(NEBULA::IndexBuffer::Create(m_squareI, sizeof(m_squareI)));
	m_squareVA->SetIndexBuffer(m_squareIB);
	std::string vsSrc = R"(#version 330 core
		layout(location = 0) in vec3 aPos;

		uniform mat4 u_Transform;

		out vec3 vPos;

		void main()
		{
			vPos = aPos;
			gl_Position = u_Transform * vec4(aPos, 1.0);
		})";
	std::string fsSrc = R"(#version 330 core

		layout(location = 0) out vec4 color;

		uniform vec4 u_Color;

		void main()
		{
			color = u_Color;
		})";
	m_shader.reset(new NEBULA::Shader(vsSrc, fsSrc));
}

void RectangleShape::Render(glm::mat4 transform)
{
	NEBULA::Renderer::Submit(m_squareVA, m_shader, transform);

}

void RectangleShape::SetColor(const float& r, const float& g, const float& b, const float& a)
{
	m_shader->Bind();
	m_shader->UploadUniformFloat4("u_Color", r / 255, g / 255, b / 255, a / 255);
	m_shader->UnBind();
} */
