#pragma
#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

class LevelManager {
public:
    LevelManager();
    virtual ~LevelManager();

    virtual void loadLevel() = 0;
    virtual void update(float dt); 
    virtual void render();  

protected:
    
};

#endif 
