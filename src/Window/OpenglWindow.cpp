#include "OpenglWindow.h"

// Constructor
OpenglWindow::OpenglWindow(const char* windowName, int windowWidth, int windowHeight)
{
    // Create window
    SetWindowName(windowName);
    SetWindowSize(windowWidth, windowHeight);
    if (!CreateWindow()) 
        std::cout << "ERROR: OpenglWindow.CreateWindow failed." << std::endl;
}

OpenglWindow::OpenglWindow(const char* windowName, const Image& image)
{
    // Create window
    SetWindowName(windowName);
    SetWindowSize(image.m_width, image.m_height);
    if (!CreateWindow())
        std::cout << "ERROR: OpenglWindow.CreateWindow failed." << std::endl;

    // Immediately draw an image
    DrawImage(image);
}

OpenglWindow::OpenglWindow(const char* windowName, const RTSettings& raytraceSettings)
{
    // Create window
    SetWindowName(windowName);
    SetWindowSize(raytraceSettings.ImageWidth, raytraceSettings.ImageHeight);
    if (!CreateWindow())
        std::cout << "ERROR: OpenglWindow.CreateWindow failed." << std::endl;
}

void OpenglWindow::SetWindowName(const char* windowName) {
    m_windowName = windowName;
}

void OpenglWindow::SetWindowSize(int width, int height) {
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

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return false;
}

void OpenglWindow::DrawImage(const Image& image)
{
}

void OpenglWindow::ClearWindow(const Colour& fillColour)
{
}
