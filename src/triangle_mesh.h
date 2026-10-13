#pragma once

class TriangleMesh {
    public:
        TriangleMesh();
        void draw();
        ~TriangleMesh();

    private:
        unsigned int VAO, VBO, vertex_count;
};