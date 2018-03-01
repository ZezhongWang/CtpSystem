/*
 * @Author: w2w 
 * @Date: 2018-02-27 21:35:53 
 * @Last Modified by: w2w
 * @Last Modified time: 2018-02-27 21:46:26
 */
#ifndef MD_ENGINE_H
#define MD_ENGINE_H

#include <base/baseengine.h>

class MdEngine: public BaseEngine
{
public:
    MdEngine(const short source = 0);
public:
    //virtual void subscribeMarketData(const vector<string>& instruments, const vector<string>& markets) {};

};



#endif