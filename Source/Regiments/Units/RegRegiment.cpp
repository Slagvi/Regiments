#include "RegRegiment.h"
#include "Engine/World.h"


ARegRegiment::ARegRegiment()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = false;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}


void ARegRegiment::BeginPlay()
{
	Super::BeginPlay();
	Template = TemplateType.GetDefaultObject();
	RecreateSoldiers(FTransform::Identity);
}


void ARegRegiment::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


void ARegRegiment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSoldiersMovement(DeltaTime);
}


void ARegRegiment::RecreateSoldiers(FTransform StartTransform)
{
	for (AActor* Soldier : DisplayedSoldiers)
	{
		Soldier->Destroy();
	}

	for (int i = 0; i < Template->MaxUnitsNum; ++i)
	{
		if (!Template->DefaultFormation.IsValidIndex(i))
		{
			UE_LOG(LogTemp, Error, TEXT("Wrong soldier in recreation"));
			return;
		}

		AActor* Soldier = GetWorld()->SpawnActor<AActor>(Template->SoldierClass, Template->DefaultFormation[i] * StartTransform);
		DisplayedSoldiers.Add(Soldier);
	}
}


void ARegRegiment::UpdateSoldiersMovement(float DeltaTime)
{
	for (int i = 0; i < DisplayedSoldiers.Num(); ++i)
	{
		AActor* Soldier = DisplayedSoldiers[i];

		if (!Template->DefaultFormation.IsValidIndex(i) || !Soldier)
		{
			UE_LOG(LogTemp, Error, TEXT("Wrong soldier in formation id"));
			return;
		}

		FTransform LocalTarget = Template->DefaultFormation[i] * TargetTransform;
		FVector Distance = LocalTarget.GetLocation() - Soldier->GetActorLocation();

		if (Distance.Size() < KINDA_SMALL_NUMBER)
		{
			Soldier->SetActorRotation(LocalTarget.GetRotation());
		}
		else
		{
			float Speed = FMath::Min(Distance.Size(), Template->MaxSpeed * DeltaTime);
			Soldier->SetActorLocation(Soldier->GetActorLocation() + Distance.GetSafeNormal() * Speed);
		}
	}
}


FVector ARegRegiment::GetRegimentLocation()
{
	FVector RegLocation = FVector::ZeroVector;

	for (AActor *Soldier : DisplayedSoldiers)
	{
		RegLocation += Soldier->GetActorLocation();
	}

	return RegLocation / DisplayedSoldiers.Num();
}