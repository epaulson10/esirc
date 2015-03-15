#include "protocol.h"
using std::string;
using std::cout;


parseResult parse(string msg)
{
    cout << msg << "\n";
    parseResult rtn = {false, ""};
    return rtn;
}

string Protocol::genNICK(string nick) {
    return "NICK" + nick;
}

string Protocol::genUSER(string username, string mode, string realName) {
    return "USER " + mode + " * :" + realName;
}

string Protocol::genPONG(string args) {
    return "PONG :" + args;
}

string Protocol::genPRIVMSG(string to, string msg) {
    return "PRIVMSG " + to + " :" + msg;
}

string Protocol::genQUIT(string reason) {
    return "QUIT :" + reason;
}
