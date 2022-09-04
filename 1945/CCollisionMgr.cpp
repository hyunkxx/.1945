#include "pch.h"
#include "CCollisionMgr.h"

#include "CObj.h"
#include "CShipBase.h"
#include "CEnemy.h"
#include "CItem.h"

list<CObj*>* CCollisionMgr::m_Enemys = nullptr;
list<CObj*>* CCollisionMgr::m_EnemyBullets = nullptr;
list<CObj*>* CCollisionMgr::m_Bullets=nullptr;
list<CObj*>* CCollisionMgr::m_Items = nullptr;
CObj* CCollisionMgr::m_Ship = nullptr;

void CCollisionMgr::Collision_Cheak(list<CObj*>& _bullets, list<CObj*>& _monsters)
{
	for(auto& bullet : _bullets)
		for (auto& monster : _monsters)
		{
			if (IsCollision(bullet, monster))
			{
				bullet->SetDead();
				((CEnemy*)monster)->TakeDamage(20);
			}
		}
}

void CCollisionMgr::Collision_Cheak(COLLISION _collision)
{
	for (auto& bullet : *m_EnemyBullets)
		if (IsCollision(_collision, bullet))
			bullet->SetDead();

	for (auto& monster : *m_Enemys)
	{
		if (IsCollision(_collision, monster))
		{
			if (!((CEnemy*)monster)->IsTakeSkill())
				((CEnemy*)monster)->TakeDamage(100);
			
			((CEnemy*)monster)->SetTakeSkill();
		}
	}
}

void CCollisionMgr::Collision_Cheak(CObj* _player)
{
	for (auto& bullet : *m_EnemyBullets)
	{
		if (bullet->IsDead())
			continue;

		if (IsCollision(_player, bullet))
		{
			bullet->SetDead();
			((CShipBase*)_player)->HitDamage(5);
		}
	}
		

	for (auto& monster : *m_Enemys)
	{
		if (monster->IsDead())
			continue;
		
		if (IsCollision(_player, monster))
		{
			((CEnemy*)monster)->SetDead();
			((CShipBase*)_player)->HitDamage(20);
		}	
	}

	for (auto& item : *m_Items)
	{
		if (item->IsDead())
			continue;
		
		if (IsCollision(_player, item))
		{
			item->SetDead();
			auto type=((CItem*)item)->GetItemType();
			int count = ((CShipBase*)_player)->GetItemCount(type);
			((CShipBase*)_player)->SetItemCount(type, count + 1);
		}
	}

}

bool CCollisionMgr::IsCollision(CObj* _obj1, CObj* _obj2)
{
	float x1 = _obj1->GetTransform().fX;
	float y1 = _obj1->GetTransform().fY;
	float x2 = _obj2->GetTransform().fX;
	float y2 = _obj2->GetTransform().fY;

	float rad1 = _obj1->GetTransform().fScale;
	float rad2 = _obj2->GetTransform().fScale;

	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) < (rad1 + rad2) * (rad1 + rad2);
}

bool CCollisionMgr::IsCollision(COLLISION _collision, CObj* _obj)
{
	float x1 = _obj->GetTransform().fX;
	float y1 = _obj->GetTransform().fY;
	float x2 = _collision.pos.X_COM;
	float y2 = _collision.pos.Y_COM;

	float rad1 = _obj->GetTransform().fScale;
	float rad2 = _collision.radius;
	
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) < (rad1 + rad2) * (rad1 + rad2);
}
