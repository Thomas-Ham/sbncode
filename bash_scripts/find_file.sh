detector=sbnd
name=nu_osc
stage=gen
stage2=g4

path=/pnfs/sbnd/persistent/users/tham/sbncode_nue_prod/v08_57_00/$name/$detector/$stage2

echo "Looking in $path..."
echo -n "Number of directories found: "; find $path/* -maxdepth 0 -type d | wc -l
echo ""
echo -n "Number of files found: "; find $path/*/prod*.root -maxdepth 0 -type f | wc -l

# The file we will write all the failed jobs too
#file_write=failed_directories_nue_int_sbnd_g4.txt
file_write=failed_${name}_${stage}_${detector}.list
# if it already exists, lets remove it 
if test -f $file_write; then
    rm $file_write    
fi


find_empty_directories() {
    echo "Looking for jod directories that don't contain a file and writing these to $file_write..."
    for dir in $path/*/    # list directories in the form "/tmp/dirname/"
    do                     # loop over the directories
        dir=${dir%*/}      # remove the trailing "/"
        #echo ${dir##*/}    # print everything after the final "/" i.e prints directory name

        for file in $path/${dir##*/}/prod*.root # file type to look for
        do
            if [ -f "$file" ]; then
                # echo "$file exists."
                continue
            else 
                #echo "root file does not exist."
                #echo ${dir##*_}
                #echo $dir >> $file_write # write all the directories that don't contain the above file to this txt file
                NUM=$((${dir##*_} + 1)) # Get the last bit of the directory name (the bit after the '_') and add 1 to it
                sed "${NUM}q;d" /sbnd/app/users/tham/sbncode_nue_prod/srcs/sbncode/data/lists/${name}_${stage}_${detector}.list >> $file_write  
                continue
            fi
        done
    done
}

find_missing_directories() {
    echo "Looking for directories which were not created and writing the corresponding missing files to $file_write..."
    for i in {0..9999} # Loop over the directories (directory numbering starts at 0)
    do
        dir=($path/*_$i/)
        #echo ${dir[@]}
        # Find the directories which are missing 
        if [ ! -d ${dir[@]} ]; then 
           # echo ${dir[@]}
           # echo ${dir[@]} >> $file_write
           
           # For each missing directory, find the corresponding input file from the the list of input files
           # Need to +1 to the directory number when getting the file cos list of input files starts at 1 and not 0.
           NUM=$(($i + 1))
           sed "${NUM}q;d" /sbnd/app/users/tham/sbncode_nue_prod/srcs/sbncode/data/lists/${name}_${stage}_${detector}.list >> $file_write
        fi
    done
}



# functions to run
#find_empty_directories
#find_missing_directories









