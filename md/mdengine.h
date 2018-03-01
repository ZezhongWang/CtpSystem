/*
 * @Author: w2w 
 * @Date: 2018-02-27 21:35:53 
 * @Last Modified by: w2w
 * @Last Modified time: 2018-02-27 21:46:26
 */
#include "baseengine.h"

class MdEngine: public BaseEngine
{
public:
    virtual void load();
    virtual void connect();
    virtual void login();
    
public:
    virtual void subscribeMarketData(const vector<string>& instruments, const vector<string>& markets);

}