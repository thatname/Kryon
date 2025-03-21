
cmake_minimum_required(VERSION 3.15)
project(RHI VERSION 0.1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 收集所有头文件
set(RHI_HEADERS
    Result.h
    SwapChain.h
    Texture.h
    Buffer.h
    CommandBuffer.h
    CommandPool.h
    Memory.h
    Pipeline.h
    Shader.h
    Descriptor.h
    Synchronization.h
    Adapter.h
    Device.h
    Format.h
)

# 创建接口库
add_library(RHI INTERFACE)

# 设置目标属性
target_sources(RHI
    INTERFACE
        ${RHI_HEADERS}
)

# 设置包含目录
target_include_directories(RHI
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

# 导出目标
install(TARGETS RHI
    EXPORT RHITargets
    INCLUDES DESTINATION include
)

# 安装头文件
install(FILES ${RHI_HEADERS}
    DESTINATION include/RHI
)

# 生成并安装配置文件
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "RHIConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(EXPORT RHITargets
    FILE RHITargets.cmake
    NAMESPACE RHI::
    DESTINATION lib/cmake/RHI
)

configure_file(cmake/RHIConfig.cmake.in
    "${PROJECT_BINARY_DIR}/RHIConfig.cmake"
    @ONLY
)

install(FILES
    "${PROJECT_BINARY_DIR}/RHIConfig.cmake"
    "${PROJECT_BINARY_DIR}/RHIConfigVersion.cmake"
    DESTINATION lib/cmake/RHI
)

# 添加示例和测试的选项
option(RHI_BUILD_EXAMPLES "Build RHI examples" OFF)
option(RHI_BUILD_TESTS "Build RHI tests" OFF)

if(RHI_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(RHI_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
