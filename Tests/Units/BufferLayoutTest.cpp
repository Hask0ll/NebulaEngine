//
// Created by dobar on 2/27/2025.
//

#include "Nebula.h"
#include <gtest/gtest.h>

TEST(BufferLayout, ElementProperties) {
    // Test buffer element constructor
    Nebula::BufferElement element(Nebula::ShaderDataType::Float3, "Position");
    EXPECT_EQ(element.Type, Nebula::ShaderDataType::Float3);
    EXPECT_EQ(element.Name, "Position");
    EXPECT_EQ(element.Size, 12); // 3 floats * 4 bytes
    EXPECT_EQ(element.Offset, 0);
    EXPECT_FALSE(element.Normalized);
    EXPECT_EQ(element.GetComponentCount(), 3);

    // Test other data types
    Nebula::BufferElement float4Element(Nebula::ShaderDataType::Float4, "Color");
    EXPECT_EQ(float4Element.Size, 16); // 4 floats * 4 bytes
    EXPECT_EQ(float4Element.GetComponentCount(), 4);

    Nebula::BufferElement intElement(Nebula::ShaderDataType::Int, "Index");
    EXPECT_EQ(intElement.Size, 4); // 1 int * 4 bytes
    EXPECT_EQ(intElement.GetComponentCount(), 1);

    Nebula::BufferElement boolElement(Nebula::ShaderDataType::Bool, "Active");
    EXPECT_EQ(boolElement.Size, 1); // 1 bool * 1 byte
    EXPECT_EQ(boolElement.GetComponentCount(), 1);
}

TEST(BufferLayout, OffsetsAndStride) {
    // Create a layout with multiple elements
    Nebula::BufferLayout layout = {
        { Nebula::ShaderDataType::Float3, "Position" },
        { Nebula::ShaderDataType::Float4, "Color" },
        { Nebula::ShaderDataType::Float2, "TexCoord" },
        { Nebula::ShaderDataType::Int, "EntityID" }
    };

    // Test stride calculation
    EXPECT_EQ(layout.GetStride(), 40); // 12 + 16 + 8 + 4 = 40 bytes

    // Test element offsets
    auto elements = layout.GetElements();
    EXPECT_EQ(elements[0].Offset, 0);
    EXPECT_EQ(elements[1].Offset, 12);
    EXPECT_EQ(elements[2].Offset, 28);
    EXPECT_EQ(elements[3].Offset, 36);

    // Test iterators
    int index = 0;
    for (const auto& element : layout) {
        EXPECT_EQ(element.Offset, elements[index].Offset);
        index++;
    }
    EXPECT_EQ(index, 4);
}

TEST(ShaderDataType, TypeSize) {
    // Test the ShaderDataTypeSize function
    EXPECT_EQ(Nebula::ShaderDataTypeSize(Nebula::ShaderDataType::Float), 4);
    EXPECT_EQ(Nebula::ShaderDataTypeSize(Nebula::ShaderDataType::Float2), 8);
    EXPECT_EQ(Nebula::ShaderDataTypeSize(Nebula::ShaderDataType::Float3), 12);
    EXPECT_EQ(Nebula::ShaderDataTypeSize(Nebula::ShaderDataType::Float4), 16);
    EXPECT_EQ(Nebula::ShaderDataTypeSize(Nebula::ShaderDataType::Mat3), 36);
    EXPECT_EQ(Nebula::ShaderDataTypeSize(Nebula::ShaderDataType::Mat4), 64);
    EXPECT_EQ(Nebula::ShaderDataTypeSize(Nebula::ShaderDataType::Int), 4);
    EXPECT_EQ(Nebula::ShaderDataTypeSize(Nebula::ShaderDataType::Int2), 8);
    EXPECT_EQ(Nebula::ShaderDataTypeSize(Nebula::ShaderDataType::Int3), 12);
    EXPECT_EQ(Nebula::ShaderDataTypeSize(Nebula::ShaderDataType::Int4), 16);
    EXPECT_EQ(Nebula::ShaderDataTypeSize(Nebula::ShaderDataType::Bool), 1);
    EXPECT_EQ(Nebula::ShaderDataTypeSize(Nebula::ShaderDataType::None), 0);
}