#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "GameEngine/EntitySystem/Entity.h"

namespace GameEngine
{
    class ProjectileMovementComponent : public GameEngine::Component
    {
    public:
        ProjectileMovementComponent();
        ~ProjectileMovementComponent();

        virtual void Update() override;
        virtual void OnAddToWorld() override;
        
        void SetVelocityFactor(float velocityFactor);
        void SetDir(sf::Vector2f dir);
        sf::Vector2f GetDir();
        
        float GetVelocityFactor();
        
        void StopMove();
        void StartMove();
        bool IsOutOfBound();
        void SetPlayerEntity(Entity* player);

    private:
        float m_velocityFactor;
        bool m_moving;
        Entity* m_player;
        sf::Vector2f m_dir;
        void CheckCollision();
    };

}
