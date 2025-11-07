/*
* NickName:  NueveCinco
* Actividad: p3
* Tiempo:    00:40
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <fstream>
#include <iomanip>

#ifdef _WIN32
#define LIMPIAR_PANTALLA "cls"
#elif defined(unix)||defined(__unix__)||defined(__unix)||defined(__APPLE__)||defined(__MACH__)
#define LIMPIAR_PANTALLA "clear"
#else
#error "SO no soportado"
#endif

using namespace std;

// a) Declaración y definición de constantes;
const int PORC_IVA = 16;
const int PORC_RET_IVA = 10;
const int PORC_RET_ISR = 10;
const int MESES_ANIO = 12;
float limitesISR[] = {0.0f, 10000.01f, 20000.01f};
int porcentajesISR[] = {11, 15, 20};

// b) Variables globales de uso interno del programa;
string meses[MESES_ANIO] = {"Enero","Febrero","Marzo","Abril","Mayo","Junio",
                            "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};

// c) Variables de programa modificables por el usuario;
float ingresos[MESES_ANIO];
float gastos[MESES_ANIO];
int mesActual;
bool banderaContinuar;

void pausa();
void inicializar();
void mostrarMenu();
void opcionEstablecerMes();
void opcionCapturaIngresos();
void opcionCapturaGastos();
void opcionMostrarIngresos();
void opcionMostrarGastos();
void opcionCalculoImpuestos();
void opcionGuardarArchivos();
int obtenerPorcentajeISR(float monto);

int main() {
    inicializar();
    do {
        mostrarMenu();
        int opcion;
        if(!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = -1;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(opcion) {
            case 1: opcionEstablecerMes(); break;
            case 2: opcionCapturaIngresos(); break;
            case 3: opcionCapturaGastos(); break;
            case 4: opcionMostrarIngresos(); break;
            case 5: opcionMostrarGastos(); break;
            case 6: opcionCalculoImpuestos(); break;
            case 7: opcionGuardarArchivos(); break;
            case 8: banderaContinuar = false; break;
            default:
                cout << "Opcion no valida" << endl;
                pausa();
        }
    } while(banderaContinuar);
    return 0;
}

void inicializar() {
    system(LIMPIAR_PANTALLA);
    for(int i = 0; i < MESES_ANIO; i++) {
        ingresos[i] = 0.0f;
        gastos[i] = 0.0f;
    }
    mesActual = 0;
    banderaContinuar = true;

    ifstream archivoIn("ingresos.txt");
    if(archivoIn.is_open()) {
        for(int i=0; i<MESES_ANIO; i++) {
            if (!(archivoIn >> ingresos[i])) {
                ingresos[i] = 0.0f;
            }
        }
        archivoIn.close();
    }
    ifstream archivoGas("gastos.txt");
    if(archivoGas.is_open()) {
        for(int i=0; i<MESES_ANIO; i++) {
            if (!(archivoGas >> gastos[i])) {
                 gastos[i] = 0.0f;
            }
        }
        archivoGas.close();
    }
}

void mostrarMenu() {
    system(LIMPIAR_PANTALLA);
    cout << "CALCULO DE IMPUESTOS ANUAL" << endl << endl;
    cout << "Menu principal:" << endl;
    cout << "1. Establecer mes para captura (mes actual es " << meses[mesActual] << ")" << endl;
    cout << "2. Captura de ingresos" << endl;
    cout << "3. Captura de gastos" << endl;
    cout << "4. Mostrar lista de ingresos anual" << endl;
    cout << "5. Mostrar lista de gastos anual" << endl;
    cout << "6. Calculo de impuestos anual" << endl;
    cout << "7. Guardar en archivo" << endl;
    cout << "8. Salir" << endl << endl;
    cout << "Opcion: ";
}

void opcionEstablecerMes() {
    system(LIMPIAR_PANTALLA);
    cout << "Establecer mes para captura" << endl;
    for(int i=0;i<MESES_ANIO;i++) cout << (i+1) << ") " << meses[i] << endl;
    cout << "Elige el mes (1-12): ";
    int elegido;
    if(!(cin >> elegido)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
        pausa();
        return;
    }
    if(elegido>=1 && elegido<=12) {
        mesActual = elegido-1;
        cout << "Mes establecido en " << meses[mesActual] << endl;
    } else {
        cout << "Mes no valido." << endl;
    }
    pausa();
}

void opcionCapturaIngresos() {
    system(LIMPIAR_PANTALLA);
    cout << "Captura de ingresos - " << meses[mesActual] << endl;
    float monto;
    do {
        cout << "Dame el ingreso (>=0): ";
        if(!(cin >> monto)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
            monto = -1.0f;
            continue;
        }
        if(monto < 0) {
            cout << "El monto no puede ser negativo." << endl;
        }
    } while(monto < 0);
    ingresos[mesActual] = monto;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    pausa();
}

void opcionCapturaGastos() {
    system(LIMPIAR_PANTALLA);
    cout << "Captura de gastos - " << meses[mesActual] << endl;
    float monto;
    do {
        cout << "Dame el gasto (>=0): ";
        if(!(cin >> monto)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
            monto = -1.0f;
            continue;
        }
        if(monto < 0) {
            cout << "El monto no puede ser negativo." << endl;
        }
    } while(monto < 0);
    gastos[mesActual] = monto;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    pausa();
}

void opcionMostrarIngresos() {
    system(LIMPIAR_PANTALLA);
    cout << "Lista de ingresos anual" << endl;
    for(int i=0;i<MESES_ANIO;i++)
        printf("%12s = %8.2f\n", meses[i].c_str(), ingresos[i]);
    pausa();
}

void opcionMostrarGastos() {
    system(LIMPIAR_PANTALLA);
    cout << "Lista de gastos anual" << endl;
    for(int i=0;i<MESES_ANIO;i++)
        printf("%12s = %8.2f\n", meses[i].c_str(), gastos[i]);
    pausa();
}

void opcionCalculoImpuestos() {
    system(LIMPIAR_PANTALLA);

    // a) Declaración de variables;
    float ingresoTotal = 0, gastoTotal = 0;
    float iva, subtotal, retISR, retIVA, total;
    float ganBruta, isr, ganNeta;
    float isrPagar;
    float gastoIVA, ivaPagar;
    int porcISR;

    // b) Cálculo de impuestos;
    for(int i=0;i<MESES_ANIO;i++) {
        ingresoTotal += ingresos[i];
        gastoTotal += gastos[i];
    }
    iva = ingresoTotal * PORC_IVA/100.0f;
    subtotal = ingresoTotal + iva;
    retISR = ingresoTotal * PORC_RET_ISR/100.0f;
    retIVA = ingresoTotal * PORC_RET_IVA/100.0f;
    total = subtotal - retISR - retIVA;

    ganBruta = ingresoTotal - gastoTotal;
    porcISR = obtenerPorcentajeISR(ganBruta);
    isr = ganBruta * porcISR/100.0f;
    ganNeta = ganBruta - isr;

    isrPagar = isr - retISR;
    gastoIVA = gastoTotal * PORC_IVA/100.0f;
    ivaPagar = iva - gastoIVA - retIVA;

    // c) Salida de datos;
    cout << "*** Tabla Recibo de Honorarios ***" << endl;
    printf("Ingresos          %10.2f\n", ingresoTotal);
    printf("(+) IVA           %10.2f\n", iva);
    printf("(=) Subtotal      %10.2f\n", subtotal);
    printf("(-) Ret ISR       %10.2f\n", retISR);
    printf("(-) Ret IVA       %10.2f\n", retIVA);
    printf("(=) Total         %10.2f\n\n", total);

    cout << "*** Tabla Ganancias ***" << endl;
    printf("Ingresos          %10.2f\n", ingresoTotal);
    printf("(-) Gastos        %10.2f\n", gastoTotal);
    printf("(=) Ganancia Bruta%10.2f\n", ganBruta);
    printf("(-) ISR %6d%%     %10.2f\n", porcISR, isr);
    printf("(=) Ganancia Neta %10.2f\n\n", ganNeta);

    cout << "*** Tabla ISR ***" << endl;
    printf("ISR %6d%%          %10.2f\n", porcISR, isr);
    printf("(-) ISR Retenido  %10.2f\n", retISR);
    printf("(=) ISR a Pagar   %10.2f\n\n", isrPagar);

    cout << "*** Tabla IVA ***" << endl;
    printf("IVA               %10.2f\n", iva);
    printf("(-) Gastos IVA    %10.2f\n", gastoIVA);
    printf("(-) Ret IVA       %10.2f\n", retIVA);
    printf("(=) IVA a Pagar   %10.2f\n\n", ivaPagar);
    pausa();
}

void opcionGuardarArchivos() {
    system(LIMPIAR_PANTALLA);

    ofstream archIn("ingresos.txt");
    if(archIn.is_open()){
        for(int i=0;i<MESES_ANIO;i++) archIn << fixed << setprecision(2) << ingresos[i] << endl;
        archIn.close();
    } else {
        cout << "Error: No se pudo abrir 'ingresos.txt' para guardar." << endl;
    }

    ofstream archGas("gastos.txt");
    if(archGas.is_open()){
        for(int i=0;i<MESES_ANIO;i++) archGas << fixed << setprecision(2) << gastos[i] << endl;
        archGas.close();
    } else {
        cout << "Error: No se pudo abrir 'gastos.txt' para guardar." << endl;
    }

    cout << "Datos guardados" << endl;
    pausa();
}

int obtenerPorcentajeISR(float monto) {
    if(monto < 0) return 0;
    int numRangos = sizeof(limitesISR) / sizeof(limitesISR[0]);
    for(int i = numRangos - 1; i >= 0; i--) {
        if(monto >= limitesISR[i]) {
            return porcentajesISR[i];
        }
    }
    return porcentajesISR[0];
}

void pausa() {
    cout << "Presione entrar para continuar...";
    cin.get();
}
