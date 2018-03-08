//
// Created by w2w on 18-3-7.
//


#include <ctime>
#include <md/ctpmdengine.h>
#include <util/iniparser.h>
#include <iostream>

using std::cout;
using std::endl;



Config* config;

void TestMd(const Config* config){
    CTPMdEngine* md = new CTPMdEngine();
    md->load(config);
    md->Connect();
    md->Login();
    vector<string> tickers;
//    tickers.push_back(M_TICKER);
    tickers.push_back("al1805");
    vector<string> markets;
    markets.push_back("CTP");
    md->subscribeMarketData(tickers, markets);
    md->Block();
}

//Config* loadConfig(const char* filePath){
//    CIni ini;
//    INI_RES rtn = ini.OpenFile(filePath, "r");
//    if (rtn == INI_SUCCESS ){
//        Config *account = new Config();
//        account->tdAddress = ini.GetStr("Account", "TD_ADDRESS");
//        account->mdAddress = ini.GetStr("Account", "MD_ADDRESS");
//        strcpy(account->brokerId, ini.GetStr("Account", "BROKER_ID"));
//        strcpy(account->userId, ini.GetStr("Account", "USER_ID"));
//        strcpy(account->passWord, ini.GetStr("Account", "PASSWORD"));
//        return account;
//    }
//    else{
//        cout<<"Load .ini "<<filePath<<"failed"<<endl;
//    }
//    return NULL;
//}



int main(int argc, char* argv[]){
    config = loadConfig("../MyConfig.ini");
    if (config != NULL){
        TestMd(config);
    }

    return 0;
}
