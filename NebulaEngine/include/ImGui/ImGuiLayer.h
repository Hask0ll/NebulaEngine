#pragma once

#include "Layer/Layer.h"

namespace Nebula
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender();
		void static Begin();
		void static End();
	};
}
