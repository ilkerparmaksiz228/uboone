art_make( BASENAME_ONLY
          MODULE_LIBRARIES
                        lardata_Utilities
                        larevt_Filters
                        lardataobj_RawData
			larcoreobj_SummaryData
			${UB_DATA_TYPES}
			${Boost_SERIALIZATION_LIBRARY}
                        nutools_RandomUtils_NuRandomService_service
                        ${ART_FRAMEWORK_CORE}
                        ${ART_FRAMEWORK_PRINCIPAL}
                        ${ART_FRAMEWORK_SERVICES_REGISTRY}
                        ${ART_FRAMEWORK_SERVICES_OPTIONAL}
                        ${ART_FRAMEWORK_SERVICES_OPTIONAL_RANDOMNUMBERGENERATOR_SERVICE}
                        ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
                        art_Persistency_Common canvas
                        art_Persistency_Provenance canvas
                        art_Utilities canvas
                        ${MF_MESSAGELOGGER}
                        ${MF_UTILITIES}
                        ${FHICLCPP}
                        cetlib cetlib_except
                        ${CLHEP}
                        ${ROOT_BASIC_LIB_LIST}
        )

# install_headers()
install_fhicl()
install_source()
