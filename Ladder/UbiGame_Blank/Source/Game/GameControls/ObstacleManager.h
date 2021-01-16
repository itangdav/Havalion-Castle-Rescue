#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include "GameEngine/Util/TextureManager.h"
#include "GameEngine/Util/AnimationManager.h"

namespace GameEngine
{
    namespace eObstacle
    {
        enum class ladderType
        {
            None = -1,
            Rock,
            Count,
        };
        enum class nonLadderType
        {
            None = -1,
            Rock,
            Count,
        };
    }
    class ObstacleManager
    {
    public:
        static ObstacleManager* GetInstance()
        {
            if (!sm_instance) sm_instance = new ObstacleManager();
            return sm_instance;
        }
        ~ObstacleManager();
        
        sf::Vector2f GetObstacleSize (eObstacle::ladderType type);
        sf::Vector2f GetObstacleSize (eObstacle::nonLadderType type);
        eTexture::type GetObstacleTexture (eObstacle::ladderType type);
        eTexture::type GetObstacleTexture (eObstacle::nonLadderType type);
        EAnimationId::type GetObstacleAnimation (eObstacle::ladderType type);
        EAnimationId::type GetObstacleAnimation (eObstacle::nonLadderType type);
        float GetObstacleVelocityFactor (eObstacle::ladderType type);
        float GetObstacleVelocityFactor (eObstacle::nonLadderType type);
        
    private:
        ObstacleManager();
        static ObstacleManager* sm_instance;
    };
}
