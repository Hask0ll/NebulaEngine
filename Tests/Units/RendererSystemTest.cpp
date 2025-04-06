//
// Created by dobar on 2/27/2025.
//

#include "Nebula.h"
#include <gtest/gtest.h>
#include <memory>

// Mock for OpenGL rendering
class MockRendererAPI : public Nebula::RendererApi {
public:
    bool clearCalled = false;
    glm::vec4 lastClearColor;
    bool drawIndexedCalled = false;
    std::shared_ptr<Nebula::VertexArray> lastVertexArray;
    uint32_t lastIndexCount = 0;

    void SetClearColor(const glm::vec4& color) override {
        lastClearColor = color;
    }

    void Clear() override {
        clearCalled = true;
    }

    void DrawIndexed(const std::shared_ptr<Nebula::VertexArray>& vertexArray, uint32_t indexCount = 0) override {
        drawIndexedCalled = true;
        lastVertexArray = vertexArray;
        lastIndexCount = indexCount;
    }
};

// Test shader class functionality
TEST(ShaderTest, ShaderFunctions) {
    // Define simple test shaders
    std::string vertexSrc = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )";

    // Create a shader (this might fail without a proper OpenGL context, so wrap in try/catch)
    try {
        Nebula::Shader shader(vertexSrc, fragmentSrc);

        // Test bind/unbind
        EXPECT_NO_THROW(shader.Bind());
        EXPECT_NO_THROW(shader.UnBind());

        // Test uniform uploads
        glm::mat4 testMatrix = glm::mat4(1.0f);
        EXPECT_NO_THROW(shader.UploadUniformMat4("u_Transform", testMatrix));

        EXPECT_NO_THROW(shader.UploadUniformFloat4("u_Color", 1.0f, 0.0f, 0.0f, 1.0f));
    }
    catch (const std::exception& e) {
        // If there's no OpenGL context, this is expected to fail
        GTEST_SKIP() << "Skipping shader test due to missing OpenGL context: " << e.what();
    }
}