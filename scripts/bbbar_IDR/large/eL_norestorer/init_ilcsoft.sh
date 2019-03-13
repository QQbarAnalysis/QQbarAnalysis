export ILCSOFT=/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02

# -------------------------------------------------------------------- ---

# ---  Use the same compiler and python as used for the installation   ---

# -------------------------------------------------------------------- ---
export PATH=/cvmfs/sft.cern.ch/lcg/contrib/gcc/4.9.3/x86_64-slc6/bin:/cvmfs/sft.cern.ch/lcg/releases/LCG_87/Python/2.7.10/x86_64-slc6-gcc49-opt/bin:${PATH}
export LD_LIBRARY_PATH=/cvmfs/sft.cern.ch/lcg/contrib/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/sft.cern.ch/lcg/contrib/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/sft.cern.ch/lcg/releases/LCG_87/Python/2.7.10/x86_64-slc6-gcc49-opt/lib:${LD_LIBRARY_PATH}

export CXX=g++
export CC=gcc


#--------------------------------------------------------------------------------
#     LCCD
#--------------------------------------------------------------------------------
export LCCD="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/lccd/v01-05"


#--------------------------------------------------------------------------------
#     CondDBMySQL
#--------------------------------------------------------------------------------
export COND_DB_DEBUGLOG="/dev/stdout"
export CondDBMySQL="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/CondDBMySQL/CondDBMySQL_ILC-0-9-6"
export LD_LIBRARY_PATH="$CondDBMySQL/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     LCIO
#--------------------------------------------------------------------------------
export LCIO="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/lcio/v02-12-01"
export PYTHONPATH="$LCIO/python:$LCIO/python/examples:$PYTHONPATH"
export PATH="$LCIO/tools:$LCIO/bin:$PATH"
export LD_LIBRARY_PATH="$LCIO/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     ROOT
#--------------------------------------------------------------------------------
export ROOTSYS="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/root/6.08.06"
export PYTHONPATH="$ROOTSYS/lib:$PYTHONPATH"
export PATH="$ROOTSYS/bin:$PATH"
export LD_LIBRARY_PATH="$ROOTSYS/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CMake
#--------------------------------------------------------------------------------
export PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/CMake/3.6.3/bin:$PATH"


#--------------------------------------------------------------------------------
#     ILCUTIL
#--------------------------------------------------------------------------------
export ilcutil="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/ilcutil/v01-05"
export LD_LIBRARY_PATH="$ilcutil/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Marlin
#--------------------------------------------------------------------------------
export MARLIN="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Marlin/v01-16"
export PATH="$MARLIN/bin:$PATH"
export MARLIN_DLL="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinDD4hep/v00-06/lib/libMarlinDD4hep.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/DDMarlinPandora/v00-10/lib/libDDMarlinPandora.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinReco/v01-25/lib/libMarlinReco.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/PandoraAnalysis/v02-00-00/lib/libPandoraAnalysis.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/LCFIVertex/v00-07-04/lib/libLCFIVertexProcessors.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/CEDViewer/v01-16/lib/libCEDViewer.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Overlay/v00-21/lib/libOverlay.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinFastJet/v00-05-01/lib/libMarlinFastJet.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/LCTuple/v01-11/lib/libLCTuple.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinKinfit/v00-06/lib/libMarlinKinfit.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinTrkProcessors/v02-10/lib/libMarlinTrkProcessors.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinKinfitProcessors/v00-04/lib/libMarlinKinfitProcessors.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/ILDPerformance/v01-06/lib/libILDPerformance.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Clupatra/v01-03/lib/libClupatra.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Physsim/v00-04-01/lib/libPhyssim.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/FCalClusterer/v01-00/lib/libFCalClusterer.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/ForwardTracking/v01-13/lib/libForwardTracking.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/ConformalTracking/v01-07/lib/libConformalTracking.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/LICH/v00-01/lib/libLICH.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinTPC/v01-04/lib/libMarlinTPC.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Garlic/v03-01/lib/libGarlic.so:$MARLIN_DLL"


#--------------------------------------------------------------------------------
#     CLHEP
#--------------------------------------------------------------------------------
export CLHEP="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/CLHEP/2.3.4.3"
export CLHEP_BASE_DIR="$CLHEP"
export CLHEP_INCLUDE_DIR="$CLHEP/include"
export PATH="$CLHEP_BASE_DIR/bin:$PATH"
export LD_LIBRARY_PATH="$CLHEP_BASE_DIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     RAIDA
#--------------------------------------------------------------------------------
export RAIDA_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/RAIDA/v01-09"
export PATH="$RAIDA_HOME/bin:$PATH"


#--------------------------------------------------------------------------------
#     GEAR
#--------------------------------------------------------------------------------
export GEAR="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/gear/v01-08"
export PATH="$GEAR/tools:$GEAR/bin:$PATH"
export LD_LIBRARY_PATH="$GEAR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     DD4hep
#--------------------------------------------------------------------------------
export DD4hep_ROOT="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/DD4hep/v01-07-02"
export DD4hepINSTALL="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/DD4hep/v01-07-02"
export DD4HEP="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/DD4hep/v01-07-02"
export DD4hep_DIR="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/DD4hep/v01-07-02"
export PYTHONPATH="$DD4HEP/python:$DD4HEP/DDCore/python:$PYTHONPATH"
export PATH="$DD4HEP/bin:$PATH"
export LD_LIBRARY_PATH="$DD4HEP/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Geant4
#--------------------------------------------------------------------------------
export G4INSTALL="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/geant4/10.03.p02"
export G4ENV_INIT="$G4INSTALL/bin/geant4.sh"
export G4SYSTEM="Linux-g++"


#--------------------------------------------------------------------------------
#     QT
#--------------------------------------------------------------------------------
export QTDIR="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/QT/4.7.4"
export QMAKESPEC="$QTDIR/mkspecs/linux-g++"
export PATH="$QTDIR/bin:$PATH"
export LD_LIBRARY_PATH="$QTDIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     XercesC
#--------------------------------------------------------------------------------
export XercesC_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/xercesc/3.1.4"
export PATH="$XercesC_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$XercesC_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Boost
#--------------------------------------------------------------------------------
export BOOST_ROOT="/cvmfs/ilc.desy.de/sw/boost/1.58.0"


#--------------------------------------------------------------------------------
#     KalTest
#--------------------------------------------------------------------------------
export KALTEST="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/KalTest/v02-05"
export LD_LIBRARY_PATH="$KALTEST/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     aidaTT
#--------------------------------------------------------------------------------
export AIDATT="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/aidaTT/v00-09"
export PATH="$AIDATT/bin:$PATH"
export LD_LIBRARY_PATH="$AIDATT/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     GSL
#--------------------------------------------------------------------------------
export GSL_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/gsl/2.1"
export PATH="$GSL_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$GSL_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     GBL
#--------------------------------------------------------------------------------
export GBL="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/GBL/V02-01-01"
export LD_LIBRARY_PATH="$GBL/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     MarlinUtil
#--------------------------------------------------------------------------------
export LD_LIBRARY_PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinUtil/v01-15/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CED
#--------------------------------------------------------------------------------
export PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/CED/v01-09-02/bin:$PATH"
export LD_LIBRARY_PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/CED/v01-09-02/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     PandoraPFANew
#--------------------------------------------------------------------------------
export PANDORAPFANEW="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/PandoraPFANew/v03-09-00"
export LD_LIBRARY_PATH="$PANDORAPFANEW/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     PandoraAnalysis
#--------------------------------------------------------------------------------
export PANDORA_ANALYSIS_DIR="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/PandoraAnalysis/v02-00-00"
export PATH="$PANDORA_ANALYSIS_DIR/bin:$PATH"
export LD_LIBRARY_PATH="$PANDORA_ANALYSIS_DIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     LCFIVertex
#--------------------------------------------------------------------------------
export LD_LIBRARY_PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/LCFIVertex/v00-07-04/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CEDViewer
#--------------------------------------------------------------------------------
export PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/CEDViewer/v01-16/bin:$PATH"
export LD_LIBRARY_PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/CEDViewer/v01-16/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     FastJet
#--------------------------------------------------------------------------------
export FastJet_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/FastJet/3.2.1"
export PATH="$FastJet_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$FastJet_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     MarlinTPC
#--------------------------------------------------------------------------------
export MARLINTPC="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinTPC/v01-04"
export PATH="$MARLINTPC/bin:$PATH"


#--------------------------------------------------------------------------------
#     lcgeo
#--------------------------------------------------------------------------------
export lcgeo_DIR="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/lcgeo/v00-16-03"
export PYTHONPATH="$lcgeo_DIR/lib/python:$PYTHONPATH"
export PATH="$lcgeo_DIR/bin:$PATH"
export LD_LIBRARY_PATH="$lcgeo_DIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     DD4hepExamples
#--------------------------------------------------------------------------------
export DD4hepExamples="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/DD4hepExamples/v01-07-02"
export PATH="$DD4hepExamples/bin:$PATH"
export LD_LIBRARY_PATH="$DD4hepExamples/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     MySQL
#--------------------------------------------------------------------------------
export MYSQL_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/mysql/5.0.45"
export MYSQL_LIBDIR="$MYSQL_HOME/lib64/mysql"
export MYSQL_PATH="$MYSQL_HOME"
export MYSQL="$MYSQL_HOME"
export PATH="$MYSQL_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$MYSQL_HOME/lib64:$MYSQL_HOME/lib:$MYSQL_HOME/lib64/mysql:$MYSQL_HOME/lib/mysql:$LD_LIBRARY_PATH"

# --- source GEANT4 INIT script ---
test -r ${G4ENV_INIT} && { cd $(dirname ${G4ENV_INIT}) ; . ./$(basename ${G4ENV_INIT}) ; cd $OLDPWD ; }

# ---  Workaraund for OpenGl bug on SL6  ---
export LIBGL_ALWAYS_INDIRECT=1
