// Encabezado
#ifndef arregloClaves_h
#define arregloClaves_h

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
#include "ordenamientoMezcla.h"
#include "productor.h"
#include "unirTablas.h"

using namespace std;

class arregloClaves {
public:
  /**
   * Función para extraer las claves de una tabla hash y almacenarlas en un
   * vector.
   *
   * @param wordCount La tabla hash de la que se extraerán las claves.
   * @return Un vector que contiene todas las claves de la tabla hash.
   */
  vector<string> obtenerClaves(const unordered_map<string, int> &wordCount) {
    // Inicializa un vector para almacenar las claves
    vector<string> claves;

    // Itera sobre cada par (clave, valor) en la tabla hash
    for (const auto &par : wordCount) {
      // Agrega la clave actual al vector de claves
      claves.push_back(par.first);
    } // End for

    // Devuelve el vector que contiene todas las claves
    return claves;
  }    // End obtenerClaves
};     // End class arregloClaves
#endif // End encabezado