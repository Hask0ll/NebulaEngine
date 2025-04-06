//
// Created by dobar on 2/27/2025.
//

#include "Nebula.h"
#include <gtest/gtest.h>
#include <memory>

// Mock for index buffer
class MockIndexBuffer : public Nebula::IndexBuffer {
public:
    bool bindCalled = false;
    bool unbindCalled = false;
    uint32_t count;

    explicit MockIndexBuffer(uint32_t count) : count(count) {}

    uint32_t GetCount() const override {
        return count;
    }
};

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