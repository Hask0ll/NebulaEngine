//
// Created by dobar on 2/27/2025.
//

#include "Nebula.h"
#include <gtest/gtest.h>
#include <memory>

// Mock for vertex buffer
class MockVertexBuffer : public Nebula::VertexBuffer {
public:
    bool bindCalled = false;
    bool unbindCalled = false;
    Nebula::BufferLayout layout;

    void Bind() const override {
        bindCalled = true;
    }

    void UnBind() const override {
        unbindCalled = true;
    }

    const Nebula::BufferLayout& GetLayout() const override {
        return layout;
    }

    void SetLayout(const Nebula::BufferLayout& newLayout) override {
        layout = newLayout;
    }
};

// Mock for index buffer
class MockIndexBuffer : public Nebula::IndexBuffer {
public:
    bool bindCalled = false;
    bool unbindCalled = false;
    uint32_t count;

    explicit MockIndexBuffer(uint32_t count) : count(count) {}

    void Bind() const override {
        bindCalled = true;
    }

    void UnBind() const override {
        unbindCalled = true;
    }

    uint32_t GetCount() const override {
        return count;
    }
};

// Test vertex buffer
TEST(VertexBufferTest, BasicFunctionality) {
    MockVertexBuffer buffer;

    // Test bind/unbind
    buffer.Bind();
    EXPECT_TRUE(buffer.bindCalled);

    buffer.UnBind();
    EXPECT_TRUE(buffer.unbindCalled);

    // Test layout
    Nebula::BufferLayout layout = {
        { Nebula::ShaderDataType::Float3, "Position" },
        { Nebula::ShaderDataType::Float4, "Color" }
    };

    buffer.SetLayout(layout);

    const auto& resultLayout = buffer.GetLayout();
    EXPECT_EQ(resultLayout.GetStride(), 28); // 12 + 16 = 28 bytes

    const auto& elements = resultLayout.GetElements();
    EXPECT_EQ(elements.size(), 2);
    EXPECT_EQ(elements[0].Type, Nebula::ShaderDataType::Float3);
    EXPECT_EQ(elements[0].Name, "Position");
    EXPECT_EQ(elements[1].Type, Nebula::ShaderDataType::Float4);
    EXPECT_EQ(elements[1].Name, "Color");
}

// Test index buffer
TEST(IndexBufferTest, BasicFunctionality) {
    const uint32_t testCount = 42;
    MockIndexBuffer buffer(testCount);

    // Test bind/unbind
    buffer.Bind();
    EXPECT_TRUE(buffer.bindCalled);

    buffer.UnBind();
    EXPECT_TRUE(buffer.unbindCalled);

    // Test count
    EXPECT_EQ(buffer.GetCount(), testCount);
}

// Test vertex array
TEST(VertexArrayTest, AddingBuffers) {
    // Create vertex array
    auto vertexArray = std::make_shared<Nebula::VertexArray>();

    // Create vertex buffer
    auto vertexBuffer = std::make_shared<MockVertexBuffer>();
    Nebula::BufferLayout layout = {
        { Nebula::ShaderDataType::Float3, "Position" }
    };
    vertexBuffer->SetLayout(layout);

    // Add vertex buffer to array
    vertexArray->AddVertexBuffer(vertexBuffer);

    // Verify buffer was added
    const auto& buffers = vertexArray->GetVertexBuffers();
    EXPECT_EQ(buffers.size(), 1);
    EXPECT_EQ(buffers[0], vertexBuffer);

    // Create index buffer
    const uint32_t testCount = 6;
    auto indexBuffer = std::make_shared<MockIndexBuffer>(testCount);

    // Set index buffer
    vertexArray->SetIndexBuffer(indexBuffer);

    // Verify index buffer was set
    EXPECT_EQ(vertexArray->GetIndexBuffer(), indexBuffer);
    EXPECT_EQ(vertexArray->GetIndexBuffer()->GetCount(), testCount);
}

// Test factory methods
TEST(BufferFactoryTest, CreationMethods) {
    // Test VertexBuffer creation
    float vertices[] = { 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };
    Nebula::VertexBuffer* vb = nullptr;

    // This might fail without a proper OpenGL context, so wrap in try/catch
    try {
        vb = Nebula::VertexBuffer::Create(vertices, sizeof(vertices));
        EXPECT_NE(vb, nullptr);
        delete vb;
    }
    catch (const std::exception& e) {
        GTEST_SKIP() << "Skipping VertexBuffer creation test due to missing OpenGL context: " << e.what();
    }

    // Test IndexBuffer creation
    uint32_t indices[] = { 0, 1, 2 };
    Nebula::IndexBuffer* ib = nullptr;

    try {
        ib = Nebula::IndexBuffer::Create(indices, 3);
        EXPECT_NE(ib, nullptr);
        EXPECT_EQ(ib->GetCount(), 3);
        delete ib;
    }
    catch (const std::exception& e) {
        GTEST_SKIP() << "Skipping IndexBuffer creation test due to missing OpenGL context: " << e.what();
    }

    // Test VertexArray creation
    Nebula::VertexArray* va = nullptr;

    try {
        va = Nebula::VertexArray::Create();
        EXPECT_NE(va, nullptr);
        delete va;
    }
    catch (const std::exception& e) {
        GTEST_SKIP() << "Skipping VertexArray creation test due to missing OpenGL context: " << e.what();
    }
}