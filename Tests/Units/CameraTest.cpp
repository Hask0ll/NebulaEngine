//
// Created by dobar on 2/27/2025.
//

#include "Nebula.h"
#include <gtest/gtest.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

TEST(OrthographicCamera, Construction) {
    // Create a camera with standard projection parameters
    Nebula::OrthographicCamera camera(-1.6f, 1.6f, -0.9f, 0.9f);

    // Check default values
    EXPECT_EQ(camera.GetPosition(), glm::vec3(0.0f, 0.0f, 0.0f));

    // The view matrix should be identity by default
    const glm::mat4& viewMatrix = camera.GetViewMatrix();
    glm::mat4 identity = glm::mat4(1.0f);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_FLOAT_EQ(viewMatrix[i][j], identity[i][j]);
        }
    }

    // Projection matrix should be set according to parameters
    const glm::mat4& projMatrix = camera.GetProjectionMatrix();

    // Check specific values in projection matrix that we can derive from the parameters
    // For an orthographic projection matrix, the diagonal elements should match the formula
    EXPECT_FLOAT_EQ(projMatrix[0][0], 2.0f / (1.6f - (-1.6f))); // 2/(right-left)
    EXPECT_FLOAT_EQ(projMatrix[1][1], 2.0f / (0.9f - (-0.9f))); // 2/(top-bottom)
    EXPECT_FLOAT_EQ(projMatrix[2][2], -2.0f / (1.0f - (-1.0f))); // -2/(far-near)

    // The ViewProjection matrix should be the product of projection and view matrices
    const glm::mat4& vpMatrix = camera.GetViewProjectionMatrix();
    glm::mat4 expectedVP = projMatrix * viewMatrix;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_FLOAT_EQ(vpMatrix[i][j], expectedVP[i][j]);
        }
    }
}

TEST(OrthographicCamera, Translation) {
    Nebula::OrthographicCamera camera(-1.6f, 1.6f, -0.9f, 0.9f);

    // Set a new position and verify
    glm::vec3 newPosition(1.0f, 2.0f, 3.0f);
    camera.SetPosition(newPosition);
    EXPECT_EQ(camera.GetPosition(), newPosition);

    // The view matrix should now be a translation matrix
    const glm::mat4& viewMatrix = camera.GetViewMatrix();

    // For a view matrix, the translation components should be negated
    // The translation appears in the last column of the inverse of the translation matrix
    EXPECT_FLOAT_EQ(viewMatrix[3][0], -newPosition.x);
    EXPECT_FLOAT_EQ(viewMatrix[3][1], -newPosition.y);
    EXPECT_FLOAT_EQ(viewMatrix[3][2], -newPosition.z);
}

TEST(OrthographicCamera, Rotation) {
    Nebula::OrthographicCamera camera(-1.6f, 1.6f, -0.9f, 0.9f);

    // Set a rotation and verify view matrix changes
    float rotation = 45.0f; // 45 degrees
    camera.SetRotation(rotation);

    // The view matrix should now include rotation
    const glm::mat4& viewMatrix = camera.GetViewMatrix();

    // Manually create a rotation matrix for comparison
    float rad = glm::radians(rotation);
    float cosTheta = cos(rad);
    float sinTheta = sin(rad);

    // In a 2D rotation around Z, we expect these values in a rotation matrix
    EXPECT_NEAR(viewMatrix[0][0], cosTheta, 0.001f);
    EXPECT_NEAR(viewMatrix[0][1], sinTheta, 0.001f);
    EXPECT_NEAR(viewMatrix[1][0], -sinTheta, 0.001f);
    EXPECT_NEAR(viewMatrix[1][1], cosTheta, 0.001f);
}

TEST(OrthographicCamera, TransformationChain) {
    Nebula::OrthographicCamera camera(-1.6f, 1.6f, -0.9f, 0.9f);

    // Apply multiple transformations
    glm::vec3 position(1.0f, 2.0f, 0.0f);
    float rotation = 30.0f;

    camera.SetPosition(position);
    camera.SetRotation(rotation);

    // The view projection matrix should transform a point correctly
    const glm::mat4& vpMatrix = camera.GetViewProjectionMatrix();

    // Create a test point
    glm::vec4 testPoint(0.5f, 0.5f, 0.0f, 1.0f);

    // Transform the point using the VP matrix
    glm::vec4 transformedPoint = vpMatrix * testPoint;

    // Create expected transformation manually
    float rad = glm::radians(rotation);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -rad, glm::vec3(0, 0, 1));
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -position);
    glm::mat4 projectionMatrix = glm::ortho(-1.6f, 1.6f, -0.9f, 0.9f, -1.0f, 1.0f);

    glm::mat4 expectedVP = projectionMatrix * translationMatrix * rotationMatrix;
    glm::vec4 expectedPoint = expectedVP * testPoint;

    // Compare results
    EXPECT_NEAR(transformedPoint.x, expectedPoint.x, 0.001f);
    EXPECT_NEAR(transformedPoint.y, expectedPoint.y, 0.001f);
    EXPECT_NEAR(transformedPoint.z, expectedPoint.z, 0.001f);
    EXPECT_NEAR(transformedPoint.w, expectedPoint.w, 0.001f);
}