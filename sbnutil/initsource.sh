# change the ifdhc version - the version written here is the same as the one when typing 'ups active'
# When running project.py it seemed to be complaining about this.. Would have assumed it was using this version by default but seemingly not so who knows what version itwas trying to use
unsetup ifdhc
setup ifdhc v2_5_7 -q e19:p372:prof
