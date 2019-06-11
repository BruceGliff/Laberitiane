
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Gun.h"


#define COM_UPDATE 1000

constexpr auto REVERS_TEX = 1;
constexpr auto POS_TEX_N = 3;



#define SET_SPEED(player)\
		{\
		bool event_F = false;\
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))\
		{\
			player->set_speed(Up, time);\
		}\
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))\
		{\
			player->set_speed(Down, time);\
		}\
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))\
		{\
			player->set_speed(S_LEFT, time);\
		}\
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))\
		{\
			player->set_speed(Right, time);\
		}\
		}


class Player : public ObjectCore
{
	int heroNumber_;
	int revDir_;
	int dir_;
	float speed_;
	float speedF_;
	float lastMoveT_;

	float* playerX_;
	float* playerY_;

	float last_x_;
	float last_y_;

	float winX_ = 300;
	float winY_ = 240;
	sf::View view_;

	Gun * pistol_;

	int step_;
	int upd_count_;
	Level* lvl_;
	int* commands_;
	int ind_;
	int startX_;
	int startY_;
	bool isTarget_;
	bool isCentre_;

public:

	float* this_is_long_name_of_function_to_get_player_coord_X()
	{
		return &x_;
	}

	float* this_is_long_name_of_function_to_get_player_coord_Y()
	{
		return &y_;
	}


	Player(std::vector<ObjectCore *> & vec, bool alive = 0, float x = 0, float y = 0, int heroNumber = 0, float* playerX = 0, float* playerY = 0, Level* lvl = nullptr,  bool active = true, bool visible = true, 
		float dx = 0, float dy = 0, float animSpeed = 0.02f, int frames = 3, int w = 16, int h = 16, const char * fileName = "ref/images/skins.png", float speed = 0.2f) :

		ObjectCore(alive, x, y, active, visible, dx, dy, animSpeed, frames, w, h, fileName, 0, true),
		heroNumber_(heroNumber),
		speed_(speed),
		speedF_(speed),
		playerX_(playerX),
		playerY_(playerY),
		lvl_(lvl),
		step_(COM_UPDATE),
		isTarget_(true)
	{
		view_.reset(sf::FloatRect(0.f, 0.f, winX_, winY_));
		view_.setCenter(x + w / 2, y + h / 2);
		updateRect(POS_TEX_N * heroNumber);
		createCol();
		dir_ = Down;
		pistol_ = new Gun(vec, 7);

		if(!alive_)
			commands_ = new int [lvl->GetSize() * lvl->GetSize() + 10];
	}

	~Player()
	{
		if (!alive_)
			delete[] commands_;

		delete pistol_;
	}

	void keep_move(float time);

	void set_speed(int dir, float time)
	{
		lastMoveT_ = time;
		dir %= 4;
		dir_ = dir;
		switch (dir)
		{
		case Up:
			revDir_ = Down;
			dy_ += -speed_;
			/*ObjectCore::move(0, -speed_, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 1, time);*/
			break;
		case Right:
			revDir_ = S_LEFT;
			dx_ += speed_;
			/*ObjectCore::move(speed_, 0, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 2, time);*/
			break;
		case Down:
			revDir_ = Up;
			dy_ += speed_; 
			/*ObjectCore::move(0, speed_, time);
			updateRect(POS_TEX_N * heroNumber_, time);*/
			break;
		case Left:
			revDir_ = Right;
			dx_ += -speed_;
			/*ObjectCore::move(-speed_, 0, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 2, time, REVERS_TEX);*/
			break;
		}

		if (dx_ != 0 && dy_ != 0)
		{
			dx_ /= 1.4f;
			dy_ /= 1.4f;
		}

		setViewCoor(getX(), getY());
	}

	void createCol(float degree = 0)
	{
		col_.setSize(sf::Vector2f(w_ - 4.f, 3.f));
		col_.setFillColor(sf::Color(255, 0, 0));
		col_.setRotation(degree);
		col_.setPosition(x_ + 2, y_ + h_ - 2);

		horiCol_.setSize(sf::Vector2f(w_ - 6.f, 1.f));
		horiCol_.setFillColor(sf::Color(0, 0, 255));
		horiCol_.setRotation(degree);
		horiCol_.setPosition(x_ + 3, y_ + h_ / 2 - 3.f);

		vertCol_.setSize(sf::Vector2f(1.f, h_ - 5.f));
		vertCol_.setFillColor(sf::Color(0, 255, 0));
		vertCol_.setRotation(degree);
		vertCol_.setPosition(x_ + w_ / 2, y_);
	}


	void setViewCoor(float x, float y) { view_.setCenter(x + getW() / 2, y + getH() / 2); }

	void setView(sf::RenderWindow * window) { window->setView(view_); }

	sf::View * getView() { return &view_; }
	int getDir() { return dir_; }


	bool interSection(ObjectCore * second)
	{

		UWall * u = dynamic_cast<UWall *>(second);
		LWall * l = dynamic_cast<LWall *>(second);
		if (u || l)
		{
			if ((u) && alive())
				interSectionPos(second);
			if (ObjectCore::interSection(second))
			{
				teleport(revDir_, lastMoveT_);
				speed_ = 0;
				return true;
			}
		}
		speed_ = speedF_;
		return false;
	}

	bool interSectionPos(ObjectCore * second)
	{
		if ((getX() + getW() - 4 > second->getX()) && (getSpr().getGlobalBounds().intersects(second->getSpr().getGlobalBounds())) && (second->getY() < (getY() + getH())) && ((second->getY() + second->getH()) > (getY() + getH())))
		{
			second->updateRect(1);
			return true;
		}
		second->updateRect(0);
		return false;
	}


	void teleport(int dir, float time)
	{
		lastMoveT_ = time;
		x_ = last_x_;
		y_ = last_y_;

		setViewCoor(getX(), getY());
	}

	void evnt(float time, float globTime, sf::RenderWindow * window)
	{
		if (alive_)
		{
			SET_SPEED(this);
			pistol_->shot(this, time, globTime, window);
			pistol_->reload();
		}
		else
		{
			//std:: cout << *playerX_ << ' ' << *playerY_ << '\n';
			step_++;


			int x1 = ((int) x_ + 5) / 34;
			int y1 = ((int) y_ + 15) / 34;

			if ((step_ > COM_UPDATE && isTarget_) || step_ > 2 * COM_UPDATE)
			{
				step_ %= COM_UPDATE;

				ind_ = 0;

				x1 = ((int) x_ + 5) / 34;
				y1 = ((int) y_ + 15) / 34;

				int x2 = ((int) *playerX_ + 5) /34;
				int y2 = ((int) *playerY_ + 15) /34;

				std:: cout << x1 << ' ' << y1 << '\n';
				std:: cout << x2 << ' ' << y2 << '\n';

				commands_ = lvl_->getCommands(commands_, y1, x1, y2, x2);
				ind_ = 0;

				startX_ = x_ + 5;

				startY_ = y_ + 15;

				isTarget_ = false;

				isCentre_ = false;
			}

			if(!isCentre_)
			{
				bool hor = false;
				bool vert = false;

				if(x_ + 5 < x1 * 34.0f + 13.0f)
					set_speed(Right, time);
				else if(x_ + 5 > x1 * 34.0f + 21.0f)
				{
					std:: cout << "LeFt ";
					set_speed(Left, time);
				}
				else
					hor = true;

				if(y_ + 15 > y1 * 34.0f + 21.0f)
					set_speed(Up, time);
				else if(y_ + 15 < y1 * 34.0f + 13.0f)
					set_speed(Down, time);
				else
					vert = true;
				if (!vert || !hor)
					return;
				isCentre_ = true;
			}

			switch(commands_[ind_])
			{
				case S_UP:
					if (startY_ - 34.f < y_ + 15)
					{
						isTarget_ = false;
						set_speed(Up, time);
					}
					else
					{
						ind_++;
						startY_ = y_ + 15;
						isTarget_ = true;
					}
					break;
				case S_DOWN:
					if (startY_ + 34.f > y_ + 15)
					{
						isTarget_ = false;
						set_speed(Down, time);
					}
					else
					{
						ind_++;
						startY_ = y_ + 15;
						isTarget_ = true;
					}
					break;
				case S_RIGHT:
					if (startX_ + 34.f > x_ + 5)
					{
						isTarget_ = false;
						set_speed(Right, time);
					}
					else
					{
						isTarget_ = true;
						ind_++;
						startX_ = x_ + 5;
					}
					break;
				case S_LEFT:
					if (startX_ - 34.f < x_ + 5)
					{
						std:: cout << "LEFT  ";
						isTarget_ = false;
						set_speed(Left, time);
					}
					else
					{
						isTarget_ = true;
						ind_++;
						startX_ = x_ + 5;
					}
					break;
				case S_END:
					step_++;
					break;
			}

		}
	}


};


void Player:: keep_move(float time)
{
	last_x_ = x_;
	last_y_ = y_;

	if (dx_ != 0)
	{
		if(dx_ > 0)
		{
			ObjectCore::move(dx_, dy_, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 2, time);
		}
		else
		{
			ObjectCore::move(dx_, dy_, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 2, time, REVERS_TEX);
		}
	}
	else
		if (dy_ != 0)
		{
			if (dy_ > 0)
			{
				ObjectCore::move(dx_, dy_, time);
				updateRect(POS_TEX_N * heroNumber_, time);
			}
			else
			{
				ObjectCore::move(dx_, dy_, time);
				updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 1, time);
			}
		}
	

	dx_ = 0;
	dy_ = 0;
}