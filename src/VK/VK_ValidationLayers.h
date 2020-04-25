#include "vector"
#include "vulkan/vulkan.h"
class VK_ValidationLayers {
    const VkInstance* vk_instance;
    VkDebugUtilsMessengerCreateInfoEXT create_info{};
    VkDebugUtilsMessengerEXT debug_messenger;

    std::vector<const char*> validation_layers={
            "VK_LAYER_KHRONOS_validation"
    };
    bool checkForSupport();
public:
    VK_ValidationLayers();

    ~VK_ValidationLayers();
    void init(const VkInstance& vk_instance);
    const VkDebugUtilsMessengerCreateInfoEXT& getCreateInfo();
    const char** getValidationLayersNames();
    uint32_t getCount();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);

};
