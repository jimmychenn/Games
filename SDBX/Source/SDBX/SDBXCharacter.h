// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "BeatSpawner.h"
#include "BeatSlot.h"
#include "SDBXCharacter.generated.h"

UCLASS(config=Game)
class ASDBXCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void SetupColor();

	void HitBeat();

	void ComboBreaker();

	bool CastRay();

	UFUNCTION()
	void OnPunchOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnKickOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Attack();

	void Dance();

	void Block();

	void PlayAnim(UAnimMontage * animation);
	
	void OnDeath();

	void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	ABeatSpawner * bSpawner;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage * PunchAnim;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage * KickAnim;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage * BlockAnim;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage * DanceAnim;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage * HitAnim;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage * DeathAnim;

	bool isPunching;

	bool isKicking;

	bool isBlocking;

	bool isDancing;

	ABeatSlot* bSlot;

	UPROPERTY(EditAnywhere, Category = Damage)
		float Health = 100.0f;

	float CurrentHealth;

	float HealthVelocity = 0;

	float SpringHealth(float DeltaTime);

	UPROPERTY(EditDefaultsOnly, Category = Health)
		float SpringConstant = 200.0f;

	UPROPERTY(EditAnywhere, Category = Damage)
		float Damage = 1.0f;

	UPROPERTY(EditAnywhere, Category = Damage)
		float KickDamage = 1.2f;

	UPROPERTY(EditAnywhere, Category = Combos)
		float ComboBreakerTime = 5.0f;

	UPROPERTY(EditAnywhere, Category = Physics)
		float FallSpeed = -1000.0f;

	UPROPERTY(EditAnywhere, Category = Physics)
		float KnockBack = 10.0f;

	USphereComponent* punchCollider;
	USphereComponent* footCollider;
	USphereComponent* calfCollider;

	float Multiplier = 1.0;

	int32 id;

	int Combo = 0;
	int TotalHits = 0;

	UFUNCTION(BlueprintCallable, Category = "LocalMP")
		int32 GetPlayerID(){ return id; }

	FTimerHandle comboHandle;
	FTimerHandle inputHandle;
public:
	ASDBXCharacter();
	void SetBeatSlot(ABeatSlot* bS){ bSlot = bS; }
	void SetBeatSpawner(ABeatSpawner* bS){ bSpawner = bS; }
	UFUNCTION(BlueprintCallable, Category = "Scoring")
		float GetMultiplier(){ return Multiplier; }
	bool IsBlocking() { return isBlocking; }
	void ResetStates();

};
