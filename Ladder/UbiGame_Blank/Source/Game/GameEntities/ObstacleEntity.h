#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"
#include "GameEngine/GameEngineMain.h"

namespace GameEngine
{
    class ObstacleShower;

    class ObstacleEntity : public GameEngine::Entity
    {
    public:
        ObstacleEntity();
        ~ObstacleEntity();
        virtual void OnAddToWorld() override;
        virtual void OnRemoveFromWorld() override;
        virtual void Update() override;
        
        void SetVelocityFactor(float velocityFactor);
        float GetVelocityFactor();
                
    protected:
        GameEngine::SpriteRenderComponent* m_renderComponent;
    };
}
