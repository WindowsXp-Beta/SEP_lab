#ifndef ERROR_H
#define ERROR_H

#include <string>
using namespace std;

class XAppError{
public:
    explicit XAppError(const string& error_msg): error_msg(error_msg) {}
    string getErrorMsg() {return error_msg;}
private:
    string error_msg;
};
#endif // ERROR_H
