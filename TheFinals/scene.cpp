#include "scene.h"
#include "flecs/flecs.h"

namespace scene {
    struct Position {
        float x, y;
    };

    struct Velocity {
        float x, y;
    };

    void setup() {
        flecs::world world;

        auto e = world.entity()
            .insert([](Position &p, Velocity &v) {
            p = { 10, 20 };
            v = { 1, 2 };
                });

        world.each([](Position &p, Velocity &v) { // flecs::entity argument is optional
            p.x += v.x;
            p.y += v.y;
            });
    }

    void update() {

    }
}
