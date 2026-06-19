#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Persona {
    string nombre;
    string fechaNacimiento; // AAAA-MM-DD
    string relacion;
};

vector<Persona> familia;

// Registrar persona
void registrarPersona() {
    Persona p;

    cout << "Nombre: ";
    cin >> p.nombre;

    cout << "Fecha de nacimiento (AAAA-MM-DD): ";
    cin >> p.fechaNacimiento;

    cout << "Relacion familiar (Hijo, Nieto, etc.): ";
    cin >> p.relacion;

    familia.push_back(p);

    cout << "Persona registrada correctamente.\n";
}

// c) Mostrar generaciones en orden jerarquico
void mostrarGeneraciones() {
    cout << "\n=== Arbol Genealogico de Lucia ===\n";

    for (int i = 0; i < familia.size(); i++) {
        cout << "\nNombre: " << familia[i].nombre;
        cout << "\nFecha de nacimiento: " << familia[i].fechaNacimiento;
        cout << "\nRelacion familiar: " << familia[i].relacion;
        cout << "\n------------------------";
    }
}

// d) Buscar familiar por nombre
void buscarFamiliar() {
    string nombreBuscado;
    bool encontrado = false;

    cout << "Ingrese el nombre a buscar: ";
    cin >> nombreBuscado;

    for (int i = 0; i < familia.size(); i++) {
        if (familia[i].nombre == nombreBuscado) {
            cout << "\nFamiliar encontrado:\n";
            cout << "Nombre: " << familia[i].nombre << endl;
            cout << "Fecha de nacimiento: " << familia[i].fechaNacimiento << endl;
            cout << "Relacion familiar: " << familia[i].relacion << endl;

            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontro el familiar.\n";
    }
}

// e) Ordenar por fecha de nacimiento
bool compararFecha(Persona a, Persona b) {
    return a.fechaNacimiento < b.fechaNacimiento;
}

void ordenarDescendientes() {
    sort(familia.begin(), familia.end(), compararFecha);

    cout << "\nDescendientes ordenados por fecha de nacimiento:\n";

    for (int i = 0; i < familia.size(); i++) {
        cout << familia[i].nombre << " - "
             << familia[i].fechaNacimiento << " - "
             << familia[i].relacion << endl;
    }
}

int main() {
    int opcion;

    do {
        cout << "\n===== MENU =====";
        cout << "\n1. Registrar persona";
        cout << "\n2. Mostrar generaciones";
        cout << "\n3. Buscar familiar";
        cout << "\n4. Ordenar descendientes por fecha";
        cout << "\n5. Salir";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarPersona();
                break;

            case 2:
                mostrarGeneraciones();
                break;

            case 3:
                buscarFamiliar();
                break;

            case 4:
                ordenarDescendientes();
                break;

            case 5:
                cout << "Fin del programa.\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 5);

    return 0;
}