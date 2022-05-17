# Run executable file in bin directory.
CURRENT_SHELL_DIRECTORY=$(dirname ${BASH_SOURCE})
${CURRENT_SHELL_DIRECTORY}/bin/example > ${CURRENT_SHELL_DIRECTORY}/bin/example.log

# Wait for 1s
sleep 1s

# Output result
cat ${CURRENT_SHELL_DIRECTORY}/bin/example.log
