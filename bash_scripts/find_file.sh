path=/pnfs/sbnd/persistent/users/tham/sbncode_nue_prod/v08_57_00/intrinsic_nue/sbnd/gen

echo -n "Number of directories found: "; find $path/* -maxdepth 0 -type d | wc -l
echo ""

for dir in $path/*/    # list directories in the form "/tmp/dirname/"
do                     # loop over the directories
    dir=${dir%*/}      # remove the trailing "/"
    #echo ${dir##*/}    # print everything after the final "/" i.e prints directory name

  #  for file in $path/${dir##*/}/prod*.root
  #  do
  #      echo ${file##*/}
  #  done

    for file in $path/${dir##*/}/prod*.root # file type to look for
    do
        if [ -f "$file" ]; then
           # echo "$file exists."
           continue
        else 
           # echo "root file does not exist."
            echo $dir >> empty_directories.txt # write all the directories that don't contain the above file to this txt file
        fi
    done

done
