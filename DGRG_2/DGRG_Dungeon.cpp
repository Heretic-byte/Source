
#include "DGRG_Dungeon.h"
#include "Builders/Grid/GridDungeonConfig.h"
#include "GridDungeonModelHelper.h"
#include "Delegate.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "NavArea.h"
#include "NavigationData.h"


ADGRG_Dungeon::ADGRG_Dungeon()
{
	PrimaryActorTick.bCanEverTick = false;
	m_MonsterHordeClass = AMonsterHordeManager::StaticClass();
}

void ADGRG_Dungeon::BeginPlay()
{
	Super::BeginPlay();

	m_GameInstance = GetGameInstance<UDGRG_GameInstance>();
	FVector location = GetActorLocation();
	m_DungeonInstance = Cast<ADungeon>(GetWorld()->SpawnActor(ADungeon::StaticClass(), &location));


	m_DungeonInstance->OnDungeonBuildComplete.AddDynamic(this, &ADGRG_Dungeon::OnDungeonBuildComplete);

	PRINTF("DG_Begin");
}
void ADGRG_Dungeon::SetInstance(int32 playerLevel, E_DIFFICULTY diff,  UDGRG_DungeonThemeAsset * dgTheme)
{
	m_DungeonSizeScale = 1.0f;
	m_RoomCount = 0;
	SetDungeonLevel(playerLevel);
	SetDifficulty(diff);
	SetDungeonTheme(dgTheme);
	PRINTF("DG_SetIns");
}

void ADGRG_Dungeon::SetDungeonLevel(int32 lvl)
{
	m_CurrentLevel = lvl;
	m_DungeonSizeScale += m_GameInstance->GetDungeonLevelScale(lvl).m_Value;
}

void ADGRG_Dungeon::SetDifficulty(E_DIFFICULTY diff)
{
	m_CurrentDifficulty = diff;

	m_DungeonSizeScale += m_GameInstance->GetDungeonDiffyScale(diff).m_Value;
}

void ADGRG_Dungeon::SetDungeonTheme( UDGRG_DungeonThemeAsset * dgTheme)
{
	m_DungeonInstance->Themes.Empty();

	m_CurrentThemeAsset = dgTheme;

	m_DungeonInstance->Themes.Add(m_CurrentThemeAsset->GetDungeonTheme());
}

void ADGRG_Dungeon::GenerateDungeon()
{
	PRINTF("Spawn Mesh Dungeon");
	SpawnDungeonMesh();
}

void ADGRG_Dungeon::SpawnDungeonMesh()
{
	PRINTF("Spawn Mesh 1");
	if (m_DungeonInstance->GetModel())
	{
		PRINTF("Spawn Mesh 2");
		m_DungeonInstance->DestroyDungeon();
	}
	PRINTF("Spawn Mesh 3");
	m_DungeonInstance->BuildDungeon();
}

void ADGRG_Dungeon::CreateHordeInRoom()
{
	PRINTF("CreateHordeInRoom");

	auto GridModel = Cast<UGridDungeonModel>(m_DungeonInstance->GetModel());
	auto GridConfig = Cast<UGridDungeonConfig>(m_DungeonInstance->GetConfig());
	for (int32 i = 0; i < GridModel->Cells.Num(); i++)
	{
		if (GridModel->Cells[i].CellType == FCellType::Room)
		{
			FCell Cell = GridModel->Cells[i];
			FVector Center;
			UGridDungeonModelHelper::GetCellCenter(Cell, Center);
			Center *= GridConfig->GridCellSize;
			SpawnHordeManager(Center);
			m_RoomCount++;
		}
	}

	PRINTF("%d of room created",m_RoomCount);
}

void ADGRG_Dungeon::CreateHordeRandomCellLoca()
{
	PRINTF("CreateHordeInRandom Cell");
	auto GridModel = Cast<UGridDungeonModel>(m_DungeonInstance->GetModel());
	auto GridConfig = Cast<UGridDungeonConfig>(m_DungeonInstance->GetConfig());
	auto iter = m_RoomCount * m_DungeonSizeScale;

	int TestCount = 0;
	for (int32 i = 0; i < iter; i++) 
	{
		FVector loca = UGridDungeonModelHelper::
			GetRandomCellLocation(GridModel, GridConfig);
		SpawnHordeManager(loca);
		TestCount++;
	}

	PRINTF("%d of horde rand cell created", TestCount);
}

void ADGRG_Dungeon::SpawnHordeManager(FVector location)
{
	 auto MonsterHorde= Cast<AMonsterHordeManager>( GetWorld()->SpawnActor(m_MonsterHordeClass, &location));
	 MonsterHorde->SpawnHorde(this);
}

void ADGRG_Dungeon::ClearCurrentDungeon()
{
	m_DungeonSizeScale = 1.0f;
	m_RoomCount = 0;
	m_DungeonInstance->DestroyDungeon();
	//애초에 던전이동자체를 새로운 레벨로 만드는게 편할듯
}

void ADGRG_Dungeon::OnDungeonBuildComplete(ADungeon * dg)
{
	PRINTF("DungeonBuildComplete");

	UNavigationSystemBase* NavSystems = (GetWorld()->GetNavigationSystem());
	UNavigationSystemV1* NavV1 = Cast<UNavigationSystemV1>(NavSystems);

	NavV1->OnNavigationGenerationFinishedDelegate.AddDynamic(this, &ADGRG_Dungeon::OnNavCookComplete);
}
//CreateHordeInRoom
void ADGRG_Dungeon::OnNavCookComplete(ANavigationData * nav)
{
	PRINTF("NavComplete");

	CreateHordeInRoom();
	CreateHordeRandomCellLoca();
}

FVector ADGRG_Dungeon::GetStartPoint()
{
	auto GridModel = Cast<UGridDungeonModel>(m_DungeonInstance->GetModel());
	auto GridConfig = Cast<UGridDungeonConfig>(m_DungeonInstance->GetConfig());

	FVector loca = UGridDungeonModelHelper::
		GetRandomCellLocation(GridModel, GridConfig);

	return loca;
}

UDGRG_DungeonThemeAsset * ADGRG_Dungeon::GetCurrentTheme()
{
	return m_CurrentThemeAsset;
}

int32 ADGRG_Dungeon::GetCurrentLevel()
{
	return m_CurrentLevel;
}

E_DIFFICULTY ADGRG_Dungeon::GetCurrentDifficulty()
{
	return m_CurrentDifficulty;
}

ADungeon * ADGRG_Dungeon::GetCurrentDungeonInstance()
{
	return m_DungeonInstance;
}

TSubclassOf<AMonsterHordeManager> ADGRG_Dungeon::GetCurrentHordeClass()
{
	return m_MonsterHordeClass;
}


int32 ADGRG_Dungeon::GetRoomCount()
{
	return m_RoomCount;
}

float ADGRG_Dungeon::GetDgSizeScale()
{
	return m_DungeonSizeScale;
}
