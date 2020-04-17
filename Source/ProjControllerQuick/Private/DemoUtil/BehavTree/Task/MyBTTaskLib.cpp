#include "MyBTTaskLib.h"
#include "Util\Core\LogUtilLib.h"

void UMyBTTaskLib::LogBTNodeResult(EBTNodeResult::Type NodeResult)
{
	M_LOG(TEXT("Node result: %s"), *GetBTNodeResultString(NodeResult));
}

FString UMyBTTaskLib::GetBTNodeResultString(EBTNodeResult::Type NodeResult)
{
	switch(NodeResult)
	{
	case EBTNodeResult::InProgress:
		return FString(TEXT("InProgress"));
	
	case EBTNodeResult::Succeeded:
		return FString(TEXT("Succeeded"));

	case EBTNodeResult::Failed:
		return FString(TEXT("Failed"));

	case EBTNodeResult::Aborted:
		return FString(TEXT("Aborted"));

	default:
		return FString(TEXT("UNKNOWN_CODE"));
	}
}
