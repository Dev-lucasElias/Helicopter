#include "Missile.h"
#include <cmath>


void Missile::update() {
    if (!active) return;

    // Atualiza posição
    position.x += velocityX;
    position.y += velocityY;

    // Verifica se saiu da tela (exemplo de condição)
    if (position.x < 0 || position.x > 800 || position.y < 0 || position.y > 600) {
        active = false;
    }
}
Missile::Missile()
    : position{ 0.0, 0.0 }, velocityX(0), velocityY(0), active(false), speed(0) {
}

// Implementação do construtor principal
Missile::Missile(Position startPos, double targetX, double targetY, double missileSpeed)
    : position(startPos), active(true), speed(missileSpeed) {
    double dx = targetX - startPos.x;
    double dy = targetY - startPos.y;
    double distance = std::sqrt(dx * dx + dy * dy);

    velocityX = (dx / distance) * speed;
    velocityY = (dy / distance) * speed;
}