// Fill out your copyright notice in the Description page of Project Settings.

#include "../header/MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "../../AI/header/CharacterAIController.h"
#include "../../AI/header/BTTask_Attack.h"
#include "Kismet/GameplayStatics.h"

#include <random>

// static 변수 초기화
TMap<ECharacters, FName> AMyCharacter::CharacterNameMap;

AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Sphere Collision Component의 소켓 이름 초기화. 각 캐릭터 클래스에서 재정의
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
	MovingKeyDoubleClickTime = 0.0f;

	// Attack 변수 초기화
	KeyClickInterval = 0.0f;
	CurrentAttackMotion = EAttackMotion::Idle;

	// Hit 변수 초기화
	bIsHit = false;

	// 각종 컴포넌트 초기화
	InitializeComponents();

	// 캐릭터 AI 컨트롤러 설정
	AIControllerClass = ACharacterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 플레이어가 해당 캐릭터 조종
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 달리기 구현을 위한 변수
	if (bMovingKeyDoubleClicked)
		MovingKeyDoubleClickTime += DeltaTime;

	// 0.3초 동안 이동 키를 다시 누르지 않는다면 해당 변수들 초기화
	if (MovingKeyDoubleClickTime > 0.3f)
	{
		MovingKeyDoubleClickTime = 0.0f;
		bMoving = false;
		bMovingKeyDoubleClicked = false;
	}

	// 공격 콤보 구현을 위한 변수
	if (bAnyKeyClicked)
		KeyClickInterval += DeltaTime;

	// 0.7초 동안 공격 키를 누르지 않았다면 해당 변수들 초기화하고 캐릭터를 Idle 상태로 설정
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

	// 이동 키
	InputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	InputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRun);
	
	// 마우스 이동을 통한 화면 회전
	InputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);

	// 공격 키
	InputComponent->BindAction("LeftPunch", IE_Pressed, this, &AMyCharacter::WhenLeftPunchKeyClicked);
	InputComponent->BindAction("RightPunch", IE_Pressed, this, &AMyCharacter::WhenRightPunchKeyClicked);
	InputComponent->BindAction("LeftKick", IE_Pressed, this, &AMyCharacter::WhenLeftKickKeyClicked);
	InputComponent->BindAction("RightKick", IE_Pressed, this, &AMyCharacter::WhenRightKickKeyClicked);

	// 점프 키
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);
}

void AMyCharacter::CharacterClassCommonConstructor()
{
	// 캐릭터 이름을 저장한 해시 테이블에 캐릭터 이름 추가
	CharacterNameMap.Emplace(CharacterID, CharacterName);

	// 공격 모션마다 해당하는 콜리젼 컴포넌트를 저장한 해시 테이블에 기본값 추가
	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Idle, nullptr);

	// 좌우 손발의 Sphere Collision Component를 매쉬에 Attach
	AttachCollisionComponentsToMesh();
}

void AMyCharacter::InitializeCharacterDetail()
{
	// 각 캐릭터 클래스에서 재정의
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
	// 카메라 컴포넌트를 설정하고 캐릭터의 캡슐 컴포넌트에 부착
	// 캐릭터의 뒷상단에 카메라 위치

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
	// 캐릭터가 앞을 바라보도록 설정

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
	// 이후 각종 설정 초기화 후 이벤트 함수 바인딩

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
	// 조건
	// 1. 오버랩된 컴포넌트가 상대 액터의 캡슐 컴포넌트
	// 2. 자기 자신의 캡슐 컴포넌트와 부딪힌 게 아님
	// 3. 현재 캐릭터가 공격 중 (애님 노티파이 활용)
	// 4. 현재 공격 모션에 맞는 콜리전 컴포넌트가 부딪힘
	// 효과
	// 1. 상대 캐릭터의 HP를 깎음
	// 2. 해당 콜리전 컴포넌트의 파티클 시스템 활성화

	AMyCharacter* OtherCharacter = Cast<AMyCharacter>(OtherActor);
	
	if (OtherCharacter)
	{
		// 현재 공격 모션에 따른 콜리전 컴포넌트 설정
		USphereComponent* CollisionComponent;
		if (AttackMotionCollisionComponentTable.Contains(CurrentAttackMotion))
			CollisionComponent = AttackMotionCollisionComponentTable[CurrentAttackMotion];
		else
			CollisionComponent = nullptr;

		if (OtherCharacter->GetCapsuleComponent() == OtherComp && OtherCharacter != this && bAttacking && Cast<USphereComponent>(OverlappedComp) == CollisionComponent)
		{
			OtherCharacter->UpdateHpLeft(-AttackMotionDamageTable[CurrentAttackMotion]);
			Cast<UParticleSystemComponent>((OverlappedComp->GetAttachChildren())[0])->Activate(true);
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
	// 해당 부위에 Sphere Collision Component가 생성 되었어야 Particle System Component 생성
	// 생성 이후 좌우 손발의 Sphere Collision Component에 Attach

	// 왼손
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

	// 오른손
	if (RightHandCollision)
	{
		RightHandParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RightHandParticleSystem"));
		RightHandParticleSystem->SetupAttachment(RightHandCollision);
		RightHandParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		RightHandParticleSystem->SetVisibility(true);
		RightHandParticleSystem->SetHiddenInGame(false);
		RightHandParticleSystem->SetAutoActivate(false);
	}

	// 왼발
	if (LeftFootCollision)
	{
		LeftFootParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LeftFootParticleSystem"));
		LeftFootParticleSystem->SetupAttachment(LeftFootCollision);
		LeftFootParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		LeftFootParticleSystem->SetVisibility(true);
		LeftFootParticleSystem->SetHiddenInGame(false);
		LeftFootParticleSystem->SetAutoActivate(false);
	}

	// 오른발
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
	// 조건
	// 1. 자기 자신과 부딪힌 게 아님
	// 2. 상대 공격 모션에 맞는 콜리전 컴포넌트와 부딪힘
	// 3. 상대 캐릭터가 공격 중
	// 효과
	// 1. 상대 공격 모션에 맞는 부위가 맞았다고 설정
	// 2. bIsHit 변수 true로 설정

	auto OtherCharacter = Cast<AMyCharacter>(OtherActor);

	if (OtherCharacter)
	{
		EAttackMotion AttackMotion = OtherCharacter->CurrentAttackMotion;	// 상대 캐릭터의 공격 모션
		bool bOtherCharacterAttacking = OtherCharacter->bAttacking;	// 상대 캐릭터가 공격 중인지
		
		// 상대 공격 모션에 맞는 콜리전 컴포넌트
		USphereComponent* CollisionComponent;
		if (OtherCharacter->AttackMotionCollisionComponentTable.Contains(AttackMotion))
			CollisionComponent = OtherCharacter->AttackMotionCollisionComponentTable[AttackMotion];
		else
			CollisionComponent = nullptr;

		if (OtherCharacter != this && Cast<USphereComponent>(OtherComp) == CollisionComponent && bOtherCharacterAttacking)
		{
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
	// 캡슐 컴포넌트 초기화 이후 이벤트 함수 바인딩

	UCapsuleComponent* MyCapsuleComponent = GetCapsuleComponent();
	MyCapsuleComponent->SetGenerateOverlapEvents(true);
	MyCapsuleComponent->SetVisibility(false);
	MyCapsuleComponent->SetHiddenInGame(false);
	MyCapsuleComponent->CanCharacterStepUpOn = ECB_Yes;
	MyCapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
	MyCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnCapsuleComponentBeginOverlap);
	MyCapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::OnCapsuleComponentEndOverlap);
}

bool AMyCharacter::GetAttackMotionBoolTable(EAttackMotion AttackMotion)
{
	if (AttackMotionBoolTable.Contains(AttackMotion))
		return AttackMotionBoolTable[AttackMotion];
	else
		return false;
}

void AMyCharacter::UpdateHpLeft(int32 HpDiff)
{
	// 게임이 끝났을 때는 체력 업데이트 불가
	// 체력이 최대 체력을 넘어가거나 0밑으로 떨어질 수는 없음

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
	// 앞 뒤로 이동
	// 뛸 때는 속도를 3배로 설정

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
	// 좌우로 이동
	// 뛸 때는 속도를 3배로 설정

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	if (bMoving && bMovingKeyDoubleClicked)
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
	bMovingKeyDoubleClicked = true;
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
	// 점프 상태 해제
	bPressedJump = false;

	// 입력 키 스택 비우기
	InputKeyArray.Empty();

	// 모든 공격 모션 상태 해제
	for (auto& Elem : AttackMotionBoolTable)
	{
		AttackMotionBoolTable[Elem.Key] = false;
	}

	// 공격 상태 해제
	bAttacking = false;

	// 현재 공격 모션을 기본값으로 설정
	CurrentAttackMotion = EAttackMotion::Idle;
}

void AMyCharacter::InitializeAttackTable()
{
	// 각 캐릭터 클래스에서 재정의
}

void AMyCharacter::AddKeyToInputArray(FString PressedKeyName)
{
	// 스택에 입력 키 쌓기
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
	EAttackMotion NewAttackMotion = EAttackMotion::Idle;

	// 입력 키 스택에서 하나씩 빼면서 그에 해당하는 공격 모션이 존재하는지 검사
	// 최대한 길게 매치될 때까지 진행 후 공격 모션 결정
	// 입력 키는 처리가 편하도록 스트링으로 치환하여 생각
	// 왼쪽 손 : H
	// 오른쪽 손 : J
	// 왼쪽 발 : K
	// 오른쪽 발 : L
	
	for (int32 i = InputKeyArray.Num() - 1; i >= 0; i--)
	{
		InputString = InputKeyArray[i] + InputString;

		if (!AttackMotionTable.Contains(InputString))
		{
			break;
		}

		if (AttackMotionTable.Contains(InputString))
		{
			NewAttackMotion = AttackMotionTable[InputString];
		}
	}

	// 기존 공격 모션을 비활성화 시키고 새로운 공격 모션 활성화
	if (AttackMotionBoolTable.Contains(CurrentAttackMotion))
		AttackMotionBoolTable[CurrentAttackMotion] = false;
	if (AttackMotionBoolTable.Contains(NewAttackMotion))
		AttackMotionBoolTable[NewAttackMotion] = true;
	CurrentAttackMotion = NewAttackMotion;

	// 만약 이후 연결되는 공격 콤보가 없다면 스택 초기화
	if (FinalAttackMotions.Contains(NewAttackMotion))
		InputKeyArray.Empty();

}

void AMyCharacter::WhenLeftPunchKeyClicked()
{
	WhenAnyKeyClicked(TEXT("H"));
	DetermineAttackMotion();
}

void AMyCharacter::WhenRightPunchKeyClicked()
{
	WhenAnyKeyClicked(TEXT("J"));
	DetermineAttackMotion();
}

void AMyCharacter::WhenLeftKickKeyClicked()
{
	WhenAnyKeyClicked(TEXT("K"));
	DetermineAttackMotion();
}

void AMyCharacter::WhenRightKickKeyClicked()
{
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
	// 랜덤으로 4가지 공격 키 중 하나 입력

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