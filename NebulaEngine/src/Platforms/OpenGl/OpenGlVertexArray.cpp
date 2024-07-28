#include "platform/OpenGl/VertexArray/OpenGlVertexArray.h"

#include <glad/glad.h>

#include "Debug/Logger.h"

namespace Nebula
{

	static GLenum ShaderDataTypeToOpenGlType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:   return GL_FLOAT;
		case ShaderDataType::Float2:  return GL_FLOAT;
		case ShaderDataType::Float3:  return GL_FLOAT;
		case ShaderDataType::Float4:  return GL_FLOAT;
		case ShaderDataType::Mat3:    return GL_FLOAT;
		case ShaderDataType::Mat4:    return GL_FLOAT;
		case ShaderDataType::Int:     return GL_INT;
		case ShaderDataType::Int2:    return GL_INT;
		case ShaderDataType::Int3:    return GL_INT;
		case ShaderDataType::Int4:    return GL_INT;
		case ShaderDataType::Bool:    return GL_BOOL;
		}
		return 0;
	}

	OpenGlVertexArray::OpenGlVertexArray()
	{
		Logger::Log(Logger::Info, "Creating vertex arrays");
		glCreateVertexArrays(1, &m_RendererID);
	}

	void OpenGlVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGlVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGlVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(),
				ShaderDataTypeToOpenGlType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(), (const void*)element.Offset);
			index++;
		}
		m_VertexBuffer.push_back(vertexBuffer);
	}

	void OpenGlVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}