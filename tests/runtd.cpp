//
// Created by w2w on 18-3-7.
//
/*
 * @Author: w2w
 * @Date: 2018-02-28 22:10:38
 * @Last Modified by: w2w
 * @Last Modified time: 2018-03-01 12:31:08
 */


#define M_TICKER "rb1801"

#include <ctime>
#include <td/ctptdengine.h>
#include <util/iniparser.h>

Config* config;

void TestTd(Config *config){
    CTPTdEngine* td = new CTPTdEngine();
    td->load(config);
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
    strcpy(order->InstrumentID, "al1803");
    strcpy(order->OrderRef, "000000000001");
    // 不确定
//    strcpy(order->UserID, "13226602970");
    order->OrderPriceType = WZ_CHAR_LimitPrice;
    order->Direction = WZ_CHAR_Buy;
    order->OffsetFlag = WZ_CHAR_Open;
    order->HedgeFlag = WZ_CHAR_Speculation;
    order->LimitPrice = 14060;
    order->Volume = 10;
    order->TimeCondition = WZ_CHAR_GFD;
    order->VolumeCondition = WZ_CHAR_AV;
    order->MinVolume = 1;
    order->ContingentCondition = WZ_CHAR_Immediately;
    order->StopPrice = 0;
    order->ForceCloseReason = WZ_CHAR_NotForceClose;
    order->IsAutoSuspend = 0;


    td->req_order_insert(order, 0, 0, 0);

    WZOrderActionField* action = new WZOrderActionField();
    strcpy(action->BrokerID, "9999");
    strcpy(action->InvestorID, "111048");
    strcpy(action->InstrumentID, "al1803");
    strcpy(action->OrderRef, "000000000001");
    td->Block();
}

int main(int argc, char* argv[]){
    config = loadConfig("../MyConfig.ini");
    if (config != NULL){
        TestTd(config);
    }

    return 0;
}