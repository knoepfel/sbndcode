art_make(
             LIB_LIBRARIES larcorealg_Geometry
                           larcore_Geometry_Geometry_service
                           larsim_Simulation lardataobj_Simulation
                           larsim_MCCheater_BackTrackerService_service
                           larsim_MCCheater_ParticleInventoryService_service
                           lardata_Utilities
                           larevt_Filters
                           lardataobj_RawData
                           lardataobj_RecoBase
                           lardata_RecoObjects  
                           larpandora_LArPandoraInterface
                           nusimdata_SimulationBase
                           cetlib cetlib_except
                           ${ART_FRAMEWORK_CORE}
                           ${ART_FRAMEWORK_PRINCIPAL}
                           ${ART_FRAMEWORK_SERVICES_REGISTRY}
                           ${ART_ROOT_IO_TFILE_SUPPORT} ${ROOT_CORE}
                           ${ART_ROOT_IO_TFILESERVICE_SERVICE}
                           art_Persistency_Common canvas
                           art_Persistency_Provenance canvas
                           art_Utilities canvas
                           ${MF_MESSAGELOGGER}
                           
                           ${FHICLCPP}
                           ${ROOT_GEOM}
                           ${ROOT_XMLIO}
                           ${ROOT_GDML}
                           ${ROOT_BASIC_LIB_LIST}
                           ${Boost_SYSTEM_LIBRARY}
        )

install_headers()
install_fhicl()
install_source()


#art_make( LIBRARY_NAME RecoUtils
#	  LIB_LIBRARIES larcorealg_Geometry
#	  	        larcore_Geometry_Geometry_service
#		        larsim_Simulation nug4_ParticleNavigation lardataobj_Simulation
# 	  	        larsim_MCCheater_BackTrackerService_service
#	  	        lardata_Utilities
#larevt_Filters
#	  	        lardataobj_RawData
#	  	        lardataobj_RecoBase
#	  	        lardata_RecoObjects
#larreco_RecoAlg
#larreco_Calorimetry
#larpandora_LArPandoraInterface
#          	        nusimdata_SimulationBase
#          	        ${LARRECO_LIB}
#          	        ${LARDATA_LIB}
#	  	        ${MF_MESSAGELOGGER}
#	  	        
#	  	        ${FHICLCPP}
#	  	        cetlib cetlib_except
#          	        ${ROOT_GEOM}
#          	        ${ROOT_XMLIO}
#          	        ${ROOT_GDML}
#	  	        ${ROOT_BASIC_LIB_LIST}
#	  MODULE_LIBRARIES RecoUtils
#          	           ${ART_FRAMEWORK_CORE}
#	  	           ${ART_FRAMEWORK_PRINCIPAL}
#		       	   ${ART_FRAMEWORK_SERVICES_REGISTRY}
#	  	       	   ${ART_ROOT_IO_TFILE_SUPPORT} ${ROOT_CORE}
#			   ${ART_ROOT_IO_TFILESERVICE_SERVICE}
#	  	           art_Persistency_Common canvas
#	  	           art_Persistency_Provenance canvas
#	  	           art_Utilities canvas
#        )
#
#install_headers()
##install_fhicl()
#install_source()
##install_scripts()
