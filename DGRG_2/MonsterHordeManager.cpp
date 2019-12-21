// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHordeManager.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "NavArea.h"
#include "NavigationData.h"
#include "DGRG_Dungeon.h"
// Sets default values
AMonsterHordeManager::AMonsterHordeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldRoot"));
	m_SphereColl = CreateDefaultSubobject<USphereComponent>(TEXT("SphereColl"));
	m_SphereColl->SetupAttachment(RootComponent);
	bCanBeDamaged = false;
	
}

void AMonsterHordeManager::SpawnHorde( ADGRG_Dungeon* const  dg)
{
	auto MobArray = dg->GetCurrentTheme()->GetThemeMobs();
	//WorldÁö¿ï°Í
	UNavigationSystemBase* NavSystems = (GetWorld()->GetNavigationSystem());
	UNavigationSystemV1* NavV1 = Cast<UNavigationSystemV1>(NavSystems);
	FNavLocation NavDataArea;

	m_MyMonsters.Empty();

	for (int i = 0; i < 10; i++)
	{
		auto Mob = MobArray[rand() % MobArray.Num()];
		if (NavV1->GetRandomReachablePointInRadius(GetActorLocation(), m_SphereColl->GetScaledSphereRadius(), NavDataArea))
		{
			auto ActorS = (GetWorld()->SpawnActor(Mob, &NavDataArea.Location));
			if (!ActorS)
			{
				continue;
			}
			
			AMonsterBase* CreatedMonster = Cast<AMonsterBase>(ActorS);
			CreatedMonster->SetMonsterStat(dg->GetCurrentLevel(),dg->GetCurrentDifficulty());
			CreatedMonster->SetActive(false);

			m_MyMonsters.Add(CreatedMonster);
		}
	}


}

void AMonsterHordeManager::SetActiveTrueAll()
{
	for (int i = 0; i < m_MyMonsters.Num(); i++)
	{
		m_MyMonsters[i]->SetActive(true);
	}

	m_MyMonsters.Empty();

	m_SphereColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*for (auto& Mob : m_MyMonsters)
	{
		Mob->SetActive(true);
	}*/
}


