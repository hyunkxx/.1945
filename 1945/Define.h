#pragma once


#define TEXT_LENGTH			64
#define WIDTH				500
#define HIGHT				700
#define PURE				= 0
#define SHIP_COUNT			3
#define PI					3.14f


// 진건 추가
// 난수를 위한 타임 헤더
#include <ctime>

//#define		PI			3.141592f

// 세이프 딜리트
template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}
// 적이 생성되는 스폰위치
enum EnemySpawnPoint {
	Point1, Point2, Point3, Point4, Point5, Point6, Point7, Point8, Point9,
	Point10, Point11, Point12, Point13, Point14, Point15, Point16, Point17, Point18, Point19, MaxEnemy
};

// 적의 이동 방향
enum EnemyType { 전투기, 고정포탑, 가미카제 };

enum Type1EnemySpawnPoint { 전투기스폰1, 전투기스폰2, 전투기스폰3, 전투기스폰4, 전투기스폰5, 전투기스폰6, 전투기스폰7, 전투기스폰8, 전투기스폰9, 전투기Max };
enum Type2EnemySpawnPoint { 포탑스폰1, 포탑스폰2, 포탑스폰3, 포탑스폰4, 포탑스폰5, 포탑스폰6, 포탑스폰7, 포탑스폰8, 포탑스폰9, 포탑Max };
enum Type3EnemySpawnPoint { 가미카제스폰1, 가미카제스폰2, 가미카제스폰3, 가미카제스폰4, 가미카제스폰5, 가미카제스폰6, 가미카제스폰7, 가미카제스폰8, 가미카제스폰9, 가미카제Max };
enum StageRount { 스테이지1 = 1, 스테이지2, 스테이지3, 보스스테이지 };

