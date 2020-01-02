// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MonsterHordeManager.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "NavArea.h"
#include "NavigationData.h"
#include "Actor/MonsterBase.h"
#include "Manager/DungeonManager.h"


// Sets default values
AMonsterHordeManager::AMonsterHordeManager()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldRoot"));
	m_SphereColl = CreateDefaultSubobject<USphereComponent>(TEXT("SphereColl"));
	m_SphereColl->SetupAttachment(RootComponent);
	bCanBeDamaged = false;
}

void AMonsterHordeManager::SpawnHorde(const UDungeonManager*   dg)
{
	OnDestroyed.AddDynamic(this,&AMonsterHordeManager::ClearMobs);

	int Level = dg->GetCurrentLevel();
	E_DIFFICULTY Diffy = dg->GetCurrentDifficulty();
	auto MobArray = dg->GetCurrentTheme()->GetThemeMobs();
	//WorldÁö¿ï°Í
	UNavigationSystemBase* NavSystems = (GetWorld()->GetNavigationSystem());
	UNavigationSystemV1* NavV1 = Cast<UNavigationSystemV1>(NavSystems);
	FNavLocation NavDataArea;

	m_MyMonsters.Empty();
	m_MyMonsters.Reserve(10);
	for (int i = 0; i < 10; i++)
	{
		auto Mob = MobArray[rand() % MobArray.Num()];

		auto Loc = GetActorLocation();
		Loc.Z += 100.f;

		if (NavV1->GetRandomReachablePointInRadius(GetActorLocation(), m_SphereColl->GetScaledSphereRadius(), NavDataArea))
		//if (NavV1->GetRandomPointInNavigableRadius(Loc, m_SphereColl->GetScaledSphereRadius(), NavDataArea))
		{
			auto ActorS = (GetWorld()->SpawnActor(Mob, &NavDataArea.Location));
			if (!ActorS)
			{
				continue;
			}
			AMonsterBase* CreatedMonster = Cast<AMonsterBase>(ActorS);
			CreatedMonster->SetMonsterStat(Level, Diffy);
			CreatedMonster->SetActive(false);
			m_MyMonsters.Emplace(CreatedMonster);
		}
	}


}

void AMonsterHordeManager::SetActiveTrueAll()
{
	PRINTF("Horde, True all 1");
	PRINTF("MobCOunt : %d", m_MyMonsters.Num());
	for (int i = 0; i < m_MyMonsters.Num(); i++)
	{
		m_MyMonsters[i]->SetActive(true);
	}

	//m_MyMonsters.Empty();
	m_SphereColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMonsterHordeManager::ClearMobs(AActor * mySelf)
{
	for (int i = 0; i < m_MyMonsters.Num(); i++)
	{

		m_MyMonsters[i]->Destroy();
	}
}


