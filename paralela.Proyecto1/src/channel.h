// Bibliotecas
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <optional>
#include <pthread.h>
#include <queue>
#include <thread>
#include <algorithm>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;

// Encabezado
#ifndef chanel_h
#define chanel_h

// Uso de plantillas para poder usar cualquier tipo de dato
template <typename T>

// Implementacion del canal
class Channel {
public:
  // Enviar valores al canal de los valores que se definan al instanciarla
  void sendChannel(T valorGenerico) {
    // Crear un candado
    lock_guard<mutex> lock(mtx);
    // Pusheo del valor a la cola
    colaGenerica.push(valorGenerico);
    // notify_one() despierta a uno de los hilos que está esperando en la
    // condición variable cond_var
    cond_var.notify_one();
  } // End sendChannel

  // Recibir(pop) los valores de la cola
  // "optional" representa un objeto que contiene un valor de tipo T o no
  // contiene valor (está vacío)
  optional<T> receiveChannel() {

    /* -[this] Captura el puntero this de la instancia actual de la clase, para
     * que pueda acceder a la queue
     * -[this] { return !queue.empty(); } expresión lambda que define la
     * condición que se debe cumplir para que el hilo deje de esperar Si la cola
     * está vacía, devuelve false y el hilo sigue esperando -lock Su propósito
     * principal es gestionar el mutex asociado (en este caso, mtx) para
     * asegurar que el acceso a la cola queue sea seguro y sincronizado entre
     * los hilos
     */

    unique_lock<mutex> lock(mtx);
    cond_var.wait(lock, [this] { return !colaGenerica.empty(); });
    T valorGenerico = colaGenerica.front();
    colaGenerica.pop();
    return valorGenerico;
  } // End receiveChannel

private:
  // Mutex
  mutex mtx;
  // Condicion de variable
  condition_variable cond_var;
  // La cola con cualquier tipo de dato
  queue<T> colaGenerica;
};     // End class Channel
#endif // End encabezado