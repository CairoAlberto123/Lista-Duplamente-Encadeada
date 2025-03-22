#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>
using namespace std;

/*
Código desenvolvido por: Cairo Alberto  
Estudante de Engenharia da Computação - PUC Goiás  
Repositório: https://github.com/CairoAlberto123  
Data de criação: 21/03/2025  
Descrição:  
Implementação de uma classe genérica de lista duplamente encadeada (não circular) com funções de inserção, remoção, movimentação interna (move) e deslocamento de um nó para outra lista (deslocate).  
Tecnologias utilizadas:  
Linguagem C++  
Licença: MIT  
2025 Cairo Alberto - Todos os direitos reservados.  
*/

/*---------------------------------------------------------------
 * Template da estrutura Node
 * Descrição: Representa um nó da lista, contendo o dado e ponteiros
 *            para o próximo e o nó anterior.
 * Glossário:
 *    - data: armazena o valor do nó.
 *    - next: ponteiro para o próximo nó da lista.
 *    - prev: ponteiro para o nó anterior da lista.
 *---------------------------------------------------------------*/
template <typename T>
struct Node {
    T data;            // Dado armazenado no nó
    Node<T>* next;     // Ponteiro para o próximo nó
    Node<T>* prev;     // Ponteiro para o nó anterior

    // Construtor que inicializa o nó com o valor fornecido
    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

/*---------------------------------------------------------------
 * Classe DoublyLinkedList
 * Descrição: Implementa uma lista duplamente encadeada com diversas
 *            operações, como inserção, remoção, movimentação e 
 *            deslocamento de nós entre listas.
 *---------------------------------------------------------------*/
template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;   // Ponteiro para o primeiro nó da lista
    int size;        // Número de elementos presentes na lista

    // Método auxiliar para obter o nó na posição index.
    // Lança exceção se o índice estiver fora dos limites.
    Node<T>* getNodeAt(int index) const {
        if (index < 0 || index >= size)
            throw out_of_range("Índice fora dos limites da lista.");
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }

    // Método auxiliar para buscar um nó com o valor especificado.
    // Retorna o ponteiro para o nó ou nullptr se não encontrar.
    Node<T>* getNodeByValue(const T& value) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value)
                return current;
            current = current->next;
        }
        return nullptr; // Caso o valor não seja encontrado
    }

    // Método auxiliar para remover (desanexar) um nó específico.
    // Atualiza os ponteiros da lista e libera a memória.
    void removeNode(Node<T>* node) {
        if (node == nullptr)
            throw runtime_error("Operação inválida: nó nulo.");
        if (node == head) { // Se o nó a ser removido é o primeiro da lista
            head = node->next;
            if (head != nullptr)
                head->prev = nullptr;
        } else {
            node->prev->next = node->next;
            if (node->next != nullptr)
                node->next->prev = node->prev;
        }
        delete node;
        size--;
    }

    // Método auxiliar para inserir um nó já criado em uma posição específica.
    // Não aloca nova memória, apenas insere o nó fornecido.
    void insertNodeAt(Node<T>* node, int index) {
        if (index < 0 || index > size)
            throw out_of_range("Índice fora dos limites da lista.");
        if (index == 0) { // Inserção no início
            node->next = head;
            node->prev = nullptr;
            if (head != nullptr)
                head->prev = node;
            head = node;
        } else {
            // Insere o nó antes do nó atualmente na posição 'index'
            Node<T>* refNode = getNodeAt(index);
            node->prev = refNode->prev;
            node->next = refNode;
            refNode->prev->next = node;
            refNode->prev = node;
        }
        size++;
    }

public:
    // Construtor da lista: inicializa uma lista vazia.
    DoublyLinkedList() : head(nullptr), size(0) {}

    // Destrutor: remove todos os nós e libera a memória.
    ~DoublyLinkedList() {
        while (head != nullptr) {
            popFirst();
        }
    }

    /*---------------------------------------------------------------
     * Função push()
     * Descrição: Insere um novo elemento no final da lista.
     * Parâmetro:
     *    - value: valor a ser inserido.
     *---------------------------------------------------------------*/
    void push(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            // Percorre até o último nó
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
        size++;
    }

    /*---------------------------------------------------------------
     * Função pushFirst()
     * Descrição: Insere um novo elemento no início da lista.
     * Parâmetro:
     *    - value: valor a ser inserido.
     *---------------------------------------------------------------*/
    void pushFirst(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        newNode->prev = nullptr;
        if (head != nullptr)
            head->prev = newNode;
        head = newNode;
        size++;
    }

    /*---------------------------------------------------------------
     * Função push(refValue, side)
     * Descrição: Insere um novo nó à direita ('d') ou à esquerda ('r')
     *            do nó que contenha refValue.
     * Parâmetros:
     *    - refValue: valor de referência para localizar o nó.
     *    - side: 'd' para inserir à direita, 'r' para inserir à esquerda.
     *---------------------------------------------------------------*/
    void push(const T& refValue, char side) {
        Node<T>* refNode = getNodeByValue(refValue);
        if (refNode == nullptr)
            throw runtime_error("Valor de referência não encontrado na lista.");
        // Obtém a posição do nó de referência
        int idx = 0;
        Node<T>* current = head;
        while (current != nullptr && current != refNode) {
            current = current->next;
            idx++;
        }
        // Reaproveita a sobrecarga abaixo para inserir à direita ou à esquerda
        push(idx, refValue, side);
    }

    /*---------------------------------------------------------------
     * Função push(index, value, side)
     * Descrição: Insere um novo nó com 'value' à direita ('d') ou à
     *            esquerda ('r') do nó na posição index.
     * Parâmetros:
     *    - index: posição do nó de referência.
     *    - value: valor a ser inserido.
     *    - side: 'd' para inserir à direita, 'r' para inserir à esquerda.
     *---------------------------------------------------------------*/
    void push(int index, const T& value, char side) {
        if (index < 0 || index >= size)
            throw out_of_range("Índice fora dos limites da lista.");
        Node<T>* refNode = getNodeAt(index);
        Node<T>* newNode = new Node<T>(value);
        if (side == 'd') {
            // Inserir à direita: após o nó de referência
            newNode->prev = refNode;
            newNode->next = refNode->next;
            if (refNode->next != nullptr)
                refNode->next->prev = newNode;
            refNode->next = newNode;
        } else if (side == 'r') {
            // Inserir à esquerda: antes do nó de referência
            newNode->next = refNode;
            newNode->prev = refNode->prev;
            if (refNode->prev != nullptr)
                refNode->prev->next = newNode;
            refNode->prev = newNode;
            if (refNode == head)
                head = newNode;
        } else {
            delete newNode;
            throw invalid_argument("Parâmetro 'side' inválido. Use 'd' para direita ou 'r' para esquerda.");
        }
        size++;
    }

    /*---------------------------------------------------------------
     * Função insertAt()
     * Descrição: Insere um novo nó com 'value' na posição especificada.
     * Parâmetro:
     *    - index: posição onde inserir (0 para início, size para final).
     *    - value: valor a ser inserido.
     *---------------------------------------------------------------*/
    void insertAt(int index, const T& value) {
        if (index < 0 || index > size)
            throw out_of_range("Índice fora dos limites da lista.");
        if (index == 0) {
            pushFirst(value);
        } else if (index == size) {
            push(value);
        } else {
            Node<T>* newNode = new Node<T>(value);
            Node<T>* refNode = getNodeAt(index);
            newNode->prev = refNode->prev;
            newNode->next = refNode;
            refNode->prev->next = newNode;
            refNode->prev = newNode;
            size++;
        }
    }

    /*---------------------------------------------------------------
     * Função pop()
     * Descrição: Remove o último elemento da lista.
     *---------------------------------------------------------------*/
    void pop() {
        if (size == 0)
            throw underflow_error("Lista vazia. Não há elementos para remover.");
        if (size == 1) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr)
                current = current->next;
            current->prev->next = nullptr;
            delete current;
        }
        size--;
    }

    /*---------------------------------------------------------------
     * Função popFirst()
     * Descrição: Remove o primeiro elemento da lista.
     *---------------------------------------------------------------*/
    void popFirst() {
        if (head == nullptr)
            throw underflow_error("Lista vazia. Não há elementos para remover.");
        Node<T>* temp = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        delete temp;
        size--;
    }

    /*---------------------------------------------------------------
     * Função popByValue()
     * Descrição: Remove o nó que contenha o valor especificado.
     * Parâmetro:
     *    - value: valor que será buscado para remoção.
     *---------------------------------------------------------------*/
    void popByValue(const T& value) {
        Node<T>* node = getNodeByValue(value);
        if (node == nullptr)
            throw runtime_error("Valor não encontrado na lista.");
        removeNode(node);
    }

    /*---------------------------------------------------------------
     * Função popByValue(value, side)
     * Descrição: Remove o nó à direita ('d') ou à esquerda ('r') do nó
     *            que contenha o valor especificado.
     *---------------------------------------------------------------*/
    void popByValue(const T& value, char side) {
        Node<T>* refNode = getNodeByValue(value);
        if (refNode == nullptr)
            throw runtime_error("Valor de referência não encontrado na lista.");
        if (side == 'd') {
            if (refNode->next == nullptr)
                throw runtime_error("Não há nó à direita para remover.");
            removeNode(refNode->next);
        } else if (side == 'r') {
            if (refNode->prev == nullptr)
                throw runtime_error("Não há nó à esquerda para remover.");
            removeNode(refNode->prev);
        } else {
            throw invalid_argument("Parâmetro 'side' inválido. Use 'd' para direita ou 'r' para esquerda.");
        }
    }

    /*---------------------------------------------------------------
     * Função pop(index, side)
     * Descrição: Remove o nó à direita ('d') ou à esquerda ('r') do nó
     *            na posição index.
     *---------------------------------------------------------------*/
    void pop(int index, char side) {
        if (size < 2)
            throw runtime_error("Não é possível remover nó adjacente em uma lista com um único elemento.");
        Node<T>* refNode = getNodeAt(index);
        if (side == 'd') {
            if (refNode->next == nullptr)
                throw runtime_error("Não há nó à direita para remover.");
            removeNode(refNode->next);
        } else if (side == 'r') {
            if (refNode->prev == nullptr)
                throw runtime_error("Não há nó à esquerda para remover.");
            removeNode(refNode->prev);
        } else {
            throw invalid_argument("Parâmetro 'side' inválido. Use 'd' para direita ou 'r' para esquerda.");
        }
    }

    /*---------------------------------------------------------------
     * Função popAt()
     * Descrição: Remove o nó na posição especificada e retorna seu valor.
     * Parâmetro:
     *    - index: posição do nó a ser removido.
     * Retorno:
     *    - valor do nó removido.
     *---------------------------------------------------------------*/
    T popAt(int index) {
        Node<T>* node = getNodeAt(index);
        T value = node->data;
        removeNode(node);
        return value;
    }

    /*---------------------------------------------------------------
     * Função move()
     * Descrição: Move o nó da posição 'index' para a nova posição 'newIndex'
     *            dentro da mesma lista.
     *---------------------------------------------------------------*/
    void move(int index, int newIndex) {
        if (index < 0 || index >= size)
            throw out_of_range("Índice original fora dos limites da lista.");
        if (newIndex < 0 || newIndex > size - 1)
            throw out_of_range("Novo índice fora dos limites da lista.");
        if (index == newIndex)
            return; // Sem alteração
        // Obtém o nó que será movido
        Node<T>* movingNode = getNodeAt(index);
        // Desanexa o nó da lista (sem deletar)
        if (movingNode == head) {
            head = movingNode->next;
            if (head != nullptr)
                head->prev = nullptr;
        } else {
            movingNode->prev->next = movingNode->next;
            if (movingNode->next != nullptr)
                movingNode->next->prev = movingNode->prev;
        }
        size--; // Ajusta o tamanho temporariamente

        // Se o nó removido estava antes da nova posição, ajusta newIndex
        if (index < newIndex)
            newIndex--;

        // Reinsere o nó na nova posição
        if (newIndex == 0) {
            movingNode->next = head;
            movingNode->prev = nullptr;
            if (head != nullptr)
                head->prev = movingNode;
            head = movingNode;
        } else {
            Node<T>* refNode = getNodeAt(newIndex);
            movingNode->prev = refNode->prev;
            movingNode->next = refNode;
            refNode->prev->next = movingNode;
            refNode->prev = movingNode;
        }
        size++;
    }

    /*---------------------------------------------------------------
     * Operador []
     * Descrição: Permite acesso ao elemento pelo índice, para leitura
     *            e escrita.
     *---------------------------------------------------------------*/
    T& operator[](int index) {
        Node<T>* node = getNodeAt(index);
        return node->data;
    }

    /*---------------------------------------------------------------
     * Função get()
     * Descrição: Retorna o valor do elemento na posição especificada.
     *---------------------------------------------------------------*/
    T get(int index) const {
        Node<T>* node = getNodeAt(index);
        return node->data;
    }

    /*---------------------------------------------------------------
     * Função set()
     * Descrição: Define o valor do elemento na posição especificada.
     *---------------------------------------------------------------*/
    void set(int index, const T& value) {
        Node<T>* node = getNodeAt(index);
        node->data = value;
    }

    /*---------------------------------------------------------------
     * Função length()
     * Descrição: Retorna o número de elementos presentes na lista.
     *---------------------------------------------------------------*/
    int length() const {
        return size;
    }

    /*---------------------------------------------------------------
     * Função print()
     * Descrição: Imprime o elemento na posição especificada.
     *---------------------------------------------------------------*/
    void print(int index) const {
        try {
            T value = get(index);
            cout << "Elemento no índice " << index << ": " << value << endl;
        } catch (const exception& e) {
            cout << "Erro ao imprimir: " << e.what() << endl;
        }
    }

    /*---------------------------------------------------------------
     * Função printAll()
     * Descrição: Imprime todos os elementos da lista.
     *---------------------------------------------------------------*/
    void printAll() const {
        if (head == nullptr) {
            cout << "Lista vazia." << endl;
            return;
        }
        Node<T>* current = head;
        cout << "Elementos da lista: ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr)
                cout << " -> ";
            current = current->next;
        }
        cout << endl;
    }
};

/*---------------------------------------------------------------
 * Função template deslocate()
 * Descrição: Desloca o nó do índice 'index' da lista 'source'
 *            para a posição 'newIndex' na lista 'dest'.
 * Parâmetros:
 *    - source: lista de origem.
 *    - dest: lista de destino.
 *    - index: posição do nó a ser removido na lista de origem.
 *    - newIndex: posição onde o nó será inserido na lista de destino.
 *---------------------------------------------------------------*/
template <typename T>
void deslocate(DoublyLinkedList<T>& source, DoublyLinkedList<T>& dest, int index, int newIndex) {
    // Remove o nó da lista de origem e captura seu valor
    T data = source.popAt(index);
    // Insere o valor na lista de destino na posição especificada
    dest.insertAt(newIndex, data);
}

#endif // DOUBLY_LINKED_LIST_H
