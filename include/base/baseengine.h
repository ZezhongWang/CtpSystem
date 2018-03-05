/*
 * @Author: w2w 
 * @Date: 2018-02-27 21:38:42 
 * @Last Modified by: w2w
 * @Last Modified time: 2018-02-28 22:37:42
 */
#ifndef BASE_ENGINE
#define BASE_ENGINE

#include <string>

using std::string;

class BaseEngine{

protected:
    const short source_id;
    bool is_running;

public:
    BaseEngine(const short source = 0);
    ~BaseEngine();

    void initialize(const string &json_str);

//    virtual void init() = 0;
//    virtual void load() = 0;
    virtual void Connect() = 0;
    virtual void Login() = 0;
    virtual void Block() = 0;
};

#endif