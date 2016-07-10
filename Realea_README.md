# Sobre este documento #

Este proyecto contiene tres métodos de BL muy usados en optimización continua:

- Solis Wets.
- Simplex. 
- CMAES. 

## Compilación ##

El proyecto requiere:

- g++. 
- Make. 
- CMake.

Para compilar es necesario hacer:

`$ cmake .`
`$ make`

### Entorno de depuración ###

Por defecto compila para ejecutar más rápidamente, si se desea depurar es necesario hacer:

cmake -DCMAKE_BUILD_TYPE=Debug .

y luego compilar de nuevo con *make*.

## Pruebas ##

Como ejemplo de uso se ha ofrecido el programa example.cc, que refleja cómo se pueden 
usar los métodos de búsqueda local.

## Ficheros ##

Los ficheros de los tests son:

- cmaeshan, para el CMAES. 
- simplex, para el método Simplex. 
- solis, para el método Solis Wets. 

Adicionalmente, es necesario el uso de las siguientes clases:

- Random, para que los métodos de BL puedan generar los números aleatorios. 
- Domain, representa el espacio de búsqueda, usado para comprobar que
  las soluciones se encuentren siempre dentro de la búsqueda.
- Problem, para que la BL pueda evaluar soluciones, y conocer el espacio de búsqueda. 
- ProblemCEC2014, que permite obtener las distintas funciones (o problemas) del benchmark CEC'2014.

