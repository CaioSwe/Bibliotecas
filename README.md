# Bibliotecas (Raylib)

Repositório especializado em funções úteis para o desenvolvimento de projetos baseados em Raylib (C-lang).

### Prerequisitos

Raylib e GCC.

A instalação do **Raylib** pode ser feita [aqui](https://www.raylib.com).
A instalação do **GCC** pode ser feita [aqui](https://sourceforge.net/projects/gcc-win64/).

## Como utilizar

1. Extrair Bibliotecas para o mesmo ambiente da pasta do projeto alvo.
2. Mover os arquivos Makefile e CMD para um nível abaixo da árvore de pastas.
3. Criar uma subpasta _src_ no projeto alvo com arquivos fonte.
4. Executar o CMD presente no repositório.
5. Compilar o projeto usando o comando ``` make DIR=./nomeDoProjeto ```.
6. Executar o programa com ``` ./nomeDoProjeto/nomeDoProjeto ```.

> [!IMPORTANT]
> Talvez o compilador reclame de _imports_ do raylib e algumas dependências. Para resolver, basta incluir os _paths_ presentes no _c_cpp_properties_ do repositório no _Include Path_ do compilador

## Exemplo de utilização

Seguindo os passos especificados no tópico anterior, a estrutura final de pastas deve ser conforme apresentada na imagem a seguir.

![Imagem de exemplo da estrutura final do projeto com a biblioteca.](/assets/exemplo-estrutura.png)

Após a organização da estrutura, é possível utilizar as funções presentes com a inclusão padrão da linguagem (por exemplo, ``` #include <animation.h> ```).
