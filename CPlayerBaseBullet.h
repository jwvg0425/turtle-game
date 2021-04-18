#include"CBullet.h"
#include"CEnemy.h"


class CPlayerBaseBullet : public CBullet
{
private:
	CAnimation graphic;
	CPlayerBaseBullet();
public:
	CPlayerBaseBullet(int x, int y);
	virtual void Draw(HDC hdc);
	virtual void Move();
	virtual void Attack();
	virtual void SetArea();
	virtual bool IsCollusion(RECT enemy_rect);
	virtual int GetEffectType(){return PBB_EFFECT;}
	virtual int GetX(){return int(x);}
	virtual int GetY(){return int(y);}
};