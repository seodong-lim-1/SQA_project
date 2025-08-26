#!/bin/bash

simulation_dir="simulation_streams/"

# Copies tests default files to the simulation directory
cp -r frontend/tests/frontend/default/ simulation_streams/

for i in {1..5}; do
    echo "Running Day $i"

    # Gets the transaction stream directory for the current day  
    transaction_stream_dir="${simulation_dir}day_${i}/"

    bash daily.sh "$transaction_stream_dir"

    # Delete day dir DailyTansactionFile.txt for cleanup:
    rm -r "${transaction_stream_dir}DailyTransactionFile.txt"
done