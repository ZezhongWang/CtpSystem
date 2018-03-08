/*
 * @Author: w2w 
 * @Date: 2018-02-27 21:36:39 
 * @Last Modified by:   w2w 
 * @Last Modified time: 2018-02-27 21:36:39 
 */
#include <base/baseengine.h>
#include <td/tdengine.h>
#include <iostream>


using std::cout;
using std::endl;


TdEngine::TdEngine(const short source) : BaseEngine(source) {


}


void TdEngine::on_rsp_account(const WZRspAccountField *account, bool isLast, int requestId, int errorId,
                              const char *errorMsg) {
    if (errorId == 0){
        cout<<"Available\t"<<account->Available
            <<"\tBalance\t"<<account->Balance
            <<"\tBrokerID\t"<<account->BrokerID
            <<"\tCashIn\t"<<account->CashIn
            <<"\tCloseProfit\t"<<account->CloseProfit<<endl;
    }
}

void TdEngine::on_rsp_order_insert(const WZInputOrderField *order, int requestId, int errorId, const char *errorMsg) {
    cout<<"Call on_rsp_order_insert function"<<endl;
    if (errorId){
        cout<<"Order Insert failed:\n";
        cout<<"InvestorID\t"<<order->InvestorID
            <<"\tInstrumentID\t"<<order->InstrumentID
            <<"\tBusinessUnit\t"<<order->BusinessUnit
            <<"\tDirection\t"<<order->Direction
            <<"\tExchangeID\t"<<order->ExchangeID<<endl;
    }
}

void TdEngine::on_rtn_order(const WZRtnOrderField *rtn_order) {
    cout<<"Call on_rtn_order function"<<endl;
    cout<<"ExchangeID\t"<<rtn_order->ExchangeID
        <<"\tDirection\t"<<rtn_order->Direction
        <<"\tBusinessUnit\t"<<rtn_order->BusinessUnit
        <<"\tInstrumentID\t"<<rtn_order->InstrumentID
        <<"\tInvestorID\t"<<rtn_order->InvestorID
        <<"\tVolumeTraded\t"<<rtn_order->VolumeTraded
        <<"\tOrderStatus\t"<<rtn_order->OrderStatus
        <<"\tLimitPrice\t"<<rtn_order->LimitPrice
        <<"\tOrderStatus\t"<<rtn_order->OrderStatus<<endl;
}

void TdEngine::on_rtn_trade(const WZRtnTradeField *rtn_order) {
    cout<<"Call on_rtn_trade function"<<endl;
    cout<<"ExchangeID\t"<<rtn_order->ExchangeID
        <<"\tDirection\t"<<rtn_order->Direction
        <<"\tVolume\t"<<rtn_order->Volume
        <<"\tInstrumentID\t"<<rtn_order->InstrumentID
        <<"\tInvestorID\t"<<rtn_order->InvestorID<<endl;
}

void TdEngine::on_rsp_order_action(const WZOrderActionField *order, int requestId, int errorId, const char *errorMsg) {
    cout<<"Call on_rsp_order_action function"<<endl;
    cout<<"Error Id = "<<errorId<<endl;
}

void TdEngine::load(const Config *config) {
    this->tdAddress = config->tdAddress;
    this->mdAddress = config->mdAddress;
    strcpy(this->brokerId, config->brokerId);
    strcpy(this->userId, config->userId);
    strcpy(this->passWord, config->passWord);
}