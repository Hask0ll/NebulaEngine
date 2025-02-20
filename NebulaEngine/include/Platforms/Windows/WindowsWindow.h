#pragma once

#include <memory>

#include "window/Window.h"

namespace Nebula
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* NativeWindow() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		struct Internal;
		std::unique_ptr<Internal> m_impl;
		OpenGLContext* m_Context{};

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		} m_Data;

	};
}