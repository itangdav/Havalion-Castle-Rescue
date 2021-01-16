#include "LinkedEntityComponent.h"
#include <SFML/Window/Keyboard.hpp>
#include "GameEngine/GameEngineMain.h"

using namespace Game;

LinkedEntityComponent::LinkedEntityComponent()
	: followedEntity(nullptr),
	followOffset(sf::Vector2f(0, 0))
{

}

LinkedEntityComponent::~LinkedEntityComponent() {

}

void LinkedEntityComponent::Update() {
	Component::Update();

	if (followedEntity) {
		GetEntity()->SetPos(followedEntity->GetPos() + followOffset);
	}
}

void LinkedEntityComponent::OnAddToWorld() {
	Component::OnAddToWorld();
}