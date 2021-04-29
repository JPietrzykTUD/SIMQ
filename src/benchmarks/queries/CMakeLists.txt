IF (${CPLATFORM} MATCHES "INTEL")
    add_subdirectory(q11)
    add_subdirectory(q12)
ENDIF ()