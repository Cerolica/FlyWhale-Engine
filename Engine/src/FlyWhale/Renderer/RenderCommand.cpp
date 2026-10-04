#include "fwpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace FlyWhale
{

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}