// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterBase.h"
#include "Manager/DGRG_GameInstance.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "NavArea.h"
#include "NavigationData.h"

#include "DroppedItemActor.h"
#include "Manager/DGRG_2GameMode.h"
//#include "ActionManagerComponent.h"
#include "Datas/DataTableRowBase.h"
#include "AIController.h"
#include "Datas/DGRG_Enum.h"
#include "DGRG_AiCon.h"
#include "Delegate.h"
#include "Perception/AIPerceptionComponent.h"
#include "Manager/PlayerStatManager.h"


 AMonsterBase::AMonsterBase(const FObjectInitializer& ObjectInitializer)
	 :Super(ObjectInitializer)
{
	 m_DropRadius = 300.0f;
	 m_Type = E_ATTACKTYPE::PHYSICAL;
	 m_CurrentTier = E_ITEMTIER::NORMAL;
	 m_bManuallySet = false;
	 m_HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetCompo"));
	 m_HealthBarComponent->SetupAttachment(RootComponent);
}

void AMonsterBase::SetMonsterStat(int dgLevel, E_DIFFICULTY dgDifficult)
{
	m_MyData = &(m_GameInstance->GetMonsterStat(m_CharId.RowName));
	m_CurrentLevel = dgLevel;
	m_CurrentTier = m_MyData->m_ItemTierRoll.SetRandomTierRoll();
	m_Type = E_ATTACKTYPE::PHYSICAL;//³ªÁß¿¡

	auto& TierScale= m_GameInstance->GetMonsterNamedScale(m_CurrentTier);
	auto& DiffScale= m_GameInstance->GetDifficultyScale(dgDifficult);

	OnMonsterKilled.AddDynamic(m_GameInstance, &UDGRG_GameInstance::OnMonsterKilled);

	m_MyData->CalculateScale(m_StatFinal,m_CurrentLevel,TierScale, DiffScale);

	CalculatePrizeScaleFromPlayer();

	SetSizeScale(TierScale.m_SizeScale);


	SetCurrentHealthToMax();
}

void AMonsterBase::CalculatePrizeScaleFromPlayer()
{
	auto& PlayerFinalStat = GetGameInstance<UDGRG_GameInstance>()->GetPlayerStatManager()->GetFinalStat();
	m_StatFinal.m_ExpScale.IncreasePerBonus(PlayerFinalStat.m_ExpScale.GetFinalValue());
	m_StatFinal.m_GoldBonusScale.IncreasePerBonus(PlayerFinalStat.m_GoldBonusScale.GetFinalValue());
	m_StatFinal.m_DropRateScale.IncreasePerBonus(PlayerFinalStat.m_DropRateScale.GetFinalValue());
}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	PRINTF("Monster BeginPlay");
	if (m_bManuallySet)
	{
		if (!GetGameInstance())
		{
			PRINTF("Manager NULL")
			return;
		}

		SetMonsterStat(2,E_DIFFICULTY::EASY);
	}
}


const FMonsterStatTable & AMonsterBase::GetMonsterData() const
{
	return *m_MyData;
}


void AMonsterBase::GetKill()
{
	Super::GetKill();
	m_HealthBarComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
	OnMonsterKilled.Broadcast(this);
}

void AMonsterBase::SetSizeScale(float v)
{
	SetActorScale3D(FVector(v,v,v));
}

void AMonsterBase::SetActive(bool b)
{
	Super::SetActive(b);
	if(GetController())
		Cast<ADGRG_AiCon>(GetController())->SetActive(b);
	if (b)
	{
		m_HealthBarComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		m_HealthBarComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
	}
}



