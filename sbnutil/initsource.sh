# change the ifdhc version - the version written here is the same as the one when typing 'ups active'
# When running project.py it seemed to be complaining about this.. Would have assumed it was using this version by default but seemingly not so who knows what version itwas trying to use
unsetup ifdhc
setup ifdhc v2_5_7 -q e19:p372:prof

echo "Setting up SBNanalysis from initsource" 
export SBN_ANALYSIS_DIR=$MRB_INSTALL/sbncode/sbnanalysis/build
export SBN_LIB_DIR=$SBN_ANALYSIS_DIR/lib
export LD_LIBRARY_PATH=$SBN_LIB_DIR:$LD_LIBRARY_PATH
export PATH=$SBN_ANALYSIS_DIR/bin:$PATH
export FHICL_FILE_PATH=.:$MRB_INSTALL/sbncode/sbnanalysis/build/fcl:$FHICL_FILE_PATH
function run_sbn_grid_SBNOsc_NueSelection() {
    sbn-grid -m SBNOsc_NueSelection $@
}
