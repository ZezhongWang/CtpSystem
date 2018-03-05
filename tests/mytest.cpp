/*
 * @Author: w2w 
 * @Date: 2018-02-28 22:10:38 
 * @Last Modified by: w2w
 * @Last Modified time: 2018-03-01 12:31:08
 */

#include "md/ctpmdengine.h"

#define M_TICKER "rb1801"

#include <ctime>
#include <td/ctptdengine.h>

void TestMd(){
    CTPMdEngine* md = new CTPMdEngine();
    md->Connect();
    md->Login();

//    md->subscribeMarketData();
    vector<string> tickers;
    tickers.push_back(M_TICKER);
    tickers.push_back("al1805");
    vector<string> markets;
    markets.push_back("CTP");
    md->subscribeMarketData(tickers, markets);

    md->Block();
}

void TestTd(){
    CTPTdEngine* td = new CTPTdEngine();
    td->Connect();
    td->Login();
    // 账户查询
    WZQryAccountField* req = new WZQryAccountField();
    strcpy(req->BrokerID, "9999");
    strcpy(req->InvestorID, "111048");
    td->req_qry_account(req, 0, 0);
    // 插入订单
    WZInputOrderField* order = new WZInputOrderField();
    strcpy(order->BrokerID, "9999");
    strcpy(order->InvestorID, "111048");
    strcpy(order->InstrumentID, "al1805");
    strcpy(order->OrderRef, "000000000001");
    // 不确定
//    strcpy(order->UserID, "13226602970");
    order->OrderPriceType = WZ_CHAR_LimitPrice;
    order->Direction = WZ_CHAR_Buy;
    order->OffsetFlag = WZ_CHAR_Open;
    order->HedgeFlag = WZ_CHAR_Hedge;
    order->LimitPrice = 50000;
    order->Volume = 10;
    order->TimeCondition = WZ_CHAR_GFD;
    order->VolumeCondition = WZ_CHAR_AV;
    order->MinVolume = 0;
    order->ContingentCondition = WZ_CHAR_Immediately;
    order->StopPrice = 0;
    order->ForceCloseReason = WZ_CHAR_NotForceClose;
    order->IsAutoSuspend = 0;
    td->req_order_insert(order, 0, 0, 0);


    td->Block();
}

int main(){
//    TestMd();
    TestTd();
    return 0;
}