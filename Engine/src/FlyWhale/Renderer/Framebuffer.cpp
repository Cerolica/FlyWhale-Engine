#include "fwpch.h"
#include "Framebuffer.h"

#include "FlyWhale/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace FlyWhale
{
    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:     FW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:   return CreateRef<OpenGLFramebuffer>(spec);
            
        }

        FW_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

}