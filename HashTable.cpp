/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Student.cpp
 * Author: betolan
 * 
 * Created on 4 de junio de 2016, 08:10 AM
 */


#include "HashTable.h"

using namespace std;

HashTable::HashTable(){
    elements_for_bucket=(int*)malloc(sizeof(int)*sizeof(buckets)); 
}

HashTable::HashTable(const HashTable& orig){}

HashTable::~HashTable(){}

void HashTable::Write(int key, string data){
    int total=0;
    int total2=0;
    int indice;
    indice=key%buckets;
    
    for(int i=0; i<=indice; i++){
        total=total+elements_for_bucket[i];
    }
    
    for(int i=0; i<buckets; i++){
        total2=total2+elements_for_bucket[i];
    }
    
    ifstream inFile;
    inFile.open("HashTable.dat", ios::binary);
    ofstream outFile;
    outFile.open("temp.dat", ios::binary|ios::app);
    
    HashTable obj;
    HashTable obj2;
    
    obj2.key=key;
    obj2.data=(char*)malloc(sizeof(char)*sizeof(data));  
    strcpy(obj2.data, data.c_str());
    
    int cont=0;
    bool first=true;
    
    if(total2==0){
        outFile.write((char*)&obj2, sizeof(obj2));
        elements_for_bucket[indice]++;
    }
    
    if(total==0 && total2!=0){
         while(inFile.read((char*)&obj, sizeof(obj))){
            if(first==true){
                outFile.write((char*)&obj2, sizeof(obj2));
                outFile.write((char*)&obj, sizeof(obj));
                elements_for_bucket[indice]++;
                first=false;
            }
            else{
                outFile.write((char*)&obj, sizeof(obj));
            }

        }
    }
    
    else{

        while(inFile.read((char*)&obj, sizeof(obj))){
            cont++;

            if(total==cont){
                outFile.write((char*)&obj, sizeof(obj));
                outFile.write((char*)&obj2, sizeof(obj2));
                elements_for_bucket[indice]++;
            }
            else{
                outFile.write((char*)&obj, sizeof(obj));
            }

        }
    
    }
    
    inFile.close();
    outFile.close();
    
    remove("HashTable.dat");
    rename("temp.dat", "HashTable.dat");

}

void HashTable::Display(){
    cout<<"------------------------------------------"<<endl;
    ifstream inFile;
    inFile.open("HashTable.dat", ios::binary);
    HashTable obj;

    while(inFile.read((char*)&obj, sizeof(obj))){
    	cout<<"           "<<"Key:  "<<obj.key<<endl;
    	cout<<"           "<<"Data: "<<obj.data<<endl;
        cout<<endl;
    }
    
    cout<<"------------------------------------------"<<endl;
    inFile.close();
}

void HashTable::Delete(int key){
    HashTable obj;
    int indice;
    indice=key%buckets;
    ifstream inFile;
    inFile.open("HashTable.dat", ios::binary);

    ofstream outFile;
    outFile.open("temp.dat", ios::out|ios::binary);

    while(inFile.read((char*)&obj, sizeof(obj))){
        
        if(obj.key!=key){
            outFile.write((char*)&obj, sizeof(obj));
            elements_for_bucket[indice]--;
        }
        
    }
    
    inFile.close();
    outFile.close();
    remove("HashTable.dat");
    rename("temp.dat", "HashTable.dat");
}

void HashTable::search(int key)
{   
    int total=0;
    int indice;
    indice=key%buckets;
    
    ifstream inFile;
    inFile.open("HashTable.dat", ios::binary);
    
    for(int i=0; i<indice; i++){
        total=total+elements_for_bucket[i];
    }
    
    HashTable obj;
    
    if(elements_for_bucket[indice]==0){ 
        cout<<"No hay elementos en este bucket"<<endl;
    }
    
    else{
    
        for(int i=0; i<total;i++){
            inFile.read((char*)&obj, sizeof(obj));    
        }
        
        bool out=false;
        
        for(int i=0; i<elements_for_bucket[indice] && out==false; i++){
            inFile.read((char*)&obj, sizeof(obj));
            
            if(obj.key == key)
            {
                cout<<"           "<<"Key:  "<<obj.key<<endl;
                cout<<"           "<<"Data: "<<obj.data<<endl;
                out=true;
            }
        }
    }
    
    inFile.close();
}

void HashTable::WriteControl(){
    ofstream outFile;
    outFile.open("Control.dat", ios::binary|ios::app);
    
    for(int i=0; i<buckets; i++){
        outFile.write((char*)&elements_for_bucket[i], sizeof(elements_for_bucket[i]));
    }
    
    outFile.close();
        
}

void HashTable::ReadControl(){
    ifstream inFile;
    inFile.open("Control.dat", ios::binary);
    
    int temp=0;
    
    for(int i=0; i<buckets; i++){
        inFile.read((char*)&temp, sizeof(temp));
        elements_for_bucket[i]=temp;
        cout<<temp<<endl;
    }
    
    inFile.close();
        
}