# Trabajo Practico de Criptografia - Comunicacion de datos
## Funcionamiento:
Dadas las tablas presentadas en el Trabajo Practico, calcula las semillas posibles y pide al usuario el mensaje encriptado y devuelve su valor desencriptado
El mensaje encriptado debe ser en letras minusculas y los simbolos contemplados en la Tabla 2, ya que es la unica que verifica la tabla de valores conocidos.
## Compilacion y Ejecucion:
Para compilar y correr se requiere algun compilador de C++ que soporte C++ 11 o posterior.
Si tiene CMake instalado puede compilar desde consola usando el comando:
`cmake -B build-dir && cmake --build build-dir`
## Funciones y Definiciones principales:
1. table1 y table2 definen las tablas candidatas que podrian verificar el mensaje.
    1. el indice de cada valor en una tabla corresponde al valor codificado.
2. testTable define la tabla de valores verificados.
3. mod(int, int) calcula el modulo de a en b, sea positivo o negativo.
3. tableIndexLookup(char, vec<char>) calcula el indice (osea, codificacion) de un caracter dado para una tabla dada.
4. calculateInverse(int, int) calcula el inverso modular de un numero, si existe, usando el algoritmo de euclides extendido.
5. calculateTableInverses(vec<char>) utiliza la funcion anterior para calcular todas las semillas posibles dado un tamanio de tabla.
6. testCypher(vec<char>, vec<pair<char, char>>, pair<int, int>, int) utiliza testTable para verificar si el conjunto de numero de formula y semilla es valido para desencriptar un mensaje.
7. generateValidSeeds(vec<char>, vec<pair<char, char>>, vec<pair<int, int>>, vec<int>) genera una lista con todas las combinaciones de numero de funcion y semilla que resuelvan los valores conocidos.
8. solveCypher(vec<char>, int, pair<int, int>>) toma el mensaje a desencriptar desde consola y devuelve el mensaje desencriptado.
