add_library(
        tone_domain_lib
        app_state_holder.h app_state_holder.cpp
        config.h
        i_player.h
        player.h player.cpp
        device_state.h
        device_repository.h device_repository.cpp
        logging.h logging.cpp
        recorder_i.h
        recorder.h recorder.cpp
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