/*
 * @Author: w2w 
 * @Date: 2018-03-01 13:06:25 
 * @Last Modified by:   w2w 
 * @Last Modified time: 2018-03-01 13:06:25 
 */

#include <iostream>
#include <md/mdengine.h>
#include <md/ctpmdengine.h>
#include <wzadapter/ctpwzadapter.h>
#include <ctime>

using std::cout;
using std::endl;

CTPMdEngine::CTPMdEngine(): MdEngine(SOURCE_CTP), api(NULL), connected(false)
        , logged_in(false), req_id(0) {

}

void CTPMdEngine::Connect(){
    cout<<"Call connect function"<<endl;
    if (api == NULL) {
        api = CThostFtdcMdApi::CreateFtdcMdApi();
        api->RegisterSpi(this);
    }
    if (!connected) {
        char Md_address[] = "tcp://180.168.146.187:10031";
        api->RegisterFront(Md_address);
        api->Init();
        clock_t time_out = 3*CLOCKS_PER_SEC;
        clock_t start = clock();
        while(!connected && clock() - start < time_out){}
    }
}

void CTPMdEngine::Login(){
    cout<<"Call login function"<<endl;
    if (!logged_in) {
        CThostFtdcReqUserLoginField req;
        memset(&req, 0, sizeof(req));
        // which field is neccesary ?
        strcpy(req.BrokerID, "9999");
        strcpy(req.UserID, "111048");
        strcpy(req.Password, "9992xqq");
        int rtn_code;
        if ((rtn_code = api->ReqUserLogin(&req, req_id++))) {
            cout<<"login failed:"
                <<" error code "
                <<rtn_code<<endl;
        } else{
            clock_t start = clock();
            clock_t time_out = 3*CLOCKS_PER_SEC;
            while(!logged_in && clock() - start < time_out){}
            cout<<"Login Success!"<<endl;
        }
    }
}

void CTPMdEngine::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo,
                                 int nRequestID, bool bIsLast) {
    if (pRspInfo != NULL && pRspInfo->ErrorID !=0){
        cout<<"Login Failed:"
            <<"ErrorID = "
            <<pRspInfo->ErrorID<<endl;
    }
    else{
        logged_in = true;
    }


}
void CTPMdEngine::Block() {
    api->Join();
    api->Release();
}

void CTPMdEngine::OnFrontConnected(){
    cout<<"Call OnFrontConnected function"<<endl;
    cout<<"Connect Success"<<endl;
    connected = true;
}

void CTPMdEngine::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
//    auto data = parseFrom(*pDepthMarketData);
    WZMarketDataField data = parseFrom(*pDepthMarketData);
    on_market_data(&data);
}

void CTPMdEngine::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                     CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    cout<<"Call OnRspSubMarketData function"<<endl;
    if(pRspInfo != NULL && pRspInfo->ErrorID != 0){
        cout<<"Subscribe failed:"
            <<" error code "<<pRspInfo->ErrorID
            <<" error message"<<pRspInfo->ErrorMsg<<endl;
    }

    cout<<"register:"<<pSpecificInstrument->InstrumentID<<endl;
}

void CTPMdEngine::subscribeMarketData(const vector<string>& instruments, const vector<string>& markets) {
    cout<<"Call SubscribeMarketData function"<<endl;
    int n_count = (int)instruments.size();
    char *insts[n_count];
    for (int i = 0; i < n_count; ++i) {
        insts[i] = (char*)instruments[i].c_str();
    }
    api->SubscribeMarketData(insts, n_count);
}

