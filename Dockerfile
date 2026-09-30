FROM ubuntu:26.04

# Evita perguntas interativas durante a instalação de pacotes
ENV DEBIAN_FRONTEND=noninteractive

# Instala ferramentas de build e dependências de desenvolvimento do C++, OpenGL e GLFW
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libx11-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    && rm -rf /var/lib/apt/lists/*

# Define o diretório de trabalho dentro do container
WORKDIR /app

# Copia os arquivos do seu projeto para o container
COPY . .

# Cria a pasta de build, executa o CMake e compila o projeto
RUN mkdir -p build && cd build && cmake .. && make

# Comando executado ao rodar o container
# Lembre-se de substituir "meu_executavel" pelo nome definido no seu CMakeLists.txt (ex: add_executable(nome ...))
CMD ["./build/meu_executavel"]