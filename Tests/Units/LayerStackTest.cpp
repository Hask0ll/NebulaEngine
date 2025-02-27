//
// Created by dobar on 2/27/2025.
//

#include "Nebula.h"
#include <gtest/gtest.h>

// Mock layer for testing
class TestLayer : public Nebula::Layer {
public:
    TestLayer(const std::string& name) : Layer(name) {}

    bool attached = false;
    bool detached = false;
    bool updated = false;
    bool eventHandled = false;

    void OnAttach() override { attached = true; }
    void OnDetach() override { detached = true; }
    void OnUpdate(Nebula::TimeStep ts) override { updated = true; }
    void OnEvent(Nebula::Event& event) override { eventHandled = true; }
};

TEST(LayerStack, PushAndPopLayers) {
    Nebula::LayerStack stack;

    auto* layer1 = new TestLayer("Test Layer 1");
    auto* layer2 = new TestLayer("Test Layer 2");
    auto* overlay = new TestLayer("Test Overlay");

    // Test push layer
    stack.PushLayer(layer1);
    EXPECT_EQ(stack.begin(), stack.end() - 1);
    EXPECT_EQ(*stack.begin(), layer1);

    // Test push another layer
    stack.PushLayer(layer2);
    EXPECT_EQ(stack.begin(), stack.end() - 2);
    EXPECT_EQ(*stack.begin(), layer2);
    EXPECT_EQ(*(stack.begin() + 1), layer1);

    // Test push overlay
    stack.PushOverlay(overlay);
    EXPECT_EQ(*(stack.end() - 1), overlay);

    // Test pop layer
    stack.PopLayer(layer1);
    bool layerFound = false;
    for (auto it = stack.begin(); it != stack.end(); ++it) {
        if (*it == layer1) {
            layerFound = true;
            break;
        }
    }
    EXPECT_FALSE(layerFound);

    // Test pop overlay
    stack.PopOverlay(overlay);
    bool overlayFound = false;
    for (auto it = stack.begin(); it != stack.end(); ++it) {
        if (*it == overlay) {
            overlayFound = true;
            break;
        }
    }
    EXPECT_FALSE(overlayFound);

    // LayerStack destructor will delete layer2
}

TEST(Layer, Lifecycle) {
    auto* layer = new TestLayer("Lifecycle Test");

    layer->OnAttach();
    EXPECT_TRUE(layer->attached);

    layer->OnUpdate(Nebula::TimeStep(0.016f));
    EXPECT_TRUE(layer->updated);

    Nebula::WindowResizeEvent event(800, 600);
    layer->OnEvent(event);
    EXPECT_TRUE(layer->eventHandled);

    layer->OnDetach();
    EXPECT_TRUE(layer->detached);

    delete layer;
}