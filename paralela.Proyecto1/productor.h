// Encabezado
#ifndef productor_h
#define productor_h

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
#include "unirTablas.h"

using namespace std;

class productor {
public:
  /**
   * Función productor que envía líneas de texto convertidas a minúsculas a un
   * canal de entrada.
   *
   * @param canalStrings Puntero al canal de entrada donde se envían las líneas
   * de texto.
   */
  void productorFunction(Channel<string> *canalStrings) {
    // Mensaje de instrucción para el usuario
    //cerr << "\n\tIngrese el texto. Ctrl+D para finalizar.\n" << endl;

    // Bucle para leer líneas de texto de la entrada estándar
    string linea;
    while (getline(cin, linea)) {
      // Convertir la línea a minúsculas usando transform y luego enviarla al
      // canal de entrada
      transform(linea.begin(), linea.end(), linea.begin(), ::tolower);
      canalStrings->sendChannel(linea);
    } // End while

    // Cerrar el canal cuando el productor termina de enviar líneas de texto
    canalStrings->close();
  }    // End productorFunction
};     // End class productor
#endif // End encabezado