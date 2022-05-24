# Declare variable
ROOT=${PWD}
CURRENT_SHELL_DIRECTORY=$(dirname ${BASH_SOURCE})

# Goto executable file direcotry
cd ${CURRENT_SHELL_DIRECTORY}/bin

# Run executable file in bin directory.
[ -e ./case1 ] && ./case1 > 1-case.log &
[ -e ./case2 ] && ./case2 > 2-case.log &
ps aux

# Wait for target second
printf ">> Run executable file "
for i in {1..10}
do
    printf "."
    sleep 1s
done
printf "\n>> Output execute log\n"

# Output result
for file in $(ls *.log)
do
    echo ""
    echo "Output ${file} :"
    cat ${file}
done

# Goto root
cd ${ROOT}
