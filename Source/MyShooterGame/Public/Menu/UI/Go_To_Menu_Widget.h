// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Go_To_Menu_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API UGo_To_Menu_Widget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton *Return_To_Menu_Button;

	UFUNCTION()
	void Return_To_Menu();
};
