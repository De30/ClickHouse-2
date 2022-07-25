#pragma once

#include <Common/SharedLibrary.h>
#include <Common/logger_useful.h>

#include "CatBoostLibraryAPI.h"

namespace DB
{

/// Abstracts access to CatBoost library.
class CatBoostLibraryHandler
{
    /// Holds pointers to CatBoost library functions
    struct APIHolder
    {
        void init(SharedLibrary & lib)
        {
            ModelCalcerCreate = lib.get<CatBoostLibraryAPI::ModelCalcerCreate::Func>(CatBoostLibraryAPI::ModelCalcerCreate::name);
            ModelCalcerDelete = lib.get<CatBoostLibraryAPI::ModelCalcerDelete::Func>(CatBoostLibraryAPI::ModelCalcerDelete::name);
            GetErrorString = lib.get<CatBoostLibraryAPI::GetErrorString::Func>(CatBoostLibraryAPI::GetErrorString::name);
            LoadFullModelFromFile = lib.get<CatBoostLibraryAPI::LoadFullModelFromFile::Func>(CatBoostLibraryAPI::LoadFullModelFromFile::name);
            CalcModelPredictionFlat = lib.get<CatBoostLibraryAPI::CalcModelPredictionFlat::Func>(CatBoostLibraryAPI::CalcModelPredictionFlat::name);
            CalcModelPrediction = lib.get<CatBoostLibraryAPI::CalcModelPrediction::Func>(CatBoostLibraryAPI::CalcModelPrediction::name);
            CalcModelPredictionWithHashedCatFeatures = lib.get<CatBoostLibraryAPI::CalcModelPredictionWithHashedCatFeatures::Func>(CatBoostLibraryAPI::CalcModelPredictionWithHashedCatFeatures::name);
            GetStringCatFeatureHash = lib.get<CatBoostLibraryAPI::GetStringCatFeatureHash::Func>(CatBoostLibraryAPI::GetStringCatFeatureHash::name);
            GetIntegerCatFeatureHash = lib.get<CatBoostLibraryAPI::GetIntegerCatFeatureHash::Func>(CatBoostLibraryAPI::GetIntegerCatFeatureHash::name);
            GetFloatFeaturesCount = lib.get<CatBoostLibraryAPI::GetFloatFeaturesCount::Func>(CatBoostLibraryAPI::GetFloatFeaturesCount::name);
            GetCatFeaturesCount = lib.get<CatBoostLibraryAPI::GetCatFeaturesCount::Func>(CatBoostLibraryAPI::GetCatFeaturesCount::name);
            GetTreeCount = lib.tryGet<CatBoostLibraryAPI::GetTreeCount::Func>(CatBoostLibraryAPI::GetTreeCount::name);
            GetDimensionsCount = lib.tryGet<CatBoostLibraryAPI::GetDimensionsCount::Func>(CatBoostLibraryAPI::GetDimensionsCount::name);
        }

        CatBoostLibraryAPI::ModelCalcerCreate::Func ModelCalcerCreate; // NOLINT
        CatBoostLibraryAPI::ModelCalcerDelete::Func ModelCalcerDelete; // NOLINT
        CatBoostLibraryAPI::GetErrorString::Func GetErrorString; // NOLINT
        CatBoostLibraryAPI::LoadFullModelFromFile::Func LoadFullModelFromFile; // NOLINT
        CatBoostLibraryAPI::CalcModelPredictionFlat::Func CalcModelPredictionFlat; // NOLINT
        CatBoostLibraryAPI::CalcModelPrediction::Func CalcModelPrediction; // NOLINT
        CatBoostLibraryAPI::CalcModelPredictionWithHashedCatFeatures::Func CalcModelPredictionWithHashedCatFeatures; // NOLINT
        CatBoostLibraryAPI::GetStringCatFeatureHash::Func GetStringCatFeatureHash; // NOLINT
        CatBoostLibraryAPI::GetIntegerCatFeatureHash::Func GetIntegerCatFeatureHash; // NOLINT
        CatBoostLibraryAPI::GetFloatFeaturesCount::Func GetFloatFeaturesCount; // NOLINT
        CatBoostLibraryAPI::GetCatFeaturesCount::Func GetCatFeaturesCount; // NOLINT
        CatBoostLibraryAPI::GetTreeCount::Func GetTreeCount; // NOLINT
        CatBoostLibraryAPI::GetDimensionsCount::Func GetDimensionsCount; // NOLINT
    };

public:
    CatBoostLibraryHandler(
        const std::string & library_path,
        const std::string & model_path);

    ~CatBoostLibraryHandler();

    void evaluate();

private:
    SharedLibraryPtr library;
    APIHolder api;
    CatBoostLibraryAPI::ModelCalcerHandle * model_calcer_handle;

    size_t float_features_count;
    size_t cat_features_count;
    size_t tree_count;
};

using CatBoostLibraryHandlerPtr = std::shared_ptr<CatBoostLibraryHandler>;

}
