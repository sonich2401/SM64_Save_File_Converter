#pragma once
#include "./olcPixelGameEngine.h"
#include <map>
#include <deque>
template <class T>
struct Vec
{
	T x = 0;
	T y = 0;
	inline Vec() : x(0), y(0) {                                                            }
	inline Vec(T _x, T _y) : x(_x), y(_y) {                                                            }
	inline Vec(const Vec& v) : x(v.x), y(v.y) {                                                            }
	inline T mag() { return std::sqrt(x * x + y * y); }
	inline T mag2() { return x * x + y * y; }
	inline Vec  norm() { T r = 1 / mag(); return Vec(x * r, y * r); }
	inline Vec  perp() { return Vec(-y, x); }
	inline T dot(const Vec& rhs) { return this->x * rhs.x + this->y * rhs.y; }
	inline T cross(const Vec& rhs) { return this->x * rhs.y - this->y * rhs.x; }
	inline Vec  operator +  (const Vec& rhs) const { return Vec(this->x + rhs.x, this->y + rhs.y); }
	inline Vec  operator -  (const Vec& rhs) const { return Vec(this->x - rhs.x, this->y - rhs.y); }
	inline Vec  operator *  (const T& rhs)           const { return Vec(this->x * rhs, this->y * rhs); }
	inline Vec  operator *  (const Vec& rhs) const { return Vec(this->x * rhs.x, this->y * rhs.y); }
	inline Vec  operator /  (const T& rhs)           const { return Vec(this->x / rhs, this->y / rhs); }
	inline Vec  operator /  (const Vec& rhs) const { return Vec(this->x / rhs.x, this->y / rhs.y); }
	inline Vec& operator += (const Vec& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
	inline Vec& operator -= (const Vec& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
	inline Vec& operator *= (const T& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
	inline Vec& operator /= (const T& rhs) { this->x /= rhs; this->y /= rhs; return *this; }
	inline Vec& operator < (const T& rhs) { this->x = (this->x < rhs); this->y = (this->y < rhs); return (bool)this->x && (bool)this->y; }
	inline operator Vec<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
	inline operator Vec<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }
	inline operator Vec<double>() const { return { static_cast<double>(this->x), static_cast<double>(this->y) }; }
};
typedef Vec<int32_t>rvi2d;
typedef Vec<float>rvf2d;
struct img {
	std::deque<olc::Sprite*> imgs;
	float frameDir;
};
struct Object {
	Object(olc::PixelGameEngine* olc) {
		pge = olc;
	}
	rvf2d Pos;
	rvf2d Vel;
	olc::PixelGameEngine* pge;
	struct AnimatedSprite {
		std::map < std::string, img> Frames;
		std::string state;
		olc::Sprite RenderedSpriteBuffer;
		olc::Decal* CurrentDisplay= new olc::Decal(&RenderedSpriteBuffer);
		float timer=0;
		int currentFrame=0;
		inline void SetState(std::string StateName) {
			state = StateName;
		}
		inline void AddState(std::string StateName,float frameDiration,std::deque<std::string> PathNames) {
			img tmpi;
			tmpi.frameDir = frameDiration;
			std::deque<olc::Sprite*> tmps;
			for (unsigned int i = 0; i < PathNames.size(); i++) {
				tmpi.imgs.push_back(new olc::Sprite(PathNames[i]));
			}
			Frames[StateName] = tmpi;
		}
		inline void AddState(std::string StateName,float frameDiration,img imageDat) {
			imageDat.frameDir = frameDiration;
			Frames[StateName] = imageDat;
		}
		inline void DrawToScreen(olc::PixelGameEngine* pge,float x, float y,float fScl_x=1,float fScl_y=1) {
			RenderedSpriteBuffer = *this->Frames[state].imgs[currentFrame];
			CurrentDisplay->Update();
			pge->DrawDecal({ x,y }, CurrentDisplay, { {fScl_x},{fScl_y} });
		}
		inline void GetNextFrame(float fElapsedTime) {
			timer += fElapsedTime;
			if (timer > this->Frames[state].frameDir) {
				currentFrame++;
				if (currentFrame + 1 > this->Frames[state].imgs.size())
					currentFrame = 0;
				timer = 0;
			}
		}
		inline void Update(olc::PixelGameEngine *pge,float fElapsedTime,float x, float y) {
			this->GetNextFrame(fElapsedTime);
			this->DrawToScreen(pge, x, y);
		}
	}Sprite;
	inline void Update(float fElapsedTime) {
		Pos += {Vel*fElapsedTime};
		this->Sprite.Update(pge, fElapsedTime, Pos.x, Pos.y);
	}
};