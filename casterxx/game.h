#ifndef __GAME_H
#define __GAME_H

class Game {
public:
    bool keys[1024];
    unsigned int width, height;

    Game(unsigned int width, unsigned int height);
    ~Game();

    void init();

    void processInput(float dt);
    void update(float dt);
    void render();
};

#endif /* __GAME_H */
