#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "GameEngine/EntitySystem/Entity.h"

namespace GameEngine
{
    class ObstacleMovementComponent : public GameEngine::Component
    {
    public:
        ObstacleMovementComponent();
        ~ObstacleMovementComponent();

        virtual void Update() override;
        virtual void OnAddToWorld() override;
        
        void SetVelocityFactor(float velocityFactor);
        float GetVelocityFactor();
        
    private:
        float m_velocityFactor;
    };

}
