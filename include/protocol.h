#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <iostream>

const int MAX_MSG_LEN = 512;

typedef struct parseResultTag {
    bool responseRequired;
    std::string response;
} parseResult;

class Protocol {
    public:
        parseResult parse(std::string msg);
        std::string genNICK(std::string nick);
        std::string genUSER(std::string username, std::string mode, std::string realName);
        std::string genPONG(std::string args);
        std::string genPRIVMSG(std::string to, std::string msg);
        std::string genQUIT(std::string reason);
    private:

};

#endif
