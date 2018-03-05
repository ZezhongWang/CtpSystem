/*
 * @Author: w2w 
 * @Date: 2018-02-27 21:40:58 
 * @Last Modified by:   w2w 
 * @Last Modified time: 2018-02-27 21:40:58 
 */
#include <iostream>
#include <td/tdengine.h>
#include <td/ctptdengine.h>
#include <wzadapter/ctpwzadapter.h>
#include <ctime>

using std::cout;
using std::endl;

CTPTdEngine::CTPTdEngine(): TdEngine(SOURCE_CTP), api(NULL), connected(false)
        , logged_in(false), req_id(0) {
}

void CTPTdEngine::Connect(){
    cout<<"Call connect function"<<endl;
    if (api == NULL) {
        api = CThostFtdcTraderApi::CreateFtdcTraderApi();
        api->RegisterSpi(this);
    }
    if (!connected) {
        char Td_address[] = "tcp://180.168.146.187:10030";
        api->RegisterFront(Td_address);
        api->Init();
        clock_t time_out = 3*CLOCKS_PER_SEC;
        clock_t start = clock();
        while(!connected && clock() - start < time_out){}
    }
}

void CTPTdEngine::Login(){
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

void CTPTdEngine::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo,
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

void CTPTdEngine::OnFrontConnected() {
    cout<<"Call OnFrontConnected function"<<endl;
    cout<<"Connect Success"<<endl;
    connected = true;
}

void CTPTdEngine::Block() {
    api->Join();
    api->Release();
}

void CTPTdEngine::req_qry_account(const WZQryAccountField *data, int account_index, int requestId) {
    CThostFtdcQryTradingAccountField req = parseTo(*data);
    int rtn_val;
    if((rtn_val=api->ReqQryTradingAccount(&req, requestId))) {
        cout<<"Request account failed:"
            <<" error code "
            <<rtn_val<<endl;
    }
}

void CTPTdEngine::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount,
                                         CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    int errorId = (pRspInfo == NULL) ? 0 : pRspInfo->ErrorID;
    const char* errorMsg = (pRspInfo == NULL) ? NULL : pRspInfo->ErrorMsg;
    WZRspAccountField account = parseFrom(*pTradingAccount);
    on_rsp_account(&account, bIsLast, nRequestID, errorId, errorMsg);
}


void CTPTdEngine::req_order_insert(const WZInputOrderField *data, int account_index, int requestId, long rcv_time) {
    cout<<"Call req_order_insert function"<<endl;
    CThostFtdcInputOrderField req = parseTo(*data);
    int rtn_val;
    if((rtn_val = api->ReqOrderInsert(&req, ++requestId))){
        cout<<"Request Order Insert failed:"
            <<" error code "
            <<rtn_val<<endl;
    }
}

void CTPTdEngine::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo,
                                   int nRequestID, bool bIsLast) {
    cout<<"Call OnRspOrderInsert function"<<endl;
    int errorId = (pRspInfo == NULL) ? 0 : pRspInfo->ErrorID;
    const char* errorMsg = (pRspInfo == NULL) ? NULL : pRspInfo->ErrorMsg;
    WZInputOrderField data = parseFrom(*pInputOrder);
    if (errorId != 0){
        cout<<"order insert failed:"
            <<" error id "
            <<errorId<<endl;
    }
    on_rsp_order_insert(&data, nRequestID, errorId, errorMsg);
}
//void CTPTdEngine::req_order_insert(const WZInputOrderField *data, int account_index, int requestId, long rcv_time) {
//
//}

//void CTPTdEngine::req_order_action(const WZOrderActionField *data, int account_index, int requestId, long rcv_time) {
//
//}
