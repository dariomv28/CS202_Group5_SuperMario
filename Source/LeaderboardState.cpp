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
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
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

void LeaderboardState::loadLeaderboardData()
{
    // Clear existing data
    tableData.clear();

    // TODO: Load actual data from your game's scoring system
    // This is example data
    createTableRow(0, "1", "Player1", "100", "95", "90", "285");
    createTableRow(1, "2", "Player2", "95", "90", "85", "270");
    createTableRow(2, "3", "Player3", "90", "85", "80", "255");
    // Add more rows as needed
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