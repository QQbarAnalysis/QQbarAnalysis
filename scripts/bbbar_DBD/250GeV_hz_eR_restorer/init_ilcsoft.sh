export ILCSOFT=/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06


#--------------------------------------------------------------------------------
#     LCCD
#--------------------------------------------------------------------------------
export LCCD="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/lccd/v01-03"


#--------------------------------------------------------------------------------
#     CondDBMySQL
#--------------------------------------------------------------------------------
export COND_DB_DEBUGLOG="/dev/stdout"
export CondDBMySQL="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/CondDBMySQL/CondDBMySQL_ILC-0-9-6"
export LD_LIBRARY_PATH="$CondDBMySQL/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     LCIO
#--------------------------------------------------------------------------------
export LCIO="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/lcio/v02-05"
export PATH="$LCIO/tools:$LCIO/bin:$PATH"
export LD_LIBRARY_PATH="$LCIO/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CLHEP
#--------------------------------------------------------------------------------
export CLHEP="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/CLHEP/2.1.1.0"
export CLHEP_BASE_DIR="$CLHEP"
export CLHEP_INCLUDE_DIR="$CLHEP/include"
export PATH="$CLHEP_BASE_DIR/bin:$PATH"
export LD_LIBRARY_PATH="$CLHEP_BASE_DIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     ROOT
#--------------------------------------------------------------------------------
export ROOTSYS="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/root/5.34.18"
export PATH="$ROOTSYS/bin:$PATH"
export LD_LIBRARY_PATH="$ROOTSYS/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CMake
#--------------------------------------------------------------------------------
export PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/CMake/2.8.5/bin:$PATH"


#--------------------------------------------------------------------------------
#     ILCUTIL
#--------------------------------------------------------------------------------
export ilcutil="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/ilcutil/v01-02"
export LD_LIBRARY_PATH="$ilcutil/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Marlin
#--------------------------------------------------------------------------------
export MARLIN="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/Marlin/v01-05"
export PATH="$MARLIN/bin:$PATH"
export MARLIN_DLL="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/MarlinReco/v01-10/lib/libMarlinReco.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/PandoraAnalysis/v00-06/lib/libPandoraAnalysis.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/MarlinPandora/v00-14/lib/libMarlinPandora.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/LCFIVertex/v00-06-02/lib/libLCFIVertex.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/CEDViewer/v01-07-02/lib/libCEDViewer.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/Overlay/v00-14/lib/libOverlay.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/FastJetClustering/v00-02/lib/libFastJetClustering.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/LCTuple/v01-03-01/lib/libLCTuple.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/MarlinKinfit/v00-01-02/lib/libMarlinKinfit.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/MarlinTrkProcessors/v01-11/lib/libMarlinTrkProcessors.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/Clupatra/v00-10/lib/libClupatra.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/Physsim/v00-01/lib/libPhyssim.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/LCFIPlus/v00-05-02/lib/libLCFIPlus.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/ForwardTracking/v01-07/lib/libForwardTracking.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/MarlinTPC/v00-17/lib/libMarlinTPC.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/Garlic/v2.10.1/lib/libGarlic.so:$MARLIN_DLL"


#--------------------------------------------------------------------------------
#     RAIDA
#--------------------------------------------------------------------------------
export RAIDA_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/RAIDA/v01-06-02"
export PATH="$RAIDA_HOME/bin:$PATH"


#--------------------------------------------------------------------------------
#     GEAR
#--------------------------------------------------------------------------------
export GEAR="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/gear/v01-04-01"
export PATH="$GEAR/tools:$GEAR/bin:$PATH"
export LD_LIBRARY_PATH="$GEAR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     GSL
#--------------------------------------------------------------------------------
export GSL_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/gsl/1.14"
export PATH="$GSL_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$GSL_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CED
#--------------------------------------------------------------------------------
export PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/CED/v01-09-01/bin:$PATH"


#--------------------------------------------------------------------------------
#     Mokka
#--------------------------------------------------------------------------------
export MOKKA="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/Mokka/mokka-08-04"
export PATH="$MOKKA/bin:$PATH"


#--------------------------------------------------------------------------------
#     Geant4
#--------------------------------------------------------------------------------
export G4INSTALL="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/geant4/9.5.p02"
export G4ENV_INIT="$G4INSTALL/bin/geant4.sh"
export G4SYSTEM="Linux-g++"


#--------------------------------------------------------------------------------
#     QT
#--------------------------------------------------------------------------------
export QTDIR="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/QT/4.7.4"
export QMAKESPEC="$QTDIR/mkspecs/linux-g++"
export PATH="$QTDIR/bin:$PATH"
export LD_LIBRARY_PATH="$QTDIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     MySQL
#--------------------------------------------------------------------------------
export MYSQL_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/mysql/5.0.45"
export MYSQL_LIBDIR="$MYSQL_HOME/lib64/mysql"
export MYSQL_PATH="$MYSQL_HOME"
export MYSQL="$MYSQL_HOME"
export PATH="$MYSQL_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$MYSQL_HOME/lib64/mysql:$MYSQL_HOME/lib64:$MYSQL_HOME/lib/mysql:$MYSQL_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CERNLIB
#--------------------------------------------------------------------------------
export CERN_ROOT="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/cernlib/2006"
export CERN="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/cernlib"
export CERN_LEVEL="2006"
export CVSCOSRC="$CERN_ROOT/src"
export PATH="$CERN_ROOT/bin:$PATH"


#--------------------------------------------------------------------------------
#     PandoraPFANew
#--------------------------------------------------------------------------------
export PANDORAPFANEW="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/PandoraPFANew/v00-16"
export LD_LIBRARY_PATH="$PANDORAPFANEW/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CEDViewer
#--------------------------------------------------------------------------------
export PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/CEDViewer/v01-07-02/bin:$PATH"


#--------------------------------------------------------------------------------
#     FastJet
#--------------------------------------------------------------------------------
export FastJet_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/FastJet/2.4.2"
export PATH="$FastJet_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$FastJet_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     KalTest
#--------------------------------------------------------------------------------
export KALTEST="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/KalTest/v01-05-04"
export LD_LIBRARY_PATH="$KALTEST/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     MarlinTPC
#--------------------------------------------------------------------------------
export MARLINTPC="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/MarlinTPC/v00-17"
export PATH="$MARLINTPC/bin:$PATH"


#--------------------------------------------------------------------------------
#     GBL
#--------------------------------------------------------------------------------
export GBL="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/GBL/V01-16-04"
export LD_LIBRARY_PATH="$GBL/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Druid
#--------------------------------------------------------------------------------
export DRUID="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/Druid/2.2"
export PATH="$DRUID/bin:$PATH"


#--------------------------------------------------------------------------------
#     XercesC
#--------------------------------------------------------------------------------
export XercesC_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/xercesc/3.1.1"
export PATH="$XercesC_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$XercesC_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     HepPDT
#--------------------------------------------------------------------------------
export HepPDT_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/heppdt/3.04.01"
export PATH="$HepPDT_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$HepPDT_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     GDML
#--------------------------------------------------------------------------------
export GDML="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/gdml/v03-01-01"
export LD_LIBRARY_PATH="$GDML/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     LCDD
#--------------------------------------------------------------------------------
export LCDD="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/lcdd/v04-00-00"
export GDML_SCHEMA_DIR="$LCDD"
export LD_LIBRARY_PATH="$LCDD/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     SLIC
#--------------------------------------------------------------------------------
export SLIC="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/slic/v04-00-00"
export PATH="$SLIC/build/bin:$PATH"
export LD_LIBRARY_PATH="$SLIC/build/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     SlicPandora
#--------------------------------------------------------------------------------
export SLICPANDORA="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/slicPandora/v01-01-01"
export PATH="$SLICPANDORA/build/bin:$PATH"
export LD_LIBRARY_PATH="$SLICPANDORA/build/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     DD4hep
#--------------------------------------------------------------------------------
export DD4HEP="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/DD4hep/v00-10"
export PATH="$DD4HEP/bin:$PATH"
export LD_LIBRARY_PATH="$DD4HEP/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     DDSim
#--------------------------------------------------------------------------------
export DDSIM="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/DDSim/v00-02"
export PATH="$DDSIM/bin:$PATH"
export LD_LIBRARY_PATH="$DDSIM/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Java
#--------------------------------------------------------------------------------
export JAVA_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/java/1.6.0"
export JDK_HOME="$JAVA_HOME"
export PATH="$JDK_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$JDK_HOME/jre/lib/i386:$JDK_HOME/jre/lib/i386/client:$LD_LIBRARY_PATH"

# --- source GEANT4 INIT script ---
test -r ${G4ENV_INIT} && { cd $(dirname ${G4ENV_INIT}) ; . ./$(basename ${G4ENV_INIT}) ; cd $OLDPWD ; }

# ---  Workaraund for OpenGl bug on SL6  ---
export LIBGL_ALWAYS_INDIRECT=1
