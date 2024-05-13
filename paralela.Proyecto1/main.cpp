#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

const int BUFFER_SIZE = 8192; // Tamaño del buffer
const int LINES_PER_FILE = 20; // Número de líneas por archivo
mutex mtx; // Mutex para garantizar exclusión mutua en la escritura del archivo
int lineasTotales = 0; // Contador de líneas totales

// Función para leer datos y escribirlos en el archivo
void leerYGuardar(const string& nombreArchivo) {
    char buffer[BUFFER_SIZE];
    ifstream archivo;
    archivo.rdbuf()->pubsetbuf(0, 0); // Desactivar el buffer de entrada para evitar superposición con el buffer de salida

    while (true) {
        // Bloquear el acceso al archivo para evitar superposición
        mtx.lock();
        cin.read(buffer, BUFFER_SIZE);
        int numBytesLeidos = cin.gcount();
        mtx.unlock();

        // Comprobar si se alcanzó el final de la entrada estándar
        if (numBytesLeidos == 0)
            break;

        // Incrementar el contador de líneas
        int lineasLeidas = 0;

        // Bloquear el acceso al archivo para escribir
        mtx.lock();
        ofstream salida(nombreArchivo, ios::binary | ios::app); // Abrir el archivo en modo binario y adjuntar

        // Escribir el contenido del buffer en el archivo, contando las líneas
        for (int i = 0; i < numBytesLeidos; ++i) {
            salida.put(buffer[i]);
            if (buffer[i] == '\n') {
                ++lineasTotales;
                ++lineasLeidas;
                if (lineasTotales % LINES_PER_FILE == 0) {
                    salida.close();
                    string nuevoNombreArchivo = nombreArchivo.substr(0, nombreArchivo.find_last_of('.')) + "_" + to_string(lineasTotales / LINES_PER_FILE) + ".txt";
                    salida.open(nuevoNombreArchivo, ios::binary | ios::app);
                }
            }
        }

        salida.close(); // Cerrar el archivo
        mtx.unlock();
    }
}

int main() {
    string nombreArchivo = "Cola de texto/datos.txt"; // Nombre del archivo en el que se escribirán los datos
    vector<thread> threads; // Vector para almacenar los hilos

    cout << "Por favor, ingresa los datos. Presiona Ctrl+D (Linux/Mac) o Ctrl+Z (Windows) y Enter para finalizar." << endl;

    // Crear hilos para la lectura y escritura de datos
    for (int i = 0; i < 1; ++i) { // Solo un hilo para mantener el control sobre el contador de líneas
        threads.emplace_back(leerYGuardar, ref(nombreArchivo)); // Agregar un nuevo hilo al vector
    }

    // Esperar a que todos los hilos terminen
    for (auto& t : threads) {
        t.join();
    }

    cout << "Los datos se han escrito en archivos con nombres distintos." << endl;

    return 0;
}