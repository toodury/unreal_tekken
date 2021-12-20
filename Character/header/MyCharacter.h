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
	// Sets default values for this character's properties
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Detail")
		ECharacters CharacterID;

	// 캐릭터 종류 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Detail")
		FName CharacterName;

	// 캐릭터 최대 공격 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Detail")
		int32 MaxAttackRange;

	// 캐릭터 최소 공격 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Detail")
		int32 MinAttackRange;

	// 캐릭터 디테일 변수 초기화
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

	// 좌우 손발에 붙일 Sphere Collision Component를 생성하고 매쉬에 Attach하는 함수. 각 캐릭터 클래스 생성자에서 정의
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

	// 좌우 손발에 붙일 Particle System Component를 생성하고 이를 Sphere Collision Component에 Attach하는 함수. 각 캐릭터 클래스 생성자에서 정의
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
		int32 CurrentHp;

	// 체력 변화량을 받아서 남은 체력 업데이트. GameOver = true이면 더 이상 Hp가 변하지 않음
	UFUNCTION(BlueprintCallable, Category = "Hp")
	void UpdateHpLeft(int32 HpDiff);

	// 게임 종료 여부. 게임이 종료되면 더 이상 Hp가 변하지 않음
	UPROPERTY(BlueprintReadWrite, Category = "Hp")
		bool bGameOver;

	// 캐릭터가 죽었는지 여부. 캐릭터의 체력이 0이 되면 true
	UPROPERTY(BlueprintReadWrite, Category = "Hp")
		bool bIsDead;


	
	// Locomotion

	bool bMoving;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	bool bRunning;
	bool bDoubleClicked;
	float DoubleClickTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	EMoveDirection MoveDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	EMoveDirection PreviousMovingDirection;
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void StartRun();
	void StopRun();
	void StartJump();
	void StopJump();
	void MakeIdle();



	// Attack

	// 캐릭터가 가진 모든 공격 패턴을 가지고 있는 테이블
	UPROPERTY()
		//TMap<FEInputKeyArray, FString> AttackMotionTable;
		//TMap<FString, FString> AttackMotionTable;
		TMap<FString, EAttackMotion> AttackMotionTable;

	// 현재 공격 패턴이 활성화되어 있는지 bool 변수로 가지고 있는 테이블
	UPROPERTY()
		//TMap<FString, bool> AttackMotionBoolTable;
		TMap<EAttackMotion, bool> AttackMotionBoolTable;

	// 공격 패턴마다 데미지 저장 테이블
	UPROPERTY()
		//TMap<FString, float> AttackMotionDamageTable;
		TMap<EAttackMotion, float> AttackMotionDamageTable;

	// 이후 공격 콤보가 없는 공격 패턴 저장 배열
	UPROPERTY()
		//TArray<FString> FinalAttackMotions;
		TArray<EAttackMotion> FinalAttackMotions;

	// 공격 테이블과 bool 테이블, 데미지 테이블 초기화
		virtual void InitializeAttackTable();

	// 블루프린트에서 AttackMotionBoolTable의 value를 가져오기 위한 함수
	UFUNCTION(BlueprintCallable, Category = "Attack")
		//bool GetAttackMotionBoolTable(FString AttackMotion);
		bool GetAttackMotionBoolTable(EAttackMotion AttackMotion);

	// 블루프린트에서 AttackMotionDamageTable의 value를 가져오기 위한 함수
	UFUNCTION(BlueprintCallable, Category = "Attack")
		//float GetAttackMotionDamageTable(FString AttackMotion);
		float GetAttackMotionDamageTable(EAttackMotion AttackMotion);

	// 가장 최근 실행된 공격 모션
	UPROPERTY(BlueprintReadOnly, Category = "Attack")
		//FString CurrentAttackMotion;
		EAttackMotion CurrentAttackMotion;

	// 공격 애니메이션에서 Notify 이벤트를 통해 공격 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool bAttacking;

	// 연속 공격을 위해 만든 키를 누른 후에 흐른 시간 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		float KeyClickInterval;

	// 아무 키나 누른지 0.5초가 지나지 않았을 때 true. 연속 공격을 위해 사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool bAnyKeyClicked;

	// 지금까지 들어온 입력키를 저장한 배열
	UPROPERTY()
		//TArray<EInputKey> InputKeyArray;
		TArray<FString> InputKeyArray;

	// 사용자가 누른 키를 배열에 저장 
	UFUNCTION()
		//void AddKeyToInputArray(EInputKey PressedKeyName);
		void AddKeyToInputArray(FString PressedKeyName);

	// 아무 키나 눌렀을 때 수행해야 하는 함수
	UFUNCTION()
		//void WhenAnyKeyClicked(EInputKey PressedKeyName);
		void WhenAnyKeyClicked(FString PressedKeyName);

	// 최종 공격 모션을 결정하는 함수
	UFUNCTION(BlueprintCallable, Category = "Attack")
		void DetermineAttackMotion();

	// H 키가 눌렸을 때 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "Attack")
		void WhenLeftPunchKeyClicked();

	// J 키가 눌렸을 때 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "Attack")
		void WhenRightPunchKeyClicked();

	// K키가 눌렸을 때 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "Attack")
		void WhenLeftKickKeyClicked();

	// L키가 눌렸을 때 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "Attack")
		void WhenRightKickKeyClicked();



	// Hit

	// 캐릭터가 타격을 받았을 때 true가 되는 bool 변수
	UPROPERTY()
		bool bIsHit;

	// 캐릭터가 가진 공격 패턴마다 상대의 어느 부위를 가격하는지 정의한 테이블
	UPROPERTY()
		//TMap<FString, EHitPosition> AttackMotionHitPositionTable;
		TMap<EAttackMotion, EHitPosition> AttackMotionHitPositionTable;

	// 캐릭터가 가진 공격 패턴마다 좌우 손발 중 어느 콜리전 컴포넌트로 상대를 가격하는지 기록한 테이블
	UPROPERTY()
		//TMap<FString, USphereComponent*> AttackMotionCollisionComponentTable;
		TMap<EAttackMotion, USphereComponent*> AttackMotionCollisionComponentTable;

	// 캐릭터가 어느 부위를 맞았는지 기록한 테이블 (MyCharacter에서 정의)
	UPROPERTY()
		TMap<EHitPosition, bool> HitPositionBoolTable;

	// 블루프린트에서 HitPositionBoolTable의 value를 가져오기 위한 함수
	UFUNCTION(BlueprintCallable, Category = "Hit")
		bool GetHitPositionBoolTable(EHitPosition HitPosition);

	// AttackMotionHitPositionTable과 HitPositionBoolTable을 초기화 하는 함수
		virtual void InitializeHitTable();



	// AI

	//// 캐릭터가 AI에 의해 컨트롤되고 있는지 여부
	//UPROPERTY(BlueprintReadWrite, Category = "AI")
	//	bool bIsControlledByAI;

	// AI 캐릭터 랜덤 공격 함수. 좌우 손발 4가지 키를 랜덤으로 선택해서 입력. 만약 캐릭터에 따라 재정의가 필요할 경우에만 그 캐릭터 클래스에서 재정의
	UFUNCTION()
		virtual void RandomAttack();

	// AI 캐릭터가 공격을 끝마친 후 실행되는 함수
	// 이거 나중에 없애 왜 만들었는지 모르겠음
	UFUNCTION(BlueprintCallable, Category = "AI")
		void AIStopAttack();

	FTimerHandle BetweenAttackTimerHandle;

	bool IsBetweenAttackTimerStarted;
};