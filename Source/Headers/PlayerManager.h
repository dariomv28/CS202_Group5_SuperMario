#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <string>

class PlayerManager {
public:
    PlayerManager();
    virtual ~PlayerManager();

    // Initialization function
    virtual void init();
    std::string getImagePath() const;

protected:
    std::string m_imagePath;
};

#endif // PLAYERMANAGER_H
