#include "Player/SkateboardPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Player/SkateboardCharacter.h"

void ASkateboardPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subsystem->AddMappingContext(gameplayMappingContext, 0);
	}

	skateboardCharacter = Cast<ASkateboardCharacter>(GetPawn());
}

void ASkateboardPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &ASkateboardPlayerController::Move);
	enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Completed, this, &ASkateboardPlayerController::Decelerate);
	enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Started, this, &ASkateboardPlayerController::Jump);
	enhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &ASkateboardPlayerController::Look);
}

void ASkateboardPlayerController::Move(const FInputActionValue& inputValue)
{
	if(skateboardCharacter == nullptr) return;

	const FVector2D movementVector = inputValue.Get<FVector2D>();
	skateboardCharacter->Move(movementVector);
}

void ASkateboardPlayerController::Decelerate(const FInputActionValue& inputValue)
{
	if(skateboardCharacter == nullptr) return;

	skateboardCharacter->StartDecelerating();
}

void ASkateboardPlayerController::Jump(const FInputActionValue& inputValue)
{
	if(GetCharacter() == nullptr) return;
	
	GetCharacter()->Jump();
	OnJumpEvent.Broadcast();
}

void ASkateboardPlayerController::Look(const FInputActionValue& inputValue)
{
	if(skateboardCharacter == nullptr) return;

	const FVector2D lookVector = inputValue.Get<FVector2D>();
	skateboardCharacter->AddControllerYawInput(lookVector.X);
	skateboardCharacter->AddControllerPitchInput(lookVector.Y);
}