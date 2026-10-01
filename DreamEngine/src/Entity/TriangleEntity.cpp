#include "../include/Entity/TriangleEntity.hpp"

TriangleEntity::TriangleEntity() : Entity(DREAM::GetGUID())
{
    Log::LogMessage("Initializing Triangle Entity Object");
}