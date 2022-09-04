#pragma once

class CObj;

class CCollisionMgr
{
public:
	static void	Collision_Cheak(list<CObj*>& _bullets, list<CObj*>& _monsters);
	static void	Collision_Cheak(COLLISION _collision);
	static void	Collision_Cheak(CObj* _player);

	//static void	Collision_Cheak(CObj* _player);

private:
	static bool	IsCollision(CObj* _obj1, CObj* _obj2);
	static bool	IsCollision(COLLISION _collision, CObj* _obj);

public:
	static void SetBulletList(list<CObj*>& _bullets){ m_Bullets = &_bullets;}
	static void SetEnemyList(list<CObj*>& _Enemys) { m_Enemys = &_Enemys; }
	static void SetEnemyBulletsList(list<CObj*>& _EnemyBullets) { m_EnemyBullets = &_EnemyBullets; }
	static void SetShip(CObj* _ship) { m_Ship = _ship; }
	static void SetItemList(list<CObj*>& _items) { m_Items = &_items; }
	static list<CObj*>& GetEnemyList() { return *m_Enemys; }
	static list<CObj*>& GetEnemyBulletsList() { return *m_EnemyBullets; }
	static list<CObj*>& GetItemList() { return *m_Items; }
	
	static CObj* GetShip() { return m_Ship; }


private:
	static list<CObj*>*	m_Enemys;
	static list<CObj*>*	m_EnemyBullets;
	static list<CObj*>* m_Items;

private: 
	static list<CObj*>* m_Bullets; // 플레이어 총알
	static CObj*		m_Ship; //플레이어

};

