// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerMovementDelegate.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerMovementDelegate, bool);

UCLASS()
class TILES_API UPlayerMovementDelegate : public UObject
{
	GENERATED_BODY()

public:
	static FOnPlayerMovementDelegate OnMoveForward;
	static FOnPlayerMovementDelegate OnMoveBackward;
	static FOnPlayerMovementDelegate OnMoveRight;
	static FOnPlayerMovementDelegate OnMoveLeft;
	
};
