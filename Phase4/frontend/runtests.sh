# Gets tests run number
tests_run_num=$1

# If no tests run number is given, echoes error message and exit
if [ -z "$tests_run_num" ]; then
    echo "Error: No tests run number given. Usage: ./runtests.sh <tests run number:000-999>"
    echo "e.g. ./runtests.sh 001"
    exit 1
fi

# If the tests run number is not from 000-999, echoes error message and exit
if ! [[ $tests_run_num =~ ^[0-9]{3}$ ]]; then
    echo "Error: Tests run number must be from 000-999. Usage: ./runtests.sh <tests run number>"
    echo "e.g. ./runtests.sh 001"
    exit 1
fi

# If the tests run number is already used, echoes error message and exit
if [ -f "test/Results/TestsRunResults$tests_run_num.csv" ]; then
    echo "Error: Tests run number already used."
    exit 1
fi

# Creates the results folder if it doesn't exist
mkdir -p "test/Results"
# Initializes column names for the results csv file
echo "Test Case,Result,Reason,Fix" >> "test/Results/TestsRunResults$tests_run_num.csv"

# Runs the tests
test_dir="test/Tests"
for transaction in $test_dir/*; do
    for testcase in $transaction/*; do
        # echo "Running $testcase..."    
        mkdir -p "$testcase/Output_$tests_run_num/"   

        # Runs the auction system with the test case inputs and outputs to the test case output folder
        ./bin/auction-system test/Current_User_Accounts.txt test/Available_Items.txt $testcase/Output_$tests_run_num/Daily_Transaction.txt \
            < $testcase/Input_Stream.txt > $testcase/Output_$tests_run_num/Terminal_Output.txt

        # Makes Daily_Transaction.txt if it doesn't exist
        if [ ! -f $testcase/Output_$tests_run_num/Daily_Transaction.txt ]; then
            touch $testcase/Output_$tests_run_num/Daily_Transaction.txt
        fi
        
        #echo "Checking $testcase outputs..."
        # Compares the output of the test case with the expected output
        {
            diff -u $testcase/Expected_Terminal_Output.txt $testcase/Output_$tests_run_num/Terminal_Output.txt
            diff -u $testcase/Expected_Daily_Transaction_File.txt $testcase/Output_$tests_run_num/Daily_Transaction.txt
        } > $testcase/Output_$tests_run_num/Results.txt

        # Checks if results are empty, meaning the test case succeeded
        if [ ! -s $testcase/Output_$tests_run_num/Results.txt ]; then
            echo "${testcase#test/Tests/},Succeeded" >> "test/Results/TestsRunResults$tests_run_num.csv"
        else
            echo "${testcase#test/Tests/},Failed" >> "test/Results/TestsRunResults$tests_run_num.csv"
        fi
    done
done    

# Prints the results
cat "test/Results/TestsRunResults$tests_run_num.csv"