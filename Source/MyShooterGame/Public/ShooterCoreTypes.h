#pragma once
#include "ShooterCoreTypes.generated.h"
//Weapon

class AShooterBaseWeaponActor;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, AShooterBaseWeaponActor*);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		int64 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
		int64 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AShooterBaseWeaponActor> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* CrosshairIcon;
};

// VFX
USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UMaterialInterface* Material;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		FVector Size = FVector(10.0f);

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
			float LifeTime = 5.0f;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
			float FadeoutTime = 0.7f;
};

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
			UNiagaraSystem* NiagaraEffect;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
			FDecalData DecalData;
};

//Health 
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
		int64 PlayersNum = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
		int64 RoundsMax = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
		int64 TimeRound = 3; //in second

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FLinearColor DefaultColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray<FLinearColor> TeamColors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "20"))
		int64 RespawnTime = 10; //in second
};

UENUM(BlueprintType)
enum class ESTUMatchState : uint8
{
	WaitingToStart = 0,
	InProgress,
	Pause,
	GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature,ESTUMatchState);

USTRUCT(BlueprintType)
struct FLevelData
{
	GENERATED_USTRUCT_BODY()
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FName Level_Name = NAME_None;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FName Level_Display_Name = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	UTexture2D *LevelThumb;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelectedSignature, const FLevelData&);