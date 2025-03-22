Lista Duplamente Encadeada em C++
Este repositório contém a implementação de uma lista duplamente encadeada genérica em C++, oferecendo diversas operações essenciais, como inserção, remoção, movimentação interna e deslocamento de nós entre listas.

📌 Funcionalidades
Inserção:

push(value): Insere um novo nó no final da lista.
pushFirst(value): Insere um novo nó no início da lista.
push(index, value, side): Insere um nó antes ou depois de um índice especificado.
insertAt(index, value): Insere um nó em uma posição específica.
Remoção:

pop(): Remove o último nó da lista.
popFirst(): Remove o primeiro nó da lista.
popByValue(value): Remove um nó com um valor específico.
pop(index, side): Remove um nó à direita ou esquerda de um índice especificado.
popAt(index): Remove e retorna o nó de uma posição específica.
Movimentação e deslocamento:

move(index, newIndex): Move um nó para uma nova posição dentro da mesma lista.
deslocate(source, dest, index, newIndex): Move um nó de uma lista de origem para uma posição específica em uma lista de destino.
🛠️ Tecnologias Utilizadas
Linguagem: C++
Paradigma: Programação Orientada a Objetos (POO)
Estrutura de Dados: Lista Duplamente Encadeada
🚀 Como Usar
Clone o repositório: https://github.com/CairoAlberto123/Lista-Duplamente-Encadeada.git

Compile e execute o código:
g++ -std=c++11 nome_do_arquivo.cpp -o executavel ./executavel

📄 Licença
Este projeto está licenciado sob a MIT License – consulte o arquivo LICENSE para mais detalhes.
