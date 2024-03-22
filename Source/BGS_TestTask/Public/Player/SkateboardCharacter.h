#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkateboardCharacter.generated.h"

class ASkateboardPlayerState;
class UBoxComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class BGS_TESTTASK_API ASkateboardCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASkateboardCharacter();
	virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(FVector2D moveVector);
	void StartDecelerating();
	
protected:
	virtual void BeginPlay() override;
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	
	UPROPERTY(EditDefaultsOnly) TObjectPtr<USpringArmComponent> springArm;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UCameraComponent> camera;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> skateMesh;
	
private:
	void Decelerate();
	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	FTimerHandle decelerateHandle;
	float forwardInput;
	TObjectPtr<ASkateboardPlayerState> skateboardPlayerState;
};
