// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonCharacter.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FirstPersonCameraComponent != nullptr);

	auto root = CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent());

	LifetimeInQueue = DEFAULT_AUDIO_QUEUE_LIFETIME;

	SoundPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundPlayer"));
	SoundPlayer->SetupAttachment(root);
	SoundPlayer->OnAudioFinished.AddDynamic(this, &AFirstPersonCharacter::AssessSoundQueueStatus);

	// Attach the camera component to our capsule component.
	FirstPersonCameraComponent->SetupAttachment(root);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f + BaseEyeHeight)); // positions slightly above the eyes.
	FirstPersonCameraComponent->bUsePawnControlRotation = true; // enables the character to control camera rotation.

	// Hide the third person mesh from the owner.
	GetMesh()->SetOwnerNoSee(true);

	// Create a first person mesh component for the owning player.
	FirstPersonJarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstPersonJarMesh"));
	check(FirstPersonJarMesh != nullptr);

	FirstPersonJarMesh->SetOnlyOwnerSee(true); // only the owner sees it.
	FirstPersonJarMesh->SetupAttachment(FirstPersonCameraComponent); // attach mesh to camera.
	FirstPersonJarMesh->bCastDynamicShadow = false; // disable shadows to perserve the illusion of a single mesh.
	FirstPersonJarMesh->CastShadow = false;

	// Create a first person mesh component for the owning player.
	FirstPersonToolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstPersonToolMesh"));
	check(FirstPersonToolMesh != nullptr);

	FirstPersonToolMesh->SetOnlyOwnerSee(true); // only the owner sees it.
	FirstPersonToolMesh->SetupAttachment(FirstPersonCameraComponent); // attach mesh to camera.
	FirstPersonToolMesh->bCastDynamicShadow = false; // disable shadows to perserve the illusion of a single mesh.
	FirstPersonToolMesh->CastShadow = false;
}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFirstPersonCharacter::MoveRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &AFirstPersonCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFirstPersonCharacter::AddControllerPitchInput);

	// Unused but implemented for practice. Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFirstPersonCharacter::Unused_StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFirstPersonCharacter::Unused_StopJump);
}

void AFirstPersonCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFirstPersonCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFirstPersonCharacter::Unused_StartJump()
{
	// Uses default jump implementation.
	bPressedJump = true;
}

void AFirstPersonCharacter::Unused_StopJump()
{
	bPressedJump = false;
}

const TArray<USoundBase*>& AFirstPersonCharacter::GetSuccessSounds() const { return SuccessSounds; }
const TArray<USoundBase*>& AFirstPersonCharacter::GetFailureSounds() const { return FailureSounds; }

bool AFirstPersonCharacter::IsAcceptingSoundsToEnqueue() const { return IsAcceptingSoundsToEnqueueWithLifetime(LifetimeInQueue); }
bool AFirstPersonCharacter::IsAcceptingSoundsToEnqueueWithLifetime(float lifetimeSeconds) const
{
	float queuedSoundTotal = 0.f;

	if (SoundPlayer->IsPlaying())
	{
		queuedSoundTotal += GetWorld()->GetAudioTimeSeconds() - SoundPlayer->TimeAudioComponentPlayed;
	}

	for (int i = 0; i < SoundsToPlay.Num() && queuedSoundTotal < lifetimeSeconds; i++)
	{
		queuedSoundTotal += SoundsToPlay[i]->GetDuration();
	}

	return (queuedSoundTotal - lifetimeSeconds) < FLT_EPSILON;
}

bool AFirstPersonCharacter::EnqueueSound(USoundBase* soundToPlay) { return EnqueueSoundWithLifetime(soundToPlay, LifetimeInQueue); }
bool AFirstPersonCharacter::EnqueueSoundWithLifetime(USoundBase* soundToPlay, float lifetimeSeconds)
{
	bool isSoundAccepted = IsAcceptingSoundsToEnqueueWithLifetime(lifetimeSeconds);

	if (isSoundAccepted)
	{
		ForceEnqueueSound(soundToPlay);
	}

	return isSoundAccepted;
}

void AFirstPersonCharacter::ForceEnqueueSound(USoundBase* soundToPlay)
{
	SoundsToPlay.Add(soundToPlay);
	AssessSoundQueueStatus();
}

void AFirstPersonCharacter::ForceSoundToFrontOfQueue(USoundBase* soundToPlay)
{
	SoundsToPlay.Insert(soundToPlay, 0);
	AssessSoundQueueStatus();
}

void AFirstPersonCharacter::AssessSoundQueueStatus()
{
	if (!SoundPlayer->IsPlaying() && SoundsToPlay.Num() > 0)
	{
		SoundPlayer->SetSound(SoundsToPlay.Pop());
		SoundPlayer->Play();
	}
}
