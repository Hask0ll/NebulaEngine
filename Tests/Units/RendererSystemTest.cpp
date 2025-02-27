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

// Test fixture for renderer system
class RendererTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize necessary components
        Nebula::Log::Init();

        // Save the existing renderer API for restoration
        m_OriginalRendererApi = Nebula::RenderCommand::s_RendererApi;

        // Replace with our mock
        m_MockRendererApi = new MockRendererAPI();
        Nebula::RenderCommand::s_RendererApi = m_MockRendererApi;
    }

    void TearDown() override {
        // Restore the original renderer API
        Nebula::RenderCommand::s_RendererApi = m_OriginalRendererApi;

        // Delete our mock
        delete m_MockRendererApi;

        Nebula::Log::Shutdown();
    }

    Nebula::RendererApi* m_OriginalRendererApi;
    MockRendererAPI* m_MockRendererApi;
};

// Test RenderCommand functionality
TEST_F(RendererTest, RenderCommandFunctions) {
    // Test SetClearColor
    glm::vec4 clearColor(0.1f, 0.2f, 0.3f, 1.0f);
    Nebula::RenderCommand::SetClearColor(clearColor);
    EXPECT_EQ(m_MockRendererApi->lastClearColor, clearColor);

    // Test Clear
    Nebula::RenderCommand::Clear();
    EXPECT_TRUE(m_MockRendererApi->clearCalled);

    // Test DrawIndexed with a mock vertex array
    auto vertexArray = std::make_shared<Nebula::VertexArray>();
    Nebula::RenderCommand::DrawIndexed(vertexArray, 42);
    EXPECT_TRUE(m_MockRendererApi->drawIndexedCalled);
    EXPECT_EQ(m_MockRendererApi->lastVertexArray, vertexArray);
    EXPECT_EQ(m_MockRendererApi->lastIndexCount, 42);
}

// Test RendererManager functionality
TEST_F(RendererTest, RendererManager) {
    // Create a camera for the test
    Nebula::OrthographicCamera camera(-1.6f, 1.6f, -0.9f, 0.9f);

    // Begin a scene
    Nebula::RendererManager::BeginScene(camera);

    // Create test objects
    auto vertexArray = std::make_shared<Nebula::VertexArray>();
    auto shader = std::make_shared<Nebula::Shader>("", ""); // Empty shaders for testing

    // Submit to renderer
    Nebula::RendererManager::Submit(vertexArray, shader);

    // End the scene
    Nebula::RendererManager::EndScene();

    // Verify the renderer API was called correctly
    EXPECT_TRUE(m_MockRendererApi->drawIndexedCalled);
    EXPECT_EQ(m_MockRendererApi->lastVertexArray, vertexArray);
}

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