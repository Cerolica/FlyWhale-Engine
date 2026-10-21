#include <FlyWhale.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public FlyWhale::Layer
{
public:
    ExampleLayer() 
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
    {
        m_VertexArray = FlyWhale::VertexArray::Create();

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };

        FlyWhale::Ref<FlyWhale::VertexBuffer> vertexBuffer;
        vertexBuffer = FlyWhale::VertexBuffer::Create(vertices, sizeof(vertices));

        
        FlyWhale::BufferLayout layout = {
            { FlyWhale::ShaderDataType::Float3, "a_Position" },
            { FlyWhale::ShaderDataType::Float4, "a_Color" }
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3]={ 0, 1, 2  };
        FlyWhale::Ref<FlyWhale::IndexBuffer> indexBuffer;
        indexBuffer = FlyWhale::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA = FlyWhale::VertexArray::Create();

        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        FlyWhale::Ref<FlyWhale::VertexBuffer> squareVB;
        squareVB = FlyWhale::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
        
        squareVB->SetLayout({
            { FlyWhale::ShaderDataType::Float3, "a_Position" },
            { FlyWhale::ShaderDataType::Float2, "a_TexCoord" }
        });

        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6]={ 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<FlyWhale::IndexBuffer> squareIB;
        squareIB = FlyWhale::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position + 0.5;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }

        )";

        std::string fragmentSrc = R"(
            #version 330 core

            in vec3 v_Position;
            in vec4 v_Color;

            layout(location = 0) out vec4 color;

            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }

        )";

        m_Shader = FlyWhale::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

        std::string flatColorShaderVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position + 0.5;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }

        )";

        std::string flatColorShaderFragmentSrc = R"(
            #version 330 core

            in vec3 v_Position;

            uniform vec3 u_Color;

            layout(location = 0) out vec4 color;

            void main()
            {
                color = vec4(u_Color, 1.0f);
            }

        )";

        m_FlatColorShader = FlyWhale::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

        auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

        m_Texture = FlyWhale::Texture2D::Create("assets/textures/Checkerboard.png");
        m_ChernoLogoTexture = FlyWhale::Texture2D::Create("assets/textures/ChernoLogo.png");


        std::dynamic_pointer_cast<FlyWhale::OpenGLShader>(textureShader)->Bind();
        std::dynamic_pointer_cast<FlyWhale::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

    }

    void OnUpdate(FlyWhale::Timestep ts) override
    {
        FW_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

        if (FlyWhale::Input::IsKeyPressed(FW_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        
        if (FlyWhale::Input::IsKeyPressed(FW_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed * ts;

        if (FlyWhale::Input::IsKeyPressed(FW_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;
        
        if (FlyWhale::Input::IsKeyPressed(FW_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed * ts;

        if (FlyWhale::Input::IsKeyPressed(FW_KEY_A))
            m_CameraRotation += m_CameraRotationSpeed * ts;
        
        if (FlyWhale::Input::IsKeyPressed(FW_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed * ts;  

        FlyWhale::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        FlyWhale::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        FlyWhale::Renderer::BeginScene(m_Camera);

        static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<FlyWhale::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<FlyWhale::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);


        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++) 
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                FlyWhale::Renderer::Submit(m_FlatColorShader,  m_SquareVA, transform);
            }
        }

        auto textureShader = m_ShaderLibrary.Get("Texture");

        m_Texture->Bind();
        FlyWhale::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_ChernoLogoTexture->Bind();
        FlyWhale::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // Triangle
        //FlyWhale::Renderer::Submit(m_Shader, m_VertexArray);

        FlyWhale::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(FlyWhale::Event& event) override
    {
    } 
private:
    FlyWhale::ShaderLibrary m_ShaderLibrary;
    FlyWhale::Ref<FlyWhale::Shader> m_Shader;
    FlyWhale::Ref<FlyWhale::VertexArray> m_VertexArray;

    FlyWhale::Ref<FlyWhale::Shader> m_FlatColorShader;
    FlyWhale::Ref<FlyWhale::VertexArray> m_SquareVA;

    FlyWhale::Ref<FlyWhale::Texture2D> m_Texture, m_ChernoLogoTexture;

    FlyWhale::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 1.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 15.0f;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public FlyWhale::Application 
{
public:
    Sandbox() 
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {}
};

FlyWhale::Application* FlyWhale::CreateApplication() 
{
    return new Sandbox();
}