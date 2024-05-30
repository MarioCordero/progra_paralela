// Encabezado
#ifndef unirTablas_h
#define unirTablas_h

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

using namespace std;

class unirTablas {
public:
  /**
   * Combina un hash local con un hash global, sumando los recuentos de palabras
   * comunes y agregando nuevas palabras al hash global.
   *
   * @param global El hash global al que se agregarán las palabras y recuentos
   * del hash local.
   * @param wordCount El hash local que se combinará con el hash global.
   */
  void mergeHash(unordered_map<string, int> &global,
                 const unordered_map<string, int> &wordCount) {
    // Iterar sobre el hash local
    for (const auto &pair : wordCount) {
      // Si la palabra ya existe en el hash global, sumar su recuento
      if (global.find(pair.first) != global.end()) {
        global[pair.first] += pair.second;
      } else {
        // Si la palabra no existe en el hash global, agregarla
        global[pair.first] = pair.second;
      } // End if
    }   // End for
  }     // End mergeHash

};     // End class unirTablas
#endif // End encabezado