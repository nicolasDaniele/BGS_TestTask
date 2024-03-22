#include "Player/SkateboardCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Obstacle.h"
#include "Player/SkateboardPlayerState.h"

ASkateboardCharacter::ASkateboardCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetupAttachment(springArm);
	
	skateMesh = CreateDefaultSubobject<UStaticMeshComponent>("Skate Mesh");
	skateMesh->SetupAttachment(RootComponent);
}

void ASkateboardCharacter::BeginPlay()
{
	Super::BeginPlay();

	forwardInput = 0.0f;
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASkateboardCharacter::OnCapsuleBeginOverlap);
	skateboardPlayerState = Cast<ASkateboardPlayerState>(GetPlayerState());
}

void ASkateboardCharacter::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	if(forwardInput > 0.0f)
	{
		AddMovementInput(skateMesh->GetForwardVector(), forwardInput);
	}
}

void ASkateboardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkateboardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASkateboardCharacter::Move(FVector2D moveVector)
{
	AddMovementInput(skateMesh->GetRightVector(), moveVector.X * 0.05f);
	
	if(moveVector.Y >= 0.0f)
	{
		forwardInput = moveVector.Y;
		GetWorld()->GetTimerManager().ClearTimer(decelerateHandle);
	}
	else
	{
		forwardInput = FMath::Abs(forwardInput) > 0.01f ? FMath::Lerp(forwardInput, 0.0f, 0.1f) : 0.0f;
	}
}

void ASkateboardCharacter::StartDecelerating()
{
	GetWorld()->GetTimerManager().SetTimer(decelerateHandle, this, &ASkateboardCharacter::Decelerate, 0.05f, true);
}

void ASkateboardCharacter::Decelerate()
{
	if(FMath::Abs(forwardInput) > 0.01f)
	{
		forwardInput = FMath::Lerp(forwardInput, 0.0f, 0.1f);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(decelerateHandle);
		forwardInput = 0.0f;
	}
}

void ASkateboardCharacter::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(!OtherActor->IsA(AObstacle::StaticClass()) || skateboardPlayerState == nullptr) return;
	
	AObstacle* obstacle = Cast<AObstacle>(OtherActor);
	skateboardPlayerState->AddPlayerScore(obstacle->GetScoreForOvercomingObstacle());
}