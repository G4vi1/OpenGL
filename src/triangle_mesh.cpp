#include "triangle_mesh.h"
#include <vector>
#include <glad/glad.h>

TriangleMesh::TriangleMesh() {
    std::vector<float> data = {

        /*Cada linha é um vértice, interprete cada uma como Vértice((x, y, z), (cor1, cor2, cor3))
        como são 3 vértices(afinal é um triângulo) cada linha representa um diferente.*/
        
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    vertex_count = 3;

    /*Cria o VAO: um objeto que registra como os 
    dados dos vértices serão registrados pelo OpenGL*/
    glGenVertexArrays(1, &VAO);
    //VAO é selecionado
    glBindVertexArray(VAO);

    /*Cria um VBO: buffer que armazenará os dados na GPU.*/
    glGenBuffers(1, &VBO);
    //VBO é selecionado
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Calcula o número de bites
    size_t bufferSize = data.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, data.data(), 
            GL_STATIC_DRAW);

    //posição
    glVertexAttribPointer(0, 3, GL_FLOAT, 
            GL_FALSE, 24, (void*)0);
    glEnableVertexAttribArray(0);

    //cores
    glVertexAttribPointer(1, 3, GL_FLOAT, 
            GL_FALSE, 24, (void*)12);
    glEnableVertexAttribArray(1);
}

void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
