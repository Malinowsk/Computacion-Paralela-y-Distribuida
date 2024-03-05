# Proyecto de Computación Paralela y Distribuida

Este proyecto fue desarrollado como parte de un trabajo para la asignatura de Computación Paralela y Distribuida. Se trata de un software implementado en lenguaje C utilizando OpenMP, que permite ejecutar algoritmos para calcular PI y realizar la multiplicación de matrices. El objetivo principal es explorar diferentes técnicas de paralelismo para observar mejoras en el tiempo de ejecución en hardware con múltiples procesadores.

## Ejecución del Programa

Para ejecutar el programa, asegúrate de tener permisos de ejecución para el archivo `ejecutable.sh`. En caso de no tenerlos, puedes concederlos con el comando:

* ``` chmod +x ejecutable.sh ```

Una vez que tengas los permisos adecuados, puedes ejecutar el programa mediante el siguiente comando en la consola:

* ```./ejecutable.sh```

También se proporciona un archivo Makefile que puedes utilizar para compilar el programa. Si tu distribución de Linux no tiene instalado Make, puedes instalarlo con el siguiente comando:

* ```sudo apt-get install make```

Luego, puedes compilar el programa ejecutando:

* ```make```

Esto generará un archivo binario llamado ejecutable, que puedes ejecutar con el siguiente comando:

* ```./ejecutable```

## Estructura del Repositorio

El repositorio está organizado de la siguiente manera:

- `/src`: Contiene el código fuente de las implementaciones paralelas de los algoritmos.
- `/Documents`: Documentación relacionada con el proyecto, como informes, análisis de rendimiento y tutoriales de uso.
- `README.md`: Este archivo que proporciona una descripción general del proyecto.


## Descripción de los Algoritmos

### Cálculo de PI

El algoritmo para calcular PI se basa en el método de Monte Carlo, que aproxima el valor de PI mediante la generación de puntos aleatorios dentro de un cuadrado. Para cada punto generado, se verifica si cae dentro de un círculo inscrito en el cuadrado. El valor de PI se estima dividiendo el número de puntos dentro del círculo entre el número total de puntos generados.

### Multiplicación de Matrices

El algoritmo de multiplicación de matrices utiliza el método convencional de producto escalar para generar una nueva matriz a partir de dos matrices de entrada. Cada hilo de ejecución se encarga de calcular una parte de la matriz resultante, lo que permite aprovechar el paralelismo y mejorar el rendimiento en hardware con múltiples procesadores.

## Análisis de Resultados

Se realizaron pruebas con diferentes técnicas de paralelismo para ambos algoritmos. Para el cálculo de PI, se compararon los tiempos de ejecución utilizando técnicas como `atomic`, `critical` y `reduction`. En el caso de la multiplicación de matrices, se evaluaron técnicas como la exclusión mutua, el uso de `reduction` y la planificación de tareas.

Los resultados mostraron que las técnicas de paralelismo tienen un impacto significativo en el rendimiento del programa, y que la elección de la técnica adecuada puede mejorar considerablemente el tiempo de ejecución en hardware con múltiples procesadores.

Para obtener más detalles sobre el análisis de resultados y las conclusiones obtenidas, consulta el informe completo en la carpeta `Documents`.

## Contribuciones

Las contribuciones son bienvenidas. Si deseas contribuir al proyecto, por favor sigue estos pasos:

1. Realiza un fork del repositorio.
2. Crea una rama nueva para tu funcionalidad (`git checkout -b feature/nueva-funcionalidad`).
3. Realiza tus cambios y haz commits explicativos (`git commit -am 'Agrega nueva funcionalidad: descripción corta'`).
4. Sube tus cambios a tu fork (`git push origin feature/nueva-funcionalidad`).
5. Crea un pull request para que tus cambios sean revisados.
