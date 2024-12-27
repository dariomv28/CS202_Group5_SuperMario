#include "Headers/LeaderboardState.h"

LeaderboardState::LeaderboardState(StateData* state_data)
    : State(state_data)
{
    initVariables();
    initFonts();
    centerTable();
    initTitle();
    initHeaders();
    initBackButton();
    loadLeaderboardData();
}

LeaderboardState::~LeaderboardState()
{
    delete backButton;
}

void LeaderboardState::centerTable()
{
    // Calculate center position for table
    TABLE_X = (window->getSize().x - TOTAL_WIDTH) / 2.f;
    TABLE_Y = (window->getSize().y - (ROW_HEIGHT * MAX_ENTRIES + HEADER_HEIGHT)) / 2.f;
}

void LeaderboardState::initVariables()
{
    // Initialize header background
    headerBackground.setSize(sf::Vector2f(TOTAL_WIDTH, HEADER_HEIGHT));
    headerBackground.setFillColor(sf::Color(70, 70, 70, 200));
    // Position will be set after centerTable() is called
}

void LeaderboardState::initFonts()
{
    if (!font.loadFromFile("Source/Resources/font/American Captain.ttf"))
    {
        throw("ERROR::LEADERBOARDSTATE::COULD NOT LOAD FONT");
    }
}

void LeaderboardState::initTitle()
{
    titleText.setFont(font);
    titleText.setString("Leaderboard");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);

    // Center the title above the table
    titleText.setPosition(
        window->getSize().x / 2.f - titleText.getGlobalBounds().width / 2.f,
        TABLE_Y - 100.f
    );
}

void LeaderboardState::initHeaders()
{
    // Update header background position
    headerBackground.setPosition(TABLE_X, TABLE_Y);

    std::vector<std::string> headerNames = { "Rank", "Name", "World 1", "World 2", "World 3", "Total" };

    for (size_t i = 0; i < headerNames.size(); ++i)
    {
        sf::Text header;
        header.setFont(font);
        header.setString(headerNames[i]);
        header.setCharacterSize(24);
        header.setFillColor(sf::Color::White);
        header.setPosition(
            TABLE_X + (i * COLUMN_WIDTH) + (COLUMN_WIDTH / 2.f) - (header.getGlobalBounds().width / 2.f),
            TABLE_Y + (HEADER_HEIGHT / 2.f) - (header.getGlobalBounds().height / 2.f)
        );
        headers.push_back(header);
    }
}

void LeaderboardState::initBackButton()
{
    backButton = new GUI::TextButton(
        false,
        30.f, 30.f, 100.f, 50.f,
        &font, "Back", 24,
        sf::Color(70, 70, 70, 200),  // Background idle color
        sf::Color(250, 250, 250, 250),  // Background hover color
        sf::Color(20, 20, 20, 50),  // Background active color
        sf::Color(0, 0, 255, 255),  // Text idle color (blue)
        sf::Color(150, 150, 150, 255),  // Text hover color
        sf::Color(20, 20, 20, 255)   // Text active color
    );
}

void LeaderboardState::createTableRow(size_t index, const std::string& rank, const std::string& name,
    const std::string& world1, const std::string& world2,
    const std::string& world3, const std::string& total)
{
    std::vector<std::string> rowData = { rank, name, world1, world2, world3, total };
    std::vector<sf::Text> row;

    for (size_t i = 0; i < rowData.size(); ++i)
    {
        sf::Text cell;
        cell.setFont(font);
        cell.setString(rowData[i]);
        cell.setCharacterSize(20);
        cell.setFillColor(sf::Color::White);
        cell.setPosition(
            TABLE_X + (i * COLUMN_WIDTH) + (COLUMN_WIDTH / 2.f) - (cell.getGlobalBounds().width / 2.f),
            TABLE_Y + HEADER_HEIGHT + (index * ROW_HEIGHT) + (ROW_HEIGHT / 2.f) - (cell.getGlobalBounds().height / 2.f)
        );
        row.push_back(cell);
    }

    tableData.push_back(row);
}

/*void LeaderboardState::loadLeaderboardData()
{
    // Clear existing data
    tableData.clear();

    // TODO: Load actual data from your game's scoring system
    // This is example data
    createTableRow(0, "1", "Player1", "100", "95", "90", "285");
    createTableRow(1, "2", "Player2", "95", "90", "85", "270");
    createTableRow(2, "3", "Player3", "90", "85", "80", "255");
    // Add more rows as needed
}*/

void LeaderboardState::loadLeaderboardData()
{
    // Clear existing data
    tableData.clear();

    std::ifstream file("LeaderBoard.csv");
    if (!file.is_open())
    {
        throw std::runtime_error("ERROR::LEADERBOARDSTATE::COULD NOT OPEN LeaderBoard.csv");
    }

    std::string line;
    std::vector<std::tuple<std::string, int, int, int, int>> players; // Name, World1, World2, World3, Total

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string name, level1, level2, level3, level4, level5, level6, level7, level8, level9;
        int w1, w2, w3, total;

        // Read player name and scores for 9 levels
        std::getline(ss, name, ',');
        std::getline(ss, level1, ',');
        std::getline(ss, level2, ',');
        std::getline(ss, level3, ',');
        std::getline(ss, level4, ',');
        std::getline(ss, level5, ',');
        std::getline(ss, level6, ',');
        std::getline(ss, level7, ',');
        std::getline(ss, level8, ',');
        std::getline(ss, level9, ',');

        // Calculate world scores and total score
        w1 = std::stoi(level1) + std::stoi(level2) + std::stoi(level3);
        w2 = std::stoi(level4) + std::stoi(level5) + std::stoi(level6);
        w3 = std::stoi(level7) + std::stoi(level8) + std::stoi(level9);
        total = w1 + w2 + w3;

        if (total > 0)
        {
            players.emplace_back(name, w1, w2, w3, total);
        }
    }

    file.close();

    // Sort players by total score in descending order
    std::sort(players.begin(), players.end(), [](const auto& a, const auto& b) {
        return std::get<4>(a) > std::get<4>(b);
        });

    // Populate table with the sorted data
    size_t rank = 1;
    for (const auto& player : players)
    {
        createTableRow(rank,
            std::to_string(rank),
            std::get<0>(player),
            std::to_string(std::get<1>(player)),
            std::to_string(std::get<2>(player)),
            std::to_string(std::get<3>(player)),
            std::to_string(std::get<4>(player)));
        rank++;
    }
}

void LeaderboardState::updateButtons()
{
    backButton->update(mousePosWindow);

    if (backButton->isPressed())
    {
        endState();
    }
}

void LeaderboardState::updateGUI(const sf::Event& event)
{
    updateButtons();
}

void LeaderboardState::update(const float& dt, const sf::Event& event)
{
    updateMousePosition();
    updateGUI(event);
}

void LeaderboardState::render(sf::RenderTarget* target)
{
    if (!target)
        target = window;

    // Render title
    target->draw(titleText);

    // Render header background
    target->draw(headerBackground);

    // Render headers
    for (const auto& header : headers)
    {
        target->draw(header);
    }

    // Render table data
    for (const auto& row : tableData)
    {
        for (const auto& cell : row)
        {
            target->draw(cell);
        }
    }

    // Render back button
    backButton->render(target);
}