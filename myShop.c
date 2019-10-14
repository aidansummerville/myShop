//Build a Simulation of a shop in c

#include <stdio.h>
#include<string.h>



struct Product{
    char* name;
    double price;

};
struct ProductStock{
    struct Product product;
    int quantity;
};

struct Customer{
    char* name;
    double budget;
    struct ProductStock shoppingList[10];
};


struct Shop{
    double cash;
    struct ProductStock stock[20];
};

void printProduct(struct Product p){
    printf("------------------\n");
    printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
    printf("------------------\n");
}

void printCustomer(struct Customer c){
    printf("------------------\n");
    printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
    printf("------------------\n");
}

int main(void)
{
    struct Customer aidan = { "Aidan", 100.0};
    printCustomer(aidan);

    struct Product coke  = { "Can Coke", 1.10};
    printProduct(coke);
    
    struct ProductStock cokeStock = {coke, 20};
    printf("The shop has %d of the product %s\n",cokeStock.quantity, cokeStock.product.name);

    return 0;
}