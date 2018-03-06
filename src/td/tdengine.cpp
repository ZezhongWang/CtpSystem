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
    if (errorId == 0){
        cout<<"Order Insert Success:\n";
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
        <<"\tInvestorID\t"<<rtn_order->InvestorID<<endl;


}