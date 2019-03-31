TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    StateNode.cpp \
    PuzzleSolver.cpp \
    nvwa/bool_array.cpp \
    nvwa/debug_new.cpp \
    nvwa/file_line_reader.cpp \
    nvwa/mem_pool_base.cpp \
    nvwa/mmap_reader_base.cpp \
    nvwa/static_mem_pool.cpp

HEADERS += \
    StateNode.h \
    PuzzleSolver.h \
    nvwa/bool_array.h \
    nvwa/c++11.h \
    nvwa/c++_features.h \
    nvwa/class_level_lock.h \
    nvwa/cont_ptr_utils.h \
    nvwa/debug_new.h \
    nvwa/fast_mutex.h \
    nvwa/fc_queue.h \
    nvwa/file_line_reader.h \
    nvwa/fixed_mem_pool.h \
    nvwa/functional.h \
    nvwa/istream_line_reader.h \
    nvwa/mem_pool_base.h \
    nvwa/mmap_byte_reader.h \
    nvwa/mmap_line_reader.h \
    nvwa/mmap_line_view.h \
    nvwa/mmap_reader_base.h \
    nvwa/_nvwa.h \
    nvwa/object_level_lock.h \
    nvwa/pctimer.h \
    nvwa/set_assign.h \
    nvwa/split.h \
    nvwa/static_assert.h \
    nvwa/static_mem_pool.h \
    nvwa/tree.h

