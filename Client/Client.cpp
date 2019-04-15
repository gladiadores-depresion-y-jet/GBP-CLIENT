//
// Created by dcamachog1501 on 14/04/19.
//
#include "Client.h"
#include <iostream>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include <string.h>
#include <string>
#include <thread>
#include <pthread.h>
#include <fstream>
#include <vector>

using namespace std;
Client::Client()
{
    this->connected=false;
    this->running=true;
}
void Client::start()
{
    setData();
    int attempts=1;
    cout << "Trying to connect to server,please standby..." << endl;
    while(running)
    {
        while (running && !connected) {
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock == -1) {
                cout << "Failed to connect to server, sock=-1" << endl;
            }
            sockaddr_in hint;
            hint.sin_family = AF_INET;
            hint.sin_port = htons(port);
            inet_pton(AF_INET, ipAd.c_str(), &hint.sin_addr);
            int connectRes = connect(sock, (sockaddr *) &hint, sizeof(hint));
            if (connectRes == -1) {
                cout << "Failed to connect to server, connectRes= -1" << endl;
            } else {
                connected = true;
                cout<<"Connected!"<<endl;
                //sendMessage("getList");
            }
            cout << "Atempts to connect: " << attempts++ << endl;

        }

    }
    cout<<"Disconnecting..."<<endl;
    exit(0);
}
string Client::receiveMessage()
{
    string receivedMessage;
    try {
        memset(buff, 0, 4096);
        int bytesReceived = recv(sock, buff, 4096, 0);
        if(bytesReceived==-1)
        {
            cout<<"ERROR:Mensaje corrupto"<<endl;
        }
        else
        {
            receivedMessage = string(buff, bytesReceived);
        }

    }
    catch(exception& e){
        receivedMessage="";
        cout<<"No hay mensajes entrantes"<<endl;
    }
    receivedMessage=receivedMessage.substr(0,receivedMessage.size()-1);
    /*cout<<"Mensaje recibido: "<<receivedMessage<<endl;*/
    return receivedMessage;
}
void Client::sendMessage(string message)
{
    int sendMes=send(sock,message.c_str(),message.size()+1,0);

    if(sendMes==-1)
    {
        cout<<"Couldn't send the message: "<<message<<endl;
    }
    /*cout<<"Mensaje enviado: "<<message<<endl;*/
}
void Client::setData()
{
    ifstream file;
    file.open("../configFile.txt");
    string element;
    string ip;
    string port;

    bool flag = true;
    vector<string> vector;

    if(file.is_open()){
        while(file >> element){
            if(!flag){
                vector.push_back(element);
                cout<<"Element: "<<element<<endl;
            }
            flag = !flag;

        }
        file.close();
        ip = vector[0];
        port = vector[1];

        cout<<"IP    "<<ip<<endl;
        this->ipAd=ip;
        cout<<"PORT  "<<port<<endl;
        this->port=stoi(port);

    }else{
        cout<<"cant open the file..."<<endl;
    }
}