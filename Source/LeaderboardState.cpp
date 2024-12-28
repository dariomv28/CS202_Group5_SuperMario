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
    // Adjust TABLE_Y to move the table closer to the header
    TABLE_Y = (window->getSize().y - (ROW_HEIGHT * MAX_ENTRIES + HEADER_HEIGHT)) / 2.f - 50.f;
}

void LeaderboardState::initVariables()
{
    // Initialize header background
    headerBackground.setSize(sf::Vector2f(TOTAL_WIDTH, HEADER_HEIGHT));
    headerBackground.setFillColor(sf::Color(144, 238, 144, 200)); // Set header background color to light green
    // Position will be set after centerTable() is called

    // Initialize gradient background
    gradientBackground.setPrimitiveType(sf::Quads);
    gradientBackground.resize(4);

    gradientBackground[0].position = sf::Vector2f(0, 0);
    gradientBackground[1].position = sf::Vector2f(window->getSize().x, 0);
    gradientBackground[2].position = sf::Vector2f(window->getSize().x, window->getSize().y);
    gradientBackground[3].position = sf::Vector2f(0, window->getSize().y);

    gradientBackground[0].color = sf::Color(50, 50, 150); // Top-left color
    gradientBackground[1].color = sf::Color(50, 50, 150); // Top-right color
    gradientBackground[2].color = sf::Color(150, 50, 50); // Bottom-right color
    gradientBackground[3].color = sf::Color(150, 50, 50); // Bottom-left color

    // Initialize star shapes
    starShape.setRadius(15.f);
    starShape.setPointCount(6);
    starShape.setFillColor(sf::Color(255, 215, 0));
    starShape.setOutlineColor(sf::Color(204, 172, 0));
    starShape.setOutlineThickness(2.f);

    starShape2 = starShape;

    animationTime = 0.f;
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
    titleText.setFillColor(sf::Color(255, 215, 0));  // Gold color

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
        sf::Color(50, 50, 50, 200),  // Background idle color
        sf::Color(70, 70, 70, 220),  // Background hover color (light green)
        sf::Color(90, 90, 90, 240),  // Background active color
        sf::Color(255, 255, 255, 255),  // Text idle color (blue)
        sf::Color(255, 255, 200, 255),  // Text hover color (white)
        sf::Color(255, 255, 255, 255)   // Text active color
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
        cell.setCharacterSize(30);
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
    //borders.clear(); // Clear borders as well

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
        if (total <= 0) continue;
        
        bool found = false;
        for (int i = 0; i < players.size(); i++) {
            if (name == std::get<0>(players[i])) {
                std::get<1>(players[i]) = w1;
				std::get<2>(players[i]) = w2;
				std::get<3>(players[i]) = w3;
				std::get<4>(players[i]) = total;
                found = true;
                break;
            }
        }
        if (!found)
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
    updateRowHighlighting();
    updateAnimation(dt);
    //updateScroll(event);
}

void LeaderboardState::updateAnimation(const float& dt)
{
    animationTime += dt;

    float starBob = std::sin(animationTime * 3.f) * 5.f;
    float starBob2 = std::sin(animationTime * 3.f + 1.f) * 5.f;

    starShape.setPosition(50.f, 150.f + starBob);
    starShape2.setPosition(window->getSize().x - 80.f, 150.f + starBob2);
}

void LeaderboardState::render(sf::RenderTarget* target)
{
    if (!target)
        target = window;

    // Render gradient background
    target->draw(gradientBackground);

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
    
    int counter = 15;
    for (const auto& row : tableData)
    {
        if (counter == 0)
			break;
        for (const auto& cell : row)
        {
            target->draw(cell);
        }
        counter--;
    }

    // Render star shapes
    target->draw(starShape);
    target->draw(starShape2);

    // Render back button
    backButton->render(target);
}

void LeaderboardState::updateRowHighlighting()
{
    for (size_t i = 0; i < tableData.size(); ++i)
    {
        for (auto& cell : tableData[i])
        {
            if (cell.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y))
            {
                cell.setFillColor(sf::Color::Yellow);
            }
            else
            {
                cell.setFillColor(sf::Color::White);
            }
        }
    }
}

//void LeaderboardState::updateScroll(const sf::Event& event)
//{
//    if (event.type == sf::Event::MouseWheelScrolled)
//    {
//        float scrollOffset = event.mouseWheelScroll.delta * 20.f;
//        for (auto& row : tableData)
//        {
//            for (auto& cell : row)
//            {
//                cell.move(0.f, scrollOffset);
//            }
//        }
//        for (auto& border : borders)
//        {
//            border.move(0.f, scrollOffset);
//        }
//    }
//}
