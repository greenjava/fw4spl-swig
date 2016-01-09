fwLoadProperties()

fwUseForwardInclude(
    fwCore
    fwData
    fwTools
    fwRuntime
    fwServices
    fwThread
)

add_subdirectory(swig)


find_package(LibXml2)
fwInclude(
    ${LIBXML2_INCLUDE_DIR}
)
fwLink(
    ${LIBXML2_LIBRARIES} 
)