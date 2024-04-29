/**
Prevenci�n de lavado de dinero

Se tiene una clase "PerfilCliente" que tiene los siguientes datos:

LimiteMaximoDeposito  - Limite de un dep�sito en efectivo antes de que se deba de alertar de una operaci�n inusual
PromedioMensualMaximo - Limite del promedio mensual en efectivo para este cliente antes de alertar de una operaci�n inusual

Se debe de detectar cuando exista una operaci�n inusual en efectivo que sobrepase el limite de un dep�sito,
y tambien de detectar si el promedio mensual en efectivo es superior al limite de un cliente
*/

/*Oscar Fabi�n V�squez Soto*/

#include <iostream>
#include <vector>

using namespace std;

namespace PrevencionLavado
{
    // Clase PerfilCliente
    class PerfilCliente {
    public:
        // Limite de un dep�sito �nico
        double LimiteMaximoDeposito;
        // Limite del promedio mensual
        double PromedioMensualMaximo;
    };

    // Enumeraci�n para el tipo de dep�sito
    enum TipoDeposito {
        Efectivo,
        Cheque,
        Transferencia
    };

    // Clase Deposito
    class Deposito {
    public:
        // Cantidad a depositar
        double Cantidad;
        // Fecha del dep�sito
        string Fecha;
        // Tipo de instrumento monetario
        TipoDeposito Tipo;
    };
    class parte_1_PLD {
        public:
        // Funci�n para verificar si un dep�sito pasa sin alerta
        static bool VerificarDeposito(Deposito deposito, PerfilCliente cliente) {
            if (deposito.Tipo == Efectivo && deposito.Cantidad > cliente.LimiteMaximoDeposito) {
                return false; // Se debe alertar de una operaci�n inusual
            }
            return true; // El dep�sito pasa normalmente sin alerta
        }

        // Funci�n para verificar si el promedio mensual de dep�sitos es superior al l�mite m�ximo
        static bool VerificarMes(vector<Deposito> depositos, PerfilCliente cliente, string mes) {
            double totalEfectivo = 0;
            int count = 0;

            for (Deposito dep : depositos) {
                //Se comparan los primeros 7 caracteres de la fecha de dep�sito (2024-04)
                //Si la fecha de un deposito no coincide con la del mes que se est� comparando, no se toma en cuenta
                if (dep.Fecha.substr(0, 7) == mes && dep.Tipo == Efectivo) {
                    totalEfectivo += dep.Cantidad;
                    count++;
                }
            }

            if (count > 0 && (totalEfectivo / count) > cliente.PromedioMensualMaximo) {
                return false; // Se debe alertar de una operaci�n inusual
            }
            return true; // El mes pasa normalmente sin alerta
        }
    };

}


int main() {
   
    PrevencionLavado::PerfilCliente cliente;
    cliente.LimiteMaximoDeposito = 1000; //Esta es la cantidad m�xima que se puede depositar
    cliente.PromedioMensualMaximo = 5000; //Esto es el promedio m�ximo permitido de las operaciones


    PrevencionLavado::Deposito dep1;
    dep1.Cantidad = 1200;
    dep1.Fecha = "2024-04-24";
    dep1.Tipo = PrevencionLavado::Efectivo; //Se verifican los depositos cuando son en efectivo
    //En caso de ser Cheque o transferenca, no se toman en cuenta en la validaci�n

    PrevencionLavado::Deposito dep2;
    dep2.Cantidad = 300;
    dep2.Fecha = "2024-04-15";
    dep2.Tipo = PrevencionLavado::Efectivo;

    vector<PrevencionLavado::Deposito> depositos = { dep1, dep2 };

    // Verificar dep�sito
    //Para que mande la alerta, el deposito debe ser mayor al LimiteMaximoDeposito
    if (!PrevencionLavado::parte_1_PLD::VerificarDeposito(dep1, cliente)) {
        cout << "Alerta: Se debe alertar de una operacion inusual para este deposito. (fuera del rango)" << endl;
    }
    else {
        cout <<"El dep�sito pasa normalmente sin alerta (dentro del rango)"<< endl;
    }

    // Verificar mes
    //Para que mande la alerta el promedio de los dos dep�sitos debe ser mayor al PromedioMensualMaximo 
    if (!PrevencionLavado::parte_1_PLD::VerificarMes(depositos, cliente, "2024-04")) {
        cout << "Alerta: Se debe alertar de una operacion inusual para este mes. (fuera del rango)" << endl;
    }
    else {
        cout << "El promedio de depositos pasa normalmente sin alerta (dentro del rango)" << endl;
    }

    return 0;
}

