# README

## Implementación del Algoritmo PageRank

Este proyecto consiste en la implementación del algoritmo PageRank propuesto por Larry Page y Sergey Brin para clasificar la importancia de las páginas web. El algoritmo define la importancia de una página web en función del número de enlaces entrantes que recibe.

### Requisitos
- Archivo de entrada especificado con la bandera `-src`
- Archivo de salida especificado con la bandera `-dst`
- El archivo de salida debe estar ordenado alfabéticamente por URL
- Se debe utilizar la computación en paralelo en cada iteración para acelerar el cálculo

### Implementación
1. **Lectura del Archivo de Entrada**: El programa debe leer correctamente el archivo de entrada que contiene el formato `URL origen -> URL destino`.
2. **Escritura del Archivo de Salida**: El programa debe escribir correctamente el archivo de salida con una lista de URLs de origen ordenadas alfabéticamente, seguidas por el valor calculado de PageRank.
3. **Salida Correcta**: La salida debe ser precisa y reflejar los valores de PageRank para cada URL.
4. **Ejecución en Paralelo**: El programa debe paralelizar la ejecución de manera efectiva, escalando linealmente con un aumento en el número de núcleos.
5. **Gestión de Memoria**: No debe haber fugas de memoria ni accesos inválidos detectados por Valgrind.

### Documentación
1. **Funcionalidad**: Explicación detallada de cómo funciona el proyecto.
2. **Compilación**: Instrucciones detalladas sobre cómo compilar el proyecto.
3. **Ejecución**: Guía detallada sobre cómo ejecutar el programa.
4. **Límites**: Explicación de las limitaciones del proyecto.
5. **Problemas Conocidos**: Descripción de cualquier problema conocido con el proyecto.

### Entregables
- La entrega principal del proyecto es el domingo 30 de junio, a medianoche.
- Se debe utilizar un sistema de control de versiones como Git para el desarrollo del proyecto.
- Se permite el trabajo en grupo con un máximo de 3 miembros, asegurando una contribución equitativa de cada miembro.

### Evaluación
- **Implementación (75%)**:
  - Lectura correcta del archivo de entrada
  - Escritura correcta del archivo de salida
  - Corrección de la salida
  - Paralelización efectiva
  - Ausencia de fugas de memoria o accesos inválidos
- **Documentación (25%)**:
  - Explicación detallada de la funcionalidad del proyecto
  - Instrucciones de compilación
  - Guía de ejecución
  - Limitaciones del proyecto
  - Problemas conocidos

### Actualizaciones de Progreso
- Las actualizaciones de progreso contarán como cuestionarios y se programarán en clase.

Para cualquier pregunta adicional o aclaración, consulte el documento del proyecto proporcionado.
