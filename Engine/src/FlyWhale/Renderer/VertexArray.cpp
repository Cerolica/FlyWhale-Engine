#include "fwpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace FlyWhale
{

    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:     FW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL:   return new OpenGLVertexArray();  
        }

        FW_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

}