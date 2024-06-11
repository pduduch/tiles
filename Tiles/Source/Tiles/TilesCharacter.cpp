// Copyright Epic Games, Inc. All Rights Reserved.

#include "TilesCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "PlayerMovementDelegate.h"

ATilesCharacter::ATilesCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	//Movement Delegates
	UPlayerMovementDelegate::OnMoveForward.AddUObject(this, &ATilesCharacter::OnMovingForward);
	UPlayerMovementDelegate::OnMoveBackward.AddUObject(this, &ATilesCharacter::OnMovingBackward);
	UPlayerMovementDelegate::OnMoveRight.AddUObject(this, &ATilesCharacter::OnMovingRight);
	UPlayerMovementDelegate::OnMoveLeft.AddUObject(this, &ATilesCharacter::OnMovingLeft);
}

void ATilesCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (bIsMovingForward) {
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Forward);
	}
	else if (bIsMovingBackward)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(-Forward);
	}
	else if (bIsMovingRight)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Right);
	}
	else if (bIsMovingLeft)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(-Right);
	}
}

void ATilesCharacter::OnMovingForward(bool updatedIsMovingForward)
{
	//TODO: Add check to verify if it's possible to move in the desired direction i.e. if there is something already right in front of the player.
	//      If so, don't change the value for bIsMoving<...>. This should be done after implementing the collision events!
	UE_LOG(LogTemp, Warning, TEXT("======= MOVING FORWARD SUCCESSFULLY ============"));
	if (!bIsMovingBackward && !bIsMovingLeft && !bIsMovingRight)
	{
		bIsMovingForward = !bIsMovingForward;
	}
}

void ATilesCharacter::OnMovingBackward(bool updatedIsMovingBackward)
{
	UE_LOG(LogTemp, Warning, TEXT("======= MOVING BACKWARD SUCCESSFULLY ============"));
	if (!bIsMovingForward && !bIsMovingLeft && !bIsMovingRight)
	{
		bIsMovingBackward = !bIsMovingBackward;
	}
}

void ATilesCharacter::OnMovingRight(bool updatedIsMovingRight)
{
	if (!bIsMovingForward && !bIsMovingBackward && !bIsMovingLeft)
	{
		bIsMovingRight = !bIsMovingRight;
	}
}

void ATilesCharacter::OnMovingLeft(bool updatedIsMovingLeft)
{
	if (!bIsMovingForward && !bIsMovingBackward && !bIsMovingRight)
	{
		bIsMovingLeft = !bIsMovingLeft;
	}
}
