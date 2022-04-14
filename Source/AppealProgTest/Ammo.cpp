

#include "Ammo.h"
#include "AppealChar.h"

// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAmmo::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor)
	{
		AAppealChar* CharCast = Cast<AAppealChar>(OtherActor);

		CharCast->ammo += ammoValue;
		Destroy();
	}
}


