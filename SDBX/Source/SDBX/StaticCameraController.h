// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StaticCameraController.generated.h"

UCLASS()
class SDBX_API AStaticCameraController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStaticCameraController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View Target")
		ACameraActor* ViewTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Controller")
		APlayerController* PlayerController;
};
