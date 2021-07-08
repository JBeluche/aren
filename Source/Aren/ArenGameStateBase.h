// Copyright CreatingMountains

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ArenGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class AREN_API AArenGameStateBase : public AGameStateBase
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	bool bIsNewGame = true;

	
	
};
