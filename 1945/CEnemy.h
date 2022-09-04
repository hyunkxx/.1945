#pragma once
#include "CObj.h"

// 진건 추가 헤더 CEnemy

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
    // 블릿의 주소를 가져오는 함수
    void        SetEnemyBulletList(list<CObj*>* _pEnemyBulletlist) { m_pEnemyBulletList = _pEnemyBulletlist; }
    // 포신 X Y 축 정보 가져오는 함수
    float GetPosinX() { return (float)m_tPosin.x; }
    float GetPosinY() { return (float)m_tPosin.y; }

    void        SetPlayer(CObj* _pPlayer) { m_pPlayer = _pPlayer; }

    void        TakeDamage(int _iDamage);
    int         GetEnemyHp() { return m_iEnemyHp; }

    bool        IsTakeSkill()        { return m_isTakeSkill; }
    void        SetTakeSkill()       { m_isTakeSkill = true; }
    void        SetTakeSkill_false() { m_isTakeSkill = false; }

private:
    // 가로 세로 스피드
    float       m_fSpeedX;
    float       m_fSpeedY;

    // 적 이동 패턴
    bool        m_EnumyMovement;

    // 적 종류 분류용
    int         m_iEnemyType;

    POINT       m_tPosin;
    float       m_fDistance;

    float       m_iStage;

    //barrel
    // 포신 이동속도 ?
    float		m_fPosinSpeed;
    // 포신의 각도 이동
    float		m_fPosinAngle;

    // 총알 생성을 위해 가져온 리스트 주소를 넣을거
    list<CObj*>* m_pEnemyBulletList;

    CObj*   m_pPlayer;

    // 몬스터 채력 
    int     m_iEnemyHp;
    int     m_iEnemyMaxHp;

    bool    m_isTakeSkill = false;

    // 요 아래로 코드 작성 x
private:
    // 프레임 시간에 관련된 맴버 변수 
    float m_time1 = 0.f;
    float m_time2 = 0.f;
    float m_time3 = 0.f;
    //float m_time4 = 0.f;

};


