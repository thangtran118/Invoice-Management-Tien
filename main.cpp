#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "DateUtility.h"

// Invoice Class
class Invoice
{
private:
    int id;
    std::string customerName;
    std::string issueDate;
    double totalValue;

public:
    Invoice(int id, const std::string &customerName, const std::string &issueDate, double totalValue)
        : id(id), customerName(customerName), issueDate(issueDate), totalValue(totalValue) {}

    // Getters
    int getId() const { return id; }
    std::string getCustomerName() const { return customerName; }
    std::string getIssueDate() const { return issueDate; }
    double getTotalValue() const { return totalValue; }

    // Setters
    void setId(int newId) { id = newId; }
    void setCustomerName(const std::string &newName) { customerName = newName; }
    void setIssueDate(const std::string &newDate) { issueDate = newDate; }
    void setTotalValue(double newValue) { totalValue = newValue; }

    // Other methods
    void display() const
    {
        std::cout << "ID: " << id << ", Customer: " << customerName << ", Date: " << issueDate << ", Amount: " << totalValue << std::endl;
    }
};

class InvoiceManager
{
private:
    std::vector<Invoice> invoices;
    // id auto increment
    int id = 1;

public:

    Invoice enterInvoiceData()
    {
        // int id;
        std::string customerName;
        std::string issueDate;
        double totalValue;

        std::cout << "Enter customer name: ";
        std::getline(std::cin >> std::ws, customerName);
        std::cout << "Enter issue date (DD/MM/YYYY): ";
        std::cin >> issueDate;
        std::cout << "Enter total value: ";
        std::cin >> totalValue;

        return Invoice(this->id++, customerName, issueDate, totalValue);
    }

    void addInvoice(const Invoice& invoice) {
        invoices.push_back(invoice);
    }

    void addInvoiceAtStart(const Invoice &invoice)
    {
        invoices.insert(invoices.begin(), invoice);
    }

    void addInvoiceAtPosition(const Invoice &invoice, int position)
    {
        if (position < 0 || position > invoices.size())
        {
            std::cout << "Invalid position.\n";
            return;
        }
        invoices.insert(invoices.begin() + position, invoice);
    }

    void editInvoiceById(int id)
    {
        for (auto &invoice : invoices)
        {
            if (invoice.getId() == id)
            {
                std::string customerName;
                std::string issueDate;
                double totalValue;

                std::cout << "Enter customer name: ";
                std::getline(std::cin >> std::ws, customerName);
                
                std::cout << "Enter issue date (DD/MM/YYYY): ";
                std::cin >> issueDate;
                while(!DateUtility::isValidDate(issueDate)) {
                    std::cout << "Invalid date format. Enter issue date (DD/MM/YYYY): ";
                    std::cin >> issueDate;
                }

                std::cout << "Enter total value: ";
                std::cin >> totalValue;

                invoice.setCustomerName(customerName);
                invoice.setIssueDate(issueDate);
                invoice.setTotalValue(totalValue);
                return;
            }
        }
        std::cout << "Invoice with ID " << id << " not found.\n";
    }

    void changeInvoicePosition(int id, int newPosition)
    {
        if (newPosition < 0 || newPosition >= invoices.size())
        {
            std::cout << "Invalid position.\n";
            return;
        }

        for (int i = 0; i < invoices.size(); i++)
        {
            if (invoices[i].getId() == id)
            {
                Invoice invoice = invoices[i];
                invoices.erase(invoices.begin() + i);
                invoices.insert(invoices.begin() + newPosition, invoice);
                return;
            }
        }
        std::cout << "Invoice with ID " << id << " not found.\n";
    }

    void displayAll()
    {
        for (const auto &invoice : invoices)
        {
            invoice.display();
        }
    }

    // Other methods for remaining features...
};


void displayMenu()
{
    std::cout << "\n\n=================MENU================\n";
    std::cout << "0. Enter 0 to exit.\n";
    std::cout << "1. Display All Invoices\n";
    std::cout << "2. Add Invoice at End\n";
    std::cout << "3. Add Invoice at Start\n";
    std::cout << "4. Add Invoice at Specific Position\n";
    std::cout << "5. Edit Invoice by ID\n";
    std::cout << "6. Change Invoice Position in the List\n";
    std::cout << "7. Delete Invoice by ID\n";
    std::cout << "8. Delete Invoice by Customer Name\n";
    std::cout << "9. Delete Invoice at a Specific Position\n";
    std::cout << "10. Search for Invoice Position by ID\n";
    std::cout << "11. Search for Invoice by Customer Name\n";
    std::cout << "12. Search for Invoice by Issue Date Range\n";
    std::cout << "13. Sort Invoices by Total Value (Ascending)\n";
    std::cout << "14. Sort Invoices by Total Value (Descending)\n";
    std::cout << "15. Sort Invoices by Issue Date (Ascending)\n";
    std::cout << "16. Sort Invoices by Issue Date (Descending)\n";
    std::cout << "=====================================\n";
    std::cout << "Enter your choice: ";
}

int main()
{
    InvoiceManager manager;
    int choice;

    while (true)
    {
        displayMenu();
        std::cin >> choice;

        switch (choice)
        {
            case 0:
                return 0;
            case 1:
            {
                std::cout << "All invoices:\n";
                manager.displayAll();
                break;
            }
            case 2:
            {
                std::cout << "Add Invoice at End:\n";
                manager.addInvoice(manager.enterInvoiceData());
                break;
            }
            case 3:
            {
                std::cout << "Add Invoice at Start :\n";
                manager.addInvoiceAtStart(manager.enterInvoiceData());
                break;
            }
            default:
                std::cout << "Invalid choice.\n";
                break;
        }

        std::cout << "\n\nDo you want to continue? (y/n): ";
        char ch;
        std::cin >> ch;
        if (ch != 'y' && ch != 'Y')
            break;
    }

    return 0;
}
