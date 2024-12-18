#pragma once

#include "LLMService.h"

class OllamaService : public LLMService {
public:
    // Method to generate a response to a player's message
    std::string generateResponse(const std::string& playerMessage) override;

private:
    // Static callback function for libcurl
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
};