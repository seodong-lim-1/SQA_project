#include "../include/Transactions/transaction.h"

Transaction::Transaction(Frontend& frontend, const std::string& transactionCode) : m_frontend(frontend), m_transactionCode(transactionCode) {}

Frontend& Transaction::getFrontend() const {
    return m_frontend;
}

std::string Transaction::getTransactionCode() const {
    return m_transactionCode;
}