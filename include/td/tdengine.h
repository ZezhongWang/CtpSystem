/*
 * @Author: w2w 
 * @Date: 2018-02-27 21:36:39 
 * @Last Modified by:   w2w 
 * @Last Modified time: 2018-02-27 21:36:39 
 */

#ifndef TD_ENGINE_H
#define TD_ENGINE_H

#include <base/baseengine.h>
#include <wzadapter/wzdatastruct.h>
#include <vector>
#include <util/iniparser.h>

using std::vector;

class TdEngine: public BaseEngine
{
public:
    string tdAddress;
    string mdAddress;
    char brokerId[19];
    char userId[19];
    char passWord[21];

public:
    TdEngine(const short source = 0);
public:
    virtual void load(const Config* config);

    virtual void req_qry_account(const WZQryAccountField* data, int account_index, int requestId) = 0;
    virtual void req_order_insert(const WZInputOrderField* data, int account_index, int requestId, long rcv_time) = 0;
    virtual void req_order_action(const WZOrderActionField* data, int account_index, int requestId, long rcv_time) = 0;

    void on_rsp_account(const WZRspAccountField* account, bool isLast, int requestId,
                        int errorId=0, const char* errorMsg=NULL);

    void on_rsp_order_insert(const WZInputOrderField* action, int requestId,
                             int errorId=0, const char* errorMsg=NULL);
    void on_rtn_order(const WZRtnOrderField* rtn_order);
    void on_rtn_trade(const WZRtnTradeField* rtn_order);
    void on_rsp_order_action(const WZOrderActionField* order, int requestId,
                             int errorId=0, const char* errorMsg=NULL);
};



#endif