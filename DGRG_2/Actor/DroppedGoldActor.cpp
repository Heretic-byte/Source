// Fill out your copyright notice in the Description page of Project Settings.


#include "DroppedGoldActor.h"
#include "Interactable.h"
#include "Manager/DGRG_GameInstance.h"
#include "Manager/GoldManager.h"
#include "Datas/DataTableRowBase.h"


ADroppedGoldActor::ADroppedGoldActor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	m_bInteractWithOverlapped = true;
	m_Interactable->m_bUnlocked = false;
	m_GoldFormat= FTextFormat(FText::FromString("{0}G"));
	m_nGoldAmount = 10;
}

void ADroppedGoldActor::SetGoldAmount(int goldV)
{
	float GivenGoldRate = FMath::RandRange(0.7f, 1.3f);

	SetScale(GivenGoldRate);

	m_nGoldAmount *= GivenGoldRate;

	FFormatOrderedArguments FormatArg;
	FormatArg.Add(m_nGoldAmount);

	GetWidgetItemNameCard()->SetItemNameText(FText::Format(m_GoldFormat, FormatArg));
}

void ADroppedGoldActor::AddItemToActor(AActor * interMan)
{
	auto* GoldManage=GetGameInstance<UDGRG_GameInstance>()->GetGoldManager();
	GoldManage->IncreaseGold(m_nGoldAmount);
	PRINTF("GoldGaved");
	this->Destroy();
}

void ADroppedGoldActor::IfManualSet()
{
	m_SphereColl->SetGenerateOverlapEvents(true);
	//SetGoldAmount(m_nGoldAmount);
}
