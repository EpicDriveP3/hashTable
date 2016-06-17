/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: betolan
 *
 * Created on 4 de junio de 2016, 03:20 AM
 */

#include "HashTable.h"

using namespace std;

int main(){   
    int ch, key, type;
    string tmp2;
    HashTable HT;
    
    cout<<"1. Archivo existente  2. Borrar"<<endl;
    cout<<"Total de buckets de la HashTable: "<<endl;
    cin>>HT.buckets;
    
    while(1){
        cout<<"1. Insertar  2. Borrar"<<endl;
        cout<<"3. Buscar    4. Visualizar HashTable"<<endl;
        cout<<"5. Salir"<<endl;
        cout<<"Escriba la opcion: "<<endl;
        cin>>ch;
        
        switch(ch){

            case 1:
                cout<<"Escriba el key a insertar: "<<endl;
                cin>>key;
                cout<<"1. String  2. Int"<<endl;
                cout<<"3. Float   4. Double"<<endl;
                cout<<"5. Image   6. Binary"<<endl;
                cout<<"Escriba el tipo de dato del key: "<<endl;
                cin>>type;           
                cout<<"Escriba el dato del key: "<<endl;
                cin>>tmp2;  
                HT.Write(key, tmp2);                       
                break;

            case 2:
                cout<<"Escriba el key a borrar: "<<endl;
                cin>>key;
                HT.Delete(key);
                break;

            case 3:
                cout<<"Escriba el key a buscar: "<<endl;
                cin>>key;
                HT.search(key);
                break;

            case 4:               
                HT.Display();                               
                break;
                
            case 5:               
                //remove("HashTable.dat");     
                HT.WriteControl();
                exit(0);
                    
            default:
                cout<<"Escriba alguna opcion correcta (1-5): "<<endl;
                break; 
                    
        }
    
    }
    
    return 0;
}