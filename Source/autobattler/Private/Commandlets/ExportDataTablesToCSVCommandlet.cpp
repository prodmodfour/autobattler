#include "Commandlets/ExportDataTablesToCSVCommandlet.h"
#include "Engine/DataTable.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "UObject/UObjectIterator.h"

int32 UExportDataTablesToCSVCommandlet::Main(const FString& Params)
{
    UE_LOG(LogTemp, Display, TEXT("--- Running ExportDataTablesToCSV Commandlet ---"));

    // Load the asset registry module
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

    // Force a synchronous scan of the entire /Game/ directory.
    UE_LOG(LogTemp, Display, TEXT("Scanning /Game/ path for assets..."));
    TArray<FString> PathsToScan;
    PathsToScan.Add(TEXT("/Game"));
    AssetRegistry.ScanPathsSynchronous(PathsToScan, true);

    // Now, get all assets specifically of the UDataTable class.
    TArray<FAssetData> DataTableAssets;
    FARFilter Filter;
    Filter.ClassPaths.Add(UDataTable::StaticClass()->GetClassPathName());
    Filter.PackagePaths.Add(TEXT("/Game"));
    Filter.bRecursivePaths = true;
    AssetRegistry.GetAssets(Filter, DataTableAssets);

    UE_LOG(LogTemp, Display, TEXT("Found %d Data Table assets after filtering."), DataTableAssets.Num());

    if (DataTableAssets.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No UDataTable assets were found in /Game/. Please ensure your Data Tables are saved in the Content folder."));
        return 0; // Exit gracefully
    }

    int32 ExportedCount = 0;
    for (const FAssetData& Asset : DataTableAssets)
    {
        UE_LOG(LogTemp, Log, TEXT("Processing Asset: %s"), *Asset.AssetName.ToString());

        // Use GetAsset() to load the UObject from the FAssetData
        UObject* LoadedObject = Asset.GetAsset();
        if (!LoadedObject)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load asset: %s"), *Asset.GetObjectPathString());
            continue;
        }

        UDataTable* DataTable = Cast<UDataTable>(LoadedObject);
        if (DataTable)
        {
            FString CSVString = DataTable->GetTableAsCSV();
            FString OutputPath = FPaths::ProjectContentDir() + TEXT("DataTablesAsCSV/");
            FString FileName = DataTable->GetName() + TEXT(".csv");
            FString FullPath = OutputPath + FileName;

            // Ensure the output directory exists
            IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
            if (!PlatformFile.DirectoryExists(*OutputPath))
            {
                PlatformFile.CreateDirectory(*OutputPath);
                UE_LOG(LogTemp, Log, TEXT("Created output directory: %s"), *OutputPath);
            }

            if (FFileHelper::SaveStringToFile(CSVString, *FullPath))
            {
                UE_LOG(LogTemp, Log, TEXT("SUCCESS: Exported '%s' to '%s'"), *DataTable->GetName(), *FullPath);
                ExportedCount++;
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("FAILURE: Could not save file for '%s'"), *DataTable->GetName());
            }
        }
        else
        {
             UE_LOG(LogTemp, Warning, TEXT("Asset '%s' could not be cast to UDataTable."), *Asset.AssetName.ToString());
        }
    }

    UE_LOG(LogTemp, Display, TEXT("--- Commandlet Finished: Exported %d out of %d Data Tables. ---"), ExportedCount, DataTableAssets.Num());
    return 0;
}