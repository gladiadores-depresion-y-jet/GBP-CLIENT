//
// Created by dcamachog1501 on 14/04/19.
//

#ifndef GBP_CLIENT_CLIENT_H
#define GBP_CLIENT_CLIENT_H
#include <iostream>
#include <thread>
using namespace std;


class Client{
private:
    int sock;
    string ipAd;
    int port;
    char buff[4096];
    bool connected;
    bool running;

public:
    /**
     * Constructor de la clase client.
     */
    Client();
    /**
     * Metodo para realizar la conexion con el servidor.
     */
    void start();
    /**
     * Metodo para enviar mensajes al servidor.
     * @param message Mensaje de tipo String.
     */
    void sendMessage(string message);
    /**
     * Metodo para obtener el mensaje recibido por el servidor.
     * @return Mensaje de tipo string.
     */
    string receiveMessage();
    /**
     * Metodo para establecer los parametros de configuracion del cliente.
     */
    void setData();
};
#endif //GBP_CLIENT_CLIENT_H
