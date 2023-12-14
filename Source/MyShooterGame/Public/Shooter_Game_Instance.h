// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterCoreTypes.h"
#include "Shooter_Game_Instance.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API UShooter_Game_Instance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FLevelData Get_Start_Level_Name() const { return Startup_Level; }
	void Set_Start_Level(const FLevelData &Data) { Startup_Level = Data; }
	TArray<FLevelData> Get_Levels_Data() const { return Levels_Data; }

	FName Get_Menu_Level_Name() const { return Menu_Level_Name; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	TArray<FLevelData> Levels_Data;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FName Menu_Level_Name = NAME_None;

private:
	FLevelData Startup_Level;
};
