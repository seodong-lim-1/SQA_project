# Checks if user wants to delete all tests run results or a specific tests run results

# If user gives "all" as argument, remove all tests run results:
if [ "$1" = "all" ]; then
    rm -rf test/Tests/*/*/Output_*
    rm -rf test/Results/*
# If user gives a tests run number, remove that tests run results:
elif [[ $1 =~ ^[0-9]{3}$ ]]; then
    rm -rf test/Tests/*/*/Output_$1
    rm -rf test/Results/TestsRunResults$1.csv
# If user gives an invalid argument, echo error message and exit:
else
    echo "Error: Invalid argument. Usage: ./cleantests.sh <tests run number:000-999 or all>"
    echo "e.g. ./cleantests.sh 001"
    exit 1
fi