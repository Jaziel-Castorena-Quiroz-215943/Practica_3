#include <iostream>
#include <vector>
#include <string>
using namespace std;
 
// ====================== Clase Producto ======================
class Producto {
private:
    int idProducto;
    string nombre;
    string categoria;
    float precio;
    int cantidad;
    string codigoBarras;
 
public:
    Producto(int id, string n, string cat, float p, int c, string cod)
        : idProducto(id), nombre(n), categoria(cat), precio(p), cantidad(c), codigoBarras(cod) {}
 
    int getId() { return idProducto; }
    string getNombre() { return nombre; }
    string getCodigoBarras() { return codigoBarras; }
    int getCantidad() { return cantidad; }
 
    void editarPrecioYCantidad(float p, int c) {
        precio = p;
        cantidad = c;
    }
 
    void actualizarCantidad(int c) { cantidad += c; }
 
    void mostrar() {
        cout << "ID: " << idProducto
             << " | Nombre: " << nombre
             << " | Categoria: " << categoria
             << " | Precio: " << precio
             << " | Cantidad: " << cantidad
             << " | CodigoBarras: " << codigoBarras << endl;
    }
};
 
// ====================== Clase Inventario ======================
class Inventario {
private:
    vector<Producto> productos;
    vector<string> categorias = {"Abarrotes", "Lácteos", "Carnes frías", "Bebidas", "Higiene personal", "Limpieza", "Botanas", "Enlatados"};
    int contadorID = 1;
 
public:
    bool codigoExiste(const string& cod) {
        for (auto& p : productos)
            if (p.getCodigoBarras() == cod) return true;
        return false;
    }
 
    string seleccionarCategoria() {
        int opcion;
        while (true) {
            cout << "\nSeleccione una categoría:\n";
            for (size_t i = 0; i < categorias.size(); i++) {
                cout << i + 1 << ". " << categorias[i] << endl;
            }
            cout << categorias.size() + 1 << ". Agregar nueva categoría\n";
            cout << "Opcion: ";
            cin >> opcion;
 
            if (opcion >= 1 && opcion <= (int)categorias.size()) {
                return categorias[opcion - 1];
            } else if (opcion == (int)categorias.size() + 1) {
                cin.ignore();
                string nuevaCat;
                cout << "Ingrese el nombre de la nueva categoría: ";
                getline(cin, nuevaCat);
                categorias.push_back(nuevaCat);
                return nuevaCat;
            } else {
                cout << "Opción inválida. Intente de nuevo.\n";
            }
        }
    }
 
    void agregarProducto(string n, string cat, float p, int c, string cod) {
        productos.push_back(Producto(contadorID++, n, cat, p, c, cod));
        cout << "Producto agregado con éxito.\n";
    }
 
    void eliminarProducto(int id) {
        for (size_t i = 0; i < productos.size(); i++) {
            if (productos[i].getId() == id) {
                productos.erase(productos.begin() + i);
                cout << "Producto eliminado.\n";
                return;
            }
        }
        cout << "Producto no encontrado.\n";
    }
 
    Producto* buscarProducto(int id) {
        for (auto &p : productos)
            if (p.getId() == id)
                return &p;
        return nullptr;
    }
 
    void mostrarProductos() {
        if (productos.empty()) {
            cout << "No hay productos registrados.\n";
            return;
        }
        for (auto &p : productos)
            p.mostrar();
    }
 
    void registrarEntrada(int id, int cantidad) {
        Producto* p = buscarProducto(id);
        if (p) {
            p->actualizarCantidad(cantidad);
            cout << "Entrada registrada.\n";
        } else cout << "Producto no encontrado.\n";
    }
 
    void registrarSalida(int id, int cantidad) {
        Producto* p = buscarProducto(id);
        if (p) {
            if (p->getCantidad() >= cantidad) {
                p->actualizarCantidad(-cantidad);
                cout << "Salida registrada.\n";
            } else cout << "Stock insuficiente.\n";
        } else cout << "Producto no encontrado.\n";
    }
};
 
// ====================== Menús ======================
void menuPrincipal() {
    cout << "\n==== SISTEMA DE INVENTARIO ====\n";
    cout << "1. Gestionar Productos\n";
    cout << "2. Registrar Entradas/Salidas\n";
    cout << "3. Consultar Inventario\n";
    cout << "4. Salir\n";
    cout << "Seleccione opcion: ";
}
 
void menuProductos() {
    cout << "\n--- Gestionar Productos ---\n";
    cout << "1. Agregar Producto\n";
    cout << "2. Editar Precio y Cantidad\n";
    cout << "3. Eliminar Producto\n";
    cout << "4. Mostrar Productos\n";
    cout << "5. Volver\n";
    cout << "Seleccione opcion: ";
}
 
void menuMovimientos() {
    cout << "\n--- Registrar Movimientos ---\n";
    cout << "1. Registrar Entrada\n";
    cout << "2. Registrar Salida\n";
    cout << "3. Volver\n";
    cout << "Seleccione opcion: ";
}
 
// ====================== MAIN ======================
int main() {
    Inventario inv;
    int opcion, subopcion, id, cantidad;
    string nombre, categoria, codBarras;
    float precio;
 
    do {
        menuPrincipal();
        cin >> opcion;
 
        switch (opcion) {
        case 1: 
            do {
                menuProductos();
                cin >> subopcion;
                switch (subopcion) {
                case 1:
                    cin.ignore();
                    cout << "Nombre: "; getline(cin, nombre);
                    categoria = inv.seleccionarCategoria();
                    cout << "Precio: "; cin >> precio;
                    cout << "Cantidad: "; cin >> cantidad;
                    cin.ignore();
                    do {
                        cout << "Codigo de Barras: ";
                        getline(cin, codBarras);
                        if (inv.codigoExiste(codBarras))
                            cout << "Código ya existente, ingrese otro.\n";
                    } while (inv.codigoExiste(codBarras));
                    inv.agregarProducto(nombre, categoria, precio, cantidad, codBarras);
                    break;
 
                case 2: {
                    cout << "ID del producto a editar: ";
                    cin >> id;
                    Producto* p = inv.buscarProducto(id);
                    if (p) {
                        p->mostrar();
                        cout << "Nuevo Precio: "; cin >> precio;
                        cout << "Nueva Cantidad: "; cin >> cantidad;
                        p->editarPrecioYCantidad(precio, cantidad);
                        cout << "Producto actualizado.\n";
                    } else cout << "Producto no encontrado.\n";
                } break;
 
                case 3:
                    cout << "ID del producto a eliminar: ";
                    cin >> id;
                    inv.eliminarProducto(id);
                    break;
 
                case 4:
                    inv.mostrarProductos();
                }
            } while (subopcion != 5);
            break;
 
        case 2:
            do {
                menuMovimientos();
                cin >> subopcion;
                switch (subopcion) {
                case 1:
                    cout << "ID del producto: ";
                    cin >> id;
                    cout << "Cantidad a ingresar: ";
                    cin >> cantidad;
                    inv.registrarEntrada(id, cantidad);
                    break;
                case 2:
                    cout << "ID del producto: ";
                    cin >> id;
                    cout << "Cantidad a vender: ";
                    cin >> cantidad;
                    inv.registrarSalida(id, cantidad);
                    break;
                }
            } while (subopcion != 3);
            break;
 
        case 3:
            inv.mostrarProductos();
            break;
        }
 
    } while (opcion != 4);
 
    cout << "Saliendo del sistema...\n";
    return 0;
}
 