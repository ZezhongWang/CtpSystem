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

using std::vector;

class TdEngine: public BaseEngine
{
public:
    TdEngine(const short source = 0);
public:
    virtual void req_qry_account(const WZQryAccountField* data, int account_index, int requestId) = 0;
    virtual void req_order_insert(const WZInputOrderField* data, int account_index, int requestId, long rcv_time) = 0;
//    virtual void req_order_action(const WZOrderActionField* data, int account_index, int requestId, long rcv_time) = 0;
    void on_rsp_account(const WZRspAccountField* account, bool isLast, int requestId,
                        int errorId=0, const char* errorMsg=NULL);
    void on_rsp_order_insert(const WZInputOrderField* order, int requestId,
                             int errorId=0, const char* errorMsg=NULL);
    void on_rtn_order(const WZRtnOrderField* rtn_order);
};



#endif