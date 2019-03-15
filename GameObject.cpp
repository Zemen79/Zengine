#include "GameObject.h"


namespace Zen {
	GameObject::GameObject() :
		texture(), position(0.0f), size(0.0f), origin(size/2.0f), direction(1.0f), 
		color(1.0f), uv(0, 0, 1, 1), angle(0.0f), visible(true), mass(1.0f)
	{
	}

	GameObject::~GameObject()
	{
	}

	void Zen::GameObject::Submit(SpriteBatch & spriteBatch)
	{
		spriteBatch.Submit(texture, position, size, angle, uv, color);
	}
}