// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "TouchPointer.generated.h"


class UTouchPointer;


/**
 * Turns an actor into a touch pointer.
 * Touch pointers keep track of all overlapping touch targets and raise hover events on the closest one.
 * Touch targets use the transform of touch pointers hovering them to drive their interactions.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MIXEDREALITYUTILS_API UTouchPointer : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTouchPointer();

	UFUNCTION(BlueprintSetter)
	void SetTouchRadius(float radius);

	UFUNCTION(BlueprintGetter)
	float GetTouchRadius() const;

	/** 
	 * Returns currently hovered touch target or null if there is none. 
	 * The closest point on the target surface is stored in OutClosestPointOnTarget.
	 */
	UFUNCTION(BlueprintCallable, Category = "Touch Pointer")
	UActorComponent* GetHoveredTarget(FVector& OutClosestPointOnTarget) const;

	/** Returns whether the pointer is locked on the currently hovered target. */
	UFUNCTION(BlueprintGetter)
	bool GetHoverLocked() const;

	/** Sets whether the pointer is locked on the currently hovered target. */
	UFUNCTION(BlueprintSetter)
	void SetHoverLocked(bool Value);

	UFUNCTION(BlueprintGetter)
	bool GetGrasped() const;

	UFUNCTION(BlueprintSetter)
	void SetGrasped(bool Enable);

protected:

	// 
	// UActorComponent interface

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	/** Weak reference to the currently hovered target. */
	TWeakObjectPtr<UActorComponent> HoveredTargetWeak;

	/** Closest point on the surface of the hovered target. */
	FVector ClosestPointOnHoveredTarget;

private:

	/**
	 * Whether the pointer is locked on its current hovered target.
	 * When locked, pointers won't change their hovered target even if they stop overlapping it.
	 */
	UPROPERTY(BlueprintGetter = "GetHoverLocked", BlueprintSetter = "SetHoverLocked", Category = "Touch Pointer")
	bool bHoverLocked;

	UPROPERTY(BlueprintGetter = "GetGrasped", BlueprintSetter = "SetGrasped", Category = "Touch Pointer")
	bool bIsGrasped;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Touch Pointer", meta = (AllowPrivateAccess = "true"))
	USphereComponent *TouchSphere;

	UPROPERTY(EditAnywhere, BlueprintSetter = "SetTouchRadius", BlueprintGetter = "GetTouchRadius", Category = "Touch Pointer")
	float TouchRadius;
};