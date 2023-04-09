#include "OpenglWindow.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>

std::string OpenglWindow::ParseShaderFile(const std::string& filePath)
{
    //std::ifstream stream(filePath);
    //std::ifstream t(filePath);
    //std::stringstream stringStream << t.rdbuf();
    std::string file_content;
    std::getline(std::ifstream(filePath), file_content, '\0');
    return file_content;

}

// Compiles the shader and returns the shaders ID
unsigned int OpenglWindow::CompileGlShader(unsigned int type, const std::string& source)
{
    // Get the shader source code
    unsigned int shaderID = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    // Compile the shader source code
    glCompileShader(shaderID);

    // Check if compiling went ok or not
    int compileResult;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
    if (!compileResult)
    {
        // Print error message and return 0
        int msgLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &msgLength);
        char* errorMessage = (char*)alloca(msgLength * sizeof(char));
        glGetShaderInfoLog(shaderID, msgLength, &msgLength, errorMessage);
        std::cout << "ERROR: Failed to compile shader." << std::endl;
        std::cout << errorMessage << std::endl;
        glDeleteShader(shaderID);
        return 0;
    }

    // Return the shader ID
    return shaderID;
}

// Creates the gl shader program, returns its ID
unsigned int OpenglWindow::CreateGlShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // Create shader program
    unsigned int programID = glCreateProgram();
    // Compile shader source files
    unsigned int vertShader = CompileGlShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragShader = CompileGlShader(GL_FRAGMENT_SHADER, fragmentShader);
    // Attach compiled shaders to shader program and link
    glAttachShader(programID, vertShader);
    glAttachShader(programID, fragShader);
    glLinkProgram(programID);
    glValidateProgram(programID);
    // Delete shaders after program has been created
    glDeleteShader(vertShader); glDeleteShader(fragShader);

    // Return shader program ID
    return programID;
}

// Constructor
OpenglWindow::OpenglWindow(const char* windowName, int windowWidth, int windowHeight)
{
    // Create window
    SetWindowName(windowName);
    SetWindowSize(windowWidth, windowHeight);
    if (!CreateWindow()) 
        std::cout << "ERROR: OpenglWindow.CreateWindow something went wrong." << std::endl;
}
// Constructor
OpenglWindow::OpenglWindow(const char* windowName, const Image& image)
{
    // Create window
    SetWindowName(windowName);
    SetWindowSize(image.m_width, image.m_height);
    if (!CreateWindow())
        std::cout << "ERROR: OpenglWindow.CreateWindow something went wrong." << std::endl;

    // Immediately draw an image
    DrawImage(image);
}
// Constructor
OpenglWindow::OpenglWindow(const char* windowName, const RTSettings& raytraceSettings)
{
    // Create window
    SetWindowName(windowName);
    SetWindowSize(raytraceSettings.ImageWidth, raytraceSettings.ImageHeight);
    if (!CreateWindow())
        std::cout << "ERROR: OpenglWindow.CreateWindow something went wrong." << std::endl;
}

void OpenglWindow::SetWindowName(const char* windowName) 
{
    m_windowName = windowName;
}

void OpenglWindow::SetWindowSize(int width, int height) 
{
    m_windowHeight = height;
    m_windowWidth = width;
}

// Actual window making stuff
bool OpenglWindow::CreateWindow()
{
    GLFWwindow* window;

    if (!glfwInit())
        return false;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowName, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

    if (glewInit() != GLEW_OK)
        std::cout << "ERROR: GLEW is not OK" << std::endl;
    if (glewInit() == GLEW_OK)
        std::cout << "GLEW_OK" << std::endl;


    // Vertex positions
    float positions[6] = {
        -0.5f, -0.5f,
        -0.5f,  0.5f,
         0.5f, -0.5f
    };

    // Create vertex buffers
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    // Tell opgnl the vertex size
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

    // Attach shaders to the drawcall
    std::string vertexShaderSrc = ParseShaderFile("src/Window/GLShaders/Vertexshader.shader");
    std::string fragmentShaderSrc = ParseShaderFile("src/Window/GLShaders/TextureFill.shader");
    unsigned int shaderProgram = CreateGlShader(vertexShaderSrc, fragmentShaderSrc);
    glUseProgram(shaderProgram);


    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangles
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return false;
}

void OpenglWindow::DrawImage(const Image& image)
{

}

void OpenglWindow::ClearWindow(const Colour& fillColour)
{

}
