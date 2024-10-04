#include <string>
#include "Layer/Layer.h"

namespace Nebula
{
	Layer::Layer(const std::string& debugName) : m_DebugName(debugName)
	{

	}

	Layer::~Layer() = default;
}