//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: EnemyBlue
//							  Date: 24/8/2009
//******************************************************************************************

#ifndef EnemyBlueBehavior_H_INCLUDED
#define EnemyBlueBehavior_H_INCLUDED

#include "Vector2D.h"
#include "EnemyBehavior.h"
#include "Enemy.h"
class EnemyBlueBehavior : public EnemyBehavior {
public:
	EnemyBlueBehavior();
	virtual ~EnemyBlueBehavior();
	virtual void Update(float dTime, const Hero* hero, Enemy* enemy);
protected:

	void DoAction(const Vector2D& position, Enemy* enemy, float dTime);

private:

	EnemyBlueBehavior(const EnemyBlueBehavior& t);
	EnemyBlueBehavior& operator=(const EnemyBlueBehavior& t);
	
};

#endif