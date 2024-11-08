#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
public:
    void update(float deltaTime) override;
    void draw() override;

    void handleInput(const InputState& input);

private:
    float m_moveSpeed = 5.0f;
};

#endif // PLAYER_H