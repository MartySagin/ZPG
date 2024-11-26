#pragma once

#include <vector>
#include <functional>
#include "Light.h"

using namespace std;

class Animation {
    private:
        vector<function<void(float)>> animations;

    public:
   
        void AddAnimation(function<void(float)> animation);

        void Update(float deltaTime);
};
