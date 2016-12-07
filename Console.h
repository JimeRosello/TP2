#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <iostream>
#include <limits>

/*
 * Devuelve el valor numerico ingresado por teclado.
 *
 * Pre:
 * Post:
 */
int RequestNumericInput();

/*
 * Devuelve una linea de texto ingresada por teclado.
 *
 * Pre: ---
 * Post: Devuelve una cadena con la linea ingresada.
 */
std::string RequestTextLineInput();

#endif /* CONSOLE_H_ */
