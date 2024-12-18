#include "Headers/OllamaLLMService.h"

// Static callback function implementation
size_t OllamaLLMService::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
        return newLength;
    }
    catch (std::bad_alloc& e) {
        return 0;
    }
}

// Generate response method implementation
std::string OllamaLLMService::generateResponse(const std::string& playerMessage) {

    /*
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Initialize CURL

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Local Ollama API endpoint
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:11434/api/chat");

        // Set headers
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Prepare JSON payload
        nlohmann::json payload = {
            {"model", "llama2"},
            {"messages", {
                {{"role", "system"}, {"content", "You are a helpful assistant in a game chat."}},
                {{"role", "user"}, {"content", playerMessage}}
            }},
            {"stream", false}
        };
        std::string payloadStr = payload.dump();

        // Set POST options
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());

        // Callback to store response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            return "Error: " + std::string(curl_easy_strerror(res));
        }

        // Parse the JSON response
        try {
            auto jsonResponse = nlohmann::json::parse(readBuffer);
            std::string response = jsonResponse["message"]["content"];

            // Cleanup
            curl_easy_cleanup(curl);
            curl_slist_free_all(headers);
            curl_global_cleanup();

            return response;
        }
        catch (const nlohmann::json::exception& e) {
            return "JSON Parsing Error: " + std::string(e.what()) +
                "\nRaw Response: " + readBuffer;
        }
    } */
     
       
    std::string msg = playerMessage;

    if (msg.find("hello") != std::string::npos || msg.find("hi") != std::string::npos) {
        return "Hi there! Ready to save the princess?";
    }

    if (msg.find("how to play") != std::string::npos || msg.find("controls") != std::string::npos) {
        return "Use arrow keys to move and space to jump. Good luck!";
    }

    if (msg.find("where") != std::string::npos) {
        return "You are in the Mushroom Kingdom, home to Mario and Luigi!";
    }

    if (msg.find("what should i do") != std::string::npos || msg.find("objective") != std::string::npos) {
        return "Your goal is to rescue Princess Peach and defeat Bowser!";
    }

    if (msg.find("how to jump") != std::string::npos) {
        return "Press the SPACE bar to jump over obstacles.";
    }

    if (msg.find("how to attack") != std::string::npos || msg.find("enemies") != std::string::npos) {
        return "Jump on the enemies to defeat them, or use power-ups like fireballs!";
    }

    if (msg.find("how to get power up") != std::string::npos) {
        return "Collect mushrooms and flowers from '?' blocks to get power-ups.";
    }

    if (msg.find("princess") != std::string::npos) {
        return "Reach the end of the castle and defeat Bowser to save Princess Peach.";
    }

    if (msg.find("what are coins for") != std::string::npos || msg.find("coins") != std::string::npos) {
        return "Collect 100 coins to get an extra life!";
    }

    if (msg.find("how to sprint") != std::string::npos || msg.find("run faster") != std::string::npos) {
        return "Hold down the SHIFT key while moving to sprint.";
    }

    if (msg.find("extra life") != std::string::npos) {
        return "Collect green 1-Up mushrooms or 100 coins to gain an bonus powers, not extra life!";
    }

    if (msg.find("boss") != std::string::npos) {
        return "Boss is waiting for you while playing the game. Be prepared!";
    }

    if (msg.find("game over") != std::string::npos) {
        return "Don't worry! Restart the level and try again. You can do it!";
    }

    if (msg.find("save progress") != std::string::npos) {
        return "Your progress is saved automatically after completing a level.";
    }

	if (msg.find("how are you") != std::string::npos) {
		return "Im doing great, thanks for asking. Its been a productive day, and Im happy to take a break and chat with you. I see you re in the middle of a game and it must be fun. Its always interesting to hear about the gameplay and the moments that keep you on the edge, especially when there s a lot going on.";
	}


    return "Sorry, I don't understand that.";
}
   
