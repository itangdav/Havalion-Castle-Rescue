#pragma once
#include "Game/GameEntities/ObstacleEntity.h"
#include "Game/GameControls/ObstacleManager.h"
#include "Game/Components/ObstacleMovementComponent.h"
#include "GameEngine/GameEngineMain.h"
#include <random>
#include <set>
#include <stack>

namespace GameEngine
{
    class ObstacleShower
    {
    public:
        ObstacleShower();
        ~ObstacleShower();
        
        void EnableShower();
        void DisableShower();
        void Update();
        
        void ShootArrow(int laddernum);
        void ClearObstacles();
        
    private:
        bool m_showering;
        float m_spawntimer;
        float m_arrowReloadTime;
        void SpawnNewRandomObstacles();
        void SpawnObstacle(bool onladder);
        
        void CheckOutOfBound();
        
        std::mt19937 m_g1;
        float RandFloat (float a, float b);
        int RandInt (int a, int b);
        
        std::set<ObstacleEntity*> m_obstacles;
        
        void CreateObstacle(eObstacle::nonLadderType type, sf::Vector2f& pos);
        void CreateObstacle(eObstacle::ladderType type, sf::Vector2f& pos);
    };
}

