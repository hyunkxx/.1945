#include "pch.h"
#include "CEnemy.h"


#include "pch.h"
#include "CEnemy.h"
#include "CCore.h"
#include "CBullet.h"
#include "CShipBase.h"

CEnemy::CEnemy()
{
	// ������ ��ǥ�� ������ ���� ���� �ʰ�
	ZeroMemory(&m_tPosin, sizeof(POINT));
}

CEnemy::CEnemy(Transform _transform)
	: CObj(_transform)
{
}

CEnemy::CEnemy(float _xPos, float _yPos, float _fScale, float _fSpeedX, float _fSpeedY, int _EnemyType, int _iStage)
	: CObj(_xPos, _yPos, _fScale)
	//, m_EnumyMovement(��)
{

	// ���� ������ �Է¹ް� CObj�� ����
	// fScale �� ũ�� 
	//m_transform.fX = _xPos;
	//m_transform.fY = _yPos;
	//m_transform.fScale = _fScale;
	// ���ǵ�� �ϴ� �ŰԺ����� ���� 
	// �ƴϸ� ���� ���� ? �����
	m_fSpeedX = _fSpeedX;
	m_fSpeedY = _fSpeedY;

	m_iEnemyType = _EnemyType;
	m_iStage = _iStage;

	if (��������1 == m_iStage)
	{
		if (������ == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -50.f;
		}

		if (������ž == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -20.f;
		}

		if (����ī�� == m_iEnemyType) {
			//m_fDistance = 30.f;
			m_fPosinAngle = -90.f;
			m_fPosinSpeed = 0.f;
		}

		m_iEnemyMaxHp = 100;
		m_iEnemyHp = m_iEnemyMaxHp;
	}

	if (��������2 == m_iStage)
	{
		if (������ == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -50.f;
		}
		// ������ž ������ �ӵ� ����
		if (������ž == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -50.f;
		}

		if (����ī�� == m_iEnemyType) {
			//m_fDistance = 30.f;
			m_fPosinAngle = -90.f;
			m_fPosinSpeed = 0.f;
		}

		m_iEnemyMaxHp = 100;
		m_iEnemyHp = m_iEnemyMaxHp;
	}

	if (��������3 == m_iStage)
	{
		if (������ == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -50.f;
		}
		// ������ž ������ �ӵ� ����
		if (������ž == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -70.f;
		}

		if (����ī�� == m_iEnemyType) {
			//m_fDistance = 30.f;
			m_fPosinAngle = -90.f;
			m_fPosinSpeed = 0.f;
		}

		m_iEnemyMaxHp = 100;
		m_iEnemyHp = m_iEnemyMaxHp;
	}

	if (������������ == m_iStage)
	{
		if (������ == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -50.f;
		}
		// ������ž ������ �ӵ� ����
		if (������ž == m_iEnemyType) {
			m_fDistance = 30.f;
			m_fPosinAngle = 0.f;
			m_fPosinSpeed = -100.f;
		}

		if (����ī�� == m_iEnemyType) {
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


	// ����
	// ��� ���߰� ?
		// ���� ����

		//float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		// ���� ������ ��Ÿ��� ?

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



	if (m_iEnemyType == ����ī��) {


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


	// ������ �����ͼ� ������ ��ǥ�� ����

	m_tPosin.x = LONG(GetX() + m_fDistance * cos(m_fPosinAngle * (PI / 180.f)));
	m_tPosin.y = LONG(GetY() - m_fDistance * sin(m_fPosinAngle * (PI / 180.f)));

	// cos(m_fPosinAngle * (PI / 180.f)));
	// sin(m_fPosinAngle * (PI / 180.f)));

	EnemyMoveMent();

	SetRect();



	//�� �Ʒ��� �ڵ� �ۼ� x
	//�Ѿ� ���� new
  // ���� �ð��� �Ǹ� �Ѿ��� ������
	m_time1 += _fDeltaTime;
	m_time2 += _fDeltaTime;
	m_time3 += _fDeltaTime;

	// �� Ÿ�Կ� �´� ���Ű���, ��ǥ�� �ѱ�� �Ѿ˻��� ( 1�������� )

	if (��������1 == m_iStage) {

		if (m_iEnemyType == ������)
			if ((100 < m_transform.fY) && ((m_fPosinAngle < -89.9f) && (m_fPosinAngle > -90.1f)))
				if (m_time1 > 0.7f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, ������);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time1 = 0;
				}


		if (m_iEnemyType == ������ž)
			if (50 < m_transform.fY) {
				if (m_time2 > 0.7f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, ������ž);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time2 = 0;
				}
			}
	}

	// 2�������� �Ѿ� �߻��ֱ� ����
	if (��������2 == m_iStage) {

		if (m_iEnemyType == ������)
			if ((100 < m_transform.fY) && ((m_fPosinAngle < -89.9f) && (m_fPosinAngle > -90.1f)))
				if (m_time1 > 0.5f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, ������);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time1 = 0;
				}

		if (m_iEnemyType == ������ž)
			if (50 < m_transform.fY) {
				if (m_time2 > 0.5f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, ������ž);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time2 = 0;
				}
			}
	}

	//3�������� �Ѿ� �߻� �ֱ� ���� 
	if (��������3 == m_iStage) {

		if (m_iEnemyType == ������)
			if ((100 < m_transform.fY) && ((m_fPosinAngle < -89.9f) && (m_fPosinAngle > -90.1f)))
				if (m_time1 > 0.3f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, ������);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time1 = 0;
				}


		if (m_iEnemyType == ������ž)
			if (50 < m_transform.fY) {
				if (m_time2 > 0.3f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, ������ž);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time2 = 0;
				}
			}
	}

	// ������������
	if (������������ == m_iStage) {

		if (m_iEnemyType == ������)
			if (100 < m_transform.fY)
				if (m_time1 > 0.1f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, ������);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time1 = 0;
				}


		if (m_iEnemyType == ������ž)
			if (50 < m_transform.fY) {
				if (m_time2 > 0.1f) {

					CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
					dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, ������ž);
					m_pEnemyBulletList->push_back(pEnemyBullet);
					m_time2 = 0;
				}
			}
	}

	/*if (m_iEnemyType == ����ī��)
		if (m_time3 > 0.5f) {
			CObj* pEnemyBullet = new CBullet((float)m_tPosin.x, (float)m_tPosin.y);
			dynamic_cast<CBullet*>(pEnemyBullet)->InitEnemy(m_fPosinAngle, ����ī��);
			m_pEnemyBulletList->push_back(pEnemyBullet);
			m_time3 = 0;
		}*/

		// ���� 3.f �̻��̸� �÷��̾� ��ǥ�� �����´� 
		// �÷��̾� ��ǥ �� ����/���� ������ ���ϰ� �װ����� ������ ������ �����


		// Y���� 100 ���� �����´ٸ�
		//if (100 < m_transform.fY)
		//	m_fSpeedY = 200.f;  // �ӵ��� ������ 
		//���� �� 
}

// �� , ���� ������ ���� �Լ�
void CEnemy::EnemyMoveMent() {

	// 1�������� 
	if (��������1 == m_iStage) {
		// ������ �ϰ��
		if (m_iEnemyType == ������) {
			// Y���� 300 ���� �����´ٸ�
			if (100 < m_transform.fY)
				m_fSpeedY = 100.f;  // ���߿� 0����

			// ���� ������ �Ʒ��� ���� ���� ����
			if ((m_fPosinAngle < -89.9f) && (m_fPosinAngle > -90.1f))
			{
				m_fPosinSpeed = 0.f;
			}
		}

		m_fPosinAngle += m_fPosinSpeed * CCore::g_DeltaTime;
	}
	// 2�������� ������ �� ��� �ٰ���
	if (��������2 == m_iStage) {
		// ������ �ϰ��
		if (m_iEnemyType == ������) {
			// Y���� 300 ���� �����´ٸ�
			if (100 < m_transform.fY)
				m_fSpeedY = 150.f;  // ���߿� 0����

			// ���� ������ �Ʒ��� ���� ���� ����
			if ((m_fPosinAngle < -89.9f) && (m_fPosinAngle > -90.1f))
			{
				m_fPosinSpeed = 0;
			}
		}

		m_fPosinAngle += m_fPosinSpeed * CCore::g_DeltaTime;
	}
	// 3�������� ������ ���� �ٰ���
	if (��������3 == m_iStage) {
		// ������ �ϰ��
		if (m_iEnemyType == ������) {
			// Y���� 300 ���� �����´ٸ�
			if (100 < m_transform.fY)
				m_fSpeedY = 200.f;  // ���߿� 0����

			// ��ä�� �� �߻�
			if ((m_fPosinAngle < -89.9f) && (m_fPosinAngle > -90.1f))
			{
				m_fPosinSpeed = 0;
			}
		}

		m_fPosinAngle += m_fPosinSpeed * CCore::g_DeltaTime;
	}

	// ������������
	if (������������ == m_iStage) {
		// ������ �ϰ��
		if (m_iEnemyType == ������) {
			// Y���� 300 ���� �����´ٸ�
			if (100 < m_transform.fY)
				m_fSpeedY = 0.f;  // ���߿� 0����

			// ���� ������ �Ʒ��� ���� ���� ����
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
	// �� �� �켱 �׸�� ����
	Rectangle(_hdc,
		m_rect.left,
		m_rect.top,
		m_rect.right,
		m_rect.bottom);


	// ���� ���ؼ� ���� �׸��� 
	if (����ī�� != m_iEnemyType) {
		MoveToEx(_hdc, (int)GetX(), (int)GetY(), nullptr);
		LineTo(_hdc, m_tPosin.x, m_tPosin.y);

	}


	/*Rectangle(_hdc,
		(m_rect.left + m_rect.right),
		(m_rect.top + m_rect.bottom),
		m_tPosin.x,
		m_tPosin.y);*/
}

// ���� �Ѿ� ���� - ���� ���� �� �ľ��ϰ� �Ұ�.
// ������ ���Ͱ� �������� �ʾҴµ� �Ѿ��� �����ؼ� ���� nullptr ����.

void CEnemy::TakeDamage(int _iDamage) {
	m_iEnemyHp -= _iDamage;

	if (0 >= m_iEnemyHp)
		SetDead();
}
