#include "ObstacleManager.h"

using namespace GameEngine;

ObstacleManager* ObstacleManager::sm_instance = nullptr;

ObstacleManager::ObstacleManager()
{
    
}

ObstacleManager::~ObstacleManager()
{
    
}

sf::Vector2f ObstacleManager::GetObstacleSize (eObstacle::ladderType type)
{
    switch (type)
    {
        case eObstacle::ladderType::Rock: return sf::Vector2f(60.f, 60.f);
        default: return sf::Vector2f(0.f, 0.f);
    }
    return sf::Vector2f(0.f, 0.f);
}

sf::Vector2f ObstacleManager::GetObstacleSize (eObstacle::nonLadderType type)
{
    switch (type)
    {
        case eObstacle::nonLadderType::Rock: return sf::Vector2f(60.f, 60.f);
        default: return sf::Vector2f(0.f, 0.f);
    }
    return sf::Vector2f(0.f, 0.f);
}

eTexture::type ObstacleManager::GetObstacleTexture (eObstacle::ladderType type)
{
    switch (type)
    {
        case eObstacle::ladderType::Rock: return eTexture::Rock;
        default: return eTexture::None;
    }
    return eTexture::None;
}

eTexture::type ObstacleManager::GetObstacleTexture (eObstacle::nonLadderType type)
{
    switch (type)
    {
        case eObstacle::nonLadderType::Rock: return eTexture::Rock;
        default: return eTexture::None;
    }
    return eTexture::None;
}

EAnimationId::type ObstacleManager::GetObstacleAnimation (eObstacle::ladderType type)
{
    switch (type)
    {
        case eObstacle::ladderType::Rock: return EAnimationId::RollingRock;
        default: return EAnimationId::None;
    }
    return EAnimationId::None;
}

EAnimationId::type ObstacleManager::GetObstacleAnimation (eObstacle::nonLadderType type)
{
    switch (type)
    {
        case eObstacle::nonLadderType::Rock: return EAnimationId::RollingRock;
        default: return EAnimationId::None;
    }
    return EAnimationId::None;
}

float ObstacleManager::GetObstacleVelocityFactor (eObstacle::ladderType type)
{
    switch (type)
    {
        case eObstacle::ladderType::Rock: return 10.f;
        default: return 0.f;
    }
    return 0.f;
}

float ObstacleManager::GetObstacleVelocityFactor (eObstacle::nonLadderType type)
{
    switch (type)
    {
        case eObstacle::nonLadderType::Rock: return 10.f;
        default: return 0.f;
    }
    return 0.f;
}
