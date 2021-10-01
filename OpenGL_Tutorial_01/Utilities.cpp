#include "Utilities.h"

glm::vec3 Utilities::Lerp(const glm::vec3 v1, const glm::vec3 v2, const float t)
{
    return v1 + (v2 - v1) * t;
}
