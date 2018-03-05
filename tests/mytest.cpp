/*
 * @Author: w2w 
 * @Date: 2018-02-28 22:10:38 
 * @Last Modified by: w2w
 * @Last Modified time: 2018-03-01 12:31:08
 */

#include "md/ctpmdengine.h"

#define M_TICKER "rb1801"

#include <ctime>

void TestAdapter(){
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


int main(){
    TestAdapter();
    return 0;
}