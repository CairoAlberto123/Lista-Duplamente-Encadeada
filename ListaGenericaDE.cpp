/*
Código desenvolvido por: Cairo Alberto  
Estudante de Engenharia da Computação - PUC Goiás  
Repositório: https://github.com/CairoAlberto123  
Data de criação: 21/03/2025  
Descrição:  
Implementação de uma classe genérica de lista duplamente encadeada (não circular) com funções de inserção, remoção, movimentação interna (move) e deslocamento de um nó para outra lista (deslocate).  
As funções implementadas incluem:  
  - push (push(last)), pushFirst (push(first)), push(index, valor, side) e sobrecarga relativa a um valor de referência,  
  - pop (pop(last)), popFirst (pop(first)), popByValue, pop(index, side) e popAt,  
  - move(index, newIndex): move um nó para outra posição na mesma lista,  
  - insertAt(index, valor): insere um novo nó na posição especificada,  
  - popAt(index): remove e retorna o valor do nó na posição especificada,  
  - deslocate(source, dest, index, newIndex): desloca o nó do índice especificado de uma lista origem para uma posição específica de outra lista.  
Tecnologias utilizadas:  
Linguagem C++  
Licença: MIT  
2025 Cairo Alberto - Todos os direitos reservados.  
*/

#include "ListaGenericaDE.h"

//using namespacec std;//isso é apenas para esse exemplo, pode causar problemas

// Função principal para demonstrar o uso das funções move e deslocate
int main() {
    // Exemplo 1: Movimentação interna na mesma lista
    DoublyLinkedList<string> lista;
    lista.push("A"); 
    lista.push("B");
    lista.push("C");
    lista.push("D");
    cout << "Lista original:" << endl;
    lista.printAll(); // Exibe: A -> B -> C -> D

    // Move o nó do índice 1 ("B") para a posição 3
    lista.move(1, 3);
    cout << "\nApós mover nó do índice 1 para 3:" << endl;
    lista.printAll();

    // Exemplo 2: Deslocamento de nó entre duas listas
    DoublyLinkedList<string> listaOrigem;
    DoublyLinkedList<string> listaDestino;
    
    // Preenche a lista de origem
    listaOrigem.push("X");
    listaOrigem.push("Y");
    listaOrigem.push("Z");
    cout << "\nLista Origem antes do deslocate:" << endl;
    listaOrigem.printAll();
    
    // Preenche a lista de destino
    listaDestino.push("L");
    listaDestino.push("M");
    cout << "\nLista Destino antes do deslocate:" << endl;
    listaDestino.printAll();
    
    // Desloca o nó de índice 1 ("Y") da listaOrigem para a posição 1 da listaDestino
    deslocate(listaOrigem, listaDestino, 1, 1);
    cout << "\nApós deslocate:" << endl;
    cout << "Lista Origem:" << endl;
    listaOrigem.printAll();
    cout << "Lista Destino:" << endl;
    listaDestino.printAll();
    
    return 0;
}
