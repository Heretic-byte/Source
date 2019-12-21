// Fill out your copyright notice in the Description page of Project Settings.


#include "DGRG_PlayerCon.h"
#include "PlayerCharacter.h"
#include "DGRG_GameInstance.h"
#include "ExpManager.h"
#include "GoldManager.h"
#include "ItemManager.h"
#include "PlayerStatManager.h"
#include "WidgetMainMenu.h"
#include "WidgetSlotGrid.h"
#include "DGRG_CheatManager.h"

ADGRG_PlayerCon::ADGRG_PlayerCon()
{
	PrimaryActorTick.bCanEverTick = true;
	m_TeamId = FGenericTeamId(0);
	m_CurrentAttackTarget = nullptr;
}

ADGRG_PlayerCon::ADGRG_PlayerCon(const FObjectInitializer & ObjectInitializer)
{
	CheatClass = UDGRG_CheatManager::StaticClass();
}

FGenericTeamId ADGRG_PlayerCon::GetGenericTeamId() const
{
	return m_TeamId;
}



void ADGRG_PlayerCon::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
	m_MasterWidget = CreateWidget<UWidgetMasterCanvas>(this, m_ClassMWidget);
	m_MasterWidget->AddToViewport();
	m_PlayerChar=Cast<APlayerCharacter>(GetCharacter());
	m_GameManager =GetGameInstance<UDGRG_GameInstance>();
	SetPlayerDelegate();
	SetManagerDelegate();
}

void ADGRG_PlayerCon::AddChild(UUserWidget * widget, FVector2D pos, FVector2D alignment)
{
	m_MasterWidget->AddChild(widget, pos,alignment);
}

void ADGRG_PlayerCon::OnAttackTargetFound(AMonsterBase * target)
{
	if (m_CurrentAttackTarget)
	{
		m_CurrentAttackTarget->OnHealthChange.Remove(m_OnMonsterHpDeleHandle);
	}
	m_CurrentAttackTarget = target;
	m_OnMonsterHpDeleHandle = m_CurrentAttackTarget->OnHealthChange.AddUObject(m_MasterWidget, &UWidgetMasterCanvas::SetMonsterHealthBar);
}

void ADGRG_PlayerCon::SetPlayerDelegate()
{
	m_PlayerChar->OnHealthChangeBP.AddDynamic(m_MasterWidget, &UWidgetMasterCanvas::SetHealthBar);
	m_PlayerChar->OnStaminaChangeBP.AddDynamic(m_MasterWidget, &UWidgetMasterCanvas::SetStaminaBar);
	m_PlayerChar->OnFoundMonsterBP.AddDynamic(this, &ADGRG_PlayerCon::OnAttackTargetFound);
	m_PlayerChar->OnFoundMonsterBP.AddDynamic(m_MasterWidget, &UWidgetMasterCanvas::SetMonsterInfo);
	m_PlayerChar->OnFoundMonsterBP.AddDynamic(m_MasterWidget, &UWidgetMasterCanvas::DeleShowMonsterInfo);
	m_PlayerChar->OnFoundEndMonsterBP.AddDynamic(m_MasterWidget, &UWidgetMasterCanvas::DeleHideMonsterInfo);
	//
	m_MasterWidget->
		GetMainMenu()->
		GetEquipMenu()->
		SetEquipGrid(m_PlayerChar->GetEquipSlotArray());
	//
	m_MasterWidget->
	GetMainMenu()->
		GetInvenMenu()->
		SetInven(m_PlayerChar->m_Inventory);
	//
	m_MasterWidget->GetMainMenu()->InitConstruct();
	m_MasterWidget->SetOwningPlayer(this);
	m_MasterWidget->GetMainMenu()->SetOwningPlayer(this);
}

void ADGRG_PlayerCon::SetManagerDelegate()
{
	m_GameManager->GetExpManager()->OnExpChanged.AddDynamic(m_MasterWidget, &UWidgetMasterCanvas::SetExpBar);
	m_GameManager->GetExpManager()->OnLevelUpN.AddDynamic(m_MasterWidget->GetMainMenu()->GetEquipMenu()->GetSimpleShow(), &UWidgetSimpleStatShow::SetLevel);
	m_GameManager->GetExpManager()->OnLevelUpN.AddDynamic(m_MasterWidget, &UWidgetMasterCanvas::SetLevel);
	m_GameManager->GetExpManager()->SetExp(0);
	//
	m_GameManager->GetGoldManager()->OnGoldChange.AddDynamic(m_MasterWidget, &UWidgetMasterCanvas::SetGold);
	m_GameManager->GetGoldManager()->SetGold(0);
	//
	m_GameManager->GetItemManager()->OnPotionAmountChange.AddDynamic(m_MasterWidget, &UWidgetMasterCanvas::SetHealthPotion);
	//

	m_GameManager->GetPlayerStatManager()->m_OnFinalStatUpdated.BindUObject(m_MasterWidget->GetMainMenu()->GetEquipMenu()->GetSimpleShow(), &UWidgetSimpleStatShow::SetStat);
	//
	m_MasterWidget->GetMainMenu()->GetStatMenu()->SetGameInstance(m_GameManager);
}

//// 메뉴는 위젯 일 수 있습니다.
//메뉴->AddToViewport();
//
//// 0 단계는 플레이어 컨트롤러를 가져옵니다.
//auto PlayerController = GetFirstLocalPlayerController();
//if (!ensure(PlayerController!= nullptr)) 반환;
//
//// 1 단계는 입력 모드를 설정합니다. 게임 전용 또는 게임 및 UI와 같은 여러 항목도 있습니다.
//FInputModeUIOnly InputModeData;
//// 2 단계 구성은 유형에 따라 다릅니다.
//InputModeData.SetLockMouseToViewport(false);
//InputModeData.SetWidgetToFocus(메뉴->TakeWidget()); // UMG가 슬레이트를 감싸기 때문에
//
//// 3 단계는 플레이어 컨트롤러의 모드를 설정합니다
//PlayerController->SetInputMode(InputModeData);
//
//// 4 단계 커서를 활성화하여 무엇을 클릭해야하는지 알 수 있습니다.
//PlayerController->bShowMouseCursor = true;