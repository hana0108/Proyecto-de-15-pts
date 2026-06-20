#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

// Clase Fecha: tipo de dato compuesto para representar una fecha DD/MM/AAAA
class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    // Constructor con valores por defecto: inicializa dia, mes y anio
    Fecha(int d = 1, int m = 1, int a = 1900)
        : dia(d), mes(m), anio(a) {}

    int getDia()  const { return dia;  }
    int getMes()  const { return mes;  }
    int getAnio() const { return anio; }

    void setDia(int d)  { dia  = d; }
    void setMes(int m)  { mes  = m; }
    void setAnio(int a) { anio = a; }

    // Compara si la fecha actual es anterior a 'otra'
    // Retorna true si anio/mes/dia es menor; false en caso contrario
    bool esAnteriorA(Fecha otra) const {
        if (anio != otra.anio) return anio < otra.anio;
        if (mes  != otra.mes)  return mes  < otra.mes;
        return dia < otra.dia;
    }

    // Muestra la fecha con formato DD/MM/AAAA usando cout
    void mostrar() const {
        cout << (dia  < 10 ? "0" : "") << dia  << "/"
             << (mes  < 10 ? "0" : "") << mes  << "/"
             << anio;
    }

    // Lee los valores de dia, mes y anio desde teclado con cin
    void leer() {
        cout << "    Dia  : "; cin >> dia;
        cout << "    Mes  : "; cin >> mes;
        cout << "    Anio : "; cin >> anio;
    }

    // Convierte la fecha a string con formato "DD/MM/AAAA"
    string aTexto() const {
        string d = (dia  < 10 ? "0" : "") + to_string(dia);
        string m = (mes  < 10 ? "0" : "") + to_string(mes);
        string a = to_string(anio);
        return d + "/" + m + "/" + a;
    }
};

// Clase Persona: representa un miembro de la familia en el arbol
// Usa composicion con Fecha y un vector de punteros para los hijos
class Persona {
private:
    string  nombre;
    Fecha   fechaNacimiento;
    string  relacion;
    vector<Persona*> hijos;  // punteros (*) a los hijos directos de esta persona

public:
    // Constructor: inicializa nombre, fecha de nacimiento y relacion familiar
    Persona(string n, Fecha f, string r)
        : nombre(n), fechaNacimiento(f), relacion(r) {}

    string  getNombre()   const { return nombre;          }
    Fecha   getFecha()    const { return fechaNacimiento; }
    string  getRelacion() const { return relacion;        }

    // Retorna referencia constante al vector de punteros a hijos
    const vector<Persona*>& getHijos() const { return hijos; }

    // Muestra nombre, fecha de nacimiento y relacion en consola
    void mostrarInfo() const {
        cout << "  Nombre    : " << nombre << endl;
        cout << "  Nacimiento: ";
        fechaNacimiento.mostrar();
        cout << endl;
        cout << "  Relacion  : " << relacion << endl;
    }

    // Recibe un puntero a Persona y lo agrega al vector de hijos
    // Permite construir la jerarquia del arbol enlazando nodos
    void agregarHijo(Persona* hijo) {
        hijos.push_back(hijo);
    }
};

// Arreglo estatico global para guardar el historial de busquedas (max 5)
const int MAX_HISTORIAL = 5;
string historialBusquedas[MAX_HISTORIAL];
int totalBusquedas = 0;

// Agrega un nombre al historial usando modulo para sobrescribir en ciclo
void agregarHistorial(const string& nombre) {
    historialBusquedas[totalBusquedas % MAX_HISTORIAL] = nombre;
    totalBusquedas++;
}

// Muestra todos los nombres guardados en el historial de busquedas
void mostrarHistorial() {
    cout << "\n--- Historial de busquedas ---\n";
    if (totalBusquedas == 0) {
        cout << "  (Sin busquedas realizadas aun)\n";
        return;
    }
    int cantidad = (totalBusquedas < MAX_HISTORIAL) ? totalBusquedas : MAX_HISTORIAL;
    for (int i = 0; i < cantidad; i++) {
        cout << "  " << (i + 1) << ". " << historialBusquedas[i] << endl;
    }
}

// Clase ArbolGenealogico: gestiona el arbol familiar completo
// Almacena un puntero raiz (*) y opera sobre el arbol de forma recursiva
class ArbolGenealogico {
private:
    Persona* raiz;  // puntero al nodo raiz del arbol (primer antepasado)

    // Funcion recursiva: calcula el numero total de generaciones del arbol
    // Caso base: nodo nulo o sin hijos -> retorna 1
    // Caso recursivo: retorna 1 + la generacion maxima entre todos sus hijos
    int calcularGeneraciones(Persona* p) const {
        if (p == nullptr || p->getHijos().empty()) return 1;
        int maxGen = 0;
        for (Persona* hijo : p->getHijos()) {
            int gen = calcularGeneraciones(hijo);
            if (gen > maxGen) maxGen = gen;
        }
        return maxGen + 1;
    }

    // Funcion recursiva: cuenta el total de descendientes de un nodo
    // Caso base: puntero nulo -> retorna 0
    // Caso recursivo: suma los hijos directos mas los descendientes de cada hijo
    int contarDescendientes(Persona* p) const {
        if (p == nullptr) return 0;
        int total = (int)p->getHijos().size();
        for (Persona* hijo : p->getHijos())
            total += contarDescendientes(hijo);
        return total;
    }

    // Funcion recursiva: busca un nodo por nombre recorriendo todo el arbol
    // Caso base 1: puntero nulo -> no encontrado, retorna nullptr
    // Caso base 2: nombre coincide -> retorna el puntero al nodo encontrado
    // Caso recursivo: busca en cada subárbol hijo y propaga el resultado
    Persona* buscarFamiliar(Persona* p, const string& nombre) const {
        if (p == nullptr) return nullptr;
        if (p->getNombre() == nombre) return p;
        for (Persona* hijo : p->getHijos()) {
            Persona* resultado = buscarFamiliar(hijo, nombre);
            if (resultado != nullptr) return resultado;
        }
        return nullptr;
    }

    // Funcion recursiva: muestra el arbol con sangria segun el nivel jerarquico
    // 'nivel' indica la profundidad del nodo; aumenta en cada llamada recursiva
    void mostrarArbol(Persona* p, int nivel) const {
        if (p == nullptr) return;
        for (int i = 0; i < nivel; i++) cout << "   ";
        cout << "|-- ";
        p->mostrarInfo();
        for (Persona* hijo : p->getHijos())
            mostrarArbol(hijo, nivel + 1);
    }

    // Funcion recursiva: recolecta todos los descendientes en un vector
    // Recorre el arbol en profundidad y agrega cada nodo hijo a 'lista'
    void recolectarDescendientes(Persona* p, vector<Persona*>& lista) const {
        if (p == nullptr) return;
        for (Persona* hijo : p->getHijos()) {
            lista.push_back(hijo);
            recolectarDescendientes(hijo, lista);
        }
    }

    // Muestra los hijos directos del nodo apuntado por 'p'
    void mostrarHijos(Persona* p) const {
        if (p->getHijos().empty()) {
            cout << "  " << p->getNombre() << " no tiene hijos registrados.\n";
            return;
        }
        cout << "\n  Hijos de " << p->getNombre() << ":\n";
        for (Persona* hijo : p->getHijos())
            cout << "    - " << hijo->getNombre() << endl;
    }

    // Muestra los nietos del nodo apuntado por 'p'
    // Recorre los hijos y luego los hijos de cada hijo (dos niveles)
    void mostrarNietos(Persona* p) const {
        bool tieneNietos = false;
        cout << "\n  Nietos de " << p->getNombre() << ":\n";
        for (Persona* hijo : p->getHijos()) {
            for (Persona* nieto : hijo->getHijos()) {
                cout << "    - " << nieto->getNombre() << endl;
                tieneNietos = true;
            }
        }
        if (!tieneNietos)
            cout << "  " << p->getNombre() << " no tiene nietos registrados.\n";
    }

    // Funcion recursiva: libera la memoria dinamica de todos los nodos
    // Recorre el arbol hasta las hojas y aplica delete de abajo hacia arriba
    void liberar(Persona* p) {
        if (p == nullptr) return;
        for (Persona* hijo : p->getHijos()) liberar(hijo);
        delete p;
    }

public:
    // Constructor: inicializa el puntero raiz en nullptr (arbol vacio)
    ArbolGenealogico() : raiz(nullptr) {}

    // Destructor: libera toda la memoria dinamica al destruir el objeto
    ~ArbolGenealogico() { liberar(raiz); }

    void setRaiz(Persona* p) { raiz = p; }
    Persona* getRaiz() const  { return raiz; }

    // Pide un nombre al usuario, lo busca en el arbol y muestra su informacion
    // Usa el puntero 'resultado' para verificar si el nodo fue encontrado
    void buscarFamiliar() const {
        string nombre;
        cout << "\n  Ingrese el nombre a buscar: ";
        cin >> nombre;
        agregarHistorial(nombre);
        Persona* resultado = buscarFamiliar(raiz, nombre);  // puntero al nodo encontrado
        if (resultado != nullptr) {
            cout << "\n  *** Familiar encontrado ***\n";
            resultado->mostrarInfo();
        } else {
            cout << "  No se encontro a '" << nombre << "' en el arbol.\n";
        }
    }

    // Llama a la funcion recursiva y muestra el total de descendientes de la raiz
    void contarDescendientes() const {
        if (raiz == nullptr) { cout << "  Arbol vacio.\n"; return; }
        int total = contarDescendientes(raiz);
        cout << "\n  " << raiz->getNombre()
             << " tiene " << total << " descendiente(s).\n";
    }

    // Llama a la funcion recursiva y muestra el numero de generaciones del arbol
    void calcularGeneraciones() const {
        if (raiz == nullptr) { cout << "  Arbol vacio.\n"; return; }
        int gen = calcularGeneraciones(raiz);
        cout << "\n  El arbol de " << raiz->getNombre()
             << " tiene " << gen << " generacion(es).\n";
    }

    // Inicia la visualizacion jerarquica del arbol desde la raiz (nivel 0)
    void mostrarGeneraciones() const {
        if (raiz == nullptr) { cout << "  Arbol vacio.\n"; return; }
        cout << "\n Arbol Genealogico de "
             << raiz->getNombre() << " \n";
        mostrarArbol(raiz, 0);
    }

    // Recolecta todos los descendientes en un vector, los ordena por fecha
    // con sort() y una funcion lambda, y los muestra en pantalla
    void ordenarDescendientes() const {
        if (raiz == nullptr) { cout << "  Arbol vacio.\n"; return; }
        vector<Persona*> lista;
        recolectarDescendientes(raiz, lista);
        if (lista.empty()) {
            cout << "  No hay descendientes registrados.\n";
            return;
        }
        // Ordena el vector de punteros usando esAnteriorA() como criterio
        sort(lista.begin(), lista.end(),
             [](Persona* a, Persona* b) {
                 return a->getFecha().esAnteriorA(b->getFecha());
             });
        cout << "\n  Descendientes ordenados por fecha de nacimiento:\n";
        cout << "  " << string(45, '-') << endl;
        for (Persona* p : lista) {
            cout << "  ";
            p->getFecha().mostrar();
            cout << "  " << setw(12) << left << p->getNombre()
                 << "  (" << p->getRelacion() << ")\n";
        }
    }

    // Busca una persona por nombre y permite ver sus hijos directos o nietos
    // El puntero 'p' apunta al nodo encontrado; es nullptr si no existe
    void mostrarHijosONietos() const {
        string nombre;
        cout << "\n  Ingrese el nombre de la persona: ";
        cin >> nombre;
        Persona* p = buscarFamiliar(raiz, nombre);  // puntero al nodo buscado
        if (p == nullptr) {
            cout << "  Persona '" << nombre << "' no encontrada.\n";
            return;
        }
        int opcion;
        cout << "  1. Ver hijos directos\n";
        cout << "  2. Ver nietos\n";
        cout << "  Opcion: ";
        cin >> opcion;
        if      (opcion == 1) mostrarHijos(p);
        else if (opcion == 2) mostrarNietos(p);
        else cout << "  Opcion invalida.\n";
    }

    // Crea un nuevo nodo Persona con 'new' y lo enlaza al arbol
    // Si no hay raiz, el nuevo nodo se convierte en raiz
    // Si hay raiz, busca al padre por nombre y agrega el nodo como hijo
    void registrarPersona() {
        string nombre, relacion;
        Fecha fecha;
        cout << "\n  --- Registro de nueva persona ---\n";
        cout << "  Nombre          : "; cin >> nombre;
        cout << "  Fecha de nacimiento:\n";
        fecha.leer();
        cout << "  Relacion familiar: "; cin >> relacion;
        Persona* nueva = new Persona(nombre, fecha, relacion);  // reserva memoria dinamica
        if (raiz == nullptr) {
            raiz = nueva;  // el puntero raiz apunta al primer nodo creado
            cout << "  " << nombre << " registrado(a) como raiz del arbol.\n";
        } else {
            string nombrePadre;
            cout << "  Nombre del padre/madre: "; cin >> nombrePadre;
            Persona* padre = buscarFamiliar(raiz, nombrePadre);  // puntero al padre encontrado
            if (padre != nullptr) {
                padre->agregarHijo(nueva);  // enlaza el nuevo nodo como hijo del padre
                cout << "  " << nombre << " agregado(a) como "
                     << relacion << " de " << nombrePadre << ".\n";
            } else {
                cout << "  Padre/madre '" << nombrePadre << "' no encontrado.\n";
                delete nueva;  // libera la memoria si no se pudo insertar el nodo
            }
        }
    }
};

// Funcion global: construye la familia predeterminada de Lucia con new
// Crea nodos dinamicos y los enlaza con agregarHijo para formar el arbol
void cargarFamiliaLucia(ArbolGenealogico& arbol) {
    // Cada 'new' reserva memoria dinamica y retorna un puntero al nodo creado
    Persona* lucia  = new Persona("Lucia",  Fecha(15,  3, 1955), "Raiz / Abuela");
    Persona* carlos = new Persona("Carlos", Fecha(10,  7, 1978), "Hijo");
    Persona* ana    = new Persona("Ana",    Fecha(22, 11, 1982), "Hija");
    Persona* sofia  = new Persona("Sofia",  Fecha( 5,  5, 2005), "Nieta");
    Persona* diego  = new Persona("Diego",  Fecha(18,  8, 2008), "Nieto");
    Persona* paula  = new Persona("Paula",  Fecha( 3,  2, 2010), "Nieta");
    Persona* miguel = new Persona("Miguel", Fecha(12,  1, 2015), "Bisnieto");

    // Construccion del arbol: cada llamada enlaza un puntero hijo al nodo padre
    lucia->agregarHijo(carlos);
    lucia->agregarHijo(ana);
    carlos->agregarHijo(sofia);
    carlos->agregarHijo(diego);
    ana->agregarHijo(paula);
    sofia->agregarHijo(miguel);

    arbol.setRaiz(lucia);  // asigna el puntero de Lucia como raiz del arbol
    cout << "\n  Familia de Lucia cargada. Bienvenido al sistema.\n";
}

// Funcion principal: punto de entrada del programa
// Crea el objeto arbol, carga la familia y ejecuta el menu con do-while
int main() {
    ArbolGenealogico arbol;
    int opcion;

    cargarFamiliaLucia(arbol);

    do {
        cout << "\n";
        cout << "\n   EL ARBOL DE LOS RECUERDOS - LUCIA     ";
        cout << "\n";
        cout << "\n  1. Registrar nueva persona              ";
        cout << "\n  2. Mostrar arbol (generaciones)         ";
        cout << "\n  3. Buscar familiar por nombre           ";
        cout << "\n  4. Ordenar descendientes por fecha      ";
        cout << "\n  5. Calcular generaciones del arbol      ";
        cout << "\n  6. Contar descendientes de Lucia        ";
        cout << "\n  7. Ver hijos o nietos de una persona    ";
        cout << "\n  8. Ver historial de busquedas           ";
        cout << "\n  9. Salir                                 ";
        cout << "\n";
        cout << "\n  Seleccione una opcion: ";
        cin >> opcion;
        // switch-case: redirige cada opcion a su funcion correspondiente
        switch (opcion) {
            case 1: arbol.registrarPersona();     break;
            case 2: arbol.mostrarGeneraciones();  break;
            case 3: arbol.buscarFamiliar();       break;
            case 4: arbol.ordenarDescendientes(); break;
            case 5: arbol.calcularGeneraciones(); break;
            case 6: arbol.contarDescendientes();  break;
            case 7: arbol.mostrarHijosONietos();  break;
            case 8: mostrarHistorial();           break;
            case 9: cout << "\n  Hasta luego. Los recuerdos de Lucia quedan guardados.\n"; break;
            default: cout << "\n  Opcion invalida. Intente de nuevo.\n";
        }

    } while (opcion != 9);  // repite el menu hasta que el usuario elija salir

    return 0;
}