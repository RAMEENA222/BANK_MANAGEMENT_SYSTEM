import java.util.HashMap;
import java.util.Scanner;

class Customer {
    private int accountNumber;
    private String name;
    private double balance;

    public Customer(int accountNumber, String name, double balance) {
        this.accountNumber = accountNumber;
        this.name = name;
        this.balance = balance;
    }

    public void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    public boolean withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    public int getAccountNumber() {
        return accountNumber;
    }

    public String getName() {
        return name;
    }

    public double getBalance() {
        return balance;
    }

    @Override
    public String toString() {
        return "Account Number: " + accountNumber + 
               "\nName: " + name + 
               "\nBalance: $" + String.format("%.2f", balance);
    }
}

class Bank {
    private HashMap<Integer, Customer> customers = new HashMap<>();
    private int nextAccountNumber = 1001;

    public int createAccount(String name, double initialDeposit) {
        if (initialDeposit < 0) {
            throw new IllegalArgumentException("Initial deposit cannot be negative");
        }
        int accountNumber = nextAccountNumber++;
        customers.put(accountNumber, new Customer(accountNumber, name, initialDeposit));
        return accountNumber;
    }

    public Customer getCustomer(int accountNumber) {
        return customers.get(accountNumber);
    }

    public boolean transfer(int fromAccount, int toAccount, double amount) {
        Customer source = customers.get(fromAccount);
        Customer target = customers.get(toAccount);
        
        if (source == null || target == null || amount <= 0) {
            return false;
        }
        
        if (source.withdraw(amount)) {
            target.deposit(amount);
            return true;
        }
        return false;
    }
}

public class BankManagementSystem {
    public static void main(String[] args) {
        Bank bank = new Bank();
        Scanner scanner = new Scanner(System.in);
        boolean exit = false;

        while (!exit) {
            System.out.println("\nBank Management System");
            System.out.println("1. Create New Account");
            System.out.println("2. Deposit Money");
            System.out.println("3. Withdraw Money");
            System.out.println("4. Check Balance");
            System.out.println("5. Display Account Details");
            System.out.println("6. Transfer Money");
            System.out.println("7. Exit");
            System.out.print("Enter your choice: ");

            try {
                int choice = Integer.parseInt(scanner.nextLine());

                switch (choice) {
                    case 1:
                        createAccount(bank, scanner);
                        break;
                    case 2:
                        depositMoney(bank, scanner);
                        break;
                    case 3:
                        withdrawMoney(bank, scanner);
                        break;
                    case 4:
                        checkBalance(bank, scanner);
                        break;
                    case 5:
                        displayDetails(bank, scanner);
                        break;
                    case 6:
                        transferMoney(bank, scanner);
                        break;
                    case 7:
                        exit = true;
                        System.out.println("Exiting system. Thank you!");
                        break;
                    default:
                        System.out.println("Invalid choice. Please enter 1-7.");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter a number.");
            }
        }
        scanner.close();
    }

    private static void createAccount(Bank bank, Scanner scanner) {
        System.out.print("Enter customer name: ");
        String name = scanner.nextLine().trim();
        if (name.isEmpty()) {
            System.out.println("Name cannot be empty!");
            return;
        }

        System.out.print("Enter initial deposit: $");
        try {
            double deposit = Double.parseDouble(scanner.nextLine());
            if (deposit < 0) {
                System.out.println("Initial deposit cannot be negative!");
                return;
            }
            int accNumber = bank.createAccount(name, deposit);
            System.out.println("Account created! Account Number: " + accNumber);
        } catch (NumberFormatException e) {
            System.out.println("Invalid amount format!");
        }
    }

    private static void depositMoney(Bank bank, Scanner scanner) {
        try {
            System.out.print("Enter account number: ");
            int accNumber = Integer.parseInt(scanner.nextLine());
            Customer customer = bank.getCustomer(accNumber);
            
            if (customer == null) {
                System.out.println("Account not found!");
                return;
            }

            System.out.print("Enter deposit amount: $");
            double amount = Double.parseDouble(scanner.nextLine());
            if (amount <= 0) {
                System.out.println("Amount must be positive!");
                return;
            }

            customer.deposit(amount);
            System.out.printf("Deposit successful! New balance: $%.2f%n", customer.getBalance());
        } catch (NumberFormatException e) {
            System.out.println("Invalid input format!");
        }
    }

    private static void withdrawMoney(Bank bank, Scanner scanner) {
        try {
            System.out.print("Enter account number: ");
            int accNumber = Integer.parseInt(scanner.nextLine());
            Customer customer = bank.getCustomer(accNumber);
            
            if (customer == null) {
                System.out.println("Account not found!");
                return;
            }

            System.out.print("Enter withdrawal amount: $");
            double amount = Double.parseDouble(scanner.nextLine());
            if (amount <= 0) {
                System.out.println("Amount must be positive!");
                return;
            }

            if (customer.withdraw(amount)) {
                System.out.printf("Withdrawal successful! New balance: $%.2f%n", customer.getBalance());
            } else {
                System.out.println("Withdrawal failed! Insufficient funds or invalid amount.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input format!");
        }
    }

    private static void checkBalance(Bank bank, Scanner scanner) {
        try {
            System.out.print("Enter account number: ");
            int accNumber = Integer.parseInt(scanner.nextLine());
            Customer customer = bank.getCustomer(accNumber);
            
            if (customer == null) {
                System.out.println("Account not found!");
                return;
            }

            System.out.printf("Current balance: $%.2f%n", customer.getBalance());
        } catch (NumberFormatException e) {
            System.out.println("Invalid account number!");
        }
    }

    private static void displayDetails(Bank bank, Scanner scanner) {
        try {
            System.out.print("Enter account number: ");
            int accNumber = Integer.parseInt(scanner.nextLine());
            Customer customer = bank.getCustomer(accNumber);
            
            if (customer == null) {
                System.out.println("Account not found!");
                return;
            }

            System.out.println(customer);
        } catch (NumberFormatException e) {
            System.out.println("Invalid account number!");
        }
    }

    private static void transferMoney(Bank bank, Scanner scanner) {
        try {
            System.out.print("Enter source account number: ");
            int fromAcc = Integer.parseInt(scanner.nextLine());
            System.out.print("Enter target account number: ");
            int toAcc = Integer.parseInt(scanner.nextLine());

            if (fromAcc == toAcc) {
                System.out.println("Cannot transfer to the same account!");
                return;
            }

            System.out.print("Enter transfer amount: $");
            double amount = Double.parseDouble(scanner.nextLine());
            if (amount <= 0) {
                System.out.println("Amount must be positive!");
                return;
            }

            if (bank.transfer(fromAcc, toAcc, amount)) {
                System.out.println("Transfer successful!");
            } else {
                System.out.println("Transfer failed! Check account numbers or balance.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input format!");
        }
    }
}
