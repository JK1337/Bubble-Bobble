//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: EnemyBehaviorManager
//							  Date: 24/8/2009
//******************************************************************************************

#ifndef ENEMYBEHAVIORMANAGER_H_INCLUDED
#define ENEMYBEHAVIORMANAGER_H_INCLUDED
#include <map>
using namespace std;

class EnemyBehavior;

class EnemyBehaviorManager {
public:

	virtual ~EnemyBehaviorManager();
	static EnemyBehaviorManager* GetSingleton();
	EnemyBehavior* GetBehavior(const string& behaviorname);
private:
	std::map< string, EnemyBehavior* > m_mapBehaviors;
	static EnemyBehaviorManager* m_pInstance;
	EnemyBehaviorManager();
	
	EnemyBehaviorManager(const EnemyBehaviorManager& t);
	EnemyBehaviorManager& operator=(const EnemyBehaviorManager& t);
	void Init();
};

#endif