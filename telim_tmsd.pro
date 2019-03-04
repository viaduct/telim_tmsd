TEMPLATE = lib
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += object_parallel_to_source

SOURCES += manager.cpp \
    item_type.cpp \
    item_rtti.cpp \
    member_id.cpp \
    value_type.cpp \
    value_type.tpp \
    value_alias.cpp \
    obj_type.cpp \
    item.cpp \
    obj.cpp \
    value.cpp \
    value.tpp \
    manager.tpp \
    track_id.cpp \
    value_set_event.cpp \
    value_event.cpp \
    value_event.tpp \
    value_set_event.tpp \
    value_subject.cpp \
    value_subject.tpp \
    single_event.cpp \
    single_valid_set_event.cpp \
    single_null_set_event.cpp \
    cont.cpp \
    single.cpp \
    set.cpp \
    set_event.cpp \
    set_add_event.cpp \
    set_remove_event.cpp \
    set_clear_event.cpp \
    list.cpp \
    list_event.cpp \
    list_add_event.cpp \
    list_remove_event.cpp \
    list_clear_event.cpp \
    list_move_event.cpp \
    ptr_comp.cpp \
    obj_subject.cpp \
    item_event.cpp \
    item_subject.cpp \
    obj_track.cpp \
    cont_track.cpp \
    single_track.cpp \
    item_track.cpp \
    value_track.cpp \
    value_track.tpp \
    set_track.cpp \
    list_track.cpp \
    mimicry_info.cpp \
#    comps/item.cpp \
#    comps/bundle.cpp \
#    comps/no_matching_item_error.cpp \
#    comps/composer.cpp \
    item_track_info.cpp \
    obj_track_info.cpp \
    cont_track_info.cpp \
    track.cpp \
    track_info.cpp \
    mimic.cpp \
    item_mimic.cpp \
    value_mimic.cpp \
    value_mimic.tpp \
    obj_mimic.cpp \
    cont_mimic.cpp \
    single_mimic.cpp \
    set_mimic.cpp \
    list_mimic.cpp \
    cont_event.cpp \
    stop_refer_info.cpp \
    value_stop_refer_info.cpp \
    obj_stop_refer_info.cpp \
    cont_stop_refer_info.cpp \
    single_stop_refer_info.cpp \
    set_stop_refer_info.cpp \
    list_stop_refer_info.cpp \
    single_track_info.cpp \
    set_track_info.cpp \
    list_track_info.cpp \
    value_track_info.cpp \
    cont_type.cpp \
    single_type.cpp \
    set_type.cpp \
    list_type.cpp \
    chain.cpp \
    value_track_info.tpp

HEADERS += \
    manager.h \
    item_type.h \
    item_rtti.h \
    member_id.h \
    value_type.h \
    value_alias.h \
    obj_type.h \
    item.h \
    obj.h \
    value.h \
    track_id.h \
    value_set_event.h \
    value_event.h \
    value_subject.h \
    single_event.h \
    single_valid_set_event.h \
    single_null_set_event.h \
    cont.h \
    single.h \
    set.h \
    set_event.h \
    set_add_event.h \
    set_remove_event.h \
    set_clear_event.h \
    list.h \
    list_event.h \
    list_add_event.h \
    list_remove_event.h \
    list_clear_event.h \
    list_move_event.h \
    ptr_comp.h \
    obj_subject.h \
    item_event.h \
    item_subject.h \
    obj_track.h \
    cont_track.h \
    single_track.h \
    item_track.h \
    value_track.h \
    set_track.h \
    list_track.h \
    mimicry_info.h \
#    comps/item.h \
#    comps/bundle.h \
#    comps/no_matching_item_error.h \
#    comps/composer.h \
    item_track_info.h \
    obj_track_info.h \
    cont_track_info.h \
    track.h \
    track_info.h \
    mimic.h \
    item_mimic.h \
    value_mimic.h \
    obj_mimic.h \
    cont_mimic.h \
    single_mimic.h \
    set_mimic.h \
    list_mimic.h \
    cont_event.h \
    stop_refer_info.h \
    value_stop_refer_info.h \
    obj_stop_refer_info.h \
    cont_stop_refer_info.h \
    single_stop_refer_info.h \
    set_stop_refer_info.h \
    list_stop_refer_info.h \
    single_track_info.h \
    set_track_info.h \
    list_track_info.h \
    value_track_info.h \
    cont_type.h \
    single_type.h \
    set_type.h \
    list_type.h \
    chain.h
