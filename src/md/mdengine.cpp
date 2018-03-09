//
// Created by w2w on 18-3-1.
//

#include <base/baseengine.h>
#include <md/mdengine.h>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;


MdEngine::MdEngine(const short source) : BaseEngine(source) {


}


void MdEngine::on_market_data(const WZMarketDataField *data) {
    if(is_running){
        char filePath[50] = {'\0'};
        sprintf(filePath, "../data/%s_market_data.csv", data->InstrumentID);
        ofstream fout(filePath, ios::app);
        fout<<"InstrumentID\t"<<data->InstrumentID
            <<"\tVolume\t"<<data->Volume
            <<"\tHighestPrice\t"<<data->HighestPrice
            <<"\tLowestPrice\t"<<data->LowestPrice
            <<"\tBidPrice\t"<<data->BidPrice1
            <<"\tBidVolume\t"<<data->BidVolume1
            <<"\tAskPrice\t"<<data->AskPrice1
            <<"\tAskVolume\t"<<data->AskVolume1<<endl;
        fout.close();
    }
}

void MdEngine::load(const Config *config) {
    this->tdAddress = config->tdAddress;
    this->mdAddress = config->mdAddress;
    strcpy(this->brokerId, config->brokerId);
    strcpy(this->userId, config->userId);
    strcpy(this->passWord, config->passWord);
}
