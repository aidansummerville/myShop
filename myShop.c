//Build a Simulation of a shop in c

#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <stdbool.h>


struct Product{
    char* name;
    double price;

};
struct ProductStock{
    struct Product product;
    int quantity;
};

struct Customer{
    char* uname;
    double custCash;
    struct ProductStock shoppingList[10];
    int index;
};


struct Shop{
    double cash;
    struct ProductStock stock[20];
    int index;
   

};



void printProduct(struct Product p){

    printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
    printf("------------------\n");
}

void printProduct2(struct Product p){

    printf("PRODUCT NAME: %s \n", p.name);
    

    
    printf("------------------\n");
}
// void printCustomer(struct Customer c){

//     printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
//     printf("------------------\n");
//     for(int i = 0; i < c.index; i++)
//     {
//         printProduct(c.shoppingList[i].product);
//         printf("%s Orders %d of Above Product\n", c.name,c.shoppingList[i].quantity);
//         double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price;
//         printf("The cost to %s will be €%.2f\n", c.name, cost);
//     }
// }

struct Shop createAndStockShop()
{
   
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);


    getline(&line, &len, fp);
    double cashInShop = atof(line);
    struct Shop shop ={cashInShop};

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s is a line" , line);
        char *n = strtok(line, ",");
        char *p = strtok(NULL, ",");
        char *q = strtok(NULL, ",");
        int quantity = atoi(q);
        double price = atof(p);
        char *name = malloc(sizeof(char) * 100);
        strcpy(name, n);
        struct Product product ={ name, price};
        struct ProductStock stockItem = { product, quantity};
        shop.stock[shop.index++] = stockItem;
        // printf("NAME OF PRODUCT %s PRICE %.2f Quantity %d\n", name, price, quantity);
    }
    // printProduct(shop.stock[0].product);
    return shop;
}

struct Customer fillShoppingList()
{
   
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("shoplist.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    

    
    getline(&line, &len, fp);
    // // printf("%s is a line" , line);
    char *b = strtok(line, ",");
    char *u = strtok(NULL, ",");
    double custCash = atof(b);
    char *uname = malloc(sizeof(char) * 50);
    strcpy(uname, u);
    // printf("%s\n",uname);
    // printf("%.2f\n",custCash);
    // char *user = malloc(sizeof(char) * 50);
    struct Customer user = {uname, custCash};
    // return custCash;

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s is a line" , line);
        char *n = strtok(line, ",");
        char *q = strtok(NULL, ",");
        int quantity = atoi(q);

        char *name = malloc(sizeof(char) * 100);
        strcpy(name, n);
        struct Product product ={ name};
        struct ProductStock listItem = { product, quantity};
        user.shoppingList[user.index++] = listItem;
        // struct Customer customer  ={ uname, custCash};

        // printf("NAME OF PRODUCT %s PRICE %.2f ", uname, custCash);
    }
//    struct Customer customer  ={ uname, custCash};
//    printf("NAME OF PRODUCT %s PRICE %.2f ", uname, custCash);
    return user;
    
}

void printShop(struct Shop s)
{
    printf("Shop has %.2f in cash\n", s.cash);
    for (int i = 0; i < s.index; i++)
    {
        struct Product product = s.stock[i].product;
        printProduct(product);
        printf("The Shop has %d of the above\n", s.stock[i].quantity);
    }
}

double findProductPrice(struct Shop *s, char *n)
{
    for (int i = 0; i < s->index; i++)
    {
         struct Product product = s->stock[i].product;
         char *name =  product.name;
        //   printf("%s \n", name);
         if(strcmp(name,n) == 0 )
         {
             return product.price;
         }
    }
    return -1;
}



void printShopList(struct Customer *c ,struct Shop *s)
{

    printf("CUSTOMER NAME: %sCUSTOMER BUDGET: %.2f\n", c->uname, c->custCash);
    printf("------------------\n");
    float a =0.00;
    
    int update[10];
    for(int i = 0; i < c->index; i++)
    {
      for(int j = 0; j < s->index; j++)
      {

            if(strcmp(c->shoppingList[i].product.name,s->stock[j].product.name)==0)
            {
                if(c->shoppingList[i].quantity - s->stock[j].quantity <= 0 )
                {
                // printProduct2(c->shoppingList[i].product);
                printf("PRODUCT NAME: %s\n", c->shoppingList[i].product.name);
                // char *n = c.shoppingList[i].product.name;
                double price = findProductPrice(s, c->shoppingList[i].product.name);
                
                printf("%s Orders %d of Above Product\n", c->uname,c->shoppingList[i].quantity);
                printf("PRODUCT PRICE: €%.2f\n", price);
                double cost = c->shoppingList[i].quantity * price;
                printf("The cost to %s will be €%.2f\n", c->uname, cost);
                printf("------------------\n");
                a= a+cost;
                update[i]= c->shoppingList[i].quantity;
                }
                else
                {
                    update[i] = 0;
                     printf("You have ordered %d of %s, only %d of this product left in stock please remove items from your shoppinglist\n",c->shoppingList[i].quantity,c->shoppingList[i].product.name,s->stock[j].quantity);
                }
            }
    }
    }
    printf("Total: €%.2f\n", a);
    printf("------------------\n");

    // int k;
    // for(k = 0; k < 10; k++)
    //   printf("%d ", update[k]);
    // printf("Update: %ls\n", update);
    float newCash;
    double change = c->custCash - a;
    if(change >= 0)
    {
        newCash = s->cash + a;
        printf("Change: €%.2f\n", change);
        printf("Shopcash: €%.2f\n", newCash);
            
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

        fp = fopen("stock.csv", "r+");
        if (fp == NULL)
            exit(EXIT_FAILURE);

        fprintf(fp, "%.2f", newCash);
        fclose(fp);

       
    
        
    }
    else
    {

        printf("Insuficent funds €%.2f over budget please remove items from the basket", change);
    }
}





int main(void)
{
    // struct Customer aidan = { "Aidan", 100.0};
    

    // struct Product coke  = { "Can Coke", 1.10};
    // struct Product bread  = { "Bread", .70};
    // // printProduct(coke);
    
    // struct ProductStock cokeStock = {coke, 20};
    // struct ProductStock breadStock = {bread, 2};

    // aidan.shoppingList[aidan.index++] = cokeStock;
    // aidan.shoppingList[aidan.index++] = breadStock;

    // printCustomer(aidan);

    struct Shop shop = createAndStockShop();

    // printShop(shop);
    struct Customer user =fillShoppingList();
    printShopList(&user, &shop);
    // double price = findProductPrice(shop, ptr_Shop->stock[2].product.name);
    // // printf("%.2f\n", price);
    // printf("%s \n", customer.user.shoppingList[2].product.name);
    
    
    // printf("%s", nm);
    // printf("The shop has %d of the product %s\n",cokeStock.quantity, cokeStock.product.name);

    return 0;
}