# Declare variable
ROOT=${PWD}
CURRENT_SHELL_DIRECTORY=$(dirname ${BASH_SOURCE})

# Goto executable file direcotry
cd ${CURRENT_SHELL_DIRECTORY}/bin

# Run executable file in bin directory.
# How to Run Linux Commands in the Background, https://www.makeuseof.com/run-linux-commands-in-background/
[ -e ./producer ] && ./producer > 0-producer.log &
[ -e ./consumer ] && ./consumer > 1-consumer.log &

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
