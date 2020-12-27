foreach(PROJECT ${PROJECTS})
    target_sources(${PROJECT} PRIVATE ${PROJECT}/Main.cpp)
endforeach()
