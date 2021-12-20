// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "CharacterEnumClasses.h"
#include "MyCharacter.generated.h"



//DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class TEKKEN_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// 모든 캐릭터들이 상속받는 공통 캐릭터 클래스
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 각 캐릭터 클래스 생성자에서 공통으로 실행해야 하는 함수 모음
	UFUNCTION()
		void CharacterClassCommonConstructor();



	// Character Detail (각 캐릭터 클래스에서 초기화)

	// 캐릭터 아이디
	UPROPERTY(BlueprintReadOnly, Category = "Character Detail")
		ECharacters CharacterID;

	// 캐릭터 종류 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Detail")
		FName CharacterName;

	// 캐릭터 최대 공격 범위
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Detail")
		int32 MaxAttackRange;

	// 캐릭터 최소 공격 범위
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Detail")
		int32 MinAttackRange;

	// 캐릭터 디테일 변수 초기화. 각 캐릭터 클래스에서 정의
		virtual void InitializeCharacterDetail();

	// 캐릭터의 enum class를 키, 캐릭터의 이름을 FName 값으로 갖는 해시 테이블. 각 캐릭터 클래스에서 추가
		static TMap<ECharacters, FName> CharacterNameMap;



	// Components
	// Camera, Mesh, Sphere Collision, Particle System, Capsule Component 초기화
	UFUNCTION()
		void InitializeComponents();



	// Camera

	// 캐릭터 뒤에 위치할 Camera Component
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	// Camera Component 초기화 함수
	UFUNCTION()
		void InitializeCameraComponent();



	// Mesh Component

	// Mesh Component 관련 초기화 함수
	UFUNCTION()
	void InitializeMeshComponent();



	// Sphere Collision Component
	// 캐릭터에 따라서 필요 없는 것이 존재할 경우 블루프린트에서 직접 삭제

	// 왼손에 붙일 Sphere Collision Component
	UPROPERTY(VisibleAnywhere)
		USphereComponent* LeftHandCollision;

	// 오른손에 붙일 Sphere Collision Component
	UPROPERTY(VisibleAnywhere)
		USphereComponent* RightHandCollision;

	// 왼발에 붙일 Sphere Collision Component
	UPROPERTY(VisibleAnywhere)
		USphereComponent* LeftFootCollision;

	// 오른발에 붙일 Sphere Collision Component
	UPROPERTY(VisibleAnywhere)
		USphereComponent* RightFootCollision;

	// 좌우 손발에 붙일 Sphere Collision Component를 생성하고 이벤트 함수를 바인딩하는 함수
	UFUNCTION()
		void InitializeSphereCollisionComponents();

	// 각 Sphere Collision Component가 상대 캐릭터의 Capsule Component와 Overlap 됐을 때 실행할 함수
	UFUNCTION()
		void OnSphereCollisionComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Collision Component를 매쉬의 왼손에 붙일 때 쓰일 소켓 이름. 각 캐릭터 클래스 생성자에서 정의
	UPROPERTY()
		FName LeftHandSocketName;

	// Collision Component를 매쉬의 오른손에 붙일 때 쓰일 소켓 이름. 각 캐릭터 클래스 생성자에서 정의
	UPROPERTY()
		FName RightHandSocketName;

	// Collision Component를 매쉬의 왼발에 붙일 때 쓰일 소켓 이름. 각 캐릭터 클래스 생성자에서 정의
	UPROPERTY()
		FName LeftFootSocketName;

	// Collision Component를 매쉬의 오른발에 붙일 때 쓰일 소켓 이름. 각 캐릭터 클래스 생성자에서 정의
	UPROPERTY()
		FName RightFootSocketName;

	// Sphere Collision Component를 매쉬의 해당 부위에 Attach 하는 함수. Socket 이름이 정의된 이후 각 캐릭터 클래스 생성자에서 호출
	UFUNCTION()
		void AttachCollisionComponentsToMesh();



	// Particle Component
	// 상대 공격 시 불꽃이 튀게 하기 위한 용도

	// 왼손에 붙일 Particle Component
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* LeftHandParticleSystem;

	// 오른손에 붙일 Particle Component
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* RightHandParticleSystem;

	// 왼발에 붙일 Particle Component
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* LeftFootParticleSystem;

	// 오른발에 붙일 Particle Component
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* RightFootParticleSystem;

	// 좌우 손발에 붙일 Particle System Component를 생성하고 이를 Sphere Collision Component에 Attach하는 함수
	UFUNCTION()
		void InitializeParticleSystemComponents();



	// Capsule Component

	// Capsule Component가 상대 캐릭터의 Sphere Collision Component와 Overlap 됐을 때 실행할 함수
	UFUNCTION()
		void OnCapsuleComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Capsule Component가 상대 캐릭터의 Sphere Collision Component와 Overlap이 끝났을 때 실행할 함수
	UFUNCTION()
		void OnCapsuleComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Capule Component 관련 여러 초기화와 이벤트 함수를 바인딩해주는 함수
	UFUNCTION()
		void InitializeCapsuleComponent();



	// Hp

	// 캐릭터의 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
		int32 MaxHp;

	// 캐릭터의 현재 체력
	UPROPERTY(BlueprintReadWrite, Category = "Hp")
		int32 CurrentHp;

	// 체력 변화량을 받아서 남은 체력 업데이트. bGameOver = true이면 더 이상 Hp가 변하지 않음
	UFUNCTION(BlueprintCallable, Category = "Hp")
		void UpdateHpLeft(int32 HpDiff);

	// 게임 종료 여부를 의미하는 bool 변수. 게임이 종료되면 더 이상 Hp가 변하지 않음
	UPROPERTY(BlueprintReadWrite, Category = "Hp")
		bool bGameOver;

	// 캐릭터가 죽었는지 여부를 의미하는 bool 변수. 캐릭터의 체력이 0이 되면 true로 설정
	UPROPERTY(BlueprintReadWrite, Category = "Hp")
		bool bIsDead;


	
	// Locomotion

	// 캐릭터가 이동하고 있는지를 의미하는 bool 변수
	UPROPERTY()
		bool bMoving;

	// 캐릭터가 뛰고 있는지를 의미하는 bool 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
		bool bRunning;

	// 같은 이동 키가 두 번 연속 눌렸는지를 의미하는 bool 변수. true라면 캐릭터 달리기 시작
	UPROPERTY()
		bool bMovingKeyDoubleClicked;

	// 이동 키가 눌린 이후 시간. 0.3초 안에 다시 눌러야 달리기 시작
	UPROPERTY()
		float MovingKeyDoubleClickTime;

	// 캐릭터가 이동하고 있는 방향
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
		EMoveDirection MoveDirection;

	// 캐릭터가 이전에 이동했던 방향
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
		EMoveDirection PreviousMovingDirection;

	// 캐릭터를 앞뒤로 이동시키는 함수
	UFUNCTION()
		void MoveForward(float AxisValue);

	// 캐릭터를 좌우로 이동시키는 함수
	UFUNCTION()
		void MoveRight(float AxisValue);

	// 캐릭터 달리기 시작 함수
	UFUNCTION()
		void StartRun();

	// 캐릭터 달리기 종료 함수
	UFUNCTION()
		void StopRun();

	// 캐릭터 점프 시작 함수
	UFUNCTION()
		void StartJump();

	// 캐릭터 점프 종료 함수
	UFUNCTION()
		void StopJump();

	// 캐릭터를 Idle 상태로 만드는 함수
	UFUNCTION()
		void MakeIdle();



	// Attack

	// 입력 키의 조합을 키, 그에 해당하는 공격 모션을 값으로 가지는 해시 테이블
	UPROPERTY()
		TMap<FString, EAttackMotion> AttackMotionTable;

	// 공격 모션을 키, 해당 공격 모션이  활성화되어 있는지 bool 변수를 값으로 가지고 있는 해시 테이블
	UPROPERTY()
		TMap<EAttackMotion, bool> AttackMotionBoolTable;

	// 공격 모션을 키, 해당 공격 모션의 데미지를 값으로 가지고 있는 해시 테이블
	UPROPERTY()
		TMap<EAttackMotion, int32> AttackMotionDamageTable;

	// 추가적인 공격 콤보가 없는 공격 모션들을 저장한 배열. 이에 해당하는 공격 모션이 나올 시 입력 키 스택을 초기화
	UPROPERTY()
		TArray<EAttackMotion> FinalAttackMotions;

	// 공격 모션, bool, 데미지 테이블과 FinalAttackMotions 배열 초기화. 각 캐릭터 클래스에서 정의
		virtual void InitializeAttackTable();

	// 애니메이션 블루프린트에서 AttackMotionBoolTable의 값을 가져오기 위한 함수. AnimMyCharacter 클래스에서 호출
	UFUNCTION(BlueprintCallable, Category = "Attack")
		bool GetAttackMotionBoolTable(EAttackMotion AttackMotion);

	// 가장 최근 실행된 공격 모션
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
		EAttackMotion CurrentAttackMotion;

	// 공격 애니메이션에서 애님 노티파이 이벤트를 통해 현재 캐릭터가 공격 중인지를 설정하는 bool 변수
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
		bool bAttacking;

	// 공격 키를 누른 후에 흐른 시간. 공격 콤보를 구현하기 위해 사용
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
		float KeyClickInterval;

	// 아무 키나 누른지 0.5초가 지나지 않았을 때 true로 설정되는 bool 변수. 공격 콤보를 구현하기 위해 사용
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
		bool bAnyKeyClicked;

	// 지금까지 들어온 입력 키를 저장한 배열. 스택으로서 작동
	UPROPERTY()
		TArray<FString> InputKeyArray;

	// 사용자가 누른 입력 키를 배열에 저장하는 함수
	UFUNCTION()
		void AddKeyToInputArray(FString PressedKeyName);

	// 아무 키나 눌렀을 때 수행해야 하는 함수
	UFUNCTION()
		void WhenAnyKeyClicked(FString PressedKeyName);

	// 최종 공격 모션을 결정하는 함수
	UFUNCTION(BlueprintCallable, Category = "Attack")
		void DetermineAttackMotion();

	// 왼쪽 주먹 공격 키가 눌렸을 때 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "Attack")
		void WhenLeftPunchKeyClicked();

	// 오른쪽 주먹 공격 키가 눌렸을 때 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "Attack")
		void WhenRightPunchKeyClicked();

	// 왼쪽 다리 공격 키가 눌렸을 때 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "Attack")
		void WhenLeftKickKeyClicked();

	// 오른쪽 다리 공격 키가 눌렸을 때 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "Attack")
		void WhenRightKickKeyClicked();



	// Hit

	// 캐릭터가 타격을 받았을 때 true가 되는 bool 변수
	UPROPERTY()
		bool bIsHit;

	// 캐릭터가 가진 공격 모션마다 상대의 어느 부위를 가격하는지 정의한 테이블
	UPROPERTY()
		TMap<EAttackMotion, EHitPosition> AttackMotionHitPositionTable;

	// 캐릭터가 가진 공격 모션마다 좌우 손발 중 어느 콜리전 컴포넌트로 상대를 가격하는지 기록한 테이블
	UPROPERTY()
		TMap<EAttackMotion, USphereComponent*> AttackMotionCollisionComponentTable;

	// 캐릭터가 어느 부위를 맞았는지 부위를 키, bool 변수를 값으로 가지는 해시 테이블
	UPROPERTY()
		TMap<EHitPosition, bool> HitPositionBoolTable;

	// 애니메이션 블루프린트에서 HitPositionBoolTable의 값을 가져오기 위한 함수. AnimMyCharacter 클래스에서 호출
	UFUNCTION(BlueprintCallable, Category = "Hit")
		bool GetHitPositionBoolTable(EHitPosition HitPosition);

	// Hit 관련 테이블들을 초기화하는 함수
	// AttackMotionCollisionComponentTable과 AttackMotionHitPositionTable은 각 캐릭터 클래스에서 정의
		virtual void InitializeHitTable();



	// AI

	// AI 캐릭터 랜덤 공격 함수. 좌우 손발 4가지 키를 랜덤으로 선택해서 입력. 만약 캐릭터에 따라 재정의가 필요할 경우에만 그 캐릭터 클래스에서 재정의
	UFUNCTION()
		virtual void RandomAttack();
};