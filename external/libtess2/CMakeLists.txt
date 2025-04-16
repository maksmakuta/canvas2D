add_library(tess2 STATIC
    include/libtess2/tesselator.h

    src/bucketalloc.h
    src/bucketalloc.c
    src/dict.c
    src/dict.c
    src/geom.c
    src/geom.h
    src/mesh.c
    src/mesh.h
    src/priorityq.c
    src/priorityq.h
    src/sweep.c
    src/sweep.h
    src/tess.c
    src/tess.h
)

target_include_directories(tess2 PUBLIC include)
