#include "BTTask_SetBBKey.h"
#include "Util/Core/LogUtilLib.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Name.h"

EBTNodeResult::Type UBTTask_SetBBKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Name>(BlackboardKey.GetSelectedKeyID(), NewNameValue);
	check(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Name>(BlackboardKey.GetSelectedKeyID()) == NewNameValue);
	return EBTNodeResult::Type::Succeeded;
}
