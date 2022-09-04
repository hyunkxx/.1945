#pragma once


#define TEXT_LENGTH			64
#define WIDTH				500
#define HIGHT				700
#define PURE				= 0
#define SHIP_COUNT			3
#define PI					3.14f


// ���� �߰�
// ������ ���� Ÿ�� ���
#include <ctime>

//#define		PI			3.141592f

// ������ ����Ʈ
template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}
// ���� �����Ǵ� ������ġ
enum EnemySpawnPoint {
	Point1, Point2, Point3, Point4, Point5, Point6, Point7, Point8, Point9,
	Point10, Point11, Point12, Point13, Point14, Point15, Point16, Point17, Point18, Point19, MaxEnemy
};

// ���� �̵� ����
enum EnemyType { ������, ������ž, ����ī�� };

enum Type1EnemySpawnPoint { �����⽺��1, �����⽺��2, �����⽺��3, �����⽺��4, �����⽺��5, �����⽺��6, �����⽺��7, �����⽺��8, �����⽺��9, ������Max };
enum Type2EnemySpawnPoint { ��ž����1, ��ž����2, ��ž����3, ��ž����4, ��ž����5, ��ž����6, ��ž����7, ��ž����8, ��ž����9, ��žMax };
enum Type3EnemySpawnPoint { ����ī������1, ����ī������2, ����ī������3, ����ī������4, ����ī������5, ����ī������6, ����ī������7, ����ī������8, ����ī������9, ����ī��Max };
enum StageRount { ��������1 = 1, ��������2, ��������3, ������������ };

