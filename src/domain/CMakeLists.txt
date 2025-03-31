add_library(
        tone_domain_lib
        #DefaultRecorder.h DefaultRecorder.cpp
        Player.h Player.cpp
        DeviceState.h
        DeviceFacade.h DeviceFacade.cpp
        logging.h logging.cpp
)

target_include_directories(
        tone_domain_lib
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}
        PRIVATE ${MINIAUDIO_INCLUDE_DIRS}
)

target_link_libraries(
        tone_domain_lib
        PRIVATE Boost::uuid
)