// Encabezado
#ifndef ordenamientoMezcla_h
#define ordenamientoMezcla_h

// Bibliotecas
#include <algorithm>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <mutex>
#include <optional>
#include <pthread.h>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

// Encabezados
#include "channel.h"
#include "productor.h"
#include "unirTablas.h"

using namespace std;

// Implementacion del algoritmo de ordenamiento por mezcla
class ordenamientoMezcla {
public:
  /**
   * Combina dos subarreglos ordenados en uno solo.
   *
   * @param A El arreglo original que contiene los dos subarreglos ordenados que
   * se combinarán.
   * @param izquierda El índice de inicio del primer subarreglo.
   * @param divido El índice final del primer subarreglo y el inicio del segundo
   * subarreglo.
   * @param derecha El índice final del segundo subarreglo.
   */
  void merge(vector<string> &A, int izquierda, int divido, int derecha) {
    // Calcular los tamaños de los dos subarreglos a fusionar
    int tamano1 = divido - izquierda + 1;
    int tamano2 = derecha - divido;
    // Arreglos temporales para almacenar los elementos de los subarreglos
    vector<string> arreglo1(tamano1), arreglo2(tamano2);

    // Se copian los elementos de los subarreglos originales en los arreglos
    // temporales
    for (int i = 0; i < tamano1; i++) {
      arreglo1[i] = A[izquierda + i];
    } // Fin for

    for (int j = 0; j < tamano2; j++) {
      arreglo2[j] = A[divido + 1 + j];
    } // Fin for

    // Fusionar los dos arreglos temporales en el arreglo original
    int i = 0;
    int j = 0;
    int k = izquierda;

    while (i < tamano1 && j < tamano2) {
      if (arreglo1[i] <= arreglo2[j]) {
        A[k] = arreglo1[i];
        i++;
      } else {
        A[k] = arreglo2[j];
        j++;
      } // Fin if
      k++;
    } // Fin while

    // Copiar los elementos restantes del primer subarreglo, si hay
    while (i < tamano1) {
      A[k] = arreglo1[i];
      i++;
      k++;
    } // Fin while

    // Se copian los elementos restantes del segundo subarreglo, si hay
    while (j < tamano2) {
      A[k] = arreglo2[j];
      j++;
      k++;
    } // Fin while
  }   // Fin merge

  /**
   * Divide recursivamente el arreglo en subarreglos más pequeños, hasta que
   * cada subarreglo tenga uno o ningún elemento. Luego, combina los subarreglos
   * ordenados de manera consecutiva utilizando la función merge.
   *
   * @param A El arreglo que se va a ordenar.
   * @param inicio El índice de inicio del subarreglo que se va a ordenar.
   * @param final El índice final del subarreglo que se va a ordenar.
   */
  void mergeRecursivo(vector<string> &A, int inicio, int final) {
    // Verifica si el índice de inicio es menor que el índice final, indicando
    // que hay elementos en el subarreglo a ordenar
    if (inicio < final) {
      // Se calcula el punto medio del subarreglo
      int divido = inicio + (final - inicio) / 2;
      // Ordenar la primera mitad del subarreglo
      mergeRecursivo(A, inicio, divido);
      // Ordenar la segunda mitad del subarreglo
      mergeRecursivo(A, divido + 1, final);
      // Merge para combinar las dos mitades ordenadas del subarreglo
      merge(A, inicio, divido, final);
    } // Fin if
  }   // Fin mergeRecursivo

  /**
   * Algoritmo de ordenamiento Merge Sort.
   *
   * @param A El arreglo que se va a ordenar.
   */
  void mergesort(vector<string> &A) {
    // Llama al método mergeRecursivo para ordenar el arreglo A
    mergeRecursivo(A, 0, A.size() - 1);
  } // Fin mergesort

};     // End class ordenamientoMezcla
#endif // End encabezado