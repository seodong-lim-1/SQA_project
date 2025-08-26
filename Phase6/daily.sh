#!/bin/bash

# Gets the transaction stream dir as an argument
transaction_stream_dir=$1

# Moves into dir
cd "$transaction_stream_dir"

# Remove old outputs and recreate empty
rm -r outputs/
mkdir -p outputs/

for input in inputs/*; do
	# Copies user account and available items file from the default folder
    cp ../default/UserAccountsFile.txt ../default/AvailableItemsFile.txt .

	# Cuts off 'inputs/' from variable 'input'
    input=$(echo $input | cut -c8-)
	echo "Running: $input"

    # Runs Front End with simulated transaction stream as input and redirects output to void
    ../../frontend/src/main UserAccountsFile.txt AvailableItemsFile.txt DailyTransactionFile.txt < "inputs/$input" > /dev/null

	# Removes '.txt'
	input=${input::-4}
	
	# Adds the contents of dailytransactionfile to new file in outputs folder
	cat DailyTransactionFile.txt >> outputs/"${input}_FILE.txt"
	# Clears Daily transaction file
	> DailyTransactionFile.txt
	rm ./UserAccountsFile.txt ./AvailableItemsFile.txt
done

# Concatenates the separate Daily Transaction Files into a Merged Daily Transaction file
merged_daily_transactions="MergedDailyTransactionFile.txt"
rm -f "$merged_daily_transactions" # Removes old merged file
touch "$merged_daily_transactions" # Create new merged file
# Adds all daily transaction files to the merged file
for daily_transaction_file in "outputs/"*_FILE.txt; do
    cat "$daily_transaction_file" >> "$merged_daily_transactions"
done
echo "00" >> "$merged_daily_transactions" # Adds the end of file marker

# Copies the merged file to the backend
cp "$merged_daily_transactions" ../../backend/src/

# Copies the Available Items and User Accounts files to the backend
cd ../default
cp AvailableItemsFile.txt ../../backend/src/
cp UserAccountsFile.txt ../../backend/src/

# Runs Backend with input files
cd ../../
python -m backend.src.main backend/src/UserAccountsFile.txt backend/src/AvailableItemsFile.txt backend/src/MergedDailyTransactionFile.txt

# Copies the new User Accounts and Available Items files to the default folder
cp backend/src/UserAccountsFile.txt backend/src/AvailableItemsFile.txt "$transaction_stream_dir"/../default

# Removes input files from ../../backend/src
rm backend/src/MergedDailyTransactionFile.txt backend/src/UserAccountsFile.txt backend/src/AvailableItemsFile.txt

