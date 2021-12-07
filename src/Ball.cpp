#include <SDL2/SDL_image.h>

#include <math.h>

#include "Ball.h"

std::array<const char*, 2> Ball::colors = {
        "./assets/ball.png", "./assets/ball2.png"
};

Ball::Ball(SDL_Renderer *renderer, const Vector &position, const int &color):
renderer(renderer), position(position), color(color) {
        SDL_Surface *surface = IMG_Load(colors[color]);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);
};

Ball::~Ball() {
        SDL_DestroyTexture(texture);
}

auto Ball::getPos() const -> Vector {
        return position;
}

auto Ball::isMoving() const -> bool {
        return moving;
}

auto Ball::getVelocity() const -> Vector {
        return velocity;
}

void Ball::update(const double &delta) {
        collideWithTable();

        velocity.mult(delta);
        position += velocity;

        // Friction
        velocity = velocity.mult(0.984);

        if (velocity.getMagnitude() < 0.1) {
                velocity = Vector();
                moving = false;
        }
}

void Ball::collideWithTable() {
        if (!moving) return;

        if (position.y <= 0) {
                position.y = 0;
                velocity = Vector(velocity.x, -velocity.y);
        }
        else if (position.y >= SCREEN_HEIGHT - BALL_DIAMETER) {
                position.y = SCREEN_HEIGHT - BALL_DIAMETER;
                velocity = Vector(velocity.x, -velocity.y);
        }
        if (position.x <= 0) {
                position.x = 0;
                velocity = Vector(-velocity.x, velocity.y);
        }
        else if (position.x >= SCREEN_WIDTH - BALL_DIAMETER) {
                position.x = SCREEN_WIDTH - BALL_DIAMETER;
                velocity = Vector(-velocity.x, velocity.y);
        }
}

void Ball::draw() {
        // x -> y -> w -> h

        rect = { static_cast<int>(position.x), static_cast<int>(position.y), 50, 50 };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Ball::shoot(const double &power, const double &rotation) {
        velocity = Vector(-1 * cos(rotation) * power, -1 * sin(rotation) * power);
        moving = true;
}

void Ball::setPos(const Vector &pos) {
        position = pos;
}

void Ball::setMoving(bool&& moving) {
        this->moving = moving;
}

void Ball::setVelocity(const Vector &vector) {
        velocity = vector;
}
