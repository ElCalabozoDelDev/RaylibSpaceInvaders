#define once
#include <raylib.h>
#include "ecs.h"

class SpaceshipComponent : public Component
{
private:
    /* data */
public:
    DEFINE_COMPONENT(SpaceshipComponent);
    Sound ShootSound;
};