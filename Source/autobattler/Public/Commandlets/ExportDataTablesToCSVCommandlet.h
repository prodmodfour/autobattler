#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "ExportDataTablesToCSVCommandlet.generated.h"

UCLASS()
class UExportDataTablesToCSVCommandlet : public UCommandlet
{
    GENERATED_BODY()

public:
    virtual int32 Main(const FString& Params) override;
};