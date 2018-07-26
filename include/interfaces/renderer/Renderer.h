#pragma once

class RenderComponent;

class Renderer {

public:
    /// Initialize renderer
    /// Call it after constructing the single instance
    virtual void init() = 0;

    /// Register a new render component (weak pointer)
    virtual void registerRenderComponent(RenderComponent* renderComponent) = 0;

    /// Unregister a render component (weak pointer)
    virtual void unregisterRenderComponent(RenderComponent* renderComponent) = 0;

    /// Clear screen buffer
    virtual void clear() const = 0;

    /// Render through all render components
    virtual void render() = 0;

    /// Draw a square from corner (x, y) and size (w, h) toward bottom-right
    virtual void drawSquare(float x, float y, float w, float h) = 0;
};
