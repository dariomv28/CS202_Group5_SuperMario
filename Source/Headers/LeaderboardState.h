#pragma once
#include "State.h"

class LeaderboardState : public State
{
private:
    float TABLE_X;  // Will be calculated based on window size
    float TABLE_Y;  // Will be calculated based on window size
    const float COLUMN_WIDTH = 150.f;
    const float ROW_HEIGHT = 40.f;
    const float HEADER_HEIGHT = 50.f;
    const unsigned int MAX_ENTRIES = 10;
    const float TOTAL_WIDTH = COLUMN_WIDTH * 6; // Total width of all columns

    // UI Components
    sf::Font font;
    sf::Text titleText;
    sf::RectangleShape headerBackground;

    // Column headers
    std::vector<sf::Text> headers;
    std::vector<std::vector<sf::Text>> tableData;

    // Back button
    GUI::TextButton* backButton;

    // Helper functions
    void initVariables();
    void initFonts();
    void initTitle();
    void initHeaders();
    void initBackButton();
    void loadLeaderboardData();
    void createTableRow(size_t index, const std::string& rank, const std::string& name,
        const std::string& world1, const std::string& world2,
        const std::string& world3, const std::string& total);
    void centerTable(); // New function to handle centering

public:
    LeaderboardState(StateData* state_data);
    virtual ~LeaderboardState();

    void updateButtons();
    void updateGUI(const sf::Event& event);
    virtual void update(const float& dt, const sf::Event& event);
    virtual void render(sf::RenderTarget* target = nullptr);
};