#include "BTTask_Log.h"
#include "Util\Core\LogUtilLib.h"

#include "DemoUtil\BehavTree\Task\MyBTTaskLib.h"

struct FBTLogTaskMemory
{
	int32 TickIndex = 0;
	float SecondsSinceExecuted = 0.0F;
	int32 CountLogs = 0;

	void Reset()
	{
		TickIndex = 0;
		SecondsSinceExecuted = 0.0F;
		CountLogs = 0;
	}
};

UBTTask_Log::UBTTask_Log()
{
	NodeName = "LogTest";

	bEnableTickLogging = true;
	LogTickPeriod = 10;
	MaxLogTickLogs = 10;

	DurationInSeconds = 2.0F;
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Log::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	LogTaskFunc(OwnerComp, TEXT(__FUNCTION__));
	const auto MyMem = CastInstanceNodeMemory<FBTLogTaskMemory>(NodeMemory);
	MyMem->Reset();
	if(DurationInSeconds <= 0)
	{
		M_LOG(TEXT("Duration in seconds is zero, executing as an instance action"));
		return EBTNodeResult::Type::Succeeded;
	}
	else
	{
		M_LOG(TEXT("Duration in seconds is greater than zero, executing as latent task"));
		return EBTNodeResult::Type::InProgress;
	}
}

EBTNodeResult::Type UBTTask_Log::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	LogTaskFunc(OwnerComp, TEXT(__FUNCTION__));
	return EBTNodeResult::Type::Aborted;
}

void UBTTask_Log::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto MyMem = CastInstanceNodeMemory<FBTLogTaskMemory>(NodeMemory);
	LogTickIfShould(OwnerComp, MyMem);

	MyMem->TickIndex++;
	MyMem->SecondsSinceExecuted += DeltaSeconds;

	if(MyMem->SecondsSinceExecuted >= DurationInSeconds)
	{
		M_LOG(TEXT("Finishing latent task using FinishLatentTask because of execution time limit (limit is %f seconds)"), DurationInSeconds);
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
	}
}

uint16 UBTTask_Log::GetInstanceMemorySize() const
{
	return sizeof(FBTLogTaskMemory); 
}

void UBTTask_Log::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	LogTaskFunc(OwnerComp, TEXT(__FUNCTION__));
	LogTaskResult(TaskResult, TEXT(__FUNCTION__));
}

void UBTTask_Log::OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestId, bool bSuccess)
{
	LogTaskFunc(OwnerComp, TEXT(__FUNCTION__));
	M_LOG(TEXT("Message=\"%s\", RequiestId=%d, bSuccess=%s"), *Message.ToString(), RequestId, bSuccess ? TEXT("YES") : TEXT("no"));
	Super::OnMessage(OwnerComp, NodeMemory, Message, RequestId, bSuccess);
}

void UBTTask_Log::LogTickIfShould(UBehaviorTreeComponent& OwnerComp, FBTLogTaskMemory* NodeMemory)
{
	if( !bEnableTickLogging )
	{
		return;
	}

	if((MaxLogTickLogs != 0) && (MaxLogTickLogs <= NodeMemory->CountLogs))
	{
		return;
	}

	if(NodeMemory->TickIndex % LogTickPeriod != 0)
	{
		return;
	}

	LogTaskFunc(OwnerComp, TEXT("Logging tick"));
	M_LOG(TEXT("TickIndex: %d"), NodeMemory->TickIndex);
	M_LOG(TEXT("SecondsSinceExecuted: %f"), NodeMemory->SecondsSinceExecuted);
	NodeMemory->CountLogs++;
}
	
void UBTTask_Log::LogTaskFunc(UBehaviorTreeComponent& OwnerComp, TCHAR* SenderFunction)
{
	M_LOG(TEXT("Function \"%s\" on component \"%s\" of class \"%s\""), SenderFunction, *OwnerComp.GetName(), *OwnerComp.GetClass()->GetName());
}

void UBTTask_Log::LogTaskResult(EBTNodeResult::Type TaskResult, TCHAR* SenderFunction)
{
	UMyBTTaskLib::LogBTNodeResult(TaskResult);
}
