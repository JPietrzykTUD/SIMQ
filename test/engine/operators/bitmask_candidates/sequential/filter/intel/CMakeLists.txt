IF(${CPROC} MATCHES "XEON")
    add_subdirectory(xeon)
ELSEIF(${CPROC} MATCHES "KNL")

ENDIF()