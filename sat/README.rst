=================
 Proyecto 4: SAT
=================

Integrantes
===========
 + 04-36723 - Daniel Barreto
 + 05-38675 - Kristoffer Pantic

Requerimientos
==============
S�lo python > 2.5.2, creo, y zChaff 2007.3.12

Instalaci�n
===========
Cambiar la variable `ZCHAFF_PATH` que se encuentra en el inicio del
archivo *solver.py*, ah� se coloca el path completo hacia la carpeta
que contiene el ejecutable de zchaff. Si esta variable se omite, por
defecto el ejecutable se buscar� en './zchaff/zchaff' (relativo a la
carpeta de ejecuci�n del proyecto).

Si se quiere hacer que cualquiera de los programas devuelva el formato
de salida de zchaff s�lo hay que cambiar la variable `FORMAT_OUTPUT`
al inicio del archivo *solver.py*.

Reglas de traducci�n
====================
Sudoku
------
Hablar sobre sudIndex y cnfIndex, sobre que representa cada variable

Card Puzzle
-----------
Hablar sobre que representa cada variable y sobre su interpretaci�n
en el resultado

Solitario
---------
Bastante parecido al sudoku, kizas mencionar porque es importante
utilizar una variable para cuando no hay ninguna metra en una posici�n
dada

Sudoku Hard
===========
Se adjuntan en el archivo sudoku-hard-statistics.
