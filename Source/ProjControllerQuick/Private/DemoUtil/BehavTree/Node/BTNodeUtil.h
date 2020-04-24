#pragma once

#include "BehaviorTree/BehaviorTreeTypes.h"

FString GetMemoryInitTypeString(EBTMemoryInit::Type InitType);

FString GetMemoryClearTypeString(EBTMemoryClear::Type InitType);

void LogMemoryInitType(const FString& PrefixString, EBTMemoryInit::Type InitType);

void LogMemoryClearType(const FString& PrefixString, EBTMemoryClear::Type InitType);

void LogMemoryInitType(const TCHAR* PrefixString, EBTMemoryInit::Type InitType);

void LogMemoryClearType(const TCHAR* PrefixString, EBTMemoryClear::Type InitType);
