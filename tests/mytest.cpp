/*
 * @Author: w2w 
 * @Date: 2018-02-28 22:10:38 
 * @Last Modified by: w2w
 * @Last Modified time: 2018-03-01 12:31:08
 */

#include "md/ctpmdengine.h"


void TestAdapter(){
    CTPMdEngine* md = new CTPMdEngine();
    md->connect();
    md->login();
}


int main(){
    TestAdapter();
    return 0;
}