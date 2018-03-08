/*
 * @Author: w2w 
 * @Date: 2018-02-27 21:35:53 
 * @Last Modified by: w2w
 * @Last Modified time: 2018-02-27 21:46:26
 */
#ifndef MD_ENGINE_H
#define MD_ENGINE_H

#include <base/baseengine.h>
#include <wzadapter/wzdatastruct.h>
#include <vector>
#include <util/iniparser.h>

using std::vector;

class MdEngine: public BaseEngine
{
public:
    string tdAddress;
    string mdAddress;
    char brokerId[19];
    char userId[19];
    char passWord[21];

public:
    MdEngine(const short source = 0);
public:
    virtual void load(const Config* config);

    virtual void subscribeMarketData(const vector<string>& instruments, const vector<string>& markets) = 0;
//    virtual void subscribeOrderTrade(const vector<string>& instruments, const vector<string>& markets) = 0;
    void on_market_data(const WZMarketDataField* data);

};



#endif