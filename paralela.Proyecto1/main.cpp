// Encabezados
#include "arregloClaves.h"
#include "channel.h"
#include "ordenamientoMezcla.h"
#include "productor.h"
#include "unirTablas.h"

// Bibliotecas
#include <algorithm>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <vector>

using namespace std;

// Mutex para sincronizar la salida en la consola.
pthread_mutex_t mtx;

// Definir el total de hilos a usar como el número de núcleos de la CPU
// disponibles.
#define TOTAL_THREADS sysconf(_SC_NPROCESSORS_ONLN)

// Mapa global que almacenará el recuento de palabras procesadas por todos los
// hilos.
unordered_map<string, int> global;

/**
 * Estructura para pasar los argumentos a los hilos, que principalmente incluye
 * el canal y el recuento de palabras.
 */
struct threadData {
  // Puntero al canal de entrada de texto.
  Channel<string> *lineas;

  // Puntero al mapa de recuento de palabras del hilo.
  unordered_map<string, int> *wordCount;
};

/**
 * Función que cuenta las palabras en las líneas recibidas de un canal de
 * entrada.
 *
 * @param threadDataPointer Puntero genérico que apunta a la estructura de datos
 * del hilo.
 * @return NULL al finalizar la ejecución del hilo.
 */
void *countWords(void *threadDataPointer) {
  // Recibe el puntero de datos del hilo y lo convierte al tipo correcto
  struct threadData *data = (struct threadData *)threadDataPointer;

  // Obtiene el canal de entrada y la tabla de conteo de palabras del hilo
  Channel<string> *lineas = data->lineas;
  unordered_map<string, int> *wordCount = data->wordCount;

  // Bucle principal del hilo para procesar líneas
  while (true) {
    // Bloquea el mutex antes de verificar el canal de entrada
    pthread_mutex_lock(&mtx);

    // Verifica si el canal está cerrado y no hay más datos, luego desbloquea el
    // mutex y sale del bucle
    if (lineas->isEmpty() && lineas->isClosed()) {
      // Desbloquea el mutex antes de salir
      pthread_mutex_unlock(&mtx);
      break;
    } // End if

    // Recibe una línea del canal de entrada y luego desbloquea el mutex
    auto valorGenerico = lineas->receiveChannel();
    // Desbloquea el mutex después de recibir el valor
    pthread_mutex_unlock(&mtx);

    // Procesa la línea recibida
    string linea = *valorGenerico;
    istringstream iss(linea);
    string word;

    // Divide la línea en palabras y las cuenta
    while (iss >> word) {
      (*wordCount)[word]++;
    } // End while
  }   // End while
  // Finaliza la ejecución del hilo y devuelve NULL
  pthread_exit(NULL);
} // End countWords

int main() {
  // Crear instancias:
  ordenamientoMezcla ordenamientoMezcla;
  productor productor;
  unirTablas unirTablas;
  arregloClaves arregloClaves;

  // Definir el número de hilos a utilizar según la cantidad de núcleos de la
  // CPU disponibles
  pthread_t threads[TOTAL_THREADS];

  // Inicialización del Mutex para evitar errores de sincronización
  pthread_mutex_init(&mtx, NULL);

  // Inicialización del canal de entrada de texto
  Channel<string> canalStrings;

  // Arreglo de estructuras para almacenar los datos de cada hilo
  threadData info[TOTAL_THREADS];

  // Arreglo de mapas para almacenar el recuento de palabras de cada hilo
  unordered_map<string, int> wordCounts[TOTAL_THREADS];

  // Creación de hilos para procesar el texto
  for (int i = 0; i < TOTAL_THREADS; i++) {
    info[i].lineas = &canalStrings;
    info[i].wordCount = &wordCounts[i];

    if (pthread_create(&threads[i], NULL, countWords, &info[i]) != 0) {
      perror("Error creating thread\n");
      return 1;
    } // End if
  }   // End for

  // Ingresar el texto al canal
  productor.productorFunction(&canalStrings);

  // Espera a que todos los hilos terminen su ejecución y fusiona los resultados
  for (int i = 0; i < TOTAL_THREADS; ++i) {
    pthread_join(threads[i], NULL);
    // Fusionar el recuento de palabras del hilo i con el recuento global
    pthread_mutex_lock(&mtx);
    unirTablas.mergeHash(global, wordCounts[i]);
    pthread_mutex_unlock(&mtx);
  } // End for

  // Obtener las claves del mapa global
  vector<string> claves = arregloClaves.obtenerClaves(global);
  // Ordenar las claves alfabéticamente
  ordenamientoMezcla.mergesort(claves);

  // Mostrar las claves ordenadas con su frecuencia
  //cerr << "\n\nPalabras ordenadas alfabéticamente:\n";
  for (const string &clave : claves) {
    cout << clave << ": " << global[clave] << "\n";
  } // End for

  // Destrucción del Mutex
  pthread_mutex_destroy(&mtx);
  return 0;
} // End main