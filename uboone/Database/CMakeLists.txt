cet_find_library( LIBWDA NAMES wda PATHS ENV LIBWDA_LIB NO_DEFAULT_PATH )

include_directories( $ENV{LIBWDA_FQ_DIR}/include )

art_make( BASENAME_ONLY
          LIB_LIBRARIES 
			larevt_CalibrationDBI_IOVData
			larevt_CalibrationDBI_Providers
			larcore_Geometry
			${LIBWDA}
	                ${FHICLCPP}
			cetlib cetlib_except
                        ${Boost_SYSTEM_LIBRARY}
			${ART_FRAMEWORK_SERVICES_REGISTRY}
			${ROOT_BASIC_LIB_LIST}
			art_Utilities canvas
          MODULE_LIBRARIES larcore_Geometry
                        larcore_Geometry_Geometry_service
                        larsim_Simulation nutools_ParticleNavigation lardataobj_Simulation
                        lardata_Utilities
                        larevt_Filters
                        lardataobj_RawData
                        SignalShapingServiceMicroBooNE_service
			larevt_CalibrationDBI_Providers
			uboone_Database
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
                        ${ROOT_GEOM}
                        ${ROOT_XMLIO}
                        ${ROOT_GDML}
                        ${ROOT_BASIC_LIB_LIST}
	  SERVICE_LIBRARIES 
	              larevt_CalibrationDBI_Providers
		      uboone_Database
                      ${ART_FRAMEWORK_PRINCIPAL}
                      ${ART_FRAMEWORK_SERVICES_REGISTRY}
                      art_Persistency_Common canvas
                      art_Persistency_Provenance canvas
                      ${ART_FRAMEWORK_SERVICES_BASIC}
                      ${ART_FRAMEWORK_SERVICES_OPTIONAL}
                      ${ART_FRAMEWORK_SERVICES_OPTIONAL_RANDOMNUMBERGENERATOR_SERVICE}
                      ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
                      ${ART_FRAMEWORK_SERVICES_SYSTEM_FILECATALOGMETADATA_SERVICE}
                      art_Utilities canvas
	                    larevt_CalibrationDBI_IOVData
			    lardataobj_RawData
			    larcore_Geometry
			    larcore_Geometry_Geometry_service
			    ${ART_FRAMEWORK_SERVICES_REGISTRY}
			    ${ART_FRAMEWORK_CORE}
                            ${ART_FRAMEWORK_PRINCIPAL}
                            ${ART_FRAMEWORK_SERVICES_OPTIONAL}
                            ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
                            art_Persistency_Common canvas
                            art_Persistency_Provenance canvas
			    art_Utilities canvas
			    ${FHICLCPP}
			    ${ROOT_BASIC_LIB_LIST}
)

install_headers()
install_fhicl()
install_source()
