# basic source code CMakeLists.txt


art_make(BASENAME_ONLY
	LIBRARY_NAME TPCNeutrinoIDFilter
	LIB_LIBRARIES
		     lardataobj_RecoBase
		     lardataobj_AnalysisBase
		     larcore_Geometry
		     larcore_Geometry_Geometry_service
		     lardata_Utilities
		     art_Persistency_Common canvas
		     art_Persistency_Provenance canvas
		     ${ART_FRAMEWORK_CORE}
		     ${ART_FRAMEWORK_PRINCIPAL}
		     ${ART_FRAMEWORK_SERVICES_REGISTRY}
		     ${ART_FRAMEWORK_SERVICES_OPTIONAL}
		     ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
		     ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILEDIRECTORY_SERVICE}
		     art_Utilities canvas
		     ${MF_MESSAGELOGGER}
		     ${MF_UTILITIES}
		     ${FHICLCPP}
		     cetlib cetlib_except
		     ${ROOT_BASIC_LIB_LIST}
		     ${Boost_SYSTEM_LIBRARY}
	MODULE_LIBRARIES
             TPCNeutrinoIDAlgs
		     lardataobj_RecoBase
		     lardataobj_AnalysisBase
		     larcore_Geometry
		     larcore_Geometry_Geometry_service
		     lardata_Utilities
		     art_Persistency_Common canvas
		     art_Persistency_Provenance canvas
		     ${ART_FRAMEWORK_CORE}
		     ${ART_FRAMEWORK_PRINCIPAL}
		     ${ART_FRAMEWORK_SERVICES_REGISTRY}
		     ${ART_FRAMEWORK_SERVICES_OPTIONAL}
		     ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
		     ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILEDIRECTORY_SERVICE}
		     art_Utilities canvas
		     ${MF_MESSAGELOGGER}
		     ${MF_UTILITIES}
		     ${FHICLCPP}
		     cetlib cetlib_except
		     ${ROOT_BASIC_LIB_LIST}
		     ${Boost_SYSTEM_LIBRARY}
         )

add_subdirectory(Algorithms)

install_headers()
install_source()
install_fhicl()
