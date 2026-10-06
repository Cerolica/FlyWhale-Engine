#include <FlyWhale.h>

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public FlyWhale::Layer
{
public:
    ExampleLayer() 
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
    {
        m_VertexArray.reset(FlyWhale::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };

        std::shared_ptr<FlyWhale::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(FlyWhale::VertexBuffer::Create(vertices, sizeof(vertices)));

        
        FlyWhale::BufferLayout layout = {
            { FlyWhale::ShaderDataType::Float3, "a_Position" },
            { FlyWhale::ShaderDataType::Float4, "a_Color" }
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3]={ 0, 1, 2  };
        std::shared_ptr<FlyWhale::IndexBuffer> indexBuffer;
        indexBuffer.reset(FlyWhale::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA.reset(FlyWhale::VertexArray::Create());

        float squareVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f, 
             0.5f, -0.5f, 0.0f, 
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
        };

        std::shared_ptr<FlyWhale::VertexBuffer> squareVB;
        squareVB.reset(FlyWhale::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        
        squareVB->SetLayout({
            { FlyWhale::ShaderDataType::Float3, "a_Position" }
        });

        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6]={ 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<FlyWhale::IndexBuffer> squareIB;
        squareIB.reset(FlyWhale::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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

        m_Shader.reset(new FlyWhale::Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
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

        std::string blueShaderFragmentSrc = R"(
            #version 330 core

            in vec3 v_Position;

            layout(location = 0) out vec4 color;

            void main()
            {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }

        )";

        m_BlueShader.reset(new FlyWhale::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
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

        for (int y = 0; y < 20; y++)
            for (int x = 0; x < 20; x++) 
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                FlyWhale::Renderer::Submit(m_BlueShader,  m_SquareVA, transform);
            }
        FlyWhale::Renderer::Submit(m_Shader, m_VertexArray);

        FlyWhale::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {

    }

    void OnEvent(FlyWhale::Event& event) override
    {
    } 
private:
    std::shared_ptr<FlyWhale::Shader> m_Shader;
    std::shared_ptr<FlyWhale::VertexArray> m_VertexArray;

    std::shared_ptr<FlyWhale::Shader> m_BlueShader;
    std::shared_ptr<FlyWhale::VertexArray> m_SquareVA;

    FlyWhale::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 1.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 15.0f;
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