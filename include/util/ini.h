
#ifndef INI_HPP
#define INI_HPP

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>

using std::cout;
using std::endl;
using std::ios;

struct IniConfig{
    string tdAddress;
    string mdAddress;
    string brokerId;
    string userId;
    string passWord;
};

IniConfig* loadIni(const char* filePath){
    const char* prefix = "../";
    const size_t len = strlen(filePath) + strlen(prefix);
    char* fullPath = new char[len+1];
    strcpy(fullPath, prefix);
    strcat(fullPath, filePath);
    std::ifstream fin(fullPath, ios::binary|ios::in);
    string temp;
    if(!fin){
        cout<<"Open file "<<filePath<<" failed!"<<endl;
        return NULL;
    }
    IniConfig* config = new IniConfig();
    fin>>temp;  fin>>temp;  fin>>config->tdAddress;
    fin>>temp;  fin>>temp;  fin>>config->mdAddress;
    fin>>temp;  fin>>temp;  fin>>config->brokerId;
    fin>>temp;  fin>>temp;  fin>>config->userId;
    fin>>temp;  fin>>temp;  fin>>config->passWord;
    fin.close();
    return config;
}


#endif