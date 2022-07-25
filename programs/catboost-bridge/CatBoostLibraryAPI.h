#pragma once

#include <cstdint>
#include <string>

// Function pointer typedefs and names of CatBoost library functions used by ClickHouse
struct CatBoostLibraryAPI
{
    using ModelCalcerHandle = void;

    struct ModelCalcerCreate
    {
        using Func = ModelCalcerHandle * (*)();
        static constexpr const char * name = "ModelCalcerCreate";
    };

    struct ModelCalcerDelete
    {
        using Func = void (*)(ModelCalcerHandle *);
        static constexpr const char * name = "ModelCalcerDelete";
    };

    struct GetErrorString
    {
        using Func = const char * (*)();
        static constexpr const char * name = "GetErrorString";
    };

    struct LoadFullModelFromFile
    {
        using Func = bool (*)(ModelCalcerHandle *, const char *);
        static constexpr const char * name = "LoadFullModelFromFile";
    };

    struct CalcModelPredictionFlat
    {
        using Func = bool (*)(ModelCalcerHandle *, size_t, const float **, size_t, double *, size_t);
        static constexpr const char * name = "CalcModelPredictionFlat";
    };

    struct CalcModelPrediction
    {
        using Func = bool (*)(ModelCalcerHandle *, size_t, const float **, size_t, const char ***, size_t, double *, size_t);
        static constexpr const char * name = "CalcModelPrediction";
    };

    struct CalcModelPredictionWithHashedCatFeatures
    {
        using Func = bool (*)(ModelCalcerHandle *, size_t, const float **, size_t, const int **, size_t, double *, size_t);
        static constexpr const char * name = "CalcModelPredictionWithHashedCatFeatures";
    };

    struct GetStringCatFeatureHash
    {
        using Func = int (*)(const char *, size_t);
        static constexpr const char * name = "GetStringCatFeatureHash";
    };

    struct GetIntegerCatFeatureHash
    {
        using Func = int (*)(uint64_t);
        static constexpr const char * name = "GetIntegerCatFeatureHash";
    };

    struct GetFloatFeaturesCount
    {
        using Func = size_t (*)(ModelCalcerHandle *);
        static constexpr const char * name = "GetFloatFeaturesCount";
    };

    struct GetCatFeaturesCount
    {
        using Func = size_t (*)(ModelCalcerHandle *);
        static constexpr const char * name = "GetCatFeaturesCount";
    };

    struct GetTreeCount
    {
        using Func = size_t (*)(ModelCalcerHandle *);
        static constexpr const char * name = "GetTreeCount";
    };

    struct GetDimensionsCount
    {
        using Func = size_t (*)(ModelCalcerHandle *);
        static constexpr const char * name = "GetDimensionsCount";
    };
};
