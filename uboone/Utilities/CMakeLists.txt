cet_enable_asserts()

set( uboone_util_lib_list lardata_Utilities_LArFFT_service
			larcore_Geometry
			larevt_CalibrationDBI_IOVData
			larevt_CalibrationDBI_Providers
			larreco_HitFinder
			lardataobj_RecoBase
			larcore_Geometry_Geometry_service
			lardata_Utilities
			nutools_RandomUtils_NuRandomService_service
  			${ART_FRAMEWORK_CORE}
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
			${MF_MESSAGELOGGER}
			${MF_UTILITIES}
			${FHICLCPP}
			cetlib cetlib_except
			${Boost_FILESYSTEM_LIBRARY}
			${Boost_SYSTEM_LIBRARY}
                        ${CLHEP}
			${ROOT_BASIC_LIB_LIST}
    )


simple_plugin( SignalShapingServiceMicroBooNE  "service"
               ${uboone_util_lib_list}
	       BASENAME_ONLY
        )
simple_plugin( FileCatalogMetadataMicroBooNE "service"
               ${uboone_util_lib_list}
	       BASENAME_ONLY
	)
simple_plugin( TFileMetadataMicroBooNE "service"
               ${uboone_util_lib_list}
	       BASENAME_ONLY
	)	
simple_plugin( TinyHitFinderAna "module"
               ${uboone_util_lib_list}
	       BASENAME_ONLY
        )
simple_plugin( RandomPrescale "module"
               ${uboone_util_lib_list}
	       BASENAME_ONLY
	)	
simple_plugin( FileCatalogMetadataRawDigit "plugin"
               ${uboone_util_lib_list}
	       BASENAME_ONLY
	)	
             
 
install_headers()
# do not install duplicate standard_reco_uboone.fcl file
install_fhicl( EXCLUDES standard_reco_uboone.fcl )
install_source()

add_subdirectory(test)
