#include <iostream>
using namespace std;

// f) Usar funciones recursivas para:
// g) Calcular cuántas generaciones hay

int calcularGeneraciones(Persona* persona) {

    if (persona->hijos.empty()) {
        return 1;
    }

    int maxGeneraciones = 0;

    for (Persona* hijo : persona->hijos) {

        int generaciones = calcularGeneraciones(hijo);

        if (generaciones > maxGeneraciones) {
            maxGeneraciones = generaciones;
        }
    }

    return maxGeneraciones + 1;
}

// f) Usar funciones recursivas para:
// h) Contar cuántos descendientes tiene Lucía

int contarDescendientes(Persona* persona) {

    int total = persona->hijos.size();

    for (Persona* hijo : persona->hijos) {
        total += contarDescendientes(hijo);
    }

    return total;
}

// i) Mostrar todos los hijos de una persona específica

void mostrarHijos(Persona* persona) {

    cout << "\nHijos de " << persona->nombre << ":" << endl;

    for (Persona* hijo : persona->hijos) {
        cout << "- " << hijo->nombre << endl;
    }
}

// i) Mostrar todos los nietos de una persona específica

void mostrarNietos(Persona* persona) {

    cout << "\nNietos de " << persona->nombre << ":" << endl;

    for (Persona* hijo : persona->hijos) {

        for (Persona* nieto : hijo->hijos) {
            cout << "- " << nieto->nombre << endl;
        }
    }
}