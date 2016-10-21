#include "Celular.h"
#include<iostream>
#include<string>

using namespace std;

Celular::Celular(unsigned int number, Queue messages)
{
    this->cellNumber=number;
    
    string s = to_string(number); //convierte el unsigned int en string para guardar el archivo
                                  //con el numero de celular
    
    string entryFileName="/Users/Caro/Documents/entry"+s+".txt"; //guardarlo en la direccion deseada(cambiar)
    string exitFileName="/Users/Caro/Documents/exit"+s+".txt";
    
    exitFile.open(exitFileName.c_str());
    entryFile.open(entryFileName.c_str());//La funcion miembro open de ifstream abre
                                            //un archivo y le adjunta el objeto entrada
    
    //verifica la carga de arhivos
    if (!entryFile)
    {
        cerr<< "No pudo abrirse el archivo de entrada" <<endl;
    }
    
    if (!exitFile)
    {
        cerr<< "No pudo abrirse el archivo de salida" <<endl;
    }
    
    this->waitingMessages=messages;
    
    //inicializa la cola de mensajes en espera
    messages.firstNode = NULL;
    messages.lastNode = NULL;
    messages.amountOfElements=0;
  
}

unsigned int Celular::getCellNumber()
{
    return this->cellNumber;
}


void Celular::readMessages(unsigned int minute, string archRegistrosHistoricos)
{
    ifstream registrosHistoricos;
    
    registrosHistoricos.open(archRegistrosHistoricos.c_str());
    
    string word,mensaje; //variable para leer el archivo por palabra
    
    while(registrosHistoricos>>word) //leo por palabra
    {
        if (word=="Mensaje")
        {
            unsigned int celularX,celularY,min;
            registrosHistoricos>>celularX>>celularY>>min;
            
            if(celularY==getCellNumber())
            {
                if(min>=minute)
                {
                    getline(registrosHistoricos,mensaje);
                    cout<<"* Mensaje de "<<celularX<<": "<<mensaje<<endl;
                    
                }
            }
            
        }
    }
    
}

void Celular::sendMessage(unsigned int number)
{
    string mensaje;
    cout<<"Ingrese el numero del destinatario: ";
    cin>>number;
    cout<<"Ingrese el mensaje que desea enviar y presione enter para terminar:"<<endl;
    cin>>mensaje;
    
    exitFile<<"* Mensaje a "<<number<<": "<<mensaje; //falta que imprima toda la linea del mensaje
    
    
    //en el entryFile del otro celular guardo el mensaje (me falta relacionarlo con otro celular)
    
}

void Celular::showInbox()
{
    string word; //variable para escanear por palabra
    while(getline(entryFile,word))
    {
        cout<<word<<endl;
    }
}

void Celular::showOutbox()
{
    string word; //variable para escanear por palabra
    while(getline(exitFile,word))
    {
        cout<<word<<endl;
    }
}

Queue Celular::getWaitingMessages()
{
    return waitingMessages;
}

Celular::~Celular()
{
    exitFile.close();
    entryFile.close();
}