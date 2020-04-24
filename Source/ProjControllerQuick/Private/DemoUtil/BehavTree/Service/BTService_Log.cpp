#include "BTService_Log.h"
#include "Util\Core\LogUtilLib.h"

struct FBTLogServiceNodeMemory
{
	void Reset(UBTService_Log* Owner)
	{
	}
};


UBTService_Log::UBTService_Log()
{
	NodeName = TEXT("LogService");

	bEnableTickLogging = true;
	LogTickPeriod = 10;
	MaxLogTickLogs = 10;

	DurationInSeconds = 2.0F;

	bNotifyOnSearch = true;
	//bCallTickOnSearchStart = true;
}

void UBTService_Log::PostInitProperties()
{
	Super::PostInitProperties();
	LogPrefixString = FString::Printf(TEXT("From node \"%s\": "), *NodeName);
}

void UBTService_Log::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	M_LOG(TEXT("%s: %s"), *LogPrefixString, TEXT(__FUNCTION__));
}

void UBTService_Log::OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceDestroyed(OwnerComp);
	M_LOG(TEXT("%s: %s"), *LogPrefixString, TEXT(__FUNCTION__));
}

void UBTService_Log::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	//M_LOG(TEXT("%s: %s"), *LogPrefixString, TEXT(__FUNCTION__));
}

void UBTService_Log::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);
	M_LOG(TEXT("%s: %s"), *LogPrefixString, TEXT(__FUNCTION__));
}

uint16 UBTService_Log::GetInstanceMemorySize() const
{
	return sizeof(FBTLogServiceNodeMemory);
}
