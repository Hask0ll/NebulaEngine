//
// Created by dobar on 2/27/2025.
//

#include "Nebula.h"
#include <gtest/gtest.h>

TEST(EventSystem, EventTypes) {
    // Test event type getters
    Nebula::WindowResizeEvent resizeEvent(1280, 720);
    EXPECT_EQ(resizeEvent.GetEventType(), Nebula::EventType::WindowResize);
    EXPECT_STREQ(resizeEvent.GetName(), "WindowResize");
    EXPECT_TRUE(resizeEvent.IsInCategory(Nebula::EventCategoryApplication));
    EXPECT_FALSE(resizeEvent.IsInCategory(Nebula::EventCategoryInput));

    Nebula::KeyPressedEvent keyEvent(65, 0); // 'A' key
    EXPECT_EQ(keyEvent.GetEventType(), Nebula::EventType::KeyPressed);
    EXPECT_STREQ(keyEvent.GetName(), "KeyPressed");
    EXPECT_TRUE(keyEvent.IsInCategory(Nebula::EventCategoryKeyboard));
    EXPECT_TRUE(keyEvent.IsInCategory(Nebula::EventCategoryInput));
    EXPECT_FALSE(keyEvent.IsInCategory(Nebula::EventCategoryMouse));
}

TEST(EventSystem, EventDispatcher) {
    Nebula::WindowResizeEvent resizeEvent(1280, 720);
    bool windowResizeHandled = false;

    Nebula::EventDispatcher dispatcher(resizeEvent);

    // Dispatch to the correct handler
    bool dispatchResult = dispatcher.Dispatch<Nebula::WindowResizeEvent>(
        [&windowResizeHandled](Nebula::WindowResizeEvent& e) {
            EXPECT_EQ(e.GetWidth(), 1280);
            EXPECT_EQ(e.GetHeight(), 720);
            windowResizeHandled = true;
            return true;
        }
    );

    EXPECT_TRUE(dispatchResult);
    EXPECT_TRUE(windowResizeHandled);
    EXPECT_TRUE(resizeEvent.IsHandled());

    // Try to dispatch to a wrong handler
    Nebula::KeyPressedEvent keyEvent(65, 0);
    Nebula::EventDispatcher keyDispatcher(keyEvent);

    bool wrongDispatchResult = keyDispatcher.Dispatch<Nebula::WindowResizeEvent>(
        [](Nebula::WindowResizeEvent& e) {
            return true;
        }
    );

    EXPECT_FALSE(wrongDispatchResult);
    EXPECT_FALSE(keyEvent.IsHandled());
}

TEST(EventSystem, MouseEvents) {
    // Mouse moved event
    Nebula::MouseMovedEvent movedEvent(100.0f, 200.0f);
    EXPECT_FLOAT_EQ(movedEvent.GetX(), 100.0f);
    EXPECT_FLOAT_EQ(movedEvent.GetY(), 200.0f);
    EXPECT_TRUE(movedEvent.IsInCategory(Nebula::EventCategoryMouse));

    // Mouse scrolled event
    Nebula::MouseScrolledEvent scrolledEvent(1.0f, -2.0f);
    EXPECT_FLOAT_EQ(scrolledEvent.GetXOffset(), 1.0f);
    EXPECT_FLOAT_EQ(scrolledEvent.GetYOffset(), -2.0f);

    // Mouse button events
    Nebula::MouseButtonPressedEvent pressedEvent(0); // Left button
    EXPECT_EQ(pressedEvent.GetMouseButton(), 0);
    EXPECT_TRUE(pressedEvent.IsInCategory(Nebula::EventCategoryMouseButton));

    Nebula::MouseButtonReleasedEvent releasedEvent(0);
    EXPECT_EQ(releasedEvent.GetMouseButton(), 0);
}

TEST(EventSystem, KeyEvents) {
    // Key pressed event
    Nebula::KeyPressedEvent keyPressed(65, 0); // 'A' key, no repeats
    EXPECT_EQ(keyPressed.GetKeyCode(), 65);
    EXPECT_EQ(keyPressed.GetRepeatCount(), 0);

    Nebula::KeyPressedEvent keyPressedRepeat(65, 3); // 'A' key, 3 repeats
    EXPECT_EQ(keyPressedRepeat.GetRepeatCount(), 3);

    // Key released event
    Nebula::KeyReleasedEvent keyReleased(65);
    EXPECT_EQ(keyReleased.GetKeyCode(), 65);

}

TEST(EventSystem, ApplicationEvents) {
    // Window close event
    Nebula::WindowCloseEvent closeEvent;
    EXPECT_EQ(closeEvent.GetEventType(), Nebula::EventType::WindowClose);

    // Window resize event
    Nebula::WindowResizeEvent resizeEvent(1280, 720);
    EXPECT_EQ(resizeEvent.GetWidth(), 1280);
    EXPECT_EQ(resizeEvent.GetHeight(), 720);

    // App tick event
    Nebula::AppTickEvent tickEvent;
    EXPECT_EQ(tickEvent.GetEventType(), Nebula::EventType::AppTick);

    // App update event
    Nebula::AppUpdateEvent updateEvent;
    EXPECT_EQ(updateEvent.GetEventType(), Nebula::EventType::AppUpdate);

    // App render event
    Nebula::AppRenderEvent renderEvent;
    EXPECT_EQ(renderEvent.GetEventType(), Nebula::EventType::AppRender);
}