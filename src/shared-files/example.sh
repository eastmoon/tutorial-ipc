# Declare variable
ROOT=${PWD}
CURRENT_SHELL_DIRECTORY=$(dirname ${BASH_SOURCE})

# Goto executable file direcotry
cd ${CURRENT_SHELL_DIRECTORY}/bin

# Run executable file in bin directory.
[ -e ./producer ] && ./producer > 0-producer.log
[ -e ./consumer ] && ./consumer > 1-consumer.log

# Wait for target second
printf ">> Run executable file "
for i in {1..2}
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
