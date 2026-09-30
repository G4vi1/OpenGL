#include "config.h"

using namespace std;

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

        /* Mostra na tela o que foi desenhado no framebuffer.
        A janela normalmente utiliza dois buffers:
        Um que está sendo exibido outro onde estamos 
        desenhando, O SwapBuffers troca os dois.*/

        glfwSwapBuffers(window);
    }

    // Finaliza o GLFW e libera os recursos utilizados por ele.

    glfwTerminate();
    return 0;
}