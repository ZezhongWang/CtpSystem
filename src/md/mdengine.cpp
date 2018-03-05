//
// Created by w2w on 18-3-1.
//

#include <base/baseengine.h>
#include <md/mdengine.h>
#include <iostream>

using std::cout;
using std::endl;


MdEngine::MdEngine(const short source) : BaseEngine(source) {


}


void MdEngine::on_market_data(const WZMarketDataField *data) {
    if(is_running){
        cout<<"InstrumentID\t"<<data->InstrumentID
            <<"\tBidPrice\t"<<data->BidPrice1
            <<"\tBidVolume\t"<<data->BidVolume1
            <<"\tAskPrice\t"<<data->AskPrice1
            <<"\tAskVolume\t"<<data->AskVolume1<<endl;
    }
}
