// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TilesCharacter.generated.h"

UCLASS(Blueprintable)
class ATilesCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATilesCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	bool bIsMovingForward = false;
	bool bIsMovingBackward = false;
	bool bIsMovingRight = false;
	bool bIsMovingLeft = false;

	void OnMovingForward(bool updatedIsMovingForward);
	void OnMovingBackward(bool updatedIsMovingBackward);
	void OnMovingRight(bool updatedIsMovingRight);
	void OnMovingLeft(bool updatedIsMovingLeft);
};

