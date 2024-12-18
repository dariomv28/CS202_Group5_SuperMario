#include "Headers/OllamaService.h"

OllamaService::OllamaService() {
    std::ifstream file("Config/docs.txt");
    if (!file) {
        std::cerr << "Error: Unable to open file.\n";
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;

        std::getline(iss, key, '|');
        std::getline(iss, value);

        if (!key.empty() && !value.empty()) {
            responses[key] = value;
        }
    }

    file.close();
}

// Static callback function implementation
size_t OllamaService::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
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
std::string OllamaService::generateResponse(const std::string& playerMessage) {


    //CURL* curl;
    //CURLcode res;
    //std::string readBuffer;

    //// Initialize CURL

    //curl_global_init(CURL_GLOBAL_DEFAULT);
    //curl = curl_easy_init();

    //if (curl) {
    //    // Local Ollama API endpoint
    //    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:11434/api/chat");

    //    // Set headers
    //    struct curl_slist* headers = NULL;
    //    headers = curl_slist_append(headers, "Content-Type: application/json");
    //    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    //    // Prepare JSON payload
    //    nlohmann::json payload = {
    //        {"model", "llama2"},
    //        {"messages", {
    //            {{"role", "system"}, {"content", "You are a helpful assistant in a game chat."}},
    //            {{"role", "user"}, {"content", playerMessage}}
    //        }},
    //        {"stream", false}
    //    };
    //    std::string payloadStr = payload.dump();

    //    // Set POST options
    //    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    //    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());

    //    // Callback to store response
    //    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    //    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    //    // Perform the request
    //    res = curl_easy_perform(curl);

    //    // Check for errors
    //    if (res != CURLE_OK) {
    //        return "Error: " + std::string(curl_easy_strerror(res));
    //    }

    //    // Parse the JSON response
    //    try {
    //        auto jsonResponse = nlohmann::json::parse(readBuffer);
    //        std::string response = jsonResponse["message"]["content"];

    //        // Cleanup
    //        curl_easy_cleanup(curl);
    //        curl_slist_free_all(headers);
    //        curl_global_cleanup();

    //        return response;
    //    }
    //    catch (const nlohmann::json::exception& e) {
    //        return "JSON Parsing Error: " + std::string(e.what()) +
    //            "\nRaw Response: " + readBuffer;
    //    }
    //}

    std::vector<std::string> playerVectorMessage;

	std::stringstream ss(playerMessage);

    std::string token;

    while (ss >> token) {
		playerVectorMessage.push_back(token);
    }

	std::string ans = "Sorry, I don't understand that.";
    int mx = 0;

    for (const auto& res : responses) {
		std::string keyword = res.first;
		std::string response = res.second;

		int cnt = 0;

        for (std::string word : playerVectorMessage) {
			if (keyword.find(word) != std::string::npos) {
                ++cnt;
			}
        }

		if (cnt > mx) {
			mx = cnt;
			ans = response;
		}
    }

    return ans;
}

