#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "Game/GameBoard.h"
#include "GameEngine/GameEngineMain.h"
#include "Game/GameControls/ObstacleShower.h"

namespace GameEngine
{
    class GodControlComponent : public GameEngine::Component
    {
    public:
        GodControlComponent();
        ~GodControlComponent();

        virtual void Update() override;
        virtual void OnAddToWorld() override;
    private:

    };

}
