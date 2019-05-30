//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: EnemyBehavior
//							  Date: 24/8/2009
//******************************************************************************************

#ifndef ENEMYBEHAVIOR_H_INCLUDED
#define ENEMYBEHAVIOR_H_INCLUDED


class Hero;
class Enemy;

class EnemyBehavior {
public:
	EnemyBehavior();
	virtual ~EnemyBehavior();
	virtual void Update(float dTime, const Hero* hero, Enemy* enemy);
protected:
	float m_fCurrentAttackTimer, m_fTotalAttackTimer;

private:
	EnemyBehavior(const EnemyBehavior& t);
	EnemyBehavior& operator=(const EnemyBehavior& t);
};

#endif