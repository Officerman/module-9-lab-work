#include <iostream>
#include <string>
#include <memory>


// Интерфейс напитка
class Beverage {
public:
    virtual double GetCost() const = 0;
    virtual std::string GetDescription() const = 0;
    virtual ~Beverage() = default;
};

// Класс базового Кофе
class Coffee : public Beverage {
public:
    double GetCost() const override { return 50.0; }
    std::string GetDescription() const override { return "Coffee"; }
};

// Декоратор
class BeverageDecorator : public Beverage {
protected:
    std::shared_ptr<Beverage> baseBeverage;
public:
    BeverageDecorator(std::shared_ptr<Beverage> b) : baseBeverage(b) {}
    virtual double GetCost() const override { return baseBeverage->GetCost(); }
    virtual std::string GetDescription() const override { return baseBeverage->GetDescription(); }
};

// Декоратор для молока
class Milk : public BeverageDecorator {
public:
    Milk(std::shared_ptr<Beverage> b) : BeverageDecorator(b) {}
    double GetCost() const override { return baseBeverage->GetCost() + 10.0; }
    std::string GetDescription() const override { return baseBeverage->GetDescription() + ", Milk"; }
};

// Декоратор для сахара
class Sugar : public BeverageDecorator {
public:
    Sugar(std::shared_ptr<Beverage> b) : BeverageDecorator(b) {}
    double GetCost() const override { return baseBeverage->GetCost() + 5.0; }
    std::string GetDescription() const override { return baseBeverage->GetDescription() + ", Sugar"; }
};

// Декоратор для шоколада
class Chocolate : public BeverageDecorator {
public:
    Chocolate(std::shared_ptr<Beverage> b) : BeverageDecorator(b) {}
    double GetCost() const override { return baseBeverage->GetCost() + 15.0; }
    std::string GetDescription() const override { return baseBeverage->GetDescription() + ", Chocolate"; }
};

// Тестирование декораторов
void TestBeverages() {
    std::shared_ptr<Beverage> drink = std::make_shared<Coffee>();
    std::cout << drink->GetDescription() << " : " << drink->GetCost() << "\n";
    
    drink = std::make_shared<Milk>(drink);
    std::cout << drink->GetDescription() << " : " << drink->GetCost() << "\n";
    
    drink = std::make_shared<Sugar>(drink);
    std::cout << drink->GetDescription() << " : " << drink->GetCost() << "\n";
    
    drink = std::make_shared<Chocolate>(drink);
    std::cout << drink->GetDescription() << " : " << drink->GetCost() << "\n";
}


// Интерфейс платежной системы
class PaymentProcessor {
public:
    virtual void ProcessPayment(double amount) = 0;
    virtual void RefundPayment(double amount) = 0;
    virtual ~PaymentProcessor() = default;
};

// Внутренняя платежная система
class InternalProcessor : public PaymentProcessor {
public:
    void ProcessPayment(double amount) override {
        std::cout << "Processing payment of " << amount << " via internal system.\n";
    }
    void RefundPayment(double amount) override {
        std::cout << "Refunding payment of " << amount << " via internal system.\n";
    }
};

// Внешняя платежная система A
class ExternalSystemA {
public:
    void MakePayment(double amount) {
        std::cout << "Making payment of " << amount << " via External System A.\n";
    }
    void MakeRefund(double amount) {
        std::cout << "Making refund of " << amount << " via External System A.\n";
    }
};

// Адаптер для ExternalSystemA
class PaymentAdapterA : public PaymentProcessor {
private:
    ExternalSystemA systemA;
public:
    void ProcessPayment(double amount) override {
        systemA.MakePayment(amount);
    }
    void RefundPayment(double amount) override {
        systemA.MakeRefund(amount);
    }
};

// Внешняя платежная система B
class ExternalSystemB {
public:
    void SendPayment(double amount) {
        std::cout << "Sending payment of " << amount << " via External System B.\n";
    }
    void ProcessRefund(double amount) {
        std::cout << "Processing refund of " << amount << " via External System B.\n";
    }
};

// Адаптер для ExternalSystemB
class PaymentAdapterB : public PaymentProcessor {
private:
    ExternalSystemB systemB;
public:
    void ProcessPayment(double amount) override {
        systemB.SendPayment(amount);
    }
    void RefundPayment(double amount) override {
        systemB.ProcessRefund(amount);
    }
};

// Функция для тестирования адаптеров
void TestPayments() {
    std::unique_ptr<PaymentProcessor> internalProc = std::make_unique<InternalProcessor>();
    internalProc->ProcessPayment(100.0);
    internalProc->RefundPayment(50.0);

    std::unique_ptr<PaymentProcessor> adapterA = std::make_unique<PaymentAdapterA>();
    adapterA->ProcessPayment(200.0);
    adapterA->RefundPayment(100.0);

    std::unique_ptr<PaymentProcessor> adapterB = std::make_unique<PaymentAdapterB>();
    adapterB->ProcessPayment(300.0);
    adapterB->RefundPayment(150.0);
}

// =============== Основная функция ====================

int main() {
    std::cout << "=== Тестирование системы оформления заказа ===\n";
    TestBeverages();
    
    std::cout << "\n=== Тестирование системы управления оплатой ===\n";
    TestPayments();

    return 0;
}
