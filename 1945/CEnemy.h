#pragma once
#include "CObj.h"

// ���� �߰� ��� CEnemy

class CEnemy :
    public CObj
{
public:
    CEnemy();
    CEnemy(Transform _transform); // fX, fY, fScale
    CEnemy(float _xPos, float _yPos, float _fScale, float _fSpeedX, float _fSpeedY, int _EnemyType, int _iStage);
    virtual ~CEnemy();

public:
    virtual	    void Initalize() override {};
    virtual		void Update(float _fDeltaTime) override;
    virtual		void Render(HDC _hdc)		   override;

public:

    void        EnemyMoveMent();
    // ���� �ּҸ� �������� �Լ�
    void        SetEnemyBulletList(list<CObj*>* _pEnemyBulletlist) { m_pEnemyBulletList = _pEnemyBulletlist; }
    // ���� X Y �� ���� �������� �Լ�
    float GetPosinX() { return (float)m_tPosin.x; }
    float GetPosinY() { return (float)m_tPosin.y; }

    void        SetPlayer(CObj* _pPlayer) { m_pPlayer = _pPlayer; }

    void        TakeDamage(int _iDamage);
    int         GetEnemyHp() { return m_iEnemyHp; }

    bool        IsTakeSkill()        { return m_isTakeSkill; }
    void        SetTakeSkill()       { m_isTakeSkill = true; }
    void        SetTakeSkill_false() { m_isTakeSkill = false; }

private:
    // ���� ���� ���ǵ�
    float       m_fSpeedX;
    float       m_fSpeedY;

    // �� �̵� ����
    bool        m_EnumyMovement;

    // �� ���� �з���
    int         m_iEnemyType;

    POINT       m_tPosin;
    float       m_fDistance;

    float       m_iStage;

    //barrel
    // ���� �̵��ӵ� ?
    float		m_fPosinSpeed;
    // ������ ���� �̵�
    float		m_fPosinAngle;

    // �Ѿ� ������ ���� ������ ����Ʈ �ּҸ� ������
    list<CObj*>* m_pEnemyBulletList;

    CObj*   m_pPlayer;

    // ���� ä�� 
    int     m_iEnemyHp;
    int     m_iEnemyMaxHp;

    bool    m_isTakeSkill = false;

    // �� �Ʒ��� �ڵ� �ۼ� x
private:
    // ������ �ð��� ���õ� �ɹ� ���� 
    float m_time1 = 0.f;
    float m_time2 = 0.f;
    float m_time3 = 0.f;
    //float m_time4 = 0.f;

};


