#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <mutex>

using namespace std;

// Mutex para sincronizar la salida en la consola
pthread_mutex_t mtx;

// Definir el total de hilos a usar
#define TOTAL_THREADS 4

// Cola para almacenar los hilos disponibles
queue<thread> hilosDisponibles;

// Funcion X, en un futuro aqui se van a leer los datos
void funcionHilo() {

    // Realizar alguna tarea aquí...

    // Aquí simplemente mostramos un mensaje
    {
        pthread_mutex_lock(&mtx);
        cout << "\nHilo " << this_thread::get_id() << " ejecutando..." << endl;
        pthread_mutex_unlock(&mtx);
    }

    // Dormir para simular alguna tarea
    this_thread::sleep_for(chrono::milliseconds(1000));
}

int main() {

    // Definir cuantos hilos se van a usar, una constante o una variable que define cuántos hilos se van a crear
    pthread_t threads[TOTAL_THREADS];

    //Inicialización de Mutex para evitar errores de sincronización
    pthread_mutex_init(&mtx, NULL);
    
    // Vector de hilos
    std::vector<std::thread> vectorHilos;

    // Crear los hilos sin asignarles una función
    pthread_mutex_lock(&mtx);
    for (int i = 0; i < TOTAL_THREADS; ++i) {
        hilosDisponibles.emplace(funcionHilo);
        // emplace_back: Construye un nuevo objeto directamente en el lugar del final del vector, pasando los argumentos necesarios al 
        // constructor del objeto. Esto significa que no se realiza una copia ni un movimiento del objeto, sino que se crea directamente 
        // en el contenedor. Es útil cuando estás construyendo objetos en el lugar y no quieres hacer una copia adicional.
    }
    pthread_mutex_unlock(&mtx);

    cout << "Hilos creados y encolados para su uso." << endl;

    

    // Ahora, puedes obtener un hilo disponible de la cola y asignarle una tarea
    // Supongamos que deseamos utilizar un hilo para imprimir un mensaje


    cout << "\n\tIngrese el texto. Ctrl+D para finalizar.\n" << endl;
    int contador = 0;
    while (!cin.eof()) {

        string linea;
        getline(cin, linea);
        contador++;

        //Asignar cada linea leida a un hilo que debe estar encolado
        cout << "Linea #" << contador << ": \t" << linea << endl;

    }
    
    // Esperar a que todos los hilos terminen
    pthread_mutex_lock(&mtx);
    cout<<"\nUniendo hilos\n";
    contador = 1;
    while (!hilosDisponibles.empty()) {
        thread hilo = move(hilosDisponibles.front());
        hilosDisponibles.pop();
        hilo.join();
        cout<<"\tSe ha finalizado " << contador << " hilo."<<endl;
        contador++;
    }
    pthread_mutex_unlock(&mtx);



    // //Join para que los hilos terminen bien
    // // for (auto& t : threads) {
    // //     t.join();
    // // }

    // // Imprimir el total de palabras
    // cout << "\n\nTotal de palabras: " << contador << endl;

    //Destruir el mutex
    pthread_mutex_destroy(&mtx);
    return 0;
}