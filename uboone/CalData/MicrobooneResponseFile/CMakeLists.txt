
simple_plugin(MicrobooneResp "module"
                        lardata_Utilities_LArFFT_service
                        larcore_Geometry_Geometry_service
                        larcore_Geometry
			${ART_FRAMEWORK_SERVICES_REGISTRY}
			${ART_FRAMEWORK_SERVICES_OPTIONAL}
			${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
			art_Persistency_Common canvas
			art_Persistency_Provenance canvas
			art_Utilities canvas
			${MF_MESSAGELOGGER}
			${MF_UTILITIES}
	                ${FHICLCPP}
			cetlib cetlib_except
			${ROOT_BASIC_LIB_LIST}
              BASENAME_ONLY
)

install_headers()
install_fhicl()
install_source()

