#include "GodControlComponent.h"
#include <iostream>

using namespace GameEngine;

GodControlComponent::GodControlComponent()
{
    
}

GodControlComponent::~GodControlComponent()
{
    
}

void GodControlComponent::Update()
{
    Component::Update();
    if (GameEngineMain::GetInstance() -> isPaused || !(GameEngineMain::GetInstance() -> isRunning)) return;
    ObstacleShower* shower = GameEngineMain::GetInstance() -> GetGameBoard() -> GetShower();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) shower -> ShootArrow(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) shower -> ShootArrow(2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) shower -> ShootArrow(3);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) shower -> ShootArrow(4);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) shower -> ShootArrow(5);
}

void GodControlComponent::OnAddToWorld()
{
    Component::OnAddToWorld();
}
