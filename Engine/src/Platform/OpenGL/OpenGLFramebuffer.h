#pragma once

#include "FlyWhale/Renderer/Framebuffer.h"

namespace FlyWhale
{

    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFramebuffer();

        void Invalidate();
        virtual void Bind() override;
        virtual void Unbind() override;

        virtual void Resize(const Vector2& size) override;
        virtual void Resize(uint32_t width, uint32_t height) override;

        virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorTexture? m_ColorTexture->GetRendererID() : 0; }
        virtual Ref<Texture2D> GetColorAttachmentTexture2D() const override { return m_ColorTexture; }

        virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
    private:
        uint32_t m_RendererID = 0;
        uint32_t m_DepthAttachment = 0;
        Ref<Texture2D> m_ColorTexture;
        FramebufferSpecification m_Specification;
    };
}