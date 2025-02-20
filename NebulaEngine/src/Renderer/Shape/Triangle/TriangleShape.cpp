#include "Renderer/Shape/Triangle/TriangleShape.h"

#include "Logger/Log.h"
#include "Renderer/Manager/RendererManager.h"
#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Render/Render.h"
#include <iostream>

TriangleShape::TriangleShape()
{
	m_triangleVA.reset(Nebula::VertexArray::Create());
	m_triangleVB.reset(Nebula::VertexBuffer::Create(m_vertices, sizeof(m_vertices)));
	if (!m_triangleVB)
	{
		std::cerr << "Failed to create VertexBuffer" << std::endl;
		return;
	}
	m_triangleVB->SetLayout({
			{Nebula::ShaderDataType::Float3,  "aPosition" }
		});
	m_triangleVA->AddVertexBuffer(m_triangleVB);
	m_triangleIB.reset(Nebula::IndexBuffer::Create(m_triangleI, sizeof(m_triangleI)));
	m_triangleVA->SetIndexBuffer(m_triangleIB);
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
	m_shader.reset(new Nebula::Shader(vsSrc, fsSrc));
}

void TriangleShape::Render(glm::mat4 transform) const
{
	Nebula::RendererManager::Submit(m_triangleVA, m_shader, transform);

}

void TriangleShape::SetColor(const float& r, const float& g, const float& b, const float& a) const
{
	m_shader->Bind();
	m_shader->UploadUniformFloat4("u_Color", r / 255, g / 255, b / 255, a / 255);
	m_shader->UnBind();
}