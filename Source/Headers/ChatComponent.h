#ifndef CHAT_COMPONENT_H
#define CHAT_COMPONENT_H

#include "LLMService.h"

class ChatComponent {
public:
    ChatComponent(LLMService* llmService);
    void sendMessage(const std::string& playerMessage);
    std::string& getResponse();
private:
    LLMService* service;
    std::string response;
};

#endif // CHAT_COMPONENT_H