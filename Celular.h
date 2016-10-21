#ifndef Celular_h
#define Celular_h
#include<fstream>

#include "Cola.h"//CAMBIAR NOMBRE


using namespace std;

//Celular es un dispositivo que se conecta a una antena y permite:
//    *mostrar en pantalla mensajes nuevos preguntando el minuto inicial
//    *mostrar en pantalla el historial de mensajes emitidos
//    *mostrar en pantalla el historial de mensajes recibidos
//    *emitir un mensaje a otro celular
//cada celular tiene dos archivos de texto, uno indicando las operaciones de Egreso (desde el Celular hacia el Sistema) y otro para las operaciones de Ingreso (desde el Sistema hacia el Celular).
//Al momento de realizar una consulta, los celulares se indican por ID o por Número.



class Celular
{
    //atributos
private:
    unsigned int cellNumber; //almacena el numero de este celular
    fstream exitFile; //archivo de egreso
    fstream entryFile; //archivo de ingreso
    Queue waitingMessages; //para almacenar los mensajes que aun no se han enviado

    
    //metodos
public:
    //pre: -
    //post: construye un celular asignandole un numero, crea los archivos de egreso e ingreso
    //      e inicializa la cola de los mensajes en espera
    Celular(unsigned int number, Queue messages);
    
    //pre:
    //post: devuelve el numero de este celular
    unsigned int getCellNumber();
    
    
    //pre: minuto es mayor a 0 y menor a 1440 (cantidad maxima de minutos en un dia)
    //post: muestra en pantalla mensajes nuevos preguntando el minuto inicial (>>>DUDA<<<)
    void readMessages(unsigned int minute, string archRegistrosHistoricos); //CAMBIAR NOMBRE ARCHIVO
    
    //pre: otherCellNumber debe ser un numero valido
    //post: escribe el mensaje enviado en el archivo de egreso de este celular y en el
    //      archivo de ingreso del celular destinatario
    void sendMessage(unsigned int otherCellNumber);
    
    //pre:
    //post: muestra en pantalla el historial de mensajes emitidos
    void showOutbox();
    
    //pre:
    //post: muestra en pantalla el historial de mensajes recibidos
    void showInbox();
    
    //pre:
    //post:
    Queue getWaitingMessages();

    //pre:
    //post: limpia la cola
    void cleanQueue();
    
    //pre:-
    //post: cierra los archivos de ingreso y egreso
    ~Celular();
    
};

/* Num
    Q mensajes
    Constructor(...Q)
    enviar mensaje
    Destructor
    puntero a Antena
 */

#endif /* Celular_h */
