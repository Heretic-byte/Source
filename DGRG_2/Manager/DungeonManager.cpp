// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonManager.h"

#include "Builders/Grid/GridDungeonConfig.h"
#include "GridDungeonModelHelper.h"
#include "Delegate.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "NavArea.h"
#include "NavigationData.h"
#include "Datas/DGRG_DungeonThemeAsset.h"
#include "Kismet/GameplayStatics.h"
#include "FogOfWarManager.h"
#include "GridDungeonQuery.h"
#include "DrawDebugHelpers.h"
//#include "TimerManager.h"

UDungeonManager::UDungeonManager()
{
	m_CMonsterHorde = AMonsterHordeManager::StaticClass();
	m_GridDgModel = nullptr;
	m_GridDgConfig= nullptr;

}
void UDungeonManager::Init(UDGRG_GameInstance * gameInstance)
{
	Super::Init(gameInstance);
	ClearHordeManagerAry();
	FVector location(0,0,0);
	FRotator Rot(0, 0, 0);
	m_DungeonInstance = Cast<ADungeon>(m_GameInstance->GetWorld()->SpawnActor(m_CDungeon, &location));
	BindOnNavComplete();

	m_DungeonSizeScale = 1.0f;
	m_RoomCount = 0;

	SetDungeonTheme(0);
	SetDungeonLevel(1);
	FindSetFogofWarActor();
}
void UDungeonManager::SetGridPtrs()
{
	m_GridDgModel = Cast<UGridDungeonModel>(m_DungeonInstance->GetModel());
	m_GridDgConfig = Cast<UGridDungeonConfig>(m_DungeonInstance->GetConfig());
	m_GridDgModel->BuildCellLookup();
	m_GridQuery = Cast<UGridDungeonQuery>(m_DungeonInstance->GetQuery());
}

void UDungeonManager::FindSetFogofWarActor()
{
	TArray<AActor*> FoundFogWarActor;
	UGameplayStatics::GetAllActorsOfClass(m_GameInstance->GetWorld(), AFogOfWarManager::StaticClass(), FoundFogWarActor);
	m_FogWarInLevel = Cast<AFogOfWarManager>(FoundFogWarActor[0]);
}

void UDungeonManager::ClearHordeManagerAry()
{
	m_HodeManagers.Reset();
	m_HodeManagers.Reserve(10);
}
void UDungeonManager::BindOnNavComplete()
{
	UNavigationSystemBase* NavSystems = (m_GameInstance->GetWorld()->GetNavigationSystem());
	UNavigationSystemV1* NavV1 = Cast<UNavigationSystemV1>(NavSystems);
	NavV1->OnNavigationGenerationFinishedDelegate.AddDynamic(this, &UDungeonManager::OnNavCookComplete);
}

void UDungeonManager::SetDungeonLevel(int32 lvl)
{
	m_CurrentLevel = lvl;
	m_DungeonSizeScale += m_GameInstance->GetDungeonLevelScale(lvl).m_Value;
}

void UDungeonManager::SetDifficulty(E_DIFFICULTY diff)
{
	m_CurrentDifficulty = diff;

	m_DungeonSizeScale += m_GameInstance->GetDungeonDiffyScale(diff).m_Value;
}

void UDungeonManager::SetDungeonTheme(int index)
{
	m_CurrentThemeAsset = m_TotalThemeAsset[index];
	m_OnThemeChanged.Broadcast(m_CurrentThemeAsset);
	m_DungeonInstance->Themes.Empty();
	m_DungeonInstance->Themes.Emplace(m_CurrentThemeAsset->GetDungeonTheme());
}

void UDungeonManager::ShowFog()
{
	m_FogWarInLevel->ShowFog();
}

void UDungeonManager::HideFog()
{
	m_FogWarInLevel->HideFog();
}

void UDungeonManager::ReserFogMaterial()
{
	m_FogWarInLevel->ResetFogMaterial();
}

void UDungeonManager::GenerateDungeon()
{
	m_DungeonInstance->GetConfig()->Seed = FMath::RandRange(0,(int)E_GLOBAL_CONST::MILE);
	ReserFogMaterial();
	SpawnDungeonMesh();//멀티스레드니까 콜백으로 해야함
}

void UDungeonManager::SetStartEndPoint()
{
	FVector Center;
	int32 StartRoomID;
	int32 EndRoomID;
	m_GridQuery->GetFurthestRooms(StartRoomID, EndRoomID);

	UGridDungeonModelHelper::GetCellCenter(*m_GridDgModel->GetCell(StartRoomID), Center);
	Center *= m_GridDgConfig->GridCellSize;
	m_StartRoom = Center;
	UGridDungeonModelHelper::GetCellCenter(*m_GridDgModel->GetCell(EndRoomID), Center);
	Center *= m_GridDgConfig->GridCellSize;
	m_EndRoom = Center;


	DrawDebugLine(
		m_GameInstance->GetWorld(),
		m_StartRoom,
		m_EndRoom,
		FColor(255, 0, 0),
		true, -1, 0,
		12.333
	);
}


void UDungeonManager::SpawnDungeonMesh()
{
	if (m_DungeonInstance->GetModel())
	{
		ClearCurrentDungeon();
	}
	m_DungeonInstance->BuildDungeon();
}

void UDungeonManager::CreateHordeInRoom()
{
	for (int32 i = 0; i < m_GridDgModel->Cells.Num(); i++)
	{
		if (m_GridDgModel->Cells[i].CellType == FCellType::Room)
		{
			FCell Cell = m_GridDgModel->Cells[i];
			FVector Center;
			UGridDungeonModelHelper::GetCellCenter(Cell, Center);
			Center *= m_GridDgConfig->GridCellSize;
			SpawnHordeManager(Center);
			m_RoomCount++;
		}
	}

	PRINTF("%d of room created", m_RoomCount);
}

void UDungeonManager::CreateHordeRandomCellLoca()
{
	auto iter = m_RoomCount * m_DungeonSizeScale;

	int TestCount = 0;
	for (int32 i = 0; i < iter; i++)
	{
		FVector loca = UGridDungeonModelHelper::
			GetRandomCellLocation(m_GridDgModel, m_GridDgConfig);
		SpawnHordeManager(loca);
		TestCount++;
	}

	PRINTF("%d of horde rand cell created", TestCount);
}

void UDungeonManager::SpawnHordeManager(FVector location)
{
	auto MonsterHorde = Cast<AMonsterHordeManager>(m_GameInstance->GetWorld()->SpawnActor(m_CMonsterHorde, &location));
	MonsterHorde->SpawnHorde(this);
	m_HodeManagers.Emplace(MonsterHorde);
}


void UDungeonManager::ClearCurrentDungeon()
{
	PRINTF("ClearDungeon");
	m_DungeonSizeScale = 1.0f;
	m_RoomCount = 0;
	m_DungeonInstance->DestroyDungeon();

	for (auto* Horde : m_HodeManagers)
	{
		Horde->Destroy();
	}

	ClearHordeManagerAry();
}

void UDungeonManager::OnNavCookComplete(ANavigationData * nav)
{
	PRINTF("NavCookComplete");

	if (!m_DungeonInstance->GetModel())
	{
		return;
	}
	SetGridPtrs();
	CreateHordeInRoom();
	CreateHordeRandomCellLoca();
	SetStartEndPoint();

	m_OnDgBuildComplete.Broadcast();
}

FVector UDungeonManager::GetStartPoint() const
{
	return m_StartRoom;
}

FVector UDungeonManager::GetEndPoint() const
{
	return m_EndRoom;
}

UDGRG_DungeonThemeAsset * UDungeonManager::GetCurrentTheme() const
{
	return m_CurrentThemeAsset;
}

int32 UDungeonManager::GetCurrentLevel() const
{
	return m_CurrentLevel;
}

E_DIFFICULTY UDungeonManager::GetCurrentDifficulty() const
{
	return m_CurrentDifficulty;
}

ADungeon * UDungeonManager::GetCurrentDungeonInstance() const
{
	return m_DungeonInstance;
}

TSubclassOf<AMonsterHordeManager> UDungeonManager::GetCurrentHordeClass() const
{
	return m_CMonsterHorde;
}


int32 UDungeonManager::GetRoomCount() const
{
	return m_RoomCount;
}

float UDungeonManager::GetDgSizeScale() const
{
	return m_DungeonSizeScale;
}
