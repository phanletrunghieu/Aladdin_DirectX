#include "Player.h"

Player::Player():GameObject(GameObject::GameObjectType::Player)
{
	_mass = 15;
	_speed = 25;
	_jumpForce = 45;
	_jumpRunForce = 48;

	_isRight = true;
	_isGround = false;
	_allowMoveLeft = _allowMoveRight = true;

	_state = new PlayerFallState(this);
}

Player::~Player()
{
	delete _state;
}

void Player::Update(float deltaTime)
{
	if (_isGround && _velocity.y>0)//change state
	{
		_acceleration.y = 0;
		_velocity.y = 0;
	}

	//face to right or left
	if (_input->IsKeyPressed(DIK_LEFT))
		_isRight = false;
	else if(_input->IsKeyPressed(DIK_RIGHT))
		_isRight = true;

	//move
	if (_input->IsKeyPressed(DIK_LEFT) && _allowMoveLeft)
		_velocity.x = -1 * _speed;
	else if (_input->IsKeyPressed(DIK_RIGHT) && _allowMoveRight)
		_velocity.x = _speed;
	else
		_velocity.x = 0;


	GameObject::Update(deltaTime);
	_state->Update(deltaTime);
}

void Player::Draw(Camera * camera)
{
	_state->GetAnimation()->Draw(camera);

	//debug
	/*
	D3DXVECTOR3 newPosition = camera->ConvertPosition(_position.x, _position.y);

	RECT rect;
	rect.left = newPosition.x - _width / 2;
	rect.top = newPosition.y - _height / 2;
	rect.right = newPosition.x + _width / 2;
	rect.bottom = newPosition.y + _height / 2;

	Graphics::GetInstance()->GetDevice()->ColorFill(Graphics::GetInstance()->GetBackBuffer(), &rect, D3DCOLOR_XRGB(0, 255, 0));
	*/
}

void Player::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	_state->OnCollision(target, side);
}

PlayerState * Player::GetState()
{
	return _state;
}

void Player::SetState(PlayerState * state, bool fixFootPosition)
{
	if (fixFootPosition)
	{
		//make sure player's foot at the same position when change state. because each state has own height
		int newHeight = state->GetAnimation()->GetHeight();
		int currentHeight = _state->GetAnimation()->GetHeight();
		float diff = (currentHeight - newHeight) / 2.0;
		_position.y += diff;
	}

	//change state
	delete _state;
	_state = state;
}

bool Player::IsRight()
{
	return _isRight;
}

bool Player::IsGround()
{
	return _isGround;
}

void Player::SetIsGround(bool isGround)
{
	_isGround = isGround;
}

bool Player::IsAllowMoveLeft()
{
	return _allowMoveLeft;
}

bool Player::IsAllowMoveRight()
{
	return _allowMoveRight;
}

void Player::AllowMoveLeft(bool allow)
{
	_allowMoveLeft = allow;
}

void Player::AllowMoveRight(bool allow)
{
	_allowMoveRight = allow;
}

float Player::GetSpeed()
{
	return _speed;
}

void Player::SetSpeed(float speed)
{
	_speed = speed;
}

float Player::GetJumpForce()
{
	return _jumpForce;
}

void Player::SetJumpForce(float force)
{
	_jumpForce = force;
}

float Player::GetJumpRunForce()
{
	return _jumpRunForce;
}

void Player::SetJumpRunForce(float force)
{
	_jumpRunForce = force;
}
