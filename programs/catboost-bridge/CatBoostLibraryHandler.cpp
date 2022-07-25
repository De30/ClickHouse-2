#include "CatBoostLibraryHandler.h"

#include "CatBoostLibraryAPI.h"

namespace DB
{

namespace ErrorCodes
{
    extern const int CANNOT_LOAD_CATBOOST_MODEL;
}

// TODO error handling, e.g. library path does not exist, model path does not exist etc.
// TODO apply stuff done to library-bridge also to odbc bridge

CatBoostLibraryHandler::CatBoostLibraryHandler(
    const std::string & library_path,
    const std::string & model_path)
{
    library = std::make_shared<SharedLibrary>(library_path);
    api.init(*library);

    model_calcer_handle = api.ModelCalcerCreate();

    if (!api.LoadFullModelFromFile(model_calcer_handle, model_path.c_str()))
    {
        throw Exception(ErrorCodes::CANNOT_LOAD_CATBOOST_MODEL,
                "Cannot load CatBoost model: {}", api.GetErrorString());
    }

    float_features_count = api.GetFloatFeaturesCount(model_calcer_handle);
    cat_features_count = api.GetCatFeaturesCount(model_calcer_handle);

    tree_count = 1;
    if (api.GetDimensionsCount)
        tree_count = api.GetDimensionsCount(model_calcer_handle);
}

CatBoostLibraryHandler::~CatBoostLibraryHandler()
{
    api.ModelCalcerDelete(model_calcer_handle);
}

void CatBoostLibraryHandler::evaluate()
{
    /// TODO
}

}
