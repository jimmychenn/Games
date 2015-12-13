// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SDBX.h"
#include "SDBXCharacter.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "SDBXGameMode.h"
#include "BeatMarker.h"

ASDBXCharacter::ASDBXCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 3600.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	punchCollider = CreateDefaultSubobject<USphereComponent>(TEXT("PunchColliderComponent"));
	punchCollider->InitSphereRadius(0.1);
	punchCollider->AttachTo(GetMesh(), "hand_l");
	punchCollider->OnComponentBeginOverlap.AddDynamic(this, &ASDBXCharacter::OnPunchOverlapBegin);

	footCollider = CreateDefaultSubobject<USphereComponent>(TEXT("FootColliderComponent"));
	footCollider->InitSphereRadius(0.3);
	footCollider->AttachTo(GetMesh(), "foot_l");
	footCollider->OnComponentBeginOverlap.AddDynamic(this, &ASDBXCharacter::OnKickOverlapBegin);

	calfCollider = CreateDefaultSubobject<USphereComponent>(TEXT("CalfColliderComponent"));
	calfCollider->InitSphereRadius(0.3);
	calfCollider->AttachTo(GetMesh(), "calf_l");
	calfCollider->OnComponentBeginOverlap.AddDynamic(this, &ASDBXCharacter::OnKickOverlapBegin);

	CurrentHealth = Health;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ASDBXCharacter::BeginPlay(){
	Super::BeginPlay();
}

float ASDBXCharacter::SpringHealth(float DeltaTime){
	float springAccel;
	float DampConstant = 2.0f * sqrt(SpringConstant);
	float diff = CurrentHealth - Health;
	springAccel = (-SpringConstant*diff) - (DampConstant*HealthVelocity);
	HealthVelocity += springAccel * DeltaTime;
	return HealthVelocity*DeltaTime;
}

void ASDBXCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	CurrentHealth += SpringHealth(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(CurrentHealth));
	if (id == 0){
		float percent = CurrentHealth / 200.0;
		((ASDBXGameMode*)(UGameplayStatics::GetGameMode(this)))->SetScore(percent);
	}
	if (GetCharacterMovement()->IsFalling()){
		GetCharacterMovement()->AddImpulse(FVector(0.0, 0.0, 1.0*FallSpeed));
	}
}

void ASDBXCharacter::OnPunchOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	ASDBXCharacter* OtherPlayer = Cast<ASDBXCharacter>(OtherActor);
	if ((OtherPlayer != nullptr) && (OtherPlayer != this) && isPunching){
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Collided");
		if (OtherPlayer->IsBlocking()){
			FVector kbV = OtherPlayer->GetActorForwardVector();
			kbV *= KnockBack;
			LaunchCharacter(kbV, true, true);
			return;
		}
		HitBeat();
		if (!OtherPlayer->IsBlocking() || Multiplier > 2.0f){ //Check if other player is blocking, or don't care if multiplier is big enough
			Health += Damage*Multiplier;
			OtherPlayer->TakeDamage(Damage*Multiplier, FDamageEvent(), GetInstigatorController(), this);
			OtherPlayer->ComboBreaker();
			OtherPlayer->ResetStates();
		}

	}
	else if (OtherPlayer == this && isPunching){
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "NullPtr");
		//ComboBreaker();
	}
}

void ASDBXCharacter::OnKickOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	ASDBXCharacter* OtherPlayer = Cast<ASDBXCharacter>(OtherActor);
	if ((OtherPlayer != nullptr) && (OtherPlayer != this) && isKicking){
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Collided");
		if (OtherPlayer->IsBlocking()){
			FVector kbV = OtherPlayer->GetActorForwardVector();
			kbV *= KnockBack;
			LaunchCharacter(kbV, true, true);
			return;
		}
		HitBeat();
		if (!OtherPlayer->IsBlocking() || Multiplier > 5.0f){ //Check if other player is blocking, or don't care if multiplier is big enough
			Health += KickDamage*Multiplier;
			OtherPlayer->TakeDamage(KickDamage*Multiplier, FDamageEvent(), GetInstigatorController(), this);
			OtherPlayer->ComboBreaker();
			OtherPlayer->ResetStates();
		}
	}
	else if (OtherPlayer == this && isKicking){
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "NullPtr");
		//ComboBreaker();
	}
}

float ASDBXCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent,
		EventInstigator, DamageCauser);
	if (ActualDamage > 0.0f)
	{
		Health -= ActualDamage;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(Health));
		FVector kbV = DamageCauser->GetActorForwardVector();
		kbV *= Multiplier*600.0;
		LaunchCharacter(kbV, true, true);
		if (Health <= 0.0f)
		{
			// We're dead, don't allow further damage
			bCanBeDamaged = false;

			//Play death animation and disable input
			float len = PlayAnimMontage(DeathAnim, 1.0f);
			GetController()->UnPossess();
			FTimerHandle DeathTimer;
			GetWorldTimerManager().SetTimer(DeathTimer, this, &ASDBXCharacter::OnDeath, len - 0.25f, false);
			//Turn off colliders
			GetCapsuleComponent()->MoveIgnoreActors.Add(DamageCauser);
			punchCollider->DestroyComponent();
			footCollider->DestroyComponent();
			calfCollider->DestroyComponent();
			APlayerController* PC = Cast<APlayerController>(GetController());
			if (PC)
			{
				PC->SetCinematicMode(true, true, true);
			}

			//Trigger game over
			((ASDBXGameMode*)(UGameplayStatics::GetGameMode(this)))->OnGameOver();
		}
		else {
			//play hit animation
			PlayAnimMontage(HitAnim, 1.0f);
		}
	}
	return ActualDamage;
}

void ASDBXCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	id = ((APlayerController *)GetController())->GetLocalPlayer()->GetControllerId();
	SetupColor();
	// set up gameplay key bindings
	if (id == 0){
		InputComponent->BindAction("P1_Jump", IE_Pressed, this, &ACharacter::Jump);
		InputComponent->BindAction("P1_Jump", IE_Released, this, &ACharacter::StopJumping);
		InputComponent->BindAction("P1_Punch", IE_Pressed, this, &ASDBXCharacter::Attack);
		InputComponent->BindAction("P1_Block", IE_Pressed, this, &ASDBXCharacter::Block);
		InputComponent->BindAction("P1_Dance", IE_Released, this, &ASDBXCharacter::Dance);
		InputComponent->BindAxis("P1_MoveRight", this, &ASDBXCharacter::MoveRight);
	}
	else if (id == 1){
		InputComponent->BindAction("P2_Jump", IE_Pressed, this, &ACharacter::Jump);
		InputComponent->BindAction("P2_Jump", IE_Released, this, &ACharacter::StopJumping);
		InputComponent->BindAction("P2_Punch", IE_Pressed, this, &ASDBXCharacter::Attack);
		InputComponent->BindAction("P2_Block", IE_Pressed, this, &ASDBXCharacter::Block);
		InputComponent->BindAction("P2_Dance", IE_Released, this, &ASDBXCharacter::Dance);
		InputComponent->BindAxis("P2_MoveRight", this, &ASDBXCharacter::MoveRight);
	}
}

void ASDBXCharacter::MoveRight(float Value)
{
	// add movement in that direction
	if (Value != 0.0f){
		AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
	}
}

void ASDBXCharacter::ComboBreaker(){
	Combo = 0;
	Multiplier = 1.0;
	if (GetWorldTimerManager().IsTimerActive(comboHandle)){
		GetWorldTimerManager().ClearTimer(comboHandle);
	}
}

void ASDBXCharacter::HitBeat(){
	Combo++;
	TotalHits++;
	Multiplier += 0.1;
	if (GetWorldTimerManager().IsTimerActive(comboHandle)){
		GetWorldTimerManager().ClearTimer(comboHandle);
	}
	if (Multiplier >= 6.0f){
		Multiplier = 6.0f;
	}
}

bool ASDBXCharacter::CastRay(){
	if (bSlot){
		static FName FireTag = FName(TEXT("BeatTrace"));
		FVector StartPos = bSlot->GetActorLocation();
		FVector EndPos = StartPos;
		EndPos.X += 10.0f;
		FCollisionQueryParams TraceParams(FireTag, true, Instigator);
		TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = true;
		FHitResult Hit(ForceInit);
		GetWorld()->LineTraceSingleByObjectType(Hit, StartPos, EndPos,
			FCollisionObjectQueryParams::AllObjects, TraceParams);
		// Did this hit anything?
		if (Hit.bBlockingHit)
		{
			
			ABeatMarker* bM = Cast<ABeatMarker>(Hit.GetActor());
			if (bM)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Hit Beat");
				bM->Destroy();
				return true;
			}
		}
		else{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Missed Beat");
			ComboBreaker();
		}
	}
	return false;
}

void ASDBXCharacter::Attack(){
	if (CastRay()){
		if (!GetCharacterMovement()->IsFalling()){ //punches if not in the air
			isPunching = true;
			PlayAnim(PunchAnim);
		}
		else { //kicks if in the air
			isKicking = true;
			PlayAnim(KickAnim);
		}
	}
}

void ASDBXCharacter::Dance(){
	if (CastRay()){
		HitBeat();
		isDancing = true;
		float len = PlayAnimMontage(DanceAnim, 1.0f);
		DisableInput((APlayerController*)GetController());
		GetWorldTimerManager().SetTimer(inputHandle, this, &ASDBXCharacter::ResetStates, len);
	}
}

void ASDBXCharacter::ResetStates(){
	EnableInput((APlayerController*)GetController());
	isPunching = false;
	isKicking = false;
	isBlocking = false;
	isDancing = false;
}

void ASDBXCharacter::Block(){
	if (CastRay()){
		HitBeat();
		isBlocking = true;
		float len = PlayAnimMontage(BlockAnim, 1.0f);
		DisableInput((APlayerController*)GetController());
		GetWorldTimerManager().SetTimer(inputHandle, this, &ASDBXCharacter::ResetStates, len);
	}
}

void ASDBXCharacter::PlayAnim(UAnimMontage * animation){
	float len = PlayAnimMontage(animation, 1.0f);
	DisableInput((APlayerController*)GetController());
	GetWorldTimerManager().SetTimer(comboHandle, this, &ASDBXCharacter::ComboBreaker, len);
	GetWorldTimerManager().SetTimer(inputHandle, this, &ASDBXCharacter::ResetStates, len);
}

void ASDBXCharacter::OnDeath(){
	GetMesh()->Deactivate();
}

