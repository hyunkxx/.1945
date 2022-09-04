#include "pch.h"
#include "CCore.h"
#include "CShipBase.h"
#include "CInputManager.h"
#include "CBullet.h"
#include "CSkill.h"
#include "CUISystem.h"
#include "CEnemy.h"

#include "CCollisionMgr.h"
#include "CLogo.h"
#include "CItem_Boom.h"
#include "CItem_HP.h"

float CCore::g_DeltaTime;
RECT CCore::g_clientRect;
HWND CCore::g_HWND;

int CCore::g_nCurShipIndex;
int CCore::g_nNextShipIndex;
//PLTOYA
CSkill* CCore::m_pSkill = nullptr;

CCore::CCore()
	: m_hdc(0)
	, m_hWnd(0)
	, m_hBit(0)
	, m_subDC(0)
	, m_hInstance(0)
{
	for (int i = 0; i < SHIP_COUNT; i++)
		m_pShip[i] = nullptr;
}

CCore::~CCore()
{
	Release();
}

void CCore::Initalize(HWND _hWnd, HINSTANCE _hInstance, RECT _clientRect)
{
	g_HWND = _hWnd;
	m_hWnd = _hWnd;
	m_hdc = GetDC(m_hWnd);
	m_hInstance = _hInstance;
	g_clientRect = _clientRect;

	for (int i = 0; i < SHIP_COUNT; i++)
	{
		m_pShip[i] = new CShipBase(WIDTH - WIDTH, HIGHT * 0.8f, 40.f);
	}

	m_pShip[CCore::g_nCurShipIndex]->SetX(WIDTH / 2);

	for (int i = 0; i < SHIP_COUNT; i++)
	{
		static_cast<CShipBase*>(m_pShip[i])->SetShipList(m_pShip);
	}

	for (auto* ship : m_pShip)
		static_cast<CShipBase*>(ship)->Initalize();

	int i = 0;
	for (auto* ship : m_pShip)
	{
		static_cast<CShipBase*>(ship)->SetID(SHIP_ID(i));
		i++;
	}

	//static_cast<CShipBase*>(m_pShip[0])->SetCurHealth(100);
	//static_cast<CShipBase*>(m_pShip[1])->SetCurHealth(100);
	//static_cast<CShipBase*>(m_pShip[2])->SetCurHealth(100);

	CInputManager::Possess(static_cast<CShipBase*>(m_pShip[g_nCurShipIndex]));
	
	for (int i = 0; i < SHIP_COUNT; i++)
		CUISystem::ConnectShip(m_pShip);

	for (auto* elem : m_pBulletList)
	{
		elem->Initalize();
	}

	for (auto* iter : m_pShip)
		static_cast<CShipBase*>(iter)->SetBullet(&m_pBulletList);

	//PLTOYA
	m_hBit  = CreateCompatibleBitmap(m_hdc, WIDTH, HIGHT);
	m_subDC = CreateCompatibleDC(m_hdc);

	HBITMAP hDefaultBitmap = (HBITMAP)SelectObject(m_subDC, m_hBit);
	DeleteObject(hDefaultBitmap);
	
	CCollisionMgr::SetEnemyList(m_pEnemyList);
	CCollisionMgr::SetEnemyBulletsList(m_pEnemyBulletList);
	CCollisionMgr::SetItemList(m_pItemList);

	m_logo = new CLogo;
}

void CCore::Update(float _fDeltaTime)
{
	//PLTOYA
	Rectangle(m_subDC, -1, -1, WIDTH + 1, HIGHT + 1);
	
	if (m_logo)
	{
		m_logo->Update(_fDeltaTime);
		if (m_logo->IsDead())
		{
			delete m_logo;
			m_logo = nullptr;
		}
		else
			return;
	}

	g_DeltaTime = _fDeltaTime;
	CInputManager::Update(_fDeltaTime);
	CCollisionMgr::SetShip(m_pShip[g_nCurShipIndex]);

	// 플레이어 총알
	for (auto iter = m_pBulletList.begin() ; iter != m_pBulletList.end() ; )
	{
		(*iter)->Update(_fDeltaTime);
		if ((*iter)->IsDead())
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
		}
		else
			iter++;
	}

	// 플레이어
	for (int i = 0 ;  i < SHIP_COUNT ; i++)
		m_pShip[i]->Update(_fDeltaTime);

	// 몬스터 생성
	if (0 == m_pEnemyList.size())
		m_LocalTime_E += _fDeltaTime;

	// 스테이지 카운트가 10 보다 작고 프레임 사이 시간 간격이 7 보다 커지면
	if ((m_iStage_Count < 3) && (m_LocalTime_E > 4.f))
	{
		m_LocalTime_E = 0.f;

		m_iStage_Count++;
		if (m_iStage_Count >= 3) {
			m_iStage++;
			m_iStage_Count = 0;
		}

		if (m_iStage == 스테이지1) {
			for (int i = 0; i < 5; i++) {
				CreateEnemy(전투기, i, 스테이지1);
				CreateEnemy(고정포탑, i, 스테이지1);
				CreateEnemy(가미카제, i, 스테이지1);
			}
		}
		if (m_iStage == 스테이지2) {
			for (int i = 0; i < 7; i++) {
				CreateEnemy(전투기, i, 스테이지2);
				CreateEnemy(고정포탑, i, 스테이지2);
				CreateEnemy(가미카제, i, 스테이지2);
			}
		}
		if (m_iStage == 스테이지3) {
			for (int i = 0; i < 9; i++) {
				CreateEnemy(전투기, i, 스테이지3);
				CreateEnemy(고정포탑, i, 스테이지3);
				CreateEnemy(가미카제, i, 스테이지3);
			}
		}
		if (m_iStage >= 보스스테이지) {
			for (int i = 0; i < 9; i++) {
				CreateEnemy(전투기, i, 보스스테이지);
				CreateEnemy(고정포탑, i, 보스스테이지);
				//CreateEnemy(가미카제, i, 스테이지3);
			}

		}
	}
	for (auto it = m_pItemList.begin(); it != m_pItemList.end();)
	{
		(*it)->Update(_fDeltaTime);
		if ((*it)->IsDead())
		{
			delete (*it);
			it = m_pItemList.erase(it);
		}
		else
			it++;
	}

	
	// 몬스터 업데이트
	for (auto it = m_pEnemyList.begin(); it != m_pEnemyList.end();)
	{
		dynamic_cast<CEnemy*>(*it)->SetEnemyBulletList(&m_pEnemyBulletList);
		dynamic_cast<CEnemy*>(*it)->SetPlayer(m_pShip[g_nCurShipIndex]);
		(*it)->Update(_fDeltaTime);
		if (!m_pSkill)
			dynamic_cast<CEnemy*>(*it)->SetTakeSkill_false();

		if ((*it)->IsDead())
		{
			(*it)->GetTransform();
			int rand = ((int)((*it)->GetY())) % 10;
			int type = ((int)((*it)->GetX())*rand) % 아이템종류;
			if (rand < 7)
			{
				if (폭탄 == type)
					m_pItemList.push_back(new CItem_Boom("BOOM", (*it)->GetTransform()));
				else if(포션 == type)
					m_pItemList.push_back(new CItem_HP("HP", (*it)->GetTransform()));
			}
			delete (*it);
			it = m_pEnemyList.erase(it);
		}
		else
			it++;
	}
	
	
	for (auto it = m_pEnemyBulletList.begin(); it != m_pEnemyBulletList.end();)
	{
		(*it)->Update(_fDeltaTime);
		if ((*it)->IsDead())
		{
			delete (*it);
			it = m_pEnemyBulletList.erase(it);
		}
		else
			it++;
	}
	

	// 적 이 맵 밖으로 나간다면 삭제
	for (list<CObj*>::iterator iter = m_pEnemyList.begin(); iter != m_pEnemyList.end();) {

		auto& pos = (*iter)->GetTransform();

		if (pos.fY >= HIGHT + 100.f)
		{
			Safe_Delete<CObj*>(*iter);
			iter = m_pEnemyList.erase(iter);
		}
		else
			iter++;
	}

	// PLTOYA
	if (m_pSkill && !m_pSkill->IsDead())
	{
		m_pSkill->Update(_fDeltaTime);
		if (m_pSkill->IsDead())
		{
			delete m_pSkill;
			m_pSkill = nullptr;
		}
	}

	CCollisionMgr::Collision_Cheak(m_pBulletList, m_pEnemyList);
	CCollisionMgr::Collision_Cheak(m_pShip[g_nCurShipIndex]);


	CUISystem::Update(_fDeltaTime);
}

void CCore::Render()
{
	if (m_logo)
	{
		m_logo->Rander(m_hdc);
		return;
	}
	
	background();

	// PLTOYA
	m_localTime += g_DeltaTime;
	if (-45 + 400.f * m_localTime > 45.0001f)
		m_localTime = 0;

	HBRUSH myBrush, tempBrush;
	tempBrush = (HBRUSH)CreateSolidBrush(RGB(80, 80, 80));
	myBrush = (HBRUSH)SelectObject(m_subDC, tempBrush);
	Rectangle(m_subDC, WIDTH / 2 - 90, 0, WIDTH / 2 + 90, 700);
	SelectObject(m_subDC, myBrush);
	DeleteObject(tempBrush);

	tempBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
	myBrush = (HBRUSH)SelectObject(m_subDC, tempBrush);
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(-45 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(0 +   400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(45  + 400.f * m_localTime), WIDTH  / 2 + 5, static_cast < int>(90 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(135 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(180 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(225 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(270 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(315 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(360 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(405 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(450 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(495 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(540 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(585 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(630 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(675 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(720 + 400.f * m_localTime));

	SelectObject(m_subDC, myBrush);
	DeleteObject(tempBrush);


	

	// 여기서 부터 진건 추가 ( 도로랑 스킬 사이 )
	// 적 총알 출력
	for (auto* pEnemy : m_pEnemyBulletList)
		pEnemy->Render(m_subDC);

	// 적 출력
	for (auto& pEnumy : m_pEnemyList)
		pEnumy->Render(m_subDC);
	////////////////////////////////////

	// 스테이지 수 출력
	if (스테이지1 == m_iStage)
	{
		TCHAR        szBuff[32] = L"STAGE : 1";
		TextOut(m_subDC, 400, 100, szBuff, lstrlen(szBuff));
	}
	if (스테이지2 == m_iStage)
	{
		TCHAR        szBuff[32] = L"STAGE : 2";
		TextOut(m_subDC, 400, 100, szBuff, lstrlen(szBuff));
	}
	if (스테이지3 == m_iStage)
	{
		TCHAR        szBuff[32] = L"STAGE : 3";
		TextOut(m_subDC, 400, 100, szBuff, lstrlen(szBuff));
	}
	if (보스스테이지 == m_iStage)
	{
		TCHAR        szBuff[32] = L"BOSS Stage";
		TextOut(m_subDC, 400, 100, szBuff, lstrlen(szBuff));
	}


	TCHAR		Inven[32] = L"";
	wsprintf(Inven, L"Inven %d", g_nCurShipIndex);
	TextOut(m_subDC, 400, 120, Inven, lstrlen(Inven));

	TCHAR		Boom[32] = L"";
	wsprintf(Boom, L"Boom : %d", ((CShipBase*)m_pShip[g_nCurShipIndex])->GetItemCount(폭탄));
	TextOut(m_subDC, 400, 140, Boom, lstrlen(Boom));

	TCHAR		HP[32] = L"";
	wsprintf(HP, L"Heal : %d", ((CShipBase*)m_pShip[g_nCurShipIndex])->GetItemCount(포션));
	TextOut(m_subDC, 400, 160, HP, lstrlen(HP));

	// PLTOYA
	if (m_pSkill && !m_pSkill->IsDead())
		m_pSkill->Render(m_subDC);

	// 아이템
	for (auto& item : m_pItemList)
		item->Render(m_subDC);

	/* Render */	//CObj->Render(m_hdc);
	for (auto* elem : m_pBulletList)
		elem->Render(m_subDC);

	for (auto& iter : m_pShip)
		iter->Render(m_subDC);

	//UI > Render
	CUISystem::Render(m_subDC);

	BitBlt(m_hdc, 0, 0, WIDTH, HIGHT, m_subDC, 0, 0, SRCCOPY);
}

void CCore::Release()
{
	ReleaseDC(m_hWnd, m_hdc);


	for (auto& iter : m_pShip)
		delete iter;

	//PLTOYA
	DeleteDC(m_subDC);
	DeleteObject(m_hBit);
}

void CCore::background()
{
	HBRUSH myBrush, blueBrush;
	blueBrush = (HBRUSH)CreateSolidBrush(RGB(0, 105, 255));
	myBrush = (HBRUSH)SelectObject(m_subDC, blueBrush);
	//Ellipse(m_hdc, 0, 0, WIDTH + 100, HIGHT + 100);
	Rectangle(m_subDC, g_clientRect.left, g_clientRect.top, g_clientRect.right, g_clientRect.bottom);

	SelectObject(m_subDC, myBrush);
	DeleteObject(blueBrush);
}


void CCore::CreateEnemy(int _iType, int _iPoint, int _iStage) {

	if (스테이지1 == _iStage) {
		// 전투기 좌표 등 관리 변수들
		float fType1PointX = 50.f;
		float fType1PointY = 10.f;
		float fType1Size = 30.f;
		float fType1SpeedX = 0.f;
		float fType1SpeedY = 50.f;

		// 포탑 좌표 등 관리 변수들
		float fType2PointX = 50.f;
		float fType2PointY = -50.f;
		float fType2Size = 30.f;
		float fType2SpeedX = 0.f;
		float fType2SpeedY = 150.f;

		//가미카제 좌표 등 관리 변수들
		float fType3PointX = 100.f;
		float fType3PointY = 100.f;
		float fType3Size = 30.f;
		// 가미카제 는 이제 속도조절 이걸로 안함
		float fType3SpeedX = 5.f;
		float fType3SpeedY = 5.f;
		// 나중에 속도 조절 

		switch (_iType)
		{
		case 전투기:
			if (전투기스폰1 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지1)));
			if (전투기스폰2 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 3), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지1)));
			if (전투기스폰3 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 5), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지1)));
			if (전투기스폰4 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 7), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지1)));
			if (전투기스폰5 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 9), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지1)));
			break;

		case 고정포탑:
			if (포탑스폰1 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지1)));
			if (포탑스폰2 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 2), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지1)));
			if (포탑스폰3 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 3), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지1)));
			if (포탑스폰4 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 4), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지1)));
			if (포탑스폰5 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 5), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지1)));
			break;
			//		
		case 가미카제:
			if (가미카제스폰1 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType3PointX * 7), (fType3PointY * 4), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지1)));
			if (가미카제스폰2 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((-fType3PointX * 2), (-fType3PointY), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지1)));
			if (가미카제스폰3 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((-fType3PointX * 5), (fType3PointY), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지1)));
			if (가미카제스폰4 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((-fType3PointX * 5), (-fType3PointY), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지1)));
			if (가미카제스폰5 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType3PointX * 8), (fType3PointY), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지1)));
			break;


		default:
			break;
		}

	};

	if (스테이지2 == _iStage) {
		// 전투기 좌표 등 관리 변수들
		float fType1PointX = 50.f;
		float fType1PointY = -10.f;
		float fType1Size1 = 30.f;
		float fType1SpeedX = 0.f;
		float fType1SpeedY = 50.f;

		// 포탑 좌표 등 관리 변수들
		float fType2PointX = 50.f;
		float fType2PointY = -50.f;
		float fType2Size1 = 30.f;
		float fType2SpeedX = 0.f;
		float fType2SpeedY = 200.f;

		//가지카제 좌표 등 관리 변수들
		float fType3PointX = 400.f;
		float fType3PointY = 100.f;
		float fType3Size1 = 20.f;
		float fType3SpeedX = 10.f;
		float fType3SpeedY = 20.f;
		// 나중에 속도 조절 

		switch (_iType)
		{
		case 전투기:
			if (전투기스폰1 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX), (fType1PointY), (fType1Size1), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지2)));
			if (전투기스폰2 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 3), (fType1PointY), (fType1Size1), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지2)));
			if (전투기스폰3 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 5), (fType1PointY), (fType1Size1), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지2)));
			if (전투기스폰4 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 7), (fType1PointY), (fType1Size1), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지2)));
			if (전투기스폰5 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 9), (fType1PointY), (fType1Size1), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지2)));
			if (전투기스폰6 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 6), (fType1PointY * 10), (fType1Size1), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지2)));
			if (전투기스폰7 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 4), (fType1PointY * 10), (fType1Size1), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지2)));
			break;
		case 고정포탑:
			if (포탑스폰1 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY), (fType2Size1), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지2)));
			if (포탑스폰2 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 2), (fType2Size1), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지2)));
			if (포탑스폰3 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 3), (fType2Size1), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지2)));
			if (포탑스폰4 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 4), (fType2Size1), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지2)));
			if (포탑스폰5 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 5), (fType2Size1), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지2)));
			if (포탑스폰6 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 7), (fType2Size1), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지2)));
			if (포탑스폰7 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 6), (fType2Size1), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지2)));
			break;
		case 가미카제:
			if (가미카제스폰1 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType3PointX * 3), (-fType3PointY * 3), (fType3Size1), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지2)));
			if (가미카제스폰2 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((-fType3PointX), (-fType3PointY * 5), (fType3Size1), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지2)));
			if (가미카제스폰3 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType3PointX * 5), (-fType3PointY * 3), (fType3Size1), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지2)));
			if (가미카제스폰4 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((-fType3PointX * 2), (-fType3PointY * 3), (fType3Size1), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지2)));
			if (가미카제스폰5 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType3PointX * 5), (-fType3PointY * 3), (fType3Size1), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지2)));
			if (가미카제스폰6 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((-fType3PointX), (-fType3PointY * 5), (fType3Size1), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지2)));
			if (가미카제스폰7 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType3PointX * 3), (-fType3PointY * 3), (fType3Size1), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지2)));
			break;


		default:
			break;
		}
	};

	// 스테이지 3 일 떄
	if (스테이지3 == _iStage) {
		// 전투기 좌표 등 관리 변수들
		float fType1PointX = 50.f;
		float fType1PointY = -10.f;
		float fType1Size = 30.f;
		float fType1SpeedX = 0.f;
		float fType1SpeedY = 50.f;

		// 포탑 좌표 등 관리 변수들
		float fType2PointX = 50.f;
		float fType2PointY = 100.f;
		float fType2Size = 30.f;
		float fType2SpeedX = 0.f;
		float fType2SpeedY = 200.f;

		//가지카제 좌표 등 관리 변수들
		float fType3PointX = 400.f;
		float fType3PointY = 100.f;
		float fType3Size = 20.f;
		float fType3SpeedX = 10.f;
		float fType3SpeedY = 20.f;
		// 나중에 속도 조절 

		switch (_iType)
		{
		case 전투기:
			if (전투기스폰1 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지3)));
			if (전투기스폰2 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 3), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지3)));
			if (전투기스폰3 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 5), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지3)));
			if (전투기스폰4 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 7), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지3)));
			if (전투기스폰5 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 9), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지3)));
			if (전투기스폰6 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 8), (fType1PointY * 6), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지3)));
			if (전투기스폰7 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 6), (fType1PointY * 6), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지3)));
			if (전투기스폰8 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 4), (fType1PointY * 6), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지3)));
			if (전투기스폰9 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 2), (fType1PointY * 6), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (스테이지3)));
			break;
		case 고정포탑:
			if (포탑스폰1 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지3)));
			if (포탑스폰2 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 2), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지3)));
			if (포탑스폰3 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 3), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지3)));
			if (포탑스폰4 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 4), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지3)));
			if (포탑스폰5 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 5), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지3)));
			if (포탑스폰6 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 6), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지3)));
			if (포탑스폰7 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 7), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지3)));
			if (포탑스폰8 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 8), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지3)));
			if (포탑스폰9 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 9), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (스테이지3)));
			break;
		case 가미카제:
			if (가미카제스폰1 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType3PointX * 3), (-fType3PointY * 3), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지3)));
			if (가미카제스폰2 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((-fType3PointX), (-fType3PointY * 5), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지3)));
			if (가미카제스폰3 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType3PointX * 5), (-fType3PointY * 3), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지3)));
			if (가미카제스폰4 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((-fType3PointX * 2), (-fType3PointY * 3), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지3)));
			if (가미카제스폰5 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType3PointX * 5), (-fType3PointY * 3), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지3)));
			if (가미카제스폰6 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((-fType3PointX), (-fType3PointY * 5), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지3)));
			if (가미카제스폰7 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType3PointX * 3), (-fType3PointY * 3), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지3)));
			if (가미카제스폰8 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((-fType3PointX * 2), (-fType3PointY * 3), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지3)));
			if (가미카제스폰9 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType3PointX * 5), (-fType3PointY * 3), (fType3Size), (fType3SpeedX), (fType3SpeedY), (가미카제), (스테이지3)));
			break;

		default:
			break;
		}
	}
	if (보스스테이지 == _iStage) {
		float fType1PointX = 50.f;
		float fType1PointY = -10.f;
		float fType1Size = 30.f;
		float fType1SpeedX = 0.f;
		float fType1SpeedY = 50.f;

		// 포탑 좌표 등 관리 변수들
		float fType2PointX = 50.f;
		float fType2PointY = 100.f;
		float fType2Size = 30.f;
		float fType2SpeedX = 0.f;
		float fType2SpeedY = 200.f;

		//가지카제 좌표 등 관리 변수들
		float fType3PointX = 400.f;
		float fType3PointY = 100.f;
		float fType3Size = 20.f;
		float fType3SpeedX = 10.f;
		float fType3SpeedY = 20.f;
		// 나중에 속도 조절 

		switch (_iType)
		{
		case 전투기:
			if (전투기스폰1 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (보스스테이지)));
			if (전투기스폰2 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 3), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (보스스테이지)));
			if (전투기스폰3 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 5), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (보스스테이지)));
			if (전투기스폰4 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 7), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (보스스테이지)));
			if (전투기스폰5 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 9), (fType1PointY), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (보스스테이지)));
			if (전투기스폰6 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 8), (fType1PointY * 6), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (보스스테이지)));
			if (전투기스폰7 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 6), (fType1PointY * 6), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (보스스테이지)));
			if (전투기스폰8 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 4), (fType1PointY * 6), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (보스스테이지)));
			if (전투기스폰9 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType1PointX * 2), (fType1PointY * 6), (fType1Size), (fType1SpeedX), (fType1SpeedY), (전투기), (보스스테이지)));
			break;
		case 고정포탑:
			if (포탑스폰1 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (보스스테이지)));
			if (포탑스폰2 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 2), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (보스스테이지)));
			if (포탑스폰3 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 3), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (보스스테이지)));
			if (포탑스폰4 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 4), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (보스스테이지)));
			if (포탑스폰5 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 5), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (보스스테이지)));
			if (포탑스폰6 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 6), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (보스스테이지)));
			if (포탑스폰7 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 7), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (보스스테이지)));
			if (포탑스폰8 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 8), (fType2PointY * 8), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (보스스테이지)));
			if (포탑스폰9 == _iPoint)
				m_pEnemyList.push_back(new CEnemy((fType2PointX * 2), (fType2PointY * 9), (fType2Size), (fType2SpeedX), (fType2SpeedY), (고정포탑), (보스스테이지)));
			break;
		}
	};
	// 유도 ,  후순위 고정포탑 / 실드 / 스크류미사일 -> 중심이 있고 그 중심을 기준으로 돌린다 , 
}