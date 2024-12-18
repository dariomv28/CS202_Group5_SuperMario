#include "Headers/ChatComponent.h"

ChatComponent::ChatComponent(LLMService* llmService)
    : service(llmService) {};

void ChatComponent::sendMessage(const std::string& playerMessage) {
    response = service->generateResponse(playerMessage);
}

std::string& ChatComponent::getResponse() {
	// std::cout << response << std::endl;
    return response;
}   