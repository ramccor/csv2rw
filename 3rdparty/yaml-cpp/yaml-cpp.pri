DEPENDPATH += $$PWD

QT +=
!build_xlsx_lib:DEFINES += XLSX_NO_LIB

INCLUDEPATH += \
    $$PWD/src \
    $$PWD/include
	
HEADERS += \
    $$PWD/include/yaml-cpp/anchor.h \
    $$PWD/include/yaml-cpp/binary.h \
    $$PWD/include/yaml-cpp/dll.h \
    $$PWD/include/yaml-cpp/emitfromevents.h \
    $$PWD/include/yaml-cpp/emitter.h \
    $$PWD/include/yaml-cpp/emitterdef.h \
    $$PWD/include/yaml-cpp/emittermanip.h \
    $$PWD/include/yaml-cpp/emitterstyle.h \
    $$PWD/include/yaml-cpp/eventhandler.h \
    $$PWD/include/yaml-cpp/exceptions.h \
    $$PWD/include/yaml-cpp/mark.h \
    $$PWD/include/yaml-cpp/null.h \
    $$PWD/include/yaml-cpp/ostream_wrapper.h \
    $$PWD/include/yaml-cpp/parser.h \
    $$PWD/include/yaml-cpp/stlemitter.h \
    $$PWD/include/yaml-cpp/traits.h \
    $$PWD/include/yaml-cpp/yaml.h \
    $$PWD/include/yaml-cpp/contrib/anchordict.h \
    $$PWD/include/yaml-cpp/contrib/graphbuilder.h \
    $$PWD/include/yaml-cpp/node/convert.h \
    $$PWD/include/yaml-cpp/node/emit.h \
    $$PWD/include/yaml-cpp/node/impl.h \
    $$PWD/include/yaml-cpp/node/iterator.h \
    $$PWD/include/yaml-cpp/node/node.h \
    $$PWD/include/yaml-cpp/node/parse.h \
    $$PWD/include/yaml-cpp/node/ptr.h \
    $$PWD/include/yaml-cpp/node/type.h \
    $$PWD/include/yaml-cpp/node/detail/impl.h \
    $$PWD/include/yaml-cpp/node/detail/iterator.h \
    $$PWD/include/yaml-cpp/node/detail/iterator_fwd.h \
    $$PWD/include/yaml-cpp/node/detail/memory.h \
    $$PWD/include/yaml-cpp/node/detail/node.h \
    $$PWD/include/yaml-cpp/node/detail/node_data.h \
    $$PWD/include/yaml-cpp/node/detail/node_iterator.h \
    $$PWD/include/yaml-cpp/node/detail/node_ref.h \
    $$PWD/src/collectionstack.h \
    $$PWD/src/directives.h \
    $$PWD/src/emitterstate.h \
    $$PWD/src/emitterutils.h \
    $$PWD/src/exp.h \
    $$PWD/src/indentation.h \
    $$PWD/src/nodebuilder.h \
    $$PWD/src/nodeevents.h \
    $$PWD/src/ptr_vector.h \
    $$PWD/src/regex_yaml.h \
    $$PWD/src/regeximpl.h \
    $$PWD/src/scanner.h \
    $$PWD/src/scanscalar.h \
    $$PWD/src/scantag.h \
    $$PWD/src/setting.h \
    $$PWD/src/singledocparser.h \
    $$PWD/src/stream.h \
    $$PWD/src/streamcharsource.h \
    $$PWD/src/stringsource.h \
    $$PWD/src/tag.h \
    $$PWD/src/token.h

SOURCES += \
    $$PWD/src/binary.cpp \
    $$PWD/src/convert.cpp \
    $$PWD/src/directives.cpp \
    $$PWD/src/emit.cpp \
    $$PWD/src/emitfromevents.cpp \
    $$PWD/src/emitter.cpp \
    $$PWD/src/emitterstate.cpp \
    $$PWD/src/emitterutils.cpp \
    $$PWD/src/exceptions.cpp \
    $$PWD/src/exp.cpp \
    $$PWD/src/memory.cpp \
    $$PWD/src/node.cpp \
    $$PWD/src/node_data.cpp \
    $$PWD/src/nodebuilder.cpp \
    $$PWD/src/nodeevents.cpp \
    $$PWD/src/null.cpp \
    $$PWD/src/ostream_wrapper.cpp \
    $$PWD/src/parse.cpp \
    $$PWD/src/parser.cpp \
    $$PWD/src/regex_yaml.cpp \
    $$PWD/src/scanner.cpp \
    $$PWD/src/scanscalar.cpp \
    $$PWD/src/scantag.cpp \
    $$PWD/src/scantoken.cpp \
    $$PWD/src/simplekey.cpp \
    $$PWD/src/singledocparser.cpp \
    $$PWD/src/stream.cpp \
    $$PWD/src/tag.cpp
