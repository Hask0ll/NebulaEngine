#pragma once
#include "Core/Core.h"
#include "Layer/Layer.h"

namespace Nebula
{
    /**
     * @class LayerStack
     * @brief Manages a stack of Layer objects in the Nebula engine.
     *
     * The LayerStack class provides functionality to add, remove, and iterate over layers
     * and overlays in the engine.
     */
    class NEBULA LayerStack
    {
    public:
        /**
         * @brief Construct a new LayerStack object.
         */
        LayerStack();

        /**
         * @brief Destroy the LayerStack object.
         */
        ~LayerStack();

        /**
         * @brief Push a layer onto the stack.
         * @param layer Pointer to the Layer to be added.
         */
        void PushLayer(Layer* layer);

        /**
         * @brief Push an overlay onto the stack.
         * @param overlay Pointer to the Layer to be added as an overlay.
         */
        void PushOverlay(Layer* overlay);

        /**
         * @brief Remove a layer from the stack.
         * @param layer Pointer to the Layer to be removed.
         */
        void PopLayer(Layer* layer);

        /**
         * @brief Remove an overlay from the stack.
         * @param overlay Pointer to the Layer to be removed as an overlay.
         */
        void PopOverlay(Layer* overlay);

        /**
         * @brief Get an iterator to the beginning of the layer stack.
         * @return std::vector<Layer*>::iterator Iterator to the beginning of the stack.
         */
        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

        /**
         * @brief Get an iterator to the end of the layer stack.
         * @return std::vector<Layer*>::iterator Iterator to the end of the stack.
         */
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Layer*> m_Layers; /**< Vector storing all layers in the stack. */
        std::vector<Layer*>::iterator m_LayerInsert; /**< Iterator pointing to the insertion point for new layers. */
    };
}