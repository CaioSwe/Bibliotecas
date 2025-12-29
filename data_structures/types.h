#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdbool.h>

/**
 * Cabecalho destinado 'a declaracao de ponteiro de funcoes uteis para estruturas de dados
 * gene'ricas, como:
 *      Lista, Hash Table, Fila, Pilha, etc.
 * 
 * Bem como tambe'm a declaracao do tipo gene'rico Item, usado nas estruturas de dados gene'ricas.
 */

typedef void* Item;

/**
 * @brief Define um macro para supressao de warnings do tipo 'unused variable'
 */
#define UNUSED(x) (void)(x)

/**
 * @brief Funcao de liberacao de um item qualquer.
 * @return Nao ha' retorno de algum valor.
 */
typedef void (*freeFunc) (Item item, void* extra);

/**
 * @brief Compara dois itens e verifica sua igualdade.
 * @return Retorna um booleano indicando a igualdade dos itens comparados.
 */
typedef bool (*compararItens) (Item itemO, Item itemC);

/**
 * @brief Funcao de visualizacao de qualquer tipo de informacao.
 * @return Retorna um ponteiro de caracter (String).
 */
typedef char* (*printFunc) (void* item, void* extra);


/**
 * @brief Função de mapeamento que recebe um item e aplica uma operação sob ele.
 * @return Retorna o ponteiro para o item modificado.
 */
typedef Item (*mapFunction)(Item item, void* extra);

/**
 * @brief Função de co'pia de um item passado para co'pia de listas.
 * @return Retorna o endereço de memo'ria da co'pia criada pela função.
 */
typedef Item (*copyFunction)(Item item);

/**
 * @brief Funcao que recebe um item e aplica uma operacao qualquer sob ele sem modificacao.
 * @return Nao ha' retorno de algum valor.
 */
typedef void (*runThroughItems)(Item item, void* extra);

/**
 * @brief Funcao de liberacao de memo'ria convencional (free), com parametro adicional 'extra'
 * para passagem de parametro no caso do freeFunc.
 * @return Nao ha' retorno de algum valor.
 */
void freeReg(Item item, void* extra);

/**
 * @brief Checa se a alocacao foi feita corretamente.
 * @param var Varia'vel 'a ser inspecionada.
 * @param text Mensagem de erro caso ocorreu falha na alocacao.
 * @return Retorna um valor booleano: True, caso houve um erro. False, caso contra'rio.
 */
bool checkAllocation(void* var, const char* text);

#endif