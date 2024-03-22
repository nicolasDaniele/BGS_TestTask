#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "SkateboardPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ASkateboardCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpDelegate);

UCLASS()
class BGS_TESTTASK_API ASkateboardPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable) FOnJumpDelegate OnJumpEvent;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inputs") TObjectPtr<UInputMappingContext> gameplayMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Inputs") TObjectPtr<UInputAction> moveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Inputs") TObjectPtr<UInputAction> jumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "Inputs") TObjectPtr<UInputAction> lookAction;

private:
	UFUNCTION() void Move(const FInputActionValue& inputValue);
	UFUNCTION() void Jump(const FInputActionValue& inputValue);
	UFUNCTION() void Decelerate(const FInputActionValue& inputValue);
	UFUNCTION() void Look(const FInputActionValue& inputValue);

	TObjectPtr<ASkateboardCharacter> skateboardCharacter;
};
