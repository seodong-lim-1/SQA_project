CXX = g++
CXXFLAGS  = -g -Wall -std=c++17

all: main.o User.o Application.o Transaction.o TransactionFile.o UserAccountsFile.o AvailableItemsFile.o
	$(CXX) $(CXXFLAGS) -o main main.o User.o Application.o Transaction.o TransactionFile.o UserAccountsFile.o AvailableItemsFile.o

main.o: main.cpp User.h Application.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

User.o: User.h Util.h

Application.o: Application.h Transaction.h

Transaction.o: Transaction.h User.h TransactionFile.h UserAccountsFile.h AvailableItemsFile.h

TransactionFile.o: TransactionFile.h

UserAccountsFile.o: UserAccountsFile.h

AvailableItemsFile.o: AvailableItemsFile.h


clean:
	$(RM) *.o *.gch main
	