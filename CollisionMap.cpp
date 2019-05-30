//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: CollisionMap
//							  Date: 28/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "CollisionMap.h"
#include "GameManager.h"
#include "Level.h"
#include "CollisionEntity.h"
#include "MovingEntity.h"
#include "CollisionHelperClass.h"
#include "GameManager.h"
#include "hge.h"
#include "hgesprite.h"

CollisionMap* CollisionMap::m_pCollisionMap = NULL;

CollisionMap::CollisionMap():m_pLevel(0){

}
CollisionMap::~CollisionMap(){
	//delete m_pSprGreen;
	//delete m_pSprRed;
	//GameManager::GetSingleton()->GetGameEngine()->Texture_Free(m_TexGreen);
	//GameManager::GetSingleton()->GetGameEngine()->Texture_Free(m_TexRed);
}

void CollisionMap::Init()
{
	//initialiseer onze vector met 0
	m_vMapInfo = vector<char>(static_cast<unsigned int>(GameManager::GetSingleton()->GetScreenWidth()*GameManager::GetSingleton()->GetScreenHeight()),-1);
	//LoadTextureIntoSprite("CollisionDebug/green.png", m_pSprGreen, m_TexGreen);
	//LoadTextureIntoSprite("CollisionDebug/red.png", m_pSprRed, m_TexRed);
}

void CollisionMap::LoadTextureIntoSprite(const string& texname, hgeSprite*& sprite, HTEXTURE& tofillin)
{
	//todo hou screensizes bij in manager class
	//todo hou path bij in manager class / relative shit
	string pathname = GameManager::GetSingleton()->GetArtPath();
	string pathtotexture = pathname + texname;
	tofillin= GameManager::GetSingleton()->GetGameEngine()->Texture_Load(pathtotexture.c_str());
	sprite = new hgeSprite(tofillin, 0, 0, 1, 1);
}

void CollisionMap::AddItem(const RECT& dimension, int id)
{
	//voeg de dimensie toe
	for(int i = dimension.left; i<dimension.right; ++i)
	{
		for(int j=dimension.top; j<dimension.bottom; ++j)
		{
			//x = i + j*1024
			m_vMapInfo.at(static_cast<int>(i+j*GameManager::GetSingleton()->GetScreenWidth())) = id;
		}
	}
}

Vector2D CollisionMap::CheckCollision( RECT dimension, const MovingEntity* entity)
{
	//Vector2D vBack(-500,-500);
	Vector2D vBack(-10000,-10000);
	//check de dimensie
	for(int i = dimension.left; i<=dimension.right; ++i)
	{
		for(int j=dimension.top; j<=dimension.bottom; ++j)
		{
			//x = i + j*1024
			if(m_vMapInfo.at(static_cast<int>(i+j*GameManager::GetSingleton()->GetScreenWidth())) != -1)
			{
				vBack =  HandleCollisionPoint(m_vMapInfo.at(static_cast<int>(i+j*GameManager::GetSingleton()->GetScreenWidth())), dimension, Vector2D(i,j), entity);
				return vBack;
			}
		}
	}

	return vBack;

	//return moveback;
}

Vector2D CollisionMap::HandleCollisionPoint(char id, RECT dimension, const Vector2D& toplefthitpoint,  const MovingEntity* entity)
{
	//haal collision rect met id van collisionitem op
	RECT collisionrect = m_pLevel->GetCollisionItems().at(id)->GetRect();
	
	//haal acceleratievector&oldpos van de player op
	//const Vector2D& vAcc = entity->GetAccleration();
	const Vector2D& vOldPos = entity->GetOldPosition();
	const Vector2D& vPos = entity->GetPosition();
	const Vector2D& vAcc = entity->GetAccleration();
	//test de rechte(s) met de 2 mogelijke invalsassen (x / y van goeie side (afh van ricoacc))
	


	Vector2D yInterSection = FindIntersectionFast(static_cast<float>(vPos.x),static_cast<float>(vPos.y), static_cast<float>(vOldPos.x), static_cast<float>(vOldPos.y), static_cast<float>(collisionrect.left), static_cast<float>(collisionrect.top), static_cast<float>(collisionrect.right), static_cast<float>(collisionrect.top));
	Vector2D xInterSection = FindIntersectionFast(static_cast<float>(vPos.x),static_cast<float>(vPos.y), static_cast<float>(vOldPos.x), static_cast<float>(vOldPos.y), static_cast<float>(collisionrect.left), static_cast<float>(collisionrect.bottom), static_cast<float>(collisionrect.left), static_cast<float>(collisionrect.top));

	Vector2D moveback(0,0);

	if(yInterSection.x != -10000)
	{
		//momenteel geven we de y voorrang , we kunne ook via acceleratie nagaan welk punt er eerste geraakt werd
		//dit hou ik momenteel voor uitbreiding


		//check of ze beiden intersecten
		/*
		if(xInterSection.x != -10000)
		{
			
			
		}else{
			//enkel de y intersected

		}
		*/ 
		
		//moveback is de huidige positie - positie snijpunt
		moveback = vPos - yInterSection;
		moveback.x = 0;
		MovingEntity* testent = const_cast<MovingEntity*>(entity);
		RECT testrect = testent->GetRect();
		//moveback += Vector2D((testent->GetRect().right-testent->GetRect().left)/2.0f, (testent->GetRect().bottom-testent->GetRect().top)/2.0f);
		moveback += Vector2D(0, (testent->GetRect().bottom-testent->GetRect().top)/2.0f);

		testent->StopJumping();
		

	}else{
		if(xInterSection.x != -10000)
		{
			moveback = vPos - xInterSection;
			moveback.y = 0;
		}
	}

	return moveback;
}



//fastest method - the one to use
Vector2D CollisionMap::FindIntersectionFast(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	//Vector2D CollisionPoint = CollisionHelperClass::CheckIntersect(x1, y1, x2, y2, x3, y3, x4, y4);
	return CollisionHelperClass::CheckIntersect(x1, y1, x2, y2, x3, y3, x4, y4);
}

//todo :
//plaats ook bij CollisionHelperClass class
//precise method - we dont use this in the game
// calculates intersection and checks for parallel lines.
// also checks that the intersection point is actually on
// the line segment p1-p2
Vector2D CollisionMap::FindIntersection(POINT p1,POINT p2,
					   POINT p3,POINT p4) {
						   double xD1,yD1,xD2,yD2,xD3,yD3;
						   double dot,deg,len1,len2;
						   double segmentLen1,segmentLen2;
						   double ua,ub,div;

						   // calculate differences
						   xD1=p2.x-p1.x;
						   xD2=p4.x-p3.x;
						   yD1=p2.y-p1.y;
						   yD2=p4.y-p3.y;
						   xD3=p1.x-p3.x;
						   yD3=p1.y-p3.y;  

						   // calculate the lengths of the two lines
						   len1=sqrt(xD1*xD1+yD1*yD1);
						   len2=sqrt(xD2*xD2+yD2*yD2);

						   // calculate angle between the two lines.
						   dot=(xD1*xD2+yD1*yD2); // dot product
						   deg=dot/(len1*len2);

						   // if abs(angle)==1 then the lines are parallell,
						   // so no intersection is possible
						   if(abs(deg)==1) return Vector2D(-1000,-1000);

						   // find intersection Pt between two lines
						   Vector2D pt(0,0);
						   div=yD2*xD1-xD2*yD1;
						   ua=(xD2*yD3-yD2*xD3)/div;
						   ub=(xD1*yD3-yD1*xD3)/div;
						   pt.x=p1.x+ua*xD1;
						   pt.y=p1.y+ua*yD1;

						   // calculate the combined length of the two segments
						   // between Pt-p1 and Pt-p2
						   xD1=pt.x-p1.x;
						   xD2=pt.x-p2.x;
						   yD1=pt.y-p1.y;
						   yD2=pt.y-p2.y;
						   segmentLen1=sqrt(xD1*xD1+yD1*yD1)+sqrt(xD2*xD2+yD2*yD2);

						   // calculate the combined length of the two segments
						   // between Pt-p3 and Pt-p4
						   xD1=pt.x-p3.x;
						   xD2=pt.x-p4.x;
						   yD1=pt.y-p3.y;
						   yD2=pt.y-p4.y;
						   segmentLen2=sqrt(xD1*xD1+yD1*yD1)+sqrt(xD2*xD2+yD2*yD2);

						   // if the lengths of both sets of segments are the same as
						   // the lenghts of the two lines the point is actually
						   // on the line segment.

						   // if the point isn't on the line, return null
						   if(abs(len1-segmentLen1) || abs(len2-segmentLen2))
							   return Vector2D(-1000,-1000);

						   // return the valid intersection
						   return pt;
}

CollisionMap* CollisionMap::GetSingleton()
{
	if(m_pCollisionMap == NULL)
	{
		m_pCollisionMap = new CollisionMap();
		m_pCollisionMap->Init();
	}

	return m_pCollisionMap;
}


void CollisionMap::SetCurrentLevel( const Level* level )
{
	m_pLevel = level;
}


void CollisionMap::Draw()
{
	//te "laggy":
	/*
	for(int i = 0; i<GameManager::GetSingleton()->GetScreenWidth(); ++i)
	{
		for(int j=0; j<GameManager::GetSingleton()->GetScreenHeight(); ++j)
		{
			//x = i + j*1024
			if(m_vMapInfo.at(static_cast<int>(i+j*GameManager::GetSingleton()->GetScreenWidth())) != -1)
			{
				//draw red
				m_pSprRed->Render(i,j);
			}else
			{
				//draw green
				m_pSprGreen->Render(i,j);
			}
		}
	}
	*/
	

	//draw lines omdat andere methode het programma zwaar doet vertragen
	
}