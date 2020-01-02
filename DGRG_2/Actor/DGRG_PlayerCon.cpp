// Fill out your copyright notice in the Description page of Project Settings.


#include "DGRG_PlayerCon.h"
#include "Actor/PlayerCharacter.h"
#include "Manager/DGRG_GameInstance.h"
#include "Manager/ExpManager.h"
#include "Manager/GoldManager.h"
#include "Manager/ItemManager.h"
#include "Manager/PlayerStatManager.h"
#include "Widgets/WidgetMainMenu.h"
#include "Widgets/WidgetSlotGrid.h"
#include "Manager/DGRG_CheatManager.h"
#include "Widgets/WidgetDgMainEnter.h"

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
		SetInven(m_PlayerChar->GetInven());
	//
	m_MasterWidget->GetMainMenu()->InitConstruct();
	m_MasterWidget->SetOwningPlayer(this);
	m_MasterWidget->GetMainMenu()->SetOwningPlayer(this);
	//
	m_PlayerChar->m_OnStanceChanged.AddUObject(m_MasterWidget->GetMainMenu()->GetEquipMenu(),&UWidgetEquipWindow::SetEquipSlotLimit);


}

void ADGRG_PlayerCon::SetManagerDelegate()
{
	m_GameManager->SetMasterCanvas(m_MasterWidget);
	m_GameManager->SetPlayerActor(m_PlayerChar);

	m_GameManager->GetExpManager()->OnExpChanged.AddDynamic(m_MasterWidget, &UWidgetMasterCanvas::SetExpBar);
	m_GameManager->GetExpManager()->OnLevelUpN.AddDynamic(m_MasterWidget->GetMainMenu()->GetEquipMenu()->GetSimpleShow(), &UWidgetSimpleStatShow::SetLevel);
	m_GameManager->GetExpManager()->OnLevelUpN.AddDynamic(m_MasterWidget, &UWidgetMasterCanvas::SetLevel);
	m_GameManager->GetExpManager()->OnLevelUp.AddDynamic(m_PlayerChar,&APlayerCharacter::SetCurrentHealthToMax);
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
	//
	m_MasterWidget->m_OnMainMenuOpen.AddUObject(m_GameManager->GetPlayerStatManager(),&UPlayerStatManager::UpdateWidget);

	m_MasterWidget->GetDgEnter()->Init();
}

//// �޴��� ���� �� �� �ֽ��ϴ�.
//�޴�->AddToViewport();
//
//// 0 �ܰ�� �÷��̾� ��Ʈ�ѷ��� �����ɴϴ�.
//auto PlayerController = GetFirstLocalPlayerController();
//if (!ensure(PlayerController!= nullptr)) ��ȯ;
//
//// 1 �ܰ�� �Է� ��带 �����մϴ�. ���� ���� �Ǵ� ���� �� UI�� ���� ���� �׸� �ֽ��ϴ�.
//FInputModeUIOnly InputModeData;
//// 2 �ܰ� ������ ������ ���� �ٸ��ϴ�.
//InputModeData.SetLockMouseToViewport(false);
//InputModeData.SetWidgetToFocus(�޴�->TakeWidget()); // UMG�� ������Ʈ�� ���α� ������
//
//// 3 �ܰ�� �÷��̾� ��Ʈ�ѷ��� ��带 �����մϴ�
//PlayerController->SetInputMode(InputModeData);
//
//// 4 �ܰ� Ŀ���� Ȱ��ȭ�Ͽ� ������ Ŭ���ؾ��ϴ��� �� �� �ֽ��ϴ�.
//PlayerController->bShowMouseCursor = true;