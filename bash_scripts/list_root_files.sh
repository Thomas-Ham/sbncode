detector=icarus
stage=eventweightA
name=nu_osc

path=/pnfs/sbnd/persistent/users/tham/sbncode_nue_prod/v08_57_00/$name/$detector/$stage

echo "Looking in $path..."
echo -n "Number of files found: "; find $path/*/prod*.root -maxdepth 0 -type f | wc -l

# The file we will write all the failed jobs too
file_write=${name}_${stage}_${detector}.list
# if it already exists, lets remove it 
if test -f $file_write; then
    rm $file_write    
fi


echo "Writing list of files to $file_write..."

for file in $path/*/prod*.root # file type to look for
do
    if [ -f "$file" ]; then
        echo $file >> $file_write
        continue
    else 
    # echo "root file does not exist."
    #echo $dir >> $file_write # write all the directories that don't contain the above file to this txt file
    continue
    fi
done

