# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2020 Metrological
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set(PLUGIN_NAME GstPlugin)
set(MODULE_NAME ${NAMESPACE}${PLUGIN_NAME})

set(PLUGIN_GSTPLUGIN_AUTOSTART "true" CACHE STRING "Automatically start GstPlugin plugin")

find_package(${NAMESPACE}Plugins REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMERBASE REQUIRED gstreamer-app-1.0)

find_package(GStreamer REQUIRED)

add_library(${MODULE_NAME} SHARED  
    lib.cpp
    GstPlugin.cpp 
    Module.cpp )

set_target_properties(${MODULE_NAME} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES)

target_include_directories(${MODULE_NAME} PRIVATE ./)
target_include_directories(${MODULE_NAME} PRIVATE ../include)
target_include_directories(${MODULE_NAME} PRIVATE ../../helpers)
target_include_directories(${MODULE_NAME} PRIVATE ${GSTREAMER_INCLUDES})
target_include_directories(${MODULE_NAME} PRIVATE ${GSTREAMERBASE_INCLUDE_DIRS})
      
target_link_libraries(${MODULE_NAME} PRIVATE ${NAMESPACE}Plugins::${NAMESPACE}Plugins)
target_link_libraries(${MODULE_NAME} PRIVATE ${GSTREAMER_LIBRARIES})
target_link_libraries(${MODULE_NAME} PRIVATE ${GSTREAMERBASE_LIBRARIES})
        
install(TARGETS ${MODULE_NAME}
    DESTINATION lib/${STORAGE_DIRECTORY}/plugins)

write_config(PLUGINS ${PLUGIN_NAME} CLASSNAME ${PLUGIN_NAME})