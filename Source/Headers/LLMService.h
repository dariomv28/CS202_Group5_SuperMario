#pragma once

#include "stdafx.h"

class LLMService {
public:
    virtual std::string generateResponse(const std::string& playerMessage) = 0;
    virtual ~LLMService() = default;
};