

#include "Collision.hpp"

bool Collision::circleRectCollision(int cx, int cy, int radius, SDL_Rect rect) {
    // Find closest point on rect to circle center
    int closestX = std::max(rect.x, std::min(cx, rect.x + rect.w));
    int closestY = std::max(rect.y, std::min(cy, rect.y + rect.h));

    // Distance between circle center and closest point on rect
    int dx = cx - closestX;
    int dy = cy - closestY;

    bool collision = false;
    if ((dx*dx + dy*dy) <= (radius * radius)) { 
        collision = true; // Circle overlaps rectangle (distance from closest point <= radius)
    }
     return collision;
}


bool Collision::circleCircleCollision(int cx1, int cy1, int r1, int cx2, int cy2, int r2) {
    // Distance between both centers
    int dx = cx1 - cx2;
    int dy = cy1 - cy2;

    int radiusSum = r1 + r2; // Maximum distance for collision

    bool collision = false;
    if ((dx*dx + dy*dy) <= (radiusSum * radiusSum)) { 
        collision = true; // // Circles overlap (distance between centers <= sum of radii)
    }
    return collision;
}
