#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <mutex>

using namespace std;

// Número de líneas por hilo
const int linesPerThread = 1;

// Mutex para sincronizar la salida en la consola
mutex mtx;

// // Función para contar palabras en una línea
// void contarPalabras(string linea, int& contador) {
//     // Contar palabras en la línea
//     int palabras = 0;
//     size_t pos = 0;
//     while ((pos = linea.find_first_not_of(' ', pos)) != string::npos) {
//         ++palabras;
//         pos = linea.find_first_of(' ', pos);
//     }

//     // Incrementar el contador total
//     mtx.lock(); // Bloquear el mutex antes de imprimir
//     contador += palabras;
//     mtx.unlock(); // Desbloquear el mutex después de imprimir
// }

int main() {

    //Cola para almacenar los hilos disponibles
    queue<thread> hilos;

    cout << "\n\tIngrese el texto. Ctrl+D para finalizar." << endl;

    int contador = 0;

    while (!cin.eof()) {

        string linea;
        getline(cin, linea);
        contador++;

        //Asignar cada linea leida a un hilo que debe estar encolado
        cout << "Linea #" << contador << ": \t" << linea << endl;

    }

    //Join para que los hilos terminen bien
    // for (auto& t : threads) {
    //     t.join();
    // }

    // Imprimir el total de palabras
    cout << "\n\nTotal de palabras: " << contador << endl;

    return 0;
}