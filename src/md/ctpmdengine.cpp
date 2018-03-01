/*
 * @Author: w2w 
 * @Date: 2018-03-01 13:06:25 
 * @Last Modified by:   w2w 
 * @Last Modified time: 2018-03-01 13:06:25 
 */

#include <iostream>
#include <md/mdengine.h>
#include <md/ctpmdengine.h>
#include <wzadapter/wzconstant.h>

using std::cout;
using std::endl;

CTPMdEngine::CTPMdEngine(): MdEngine(SOURCE_CTP), api(NULL), connected(false)
        , logged_in(false), req_id(0) {

}

void CTPMdEngine::connect(){
    cout<<"Call connect function"<<endl;
    if (api == NULL) {
        api = CThostFtdcMdApi::CreateFtdcMdApi();

        api->RegisterSpi(this);    
    }
    if (!connected) {
        string address = "tcp://180.168.146.187:10031";
        api->RegisterFront((char *) address.c_str());
        api->Init();
    }
}

void CTPMdEngine::login(){
    cout<<"Call login function"<<endl;
    if (!logged_in) {
        CThostFtdcReqUserLoginField req = {};
        // which field is neccesary ?
        strcpy(req.BrokerID, "9999");
        strcpy(req.UserID, "111048");
        strcpy(req.Password, "9992xqq");
        if (api->ReqUserLogin(&req, req_id++)) {
            cout<<"login failed!"<<endl;
        }
    }
}

void CTPMdEngine::OnFrontConnected(){
    cout<<"Call OnFrontConnected function"<<endl;
    cout<<"Connect Success"<<endl;
}

void CTPMdEngine::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
    cout<<"Call OnRtnDepthMarketData function"<<endl;
}

void CTPMdEngine::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                     CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    cout<<"Call OnRspSubMarketData function"<<endl;
}