=================
 Proyecto 5: CSP
=================

Integrantes
===========
 + 04-36723 - Daniel Barreto
 + 05-38675 - Kristoffer Pantic

Requerimientos
==============
S�lo python > 2.4

Modo de ejecuci�n
=================
$> python crypto <OPERANDO1> <OPERANDO2> <RESULTADO>

$> python nreinas <NUMERO_DE_REINAS>

Comentarios *IMPORTANTES*
=========================
Para el programa nreinas se realizaron dos implementaciones: 

 + Una como un CSP normal en la cual se empieza con un tablero de
   reinas sin asignaci�n, y simplemente se van escongiendo reinas
   a ubicar usando la aproximaci�n MRV hasta conseguir todos los
   resultados

 + Y otra donde se realiz� un CSP con b�squeda local como se
   encuentra explicada en el libro de Norvig en la secci�n 5.3
   `Local Search for Constraint Satisfaction Problems`. Para esta
   implementaci�n se realiz� el algor�tmo `min_conflicts` y se
   puede resolver tableros de tama�o muy superior a los logrados
   con la otra implementaci�n, pero dando �nicamente una soluci�n.

Para ejecutar la segunda  implementaci�n explicada se tiene que correr
el siguiente comando:

$> python nqueens.py <NUMERO_DE_REINAS>

En el archivo nqueens.py se encuentran ambos algor�tmos, el primero
modelado dentro de una clase llamada NQueens y el segundo dentro de
otra clase llamada NQueensLS,

Comentarios menos importantes
=============================
Para la implementaci�n del programa crypto se realiz� un CSP sencillo
donde las estructuras usadas fueron:

 + *variables*: Conjunto de letras de las palabras ingresadas.
 + *asignaci�n*: Tabla de hash con letras como claves y numeros como
   valores.
 + *restricciones*: Tuplas que contienen �nicamente las
   letras/variables que forman parte de la restricci�n, colocadas en
   el orden en el cual estar�an en la restricci�n matem�tica. De esta
   forma, dependiendo de la longitud de la tupla se puede considerar
   la f�rmula matem�tica modelada as�:

   * 2 vars: V1 = W2
   * 3 vars: V1 + V/W2 = V3
   * 4 vars: V1 + V2 = V3 + 10xW4
   * 5 vars: V1 + V2 + W3 = V4 + 10xW5

   Donde las V's representan variables principales del problema y las
   W's representan variables auxiliares.
