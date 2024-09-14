# Projeto: Paint em OpenGL

Este projeto consiste na construção de uma aplicação gráfica simples, semelhante ao "Paint", utilizando a biblioteca **OpenGL** com a linguagem de programação **C**. O aplicativo permite ao usuário criar e manipular objetos geométricos básicos (pontos, linhas e polígonos) e realizar transformações geométricas como translação, rotação, escala, reflexão e cisalhamento.

## Funcionalidades

- **Criação de objetos primários:**
    - Ponto
    - Segmento de reta (linha)
    - Polígono (sequência de cliques para definir vértices)

- **Transformações geométricas:**
    - Translação (mover objetos)
    - Rotação (em torno do centro do objeto)
    - Escala (aumentar ou diminuir o tamanho do objeto)
    - Reflexão
    - Cisalhamento

- **Seleção e exclusão de objetos geométricos:**
    - Seleção de objetos para manipulação
    - Exclusão de objetos selecionados

- **Manipulação de arquivos:**
    - Salvar objetos geométricos criados em um arquivo
    - Carregar objetos geométricos a partir de um arquivo

- **Eventos de entrada:**
    - Interação com mouse e teclado
    - Clique do mouse para criar objetos
    - Teclado para realizar transformações geométricas

## Tecnologias Utilizadas

- **Linguagem**: C
- **Biblioteca gráfica**: OpenGL (usando GLUT para manipulação de janelas e eventos)
- **CMake**: Para automatização do processo de compilação

## Requisitos

Para compilar e executar este projeto, você precisará:

- **OpenGL** e **GLUT** instalados.
- **CMake** para automatizar a compilação do projeto.
- Um compilador C (como GCC ou MinGW no Windows).

### Instalando Dependências

- **Windows (com MinGW)**: Instale o MinGW e adicione o caminho para as bibliotecas OpenGL e GLUT no arquivo `CMakeLists.txt`.

    - Certifique-se de ter o seguinte instalado no MinGW:
        - `opengl32`
        - `glu32`
        - `freeglut`

- **Linux**:
    - Você pode instalar as dependências necessárias com o comando:
      ```bash
      sudo apt-get install freeglut3-dev
      ```

- **MacOS**:
    - O OpenGL já está incluído no MacOS, mas você precisará instalar o **GLUT** usando Homebrew:
      ```bash
      brew install freeglut
      ```

## Como Compilar

1. **Clonar o repositório**:
    ```bash
    git clone <link_do_repositorio>
    ```

2. **Entrar na pasta do projeto**:
    ```bash
    cd paint_opengl
    ```

3. **Compilar o projeto usando CMake**:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

4. **Executar o programa**:
    ```bash
    ./questao2
    ```

## Instruções de Uso

- **Criação de objetos**:
    - Clique com o botão esquerdo do mouse para criar **pontos** na tela.
    - Clique duas vezes com o botão direito para criar uma **linha**.
    - Para **polígonos**, clique várias vezes com o botão esquerdo para definir os vértices, e pressione `Enter` para finalizar o polígono.

- **Transformações**:
    - Use as seguintes teclas do teclado para aplicar transformações no objeto selecionado:
        - `t`: Transladar o objeto.
        - `r`: Rotacionar o objeto.
        - `x`: Excluir o objeto selecionado.

- **Salvar e carregar**:
    - Pressione `s` para salvar os objetos em um arquivo.
    - Pressione `l` para carregar objetos a partir de um arquivo.

## Estrutura do Projeto

```bash
.
├── arquivos.c           # Funções para salvar e carregar objetos geométricos
├── arquivos.h
├── main.c               # Arquivo principal, ponto de entrada da aplicação
├── objetos.c            # Implementação de funções para criação e manipulação de objetos
├── objetos.h
├── transformacoes.c      # Implementação de transformações geométricas
├── transformacoes.h
├── CMakeLists.txt        # Arquivo de configuração do CMake
└── README.md             # Documentação do projeto
```
### Autores
Este projeto foi desenvolvido por:

Breno Mota do Nascimento
Email: breno.golo@gmail.com
Felipe Oliveira Rocha
Email: felipeoliveira02114@gmail.com
### Licença
Este projeto é de uso acadêmico e foi desenvolvido como parte de um trabalho da disciplina de Computação Gráfica da Universidade Federal do Cariri (UFCA). Todos os direitos estão reservados aos autores do projeto.