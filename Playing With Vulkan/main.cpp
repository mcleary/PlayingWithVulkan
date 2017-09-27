//
//  main.cpp
//  Playing With Vulkan
//
//  Created by Thales Sabino on 27/09/2017.
//  Copyright © 2017 Thales Sabino. All rights reserved.
//

#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>

#define VK_RESULT_CHECK(result) \
    if(result != VK_SUCCESS) { \
        std::cerr << "Error: Line " << __LINE__ << std::endl; \
        std::cerr << #result << std::endl; \
        exit(1); \
    }

template<typename KeyType, typename ValueType>
void PrintKeyValuePair(KeyType key, ValueType value)
{
    std::cout << key << " : " << value << std::endl;
}

int main(int argc, const char * argv[])
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Playing with Vulkan";
    appInfo.apiVersion = VK_MAKE_VERSION(0, 1, 0);
    
    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    
    VkInstance instance;
    VK_RESULT_CHECK(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));
    
    uint32_t physicalDeviceCount = 0;
    VK_RESULT_CHECK(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr));
    
    if(physicalDeviceCount <= 0)
    {
        std::cout << "No physical device available" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::vector<VkPhysicalDevice> physicalDevices{ physicalDeviceCount };
    VK_RESULT_CHECK(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data()));
    
    for(const auto& physicalDevice : physicalDevices)
    {
        VkPhysicalDeviceProperties props = {};
        vkGetPhysicalDeviceProperties(physicalDevice, &props);
        
        PrintKeyValuePair("Device Name", props.deviceName);
    }
    
    return EXIT_SUCCESS;
}
