#include <iostream>
#include <string>
#include <queue>

using namespace std;

//Número de líneas por cola
const int linesPerElement = 1;

int main() {
    //Cola para almacenar las líneas de texto
    queue<string> cola;
    //Uso de String
    string linea;

    cout << "Ingrese el texto. Ctrl+D para finalizar." << endl;

    int contador = 0;

    while (getline(cin, linea)) {

        //Encolar la linea
        cola.push(linea);
        ++contador;

        //Sí el contador alcanza el límite, imprimir las líneas de la cola
        if (contador == linesPerElement) {

            cout << "\n\n Limite exedido. Contenido de la cola: \n\n";

            while (!cola.empty()) {
                //Imprimir la línea de la parte delantera de la cola
                cout << cola.front() << endl;
                //Eliminar la línea de la cola
                cola.pop();
            }
            //Reiniciar el contador
            contador = 0;
        }
    }

    // Imprimir las líneas restantes en la cola
    if (!cola.empty()) {
        cout << "\n\nContenido de la cola:\n\n";
        while (!cola.empty()) {
            cout << cola.front() << endl; // Imprimir la línea de la parte delantera de la cola
            cola.pop(); // Eliminar la línea de la cola
        }
    }

    return 0;
}