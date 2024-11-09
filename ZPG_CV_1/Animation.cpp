#include "Animation.h"

void Animation::AddAnimation(function<void(float)> animation) {
    animations.push_back(animation);
}

void Animation::Update(float deltaTime) {
    for (auto& animation : animations) {
        animation(deltaTime);
    }
}
