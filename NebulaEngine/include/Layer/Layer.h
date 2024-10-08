#pragma once
#include "Core/Core.h"
#include "Events/Event.h"
#include "TimeStep/TimeStep.h"

namespace Nebula
{
    /**
     * @class Layer
     * @brief Represents a layer in the Nebula engine.
     *
     * The Layer class is a base class for different layers in the engine.
     * It provides virtual methods for attaching, detaching, updating, and handling events.
     */
    class NEBULA Layer
    {
    public:
        /**
         * @brief Construct a new Layer object.
         * @param name The name of the layer (default is "Layer").
         */
        Layer(const std::string& name = "Layer");

        /**
         * @brief Destroy the Layer object.
         */
        virtual ~Layer();

        /**
         * @brief Called when the layer is attached to the engine.
         */
        virtual void OnAttach() {}

        /**
         * @brief Called when the layer is detached from the engine.
         */
        virtual void OnDetach() {}

        /**
         * @brief Called each frame to update the layer.
         * @param ts The time step since the last update.
         */
        virtual void OnUpdate(TimeStep ts) {}

        /**
         * @brief Called when an event occurs that this layer can handle.
         * @param event The event to be handled.
         */
        virtual void OnEvent(Event& event) {}

        /**
         * @brief Get the name of the layer.
         * @return const std::string& The name of the layer.
         */
        inline const std::string& GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName; /**< The debug name of the layer. */
    };
}