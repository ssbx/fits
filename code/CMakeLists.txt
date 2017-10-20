add_library(fits
        fitsbody.c
        fitscat.c
        fitscat.h
        fitscat_defs.h
        fitscheck.c
        fitscleanup.c
        fitsconv.c
        fitshead.c
        fitskey.c
        fitsmisc.c
        fitsread.c
        fitstab.c
        fitsutil.c
        fitswrite.c)

set (FITS_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "fits includes")
set (FITS_LIBRARIES fits CACHE STRING "fits lib")

target_link_libraries(fits -lm)
