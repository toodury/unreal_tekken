// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CharacterAIController.h"
#include "BTTask_Attack.h"
#include "Kismet/GameplayStatics.h"

#include <random>

TMap<ECharacters, FName> AMyCharacter::CharacterNameMap;

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Sphere Collision Component의 소켓 이름 초기화
	LeftHandSocketName = FName(TEXT("None"));
	RightHandSocketName = FName(TEXT("None"));
	LeftFootSocketName = FName(TEXT("None"));
	RightFootSocketName = FName(TEXT("None"));

	// Hp 변수 초기화
	MaxHp = 100;
	CurrentHp = MaxHp;
	bGameOver = false;
	bIsDead = false;

	// Locomotion 변수 초기화
	bMoving = false;
	bRunning = false;
	DoubleClickTime = 0.0f;

	// Attack 변수 초기화
	KeyClickInterval = 0.0f;
	//CurrentAttackMotion = TEXT("");
	//AttakMotionCollisionComponentTable.Emplace(TEXT(""), nullptr);
	// 이걸 왜 썼냐면 Sphere On Collision 에서 CurrentAttackMotion이 ""일 때 
	// 테이블에 그거에 해당하는 값이 없어서 어서트가 뜨기 때문
	CurrentAttackMotion = EAttackMotion::Idle;

	// Hit 변수 초기화
	bIsHit = false;

	// AI 변수 초기화
	//bIsControlledByAI = true;

	// 각종 컴포넌트 초기화
	InitializeComponents();

	//// 카메라 컴포넌트 초기화
	//InitializeCameraComponent();

	//// Mesh Component 초기화
	//InitializeMeshComponent();

	//// Capsule Component 초기화
	//InitializeCapsuleComponent();

	// 캐릭터 AI 컨트롤러 설정
	AIControllerClass = ACharacterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDoubleClicked)
		DoubleClickTime += DeltaTime;

	if (DoubleClickTime > 0.3f)
	{
		DoubleClickTime = 0.0f;
		bMoving = false;
		bDoubleClicked = false;
	}

	if (bAnyKeyClicked)
		KeyClickInterval += DeltaTime;

	if (KeyClickInterval > 0.7f)
	{
		bAnyKeyClicked = false;
		KeyClickInterval = 0.0f;
		InputKeyArray.Empty();
		MakeIdle();
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	InputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRun);

	InputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);

	InputComponent->BindAction("LeftPunch", IE_Pressed, this, &AMyCharacter::WhenLeftPunchKeyClicked);
	InputComponent->BindAction("RightPunch", IE_Pressed, this, &AMyCharacter::WhenRightPunchKeyClicked);
	InputComponent->BindAction("LeftKick", IE_Pressed, this, &AMyCharacter::WhenLeftKickKeyClicked);
	InputComponent->BindAction("RightKick", IE_Pressed, this, &AMyCharacter::WhenRightKickKeyClicked);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);
}

void AMyCharacter::CharacterClassCommonConstructor()
{
	// 해시 테이블에 캐릭터 이름 추가
	CharacterNameMap.Emplace(CharacterID, CharacterName);

	// 좌우 손발의 Sphere Collision Component를 매쉬에 Attach
	AttachCollisionComponentsToMesh();
}

void AMyCharacter::InitializeCharacterDetail()
{

}

void AMyCharacter::InitializeComponents()
{
	// 카메라 컴포넌트 초기화
	InitializeCameraComponent();

	// Mesh Component 초기화
	InitializeMeshComponent();

	// Sphere Collision Component 초기화
	InitializeSphereCollisionComponents();

	// Particle System Component 초기화
	InitializeParticleSystemComponents();

	// Capsule Component 초기화
	InitializeCapsuleComponent();
}

void AMyCharacter::InitializeCameraComponent()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	if (Camera)
	{
		Camera->SetupAttachment(GetCapsuleComponent());
		Camera->SetRelativeLocation(FVector(-125.0f, -25.0f, BaseEyeHeight + 90.0f));
		Camera->SetRelativeRotation(FRotator(0.0f, 35.0f, 0.0f));
		Camera->bUsePawnControlRotation = true;
	}
}

void AMyCharacter::InitializeMeshComponent()
{
	USkeletalMeshComponent* MyMesh = GetMesh();
	if (MyMesh)
	{
		MyMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -80.0f));
		MyMesh->SetRelativeRotation(FRotator(0.0f, -80.0f, 0.0f));
	}
}

void AMyCharacter::InitializeSphereCollisionComponents()
{
	// 해당 Mesh의 좌우 손발에 Attach할 Sphere Collision Component 생성
	// 이후 각종 설정 초기화

	// 왼손
	LeftHandCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandCollision"));
	LeftHandCollision->SetSphereRadius(20.0f);
	LeftHandCollision->SetVisibility(false);
	LeftHandCollision->SetHiddenInGame(false);
	LeftHandCollision->SetGenerateOverlapEvents(true);
	LeftHandCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	LeftHandCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnSphereCollisionComponentBeginOverlap);

	// 오른손
	RightHandCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandCollision"));		
	RightHandCollision->SetSphereRadius(20.0f);
	RightHandCollision->SetVisibility(false);
	RightHandCollision->SetHiddenInGame(false);
	RightHandCollision->SetGenerateOverlapEvents(true);
	RightHandCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RightHandCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnSphereCollisionComponentBeginOverlap);
	
	// 왼발
	LeftFootCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LeftFootCollision"));	
	LeftFootCollision->SetSphereRadius(20.0f);
	LeftFootCollision->SetVisibility(false);
	LeftFootCollision->SetHiddenInGame(false);
	LeftFootCollision->SetGenerateOverlapEvents(true);
	LeftFootCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	LeftFootCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnSphereCollisionComponentBeginOverlap);

	// 오른발
	RightFootCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RightFootCollision"));		
	RightFootCollision->SetSphereRadius(20.0f);
	RightFootCollision->SetVisibility(false);
	RightFootCollision->SetHiddenInGame(false);
	RightFootCollision->SetGenerateOverlapEvents(true);
	RightFootCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RightFootCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnSphereCollisionComponentBeginOverlap);
}

void AMyCharacter::OnSphereCollisionComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 오버랩된 컴포넌트가 상대 액터의 캡슐 컴포넌트이고
	// 현재 공격 모션에 맞는 콜리전 컴포넌트가 부딪힌 거고
	// 자기 자신의 캡슐 컴포넌트와 부딪힌 게 아니라면
	// 1. 상대 캐릭터의 HP를 깎음
	// 2. 해당 콜리전 컴포넌트의 파티클 시스템 활성화
	AMyCharacter* OtherCharacter = Cast<AMyCharacter>(OtherActor);
	
	if (OtherCharacter)
	{
		USphereComponent* CollisionComponent;
		if (AttackMotionCollisionComponentTable.Contains(CurrentAttackMotion))
			CollisionComponent = AttackMotionCollisionComponentTable[CurrentAttackMotion];
		else
			CollisionComponent = nullptr;

		if (OtherCharacter->GetCapsuleComponent() == OtherComp && OtherCharacter != this && bAttacking && Cast<USphereComponent>(OverlappedComp) == CollisionComponent)
		{
			OtherCharacter->UpdateHpLeft(-AttackMotionDamageTable[CurrentAttackMotion]);
			Cast<UParticleSystemComponent>((OverlappedComp->GetAttachChildren())[0])->Activate(true);
			//UE_LOG(LogTemp, Log, TEXT("CurrentAttackMotion : %s"), *CurrentAttackMotion);
		}
	}
}

void AMyCharacter::AttachCollisionComponentsToMesh()
{
	// 좌우 손발 뼈이름이 None이 아닌 다른 것으로 설정되어 있다면
	// 각 캐릭터의 매쉬의 좌우 손발에 Sphere Collision Component Attach

	if (!(LeftHandSocketName == FName(TEXT("None"))))
		LeftHandCollision->SetupAttachment(GetMesh(), LeftHandSocketName);
	if (!(RightHandSocketName == FName(TEXT("None"))))
		RightHandCollision->SetupAttachment(GetMesh(), RightHandSocketName);
	if (!(LeftFootSocketName == FName(TEXT("None"))))
		LeftFootCollision->SetupAttachment(GetMesh(), LeftFootSocketName);
	if (!(RightFootSocketName == FName(TEXT("None"))))
		RightFootCollision->SetupAttachment(GetMesh(), RightFootSocketName);
}

void AMyCharacter::InitializeParticleSystemComponents()
{
	// 블루프린트에서 매쉬에 맞는 소켓 이름을 넣어줘야 Sphere Collision Component 생성
	// 해당 부위에 Sphere Collision Component가 생성 되었어야 Particle System Component 생성
	// 생성 이후 좌우 손발의 Sphere Collision Component에 Attach

	if (LeftHandCollision)
	{
		LeftHandParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LeftHandParticleSystem"));
		if (LeftHandParticleSystem)
		{
			LeftHandParticleSystem->SetupAttachment(LeftHandCollision);
			LeftHandParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
			LeftHandParticleSystem->SetVisibility(true);
			LeftHandParticleSystem->SetHiddenInGame(false);
			LeftHandParticleSystem->SetAutoActivate(false);
		}
	}

	if (RightHandCollision)
	{
		RightHandParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RightHandParticleSystem"));
		RightHandParticleSystem->SetupAttachment(RightHandCollision);
		RightHandParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		RightHandParticleSystem->SetVisibility(true);
		RightHandParticleSystem->SetHiddenInGame(false);
		RightHandParticleSystem->SetAutoActivate(false);
	}

	if (LeftFootCollision)
	{
		LeftFootParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LeftFootParticleSystem"));
		LeftFootParticleSystem->SetupAttachment(LeftFootCollision);
		LeftFootParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		LeftFootParticleSystem->SetVisibility(true);
		LeftFootParticleSystem->SetHiddenInGame(false);
		LeftFootParticleSystem->SetAutoActivate(false);
	}

	if (RightFootCollision)
	{
		RightFootParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RightFootParticleSystem"));
		RightFootParticleSystem->SetupAttachment(RightFootCollision);
		RightFootParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		RightFootParticleSystem->SetVisibility(true);
		RightFootParticleSystem->SetHiddenInGame(false);
		RightFootParticleSystem->SetAutoActivate(false);
	}
}

void AMyCharacter::OnCapsuleComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto OtherCharacter = Cast<AMyCharacter>(OtherActor);

	if (OtherCharacter)
	{
		//FString AttckMotion = OtherCharacter->CurrentAttackMotion;	// 상대 캐릭터의 공격 모션
		EAttackMotion AttackMotion = OtherCharacter->CurrentAttackMotion;
		bool bOtherCharacterAttacking = OtherCharacter->bAttacking;

		USphereComponent* CollisionComponent;
		if (OtherCharacter->AttackMotionCollisionComponentTable.Contains(AttackMotion))
			CollisionComponent = OtherCharacter->AttackMotionCollisionComponentTable[AttackMotion];
		else
			CollisionComponent = nullptr;

		if (OtherCharacter != this && Cast<USphereComponent>(OtherComp) == CollisionComponent && bOtherCharacterAttacking)
		{
			UE_LOG(LogTemp, Log, TEXT("Hit"));
			HitPositionBoolTable[OtherCharacter->AttackMotionHitPositionTable[AttackMotion]] = true;
			bIsHit = true;
		}
	}
}

void AMyCharacter::OnCapsuleComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// HitPositionBoolTable의 모든 값을 false로 설정
	// 즉 캐릭터가 맞지 않은 상태로 설정

	bIsHit = false;

	for (auto Elem : HitPositionBoolTable)
	{
		HitPositionBoolTable[Elem.Key] = false;
	}
}

void AMyCharacter::InitializeCapsuleComponent()
{
	UCapsuleComponent* MyCapsuleComponent = GetCapsuleComponent();
	MyCapsuleComponent->SetGenerateOverlapEvents(true);
	MyCapsuleComponent->SetVisibility(false);
	MyCapsuleComponent->SetHiddenInGame(false);
	MyCapsuleComponent->CanCharacterStepUpOn = ECB_Yes;
	MyCapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
	MyCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnCapsuleComponentBeginOverlap);
	MyCapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::OnCapsuleComponentEndOverlap);
}

//bool AMyCharacter::GetAttackMotionBoolTable(FString AttackMotion)
bool AMyCharacter::GetAttackMotionBoolTable(EAttackMotion AttackMotion)
{
	if (AttackMotionBoolTable.Contains(AttackMotion))
		return AttackMotionBoolTable[AttackMotion];
	else
		return false;
}

//float AMyCharacter::GetAttackMotionDamageTable(FString AttackMotion)
float AMyCharacter::GetAttackMotionDamageTable(EAttackMotion AttackMotion)
{
	if (AttackMotionDamageTable.Contains(AttackMotion))
		return AttackMotionDamageTable[AttackMotion];
	else
		return 0.0f;
}

void AMyCharacter::UpdateHpLeft(int32 HpDiff)
{
	if (!bGameOver)
	{
		CurrentHp += HpDiff;

		if (CurrentHp >= MaxHp)
		{
			CurrentHp = MaxHp;
		}
		else if (CurrentHp <= 0)
		{
			CurrentHp = 0;
			bIsDead = true;
		}
	}
}

void AMyCharacter::MoveForward(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	if (bRunning)
	{
		AddMovementInput(Direction, AxisValue * 3.0f);
	}
	else
	{
		AddMovementInput(Direction, AxisValue);
	}

	if (AxisValue > 0.0f)
	{
		MoveDirection = EMoveDirection::Forward;
	}
	else if (AxisValue < 0.0f)
	{
		MoveDirection = EMoveDirection::Backward;
	}
}

void AMyCharacter::MoveRight(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	if (bMoving && bDoubleClicked)
	{
		AddMovementInput(Direction, AxisValue * 3.0f);
	}
	else
	{
		AddMovementInput(Direction, AxisValue);
	}

	if (AxisValue > 0.0f)
	{
		MoveDirection = EMoveDirection::Right;
	}
	else if (AxisValue < 0.0f)
	{
		MoveDirection = EMoveDirection::Left;
	}
}

void AMyCharacter::StartRun()
{
	if (bMoving)
	{
		bRunning = true;
	}
	bMoving = true;
}

void AMyCharacter::StopRun()
{
	bRunning = false;
	bDoubleClicked = true;
}

void AMyCharacter::StartJump()
{
	bPressedJump = true;
}

void AMyCharacter::StopJump()
{
	bPressedJump = false;
}

void AMyCharacter::MakeIdle()
{
	bPressedJump = false;

	// 입력 키 스택 비우기
	//InputKeyArray.Empty();

	// 모든 공격 모션 상태 해제
	for (auto& Elem : AttackMotionBoolTable)
	{
		AttackMotionBoolTable[Elem.Key] = false;
	}

	// 공격 상태 해제
	bAttacking = false;

	// 현재 공격 모션을 빈 스트링으로 설정
	//CurrentAttackMotion = TEXT("");
	CurrentAttackMotion = EAttackMotion::Idle;
}

void AMyCharacter::InitializeAttackTable()
{
	
}

void AMyCharacter::AddKeyToInputArray(FString PressedKeyName)
{
	InputKeyArray.Emplace(PressedKeyName);
}

void AMyCharacter::WhenAnyKeyClicked(FString PressedKeyName)
{
	AddKeyToInputArray(PressedKeyName);
	bAnyKeyClicked = true;
	KeyClickInterval = 0.0f;
}

void AMyCharacter::DetermineAttackMotion()
{
	FString InputString = TEXT("");
	//TArray<EInputKey> KeysToDetermineAttackMotion;
	//FString NewAttackMotion = TEXT("");
	EAttackMotion NewAttackMotion = EAttackMotion::Idle;
	
	for (int32 i = InputKeyArray.Num() - 1; i >= 0; i--)
	{
		//KeysToDetermineAttackMotion.Insert(InputKeyArray[i], 0);
		InputString = InputKeyArray[i] + InputString;

		//if (!AttackMotionTable.Contains(FEInputKeyArray(KeysToDetermineAttackMotion)))
		if (!AttackMotionTable.Contains(InputString))
		{
			break;
		}

		//if (AttackMotionTable.Contains(FEInputKeyArray(KeysToDetermineAttackMotion)))
		if (AttackMotionTable.Contains(InputString))
		{
			//NewAttackMotion = AttackMotionTable[FEInputKeyArray(KeysToDetermineAttackMotion)];
			NewAttackMotion = AttackMotionTable[InputString];
		}
	}

	if (AttackMotionBoolTable.Contains(CurrentAttackMotion))
		AttackMotionBoolTable[CurrentAttackMotion] = false;
	if (AttackMotionBoolTable.Contains(NewAttackMotion))
		AttackMotionBoolTable[NewAttackMotion] = true;
	CurrentAttackMotion = NewAttackMotion;

	if (FinalAttackMotions.Contains(NewAttackMotion))
		InputKeyArray.Empty();

}

void AMyCharacter::WhenLeftPunchKeyClicked()
{
	//WhenAnyKeyClicked(EInputKey::LeftPunch);
	WhenAnyKeyClicked(TEXT("H"));
	DetermineAttackMotion();
}

void AMyCharacter::WhenRightPunchKeyClicked()
{
	//WhenAnyKeyClicked(EInputKey::RightPunch);
	WhenAnyKeyClicked(TEXT("J"));
	DetermineAttackMotion();
}

void AMyCharacter::WhenLeftKickKeyClicked()
{
	//WhenAnyKeyClicked(EInputKey::LeftKick);
	WhenAnyKeyClicked(TEXT("K"));
	DetermineAttackMotion();
}

void AMyCharacter::WhenRightKickKeyClicked()
{
	//WhenAnyKeyClicked(EInputKey::RightKick);
	WhenAnyKeyClicked(TEXT("L"));
	DetermineAttackMotion();
}

bool AMyCharacter::GetHitPositionBoolTable(EHitPosition HitPosition)
{
	if (HitPositionBoolTable.Contains(HitPosition))
		return HitPositionBoolTable[HitPosition];
	else
		return false;
}

void AMyCharacter::InitializeHitTable()
{
	HitPositionBoolTable.Emplace(EHitPosition::LeftArm, false);
	HitPositionBoolTable.Emplace(EHitPosition::RightArm, false);
	HitPositionBoolTable.Emplace(EHitPosition::LeftLeg, false);
	HitPositionBoolTable.Emplace(EHitPosition::RightLeg, false);
	HitPositionBoolTable.Emplace(EHitPosition::Head, false);
	HitPositionBoolTable.Emplace(EHitPosition::Stomach, false);
}

void AMyCharacter::RandomAttack()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 4);

	switch (dis(gen))
	{
	case 0: WhenLeftPunchKeyClicked(); break;
	case 1: WhenRightPunchKeyClicked(); break;
	case 2: WhenLeftKickKeyClicked(); break;
	case 3: WhenRightKickKeyClicked(); break;
	default: WhenLeftPunchKeyClicked(); break;
	}
}

void AMyCharacter::AIStopAttack()
{
	if (IsBetweenAttackTimerStarted)
	{
		UBTTask_Attack::IsAttacking = false;
		MakeIdle();
		IsBetweenAttackTimerStarted = false;
		GetWorldTimerManager().ClearTimer(BetweenAttackTimerHandle);
	}
	else
	{
		GetWorldTimerManager().SetTimer(BetweenAttackTimerHandle, this, &AMyCharacter::AIStopAttack, 0.5f, true);
		IsBetweenAttackTimerStarted = true;
	}
}