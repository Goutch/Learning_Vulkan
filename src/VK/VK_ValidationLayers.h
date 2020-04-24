#include "vector"
class VK_ValidationLayers {
    std::vector<const char*> validation_layers={
            "VK_LAYER_KRONOS_validation"
    };
    bool checkForSupport();
public:
    VK_ValidationLayers();
    char** getValidationLayersNames();
};
