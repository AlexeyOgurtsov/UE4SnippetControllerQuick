#include "BTNodeUtil.h"
#include "Util\Core\LogUtilLib.h"

FString GetMemoryInitTypeString(EBTMemoryInit::Type InitType)
{
	switch(InitType)
	{
	case EBTMemoryInit::Type::Initialize:
		return FString(TEXT("Initialize"));
	case EBTMemoryInit::Type::RestoreSubtree:
		return FString(TEXT("RestoreSubtree"));
	default:
		break;
	}
	return FString(TEXT("Unknown"));
}

FString GetMemoryClearTypeString(EBTMemoryClear::Type InitType)
{
	switch(InitType)
	{
	case EBTMemoryClear::Type::Destroy:
		return FString(TEXT("Destroy"));
	case EBTMemoryClear::Type::StoreSubtree:
		return FString(TEXT("StoreSubtree"));
	default:
		break;
	}
	return FString(TEXT("Unknown"));
}

void LogMemoryInitType(const FString& PrefixString, EBTMemoryInit::Type InitType)
{
	LogMemoryInitType(*PrefixString, InitType);
}

void LogMemoryClearType(const FString& PrefixString, EBTMemoryClear::Type InitType)
{
	LogMemoryClearType(*PrefixString, InitType);
}

void LogMemoryInitType(const TCHAR* PrefixString, EBTMemoryInit::Type InitType)
{
	M_LOG(TEXT("%s: %s"), PrefixString, *GetMemoryInitTypeString(InitType));
}

void LogMemoryClearType(const TCHAR* PrefixString, EBTMemoryClear::Type InitType)
{
	M_LOG(TEXT("%s: %s"), PrefixString, *GetMemoryClearTypeString(InitType));
}
