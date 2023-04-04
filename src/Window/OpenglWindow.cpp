#include "OpenglWindow.h"

// Constructor
OpenglWindow::OpenglWindow(std::string windowName, int windowWidth, int windowHeight)
{
    SetWindowName(windowName);
    SetWindowSize(windowWidth, windowHeight);

    // Create window
    if (!CreateWindow()) 
    {
        std::cout << "ERROR: OpenglWindow.CreateWindow failed." << std::endl;
    }
}

void OpenglWindow::SetWindowName(std::string windowName) {
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
    window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowName.c_str(), NULL, NULL);
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
