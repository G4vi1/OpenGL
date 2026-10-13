#include "config.h"
#include "triangle_mesh.h"

using namespace std;

// Lê e compila um único arquivo GLSL (vertex ou fragment shader).
unsigned int make_module(const std::string& filepath, unsigned int module_type);

// Junta os dois módulos GLSL em um programa de shader que a GPU pode usar.
unsigned int make_shader(const std::string& vertex_filepath,
                         const std::string& fragment_filepath) {
    // Guardamos temporariamente os módulos separados nesta lista.
    std::vector<unsigned int> modules;

    // O vertex shader processa cada canto do triângulo.
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
    // O fragment shader define a cor de cada pixel do triângulo.
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

    // Cria o programa final e anexa os dois módulos a ele.
    unsigned int shader = glCreateProgram();
    for (unsigned int shaderModule : modules) {
        glAttachShader(shader, shaderModule);
    }
    glLinkProgram(shader);

    // Mostra no terminal caso os dois módulos não possam ser ligados.
    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        std::cout << "Shader linking error:\n" << errorLog << '\n';
    }

    // Após ligar o programa, os módulos separados podem ser liberados.
    for (unsigned int shaderModule : modules) {
        glDeleteShader(shaderModule);
    }
    return shader;
}

unsigned int make_module(const std::string& filepath, unsigned int module_type) {
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    // Lê todo o texto do arquivo GLSL.
    file.open(filepath);
    while (std::getline(file, line)) {
        bufferedLines << line << '\n';
    }
    std::string shaderSource = bufferedLines.str();
    const char* shaderSrc = shaderSource.c_str();
    file.close();

    // Cria o módulo na GPU, envia o texto e pede sua compilação.
    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    // Se houver erro no código GLSL, a mensagem aparecerá no terminal.
    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "Shader Module compilation error:\n"
                  << errorLog << std::endl;
    }
    return shaderModule;
}

int main() {

    //Inicializa a biblitoteca GLFW

    if (!glfwInit()) {
        cout << "Erro" << endl;
        return -1;
    }

    /*Diz ao GLFW qual versao do OpenGl queremos usar
    aqui no caso sendo OpenGl 3.3.*/

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /*Solicita o perfil "Core" do Open Gl.
    Este no caso sendo responsavel por usar a versao moderna
    do OpenGl e remove funcionalidades antigas/depreciadas*/

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    //Criacao da janela.

    GLFWwindow* window = glfwCreateWindow(
        640, //Largura
        480, //Altura
        "My Window", //Nome da janela
        NULL, // NULL -> monitor (NULL significa janela normal, nao fullscreen)
        NULL // NULL -> janela compartilhada (nao queremos compartilhar contexto)
    );
    

    //Verifica se a criacao da janela deu certo
    
    if (!window) {
        cout << "Falha ao criar a janela" << endl;

        // Libera os recursos que o GLFW inicializou.

        glfwTerminate();
        return -1;
    }

    /* Torna o contexto OpenGL dessa janela o contexto atual.
    O OpenGL precisa saber em qual janela/contexto ele
    deve executar os comandos. */

    glfwMakeContextCurrent(window);

     // Inicializa o GLAD.

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Falha ao iniciar o GLAD" << endl;
        glfwTerminate();
        return -1;
    }

     /*Define a cor que sera usada quando o framebuffer
    for limpo(aqui sera uma azulada)*/

    glClearColor(
        0.25f, //Red
        0.5f, //Green
        0.75f, //Blue
        1.0f    //Alpha
    );

    // O construtor de TriangleMesh cria o VAO/VBO e envia o triângulo à GPU.
    TriangleMesh* triangle = new TriangleMesh();

    // Lê e prepara as regras de desenho dos arquivos GLSL.
    unsigned int shader = make_shader(
        "shaders/vertex.txt",
        "shaders/fragment.txt"
    );

    /* Loop principal da aplicacao.
     Ele continua executando enquanto 
     o usuario nao fechar a janela. */

    while (!glfwWindowShouldClose(window)) {

        /* Verifica eventos do sistema operacional.
        Exemplos: o usuario teclou, clicou, moveu o mouse ou fechou a janela*/
        glfwPollEvents();

        /* Limpa o framebuffer usando a cor definida anteriormente
        // por glClearColor(). GL_COLOR_BUFFER_BIT significa: 
        // "limpe o buffer que contem as cores da imagem". */

        glClear(GL_COLOR_BUFFER_BIT);

        // Escolhe as regras de desenho e pede que o objeto desenhe seus 3 vértices.
        glUseProgram(shader);
        triangle->draw();

        /* Mostra na tela o que foi desenhado no framebuffer.
        A janela normalmente utiliza dois buffers:
        Um que está sendo exibido outro onde estamos 
        desenhando, O SwapBuffers troca os dois.*/

        glfwSwapBuffers(window);
    }

    // Libera o programa de shader da GPU e o objeto TriangleMesh.
    glDeleteProgram(shader);
    delete triangle;

    glfwTerminate();
    return 0;
}
