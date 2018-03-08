#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <map>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#define CONFIGLEN 256

enum INI_RES
{
    INI_SUCCESS,
    INI_ERROR,
    INI_OPENFILE_ERROR,
    INI_NO_ATTR
};

typedef map<std::string, std::string> KEYMAP;

typedef map<std::string, KEYMAP> MAINKEYMAP;

class CIni
{
public:
    CIni();
    virtual ~CIni();

public:
    int GetInt(const char* mAttr, const char* cAttr);

    char *GetStr(const char* mAttr, const char* cAttr);

    INI_RES OpenFile(const char* pathName, const char* type);

    INI_RES CloseFile();

protected:
    INI_RES GetKey(const char* mAttr, const char* cAttr, char* value);

protected:
    FILE* m_fp;
    char  m_szKey[ CONFIGLEN ];
    MAINKEYMAP m_Map;
};

struct Config{
//    char tdAddress[28];
//    char mdAddress[28];
    string tdAddress;
    string mdAddress;
    char brokerId[19];
    char userId[19];
    char passWord[21];
};

Config* loadConfig(const char* filePath){
    CIni ini;
    INI_RES rtn = ini.OpenFile(filePath, "r");
    if (rtn == INI_SUCCESS ){
        Config *account = new Config();
        account->tdAddress = ini.GetStr("Account", "TD_ADDRESS");
        account->mdAddress = ini.GetStr("Account", "MD_ADDRESS");
        strcpy(account->brokerId, ini.GetStr("Account", "BROKER_ID"));
        strcpy(account->userId, ini.GetStr("Account", "USER_ID"));
        strcpy(account->passWord, ini.GetStr("Account", "PASSWORD"));
        return account;
    }
    else{
        cout<<"Load .ini "<<filePath<<"failed"<<endl;
    }
    return NULL;
}

#endif