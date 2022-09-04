#include "pch.h"
#include "CEnemy.h"


#include "pch.h"
#include "CEnemy.h"
#include "CCore.h"
#include "CBullet.h"
#include "CShipBase.h"

CEnemy::CEnemy()
{
	// 포신의 좌표에 쓰레기 값이 들어가진 않게
	ZeroMemory(&m_tPosin, sizeof(POINT));
}

CEnemy::CEnemy(Transform _transform)
	: CObj(_transform)
{
}

CEnemy::CEnemy(float _xPos, float _yPos, float _fScale, float _fSpeedX, float _fSpeedY, int _EnemyType, int _iStage)
	: CObj(_xPos, _yPos, _fScale)
	//, m_EnumyMovement(좌)
{

	// 생성 지점을 입력받고 CObj로 전달
	// fScale 은 크기 
	//m_transform.fX = _xPos;
	//m_transform.fY = _yPos;
	//m_transform.fScale = _fScale;
	// 스피드는 일단 매게변수로 전달 
	// 아니면 따로 설정 ? 고민좀
	m_fSpeedX = _fSpeedX;
	m_fSpeedY = _fSpeedY;

	m_iEnemyType = _EnemyType;
	m_iStage = _iStage;

	if (스테이지1 == m_iStage)
	{
		if (전투기 == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -50.f;
		}

		if (고정포탑 == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -20.f;
		}

		if (가미카제 == m_iEnemyType) {
			//m_fDistance = 30.f;
			m_fPosinAngle = -90.f;
			m_fPosinSpeed = 0.f;
		}

		m_iEnemyMaxHp = 100;
		m_iEnemyHp = m_iEnemyMaxHp;
	}

	if (스테이지2 == m_iStage)
	{
		if (전투기 == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -50.f;
		}
		// 고정포탑 돌리는 속도 증가
		if (고정포탑 == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -50.f;
		}

		if (가미카제 == m_iEnemyType) {
			//m_fDistance = 30.f;
			m_fPosinAngle = -90.f;
			m_fPosinSpeed = 0.f;
		}

		m_iEnemyMaxHp = 100;
		m_iEnemyHp = m_iEnemyMaxHp;
	}

	if (스테이지3 == m_iStage)
	{
		if (전투기 == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -50.f;
		}
		// 고정포탑 돌리는 속도 증가
		if (고정포탑 == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -70.f;
		}

		if (가미카제 == m_iEnemyType) {
			//m_fDistance = 30.f;
			m_fPosinAngle = -90.f;
			m_fPosinSpeed = 0.f;
		}

		m_iEnemyMaxHp = 100;
		m_iEnemyHp = m_iEnemyMaxHp;
	}

	if (보스스테이지 == m_iStage)
	{
		if (전투기 == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -50.f;
		}
		// 고정포탑 돌리는 속도 증가
		if (고정포탑 == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -100.f;
		}

		if (가미카제 == m_iEnemyType) {
			//m_fDistance = 30.f;
			m_fPosinAngle = -90.f;
			m_fPosinSpeed = 0.f;
		}

		m_iEnemyMaxHp = 1000;
		m_iEnemyHp = m_iEnemyMaxHp;
	}


}

CEnemy::~CEnemy()
{
}



void CEnemy::Update(float _fDeltaTime)
{
	// if  target  30 , 500

	//float fTargetx = m_pPlayer->GetTransform().fX;
	//float fTargety = m_pPlayer->GetTransform().fY;

	//float lockonX = (fTargetx - (float)m_transform.fX);
	//float lockonY = (fTargety - (float)m_transform.fY);

	//float lockonRadian = atanf(lockonX / lockonY);
	//float lockonAngle = lockonRadian * (180.f / PI);


	// 각도
	// 잠깐 멈추게 ?
		// 유도 공식

		//float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		// 여기 까지가 피타고라스 ?

		//float	fRadian = atanf(fHeight / fWidth);


		//float lockonAngle = fRadian * (180.f / PI);

		//if (m_pPlayer->GetTransform().fY > m_transform.fY)
			//lockonAngle *= -1.f;

		/*m_time4 = _fDeltaTime;

		if (m_time4 > 3.0f) {
			m_fSpeedX1 = m_fSpeedX;
			m_fSpeedY1 = m_fSpeedY;

			m_fSpeedX = 0.f;
			m_fSpeedY = 0.f;

			m_transform.fX += m_fSpeedX * cosf(lockonAngle) * (PI / 180.f);
			m_transform.fY -= m_fSpeedY * sinf(lockonAngle) * (PI / 180.f);


			if (m_time4 > 10.0f)
			{
				m_fSpeedX = m_fSpeedX1;
				m_fSpeedY = m_fSpeedY1;

				m_transform.fX += m_fSpeedX * cosf(lockonAngle) * (PI / 180.f);
				m_transform.fY -= m_fSpeedY * sinf(lockonAngle) * (PI / 180.f);

			}
		}*/



	if (m_iEnemyType == 가미카제) {


		float	xdir = (m_pPlayer->GetTransform().fX - m_transform.fX);
		float	ydir = (m_pPlayer->GetTransform().fY - m_transform.fY);
		m_transform.fX += xdir * _fDeltaTime;
		m_transform.fY += ydir * _fDeltaTime;


		/*float x = m_pPlayer->GetTransform().fX - m_transform.fX;
		float y = m_pPlayer->GetTransform().fY - m_transform.fY;
		float scale = sqrt( x * x + y * y);
		float coef = 100.f;
		m_transform.fX += coef*_fDeltaTime * x * 1 / scale;
		m_transform.fY += coef*_fDeltaTime * y * 1 / scale;*/

		SetRect();

	}
	else {
		m_transform.fX += m_fSpeedX * CCore::g_DeltaTime;// CCore::g_DeltaTime;
		m_transform.fY += m_fSpeedY * CCore::g_DeltaTime; // CCore::g_DeltaTime;
	}


	// 뭔가를 가져와서 포신의 좌표를 생성

	m_tPosin.x = LONG(GetX() + m_fDistance * cos(m_fPosinAngle * (PI / 180.f)));
	m_tPosin.y = LONG(GetY() - m_fDistance * sin(m_fPosinAngle * (PI / 180.f)));

	// cos(m_fPosinAngle * (PI / 180.f)));
	// sin(m_fPosinAngle * (PI / 180.f)));

	EnemyMoveMent();

	SetRect();



	//요 아래로 코드 작성 x
	//총알 생성 new
  // 일정 시간이 되면 총알을 만들어라
	m_time1 += _fDeltaTime;
	m_time2 += _fDeltaTime;
	m_time3 += _fDeltaTime;

	// 각 타입에 맞는 포신각도, 좌표를 넘기고 총알생성 ( 1스테이지 )

	if (스테이지1 == m_iStage) {

		if (m_iEnemyType == 전투기)
			if ((100 < m_transform.fY) && ((m_fPosinAngle < -89.9f) && (m_fPosinAngle > -90.1f)))
				if (m_time1 > 0.7f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, 전투기);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time1 = 0;
				}


		if (m_iEnemyType == 고정포탑)
			if (50 < m_transform.fY) {
				if (m_time2 > 0.7f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, 고정포탑);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time2 = 0;
				}
			}
	}

	// 2스테이지 총알 발사주기 증가
	if (스테이지2 == m_iStage) {

		if (m_iEnemyType == 전투기)
			if ((100 < m_transform.fY) && ((m_fPosinAngle < -89.9f) && (m_fPosinAngle > -90.1f)))
				if (m_time1 > 0.5f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, 전투기);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time1 = 0;
				}

		if (m_iEnemyType == 고정포탑)
			if (50 < m_transform.fY) {
				if (m_time2 > 0.5f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, 고정포탑);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time2 = 0;
				}
			}
	}

	//3스테이지 총알 발사 주기 증가 
	if (스테이지3 == m_iStage) {

		if (m_iEnemyType == 전투기)
			if ((100 < m_transform.fY) && ((m_fPosinAngle < -89.9f) && (m_fPosinAngle > -90.1f)))
				if (m_time1 > 0.3f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, 전투기);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time1 = 0;
				}


		if (m_iEnemyType == 고정포탑)
			if (50 < m_transform.fY) {
				if (m_time2 > 0.3f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, 고정포탑);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time2 = 0;
				}
			}
	}

	// 보스스테이지
	if (보스스테이지 == m_iStage) {

		if (m_iEnemyType == 전투기)
			if (100 < m_transform.fY)
				if (m_time1 > 0.1f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, 전투기);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time1 = 0;
				}


		if (m_iEnemyType == 고정포탑)
			if (50 < m_transform.fY) {
				if (m_time2 > 0.1f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, 고정포탑);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time2 = 0;
				}
			}
	}

	/*if (m_iEnemyType == 가미카제)
		if (m_time3 > 0.5f) {
			CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
			dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, 가미카제);
			m_pEnemyBulletList->push_back(pEnemyBullet);
			m_time3 = 0;
		}*/

		// 만약 3.f 이상이면 플레이어 좌표를 가져온다 
		// 플레이어 좌표 와 포신/적의 각도를 구하고 그각도를 포신의 각도로 맞춘다


		// Y축이 100 까지 내려온다면
		//if (100 < m_transform.fY)
		//	m_fSpeedY = 200.f;  // 속도를 빠르게 
		//패턴 굿 
}

// 적 , 포신 움직임 관련 함수
void CEnemy::EnemyMoveMent() {

	// 1스테이지 
	if (스테이지1 == m_iStage) {
		// 전투기 일경우
		if (m_iEnemyType == 전투기) {
			// Y축이 300 까지 내려온다면
			if (100 < m_transform.fY)
				m_fSpeedY = 100.f;  // 나중에 0으로

			// 포의 각도가 아래를 보면 포를 고정
			if ((m_fPosinAngle < -89.9f) && (m_fPosinAngle > -90.1f))
			{
				m_fPosinSpeed = 0.f;
			}
		}

		m_fPosinAngle += m_fPosinSpeed * CCore::g_DeltaTime;
	}
	// 2스테이지 전투기 는 살살 다가옴
	if (스테이지2 == m_iStage) {
		// 전투기 일경우
		if (m_iEnemyType == 전투기) {
			// Y축이 300 까지 내려온다면
			if (100 < m_transform.fY)
				m_fSpeedY = 150.f;  // 나중에 0으로

			// 포의 각도가 아래를 보면 포를 고정
			if ((m_fPosinAngle < -89.9f) && (m_fPosinAngle > -90.1f))
			{
				m_fPosinSpeed = 0;
			}
		}

		m_fPosinAngle += m_fPosinSpeed * CCore::g_DeltaTime;
	}
	// 3스테이지 전투기 빨리 다가옴
	if (스테이지3 == m_iStage) {
		// 전투기 일경우
		if (m_iEnemyType == 전투기) {
			// Y축이 300 까지 내려온다면
			if (100 < m_transform.fY)
				m_fSpeedY = 200.f;  // 나중에 0으로

			// 부채꼴 포 발사
			if ((m_fPosinAngle < -89.9f) && (m_fPosinAngle > -90.1f))
			{
				m_fPosinSpeed = 0;
			}
		}

		m_fPosinAngle += m_fPosinSpeed * CCore::g_DeltaTime;
	}

	// 보스스테이지
	if (보스스테이지 == m_iStage) {
		// 전투기 일경우
		if (m_iEnemyType == 전투기) {
			// Y축이 300 까지 내려온다면
			if (100 < m_transform.fY)
				m_fSpeedY = 0.f;  // 나중에 0으로

			// 포의 각도가 아래를 보면 포를 고정
			if (m_fPosinAngle > -79.9f)
			{
				m_fPosinSpeed = -1.f;
			}
			if (m_fPosinAngle < -100.1f)
				m_fPosinSpeed = -1.f;
		}

		m_fPosinAngle += m_fPosinSpeed * CCore::g_DeltaTime;
	}

}
void CEnemy::Render(HDC _hdc)
{
	// 적 을 우선 네모로 생성
	Rectangle(_hdc,
		m_rect.left,
		m_rect.top,
		m_rect.right,
		m_rect.bottom);


	// 중점 구해서 포신 그리기 
	if (가미카제 != m_iEnemyType) {
		MoveToEx(_hdc, (int)GetX(), (int)GetY(), nullptr);
		LineTo(_hdc, m_tPosin.x, m_tPosin.y);

	}


	/*Rectangle(_hdc,
		(m_rect.left + m_rect.right),
		(m_rect.top + m_rect.bottom),
		m_tPosin.x,
		m_tPosin.y);*/
}

// 몬스터 총알 생성 - 생성 순서 잘 파악하고 할것.
// 전에는 몬스터가 생기지도 않았는데 총알을 생성해서 생긴 nullptr 오류.

void CEnemy::TakeDamage(int _iDamage) {
	m_iEnemyHp -= _iDamage;

	if (0 >= m_iEnemyHp)
		SetDead();
}
