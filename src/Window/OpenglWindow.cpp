#include "OpenglWindow.h"

#include <string>
#include <fstream>

// Parse .shader file as a string
std::string OpenglWindow::parseShaderFile(const std::string& filePath)
{
    std::string file_content;
    std::getline(std::ifstream(filePath), file_content, '\0');
    return file_content;
}

// Compiles the shader and returns the shaders ID
unsigned int OpenglWindow::compileGlShader(unsigned int type, const std::string& source)
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
unsigned int OpenglWindow::createGlShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // Create shader program
    unsigned int programID = glCreateProgram();
    // Compile shader source files
    unsigned int vertShader = compileGlShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragShader = compileGlShader(GL_FRAGMENT_SHADER, fragmentShader);
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

unsigned int OpenglWindow::createTexture(const Image& image)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    const int imageWidth  = image.m_width;
    const int imageHeight = image.m_height;
    const int coloursInImage = image.m_pixelClr.size();
    const int floatsInImage  = coloursInImage * 3;

    float* pixels = new float[floatsInImage];

    // Write rgb floats from the image colour vector and
    // copy it into the pixels array.
    // This conversion is also the biggest performance hit when it comes to
    // drawing the RT output to the viewport.
    std::vector<float> imagePixelfloats;
    for (int i = coloursInImage-1; i > 0; i--)
    {
        imagePixelfloats.push_back(image.m_pixelClr[i].r());
        imagePixelfloats.push_back(image.m_pixelClr[i].g());
        imagePixelfloats.push_back(image.m_pixelClr[i].b());
    }
    std::copy(imagePixelfloats.begin(), imagePixelfloats.end(), pixels);

    // Create opengl texture from pixels array
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_FLOAT, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    delete[] pixels;
    return textureID;
}

void OpenglWindow::createRectangle(unsigned int VAO, unsigned int VBO, unsigned int EBO)
{
    float vertices[] =
    {
        // positions          // colors           // uv
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] =
    {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Colour
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Constructor
OpenglWindow::OpenglWindow(const char* windowName, const Image& image)
{
    std::cout << std::endl << "Constructing Opengl window.." << std::endl;
    setWindowName(windowName);
    setWindowSize(image.m_width, image.m_height);
    if (!createWindow(image))
        std::cout << "ERROR: OpenglWindow.CreateWindow something went wrong." << std::endl;
}

void OpenglWindow::setWindowName(const char* windowName) 
{
    m_windowName = windowName;
}

void OpenglWindow::setWindowSize(int width, int height) 
{
    m_windowHeight = height;
    m_windowWidth = width;
}

// Actual window making stuff
bool OpenglWindow::createWindow(const Image& image)
{
    if (!glfwInit())
        return false;

    bool wireframe = false;

    // Create a windowed mode window and its OpenGL context
    m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowName, NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        return false;
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_window);

    std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;

    if (glewInit() != GLEW_OK)
        std::cout << "ERROR: GLEW is not OK" << std::endl;
    if (glewInit() == GLEW_OK)
        std::cout << "GLEW_OK" << std::endl;

    // Create buffers and rectangle
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    createRectangle(VAO, VBO, EBO);

    // Attach shaders to the drawcall
    std::string vertexShaderSrc = parseShaderFile("src/Window/GLShaders/Vertexshader.shader");
    std::string fragmentShaderSrc = parseShaderFile("src/Window/GLShaders/TextureFill.shader");
    unsigned int shaderProgram = createGlShader(vertexShaderSrc, fragmentShaderSrc);
    glUseProgram(shaderProgram);

    // Create a texture
    //Image image = Image::generateTestImage(m_windowWidth, m_windowHeight);
    unsigned int texture = createTexture(image);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(m_window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangles
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap front and back buffers
        glfwSwapBuffers(m_window);

        // Poll for and process events
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return false;
}

void OpenglWindow::clearWindow(const Colour& fillColour)
{
    std::cout << "Clearing Window" << std::endl;
    glClearColor(fillColour.r(), fillColour.g(), fillColour.b(), 1.0);
}
